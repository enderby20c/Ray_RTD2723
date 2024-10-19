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
// ID Code      : RTD2020UserInterfaceDisplay.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_INTERFACE_DISPLAY__

#include "RTD2020UserInclude.h"
#include "RTD2020UserInterfaceDisplay.h"

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_DP_FREESYNC_SUPPORT == _ON)
StructDrrTimingInfo code tDrrFreeSyncDpTimingInfo[] =
{
    // Hwidth, Vheight, Htotal, Pixel clk (0.1M), Vfreq (0.1Hz)
    {1920, 1080, 2200, 1485, 600},
    {2560, 1440, 2720, 2415, 600},
};
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
StructDrrTimingInfo code tDrrFreeSyncHdmiTimingInfo[] =
{
    // Hwidth, Vheight, Htotal, Pixel clk (0.1M), Vfreq (0.1Hz)
    {1920, 1080, 2200, 1485, 600},
    {2560, 1440, 2720, 2415, 600},

    // Established Timing Info
    {720,  400,  888,  283,  702},// 720 x 400 at 70Hz - IBM VGA
    {720,  400,  907,  355,  882},// 720 x 400 at 88Hz - IBM XGA2
    {640,  480,  800,  251,  600},// 640 x 480 at 60Hz - IBM VGA
    {640,  480,  864,  302,  667},// 640 x 480 at 67Hz - Mac II
    {640,  480,  832,  315,  728},// 640 x 480 at 72Hz - VESA
    {640,  480,  840,  315,  750},// 640 x 480 at 75Hz - VESA
    {800,  600,  1024, 360,  562},// 800 x 600 at 56Hz - VESA
    {800,  600,  1056, 400,  603},// 800 x 600 at 60Hz - VESA
    {800,  600,  1040, 500,  722},// 800 x 600 at 72Hz - VESA
    {800,  600,  1056, 495,  750},// 800 x 600 at 75Hz - VESA
    {832,  624,  1152, 572,  745},// 832 x 624 at 75Hz - Mac II
    {1024, 768,  1264, 898,  870},// 1024 x 768 at 43Hz - IBM 8514a
    {1024, 768,  1344, 650,  600},// 1024 x 768 at 60Hz - VESA
    {1024, 768,  1328, 750,  700},// 1024 x 768 at 70Hz - VESA
    {1024, 768,  1312, 787,  750},// 1024 x 768 at 75Hz - VESA
    {1280, 1024, 1688, 1350, 750},// 1280 x 1024 at 75Hz - VESA
    {1152, 870,  1456, 1000, 750},// 1152 x 870 at 75Hz - Mac II
};
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
StructDrrTimingInfo code tDrrVrrHdmiTimingInfo[] =
{
    // Hwidth, Vheight, Htotal, Pixel clk (0.1M), Vfreq (0.1Hz)
    {1920, 1080, 2200, 1485, 600},
    {2560, 1440, 2720, 2415, 600},
};
#endif

StructDtScanForceFrameBuffer code tForceFrameBufferTiming[] =
{
    // ivh, dvh
    {1440, 1080},
    {1600, 1080},
    {1600, 1440},
    {2160, 1440},
    {2160, 2160},
    {2880, 2160},
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : User OSD Get LogoOn
// Input Value  : None
// Output Value : User OSD Logo Status
//--------------------------------------------------
EnumOsdLogoStatus UserInterfaceDisplayGetLogoStatus(void)
{
    if(GET_OSD_LOGO_ON() == _TRUE)
    {
        return _OSD_LOGO_ON;
    }
    else
    {
        return _OSD_LOGO_OFF;
    }
}

//--------------------------------------------------
// Description  : Get User OSD No Support Status
// Input Value  : None
// Output Value : No Support Status
//--------------------------------------------------
EnumNoSupportStatus UserInterfaceDisplayGetNoSupportStatus(void)
{
    if(GET_OSD_DISPLAY_MODE() == _OSD_DM_1P)
    {
        if(SysRegionGetDisplayState(_DISPLAY_RGN_1P) == _DISPLAY_STATE_OOR)
        {
            return _NO_SUPPORT_TRUE;
        }
    }
    else
    {
        if(SysRegionGetDisplayStateCount(_DISPLAY_STATE_OOR) != 0x00)
        {
            return _NO_SUPPORT_TRUE;
        }
    }

    return _NO_SUPPORT_FALSE;
}

//--------------------------------------------------
// Description  : Check Whether to support this timing of specific region
// Input Value  : None
// Output Value : _NO_SUPPORT_TRUE => Go to No Support State
//--------------------------------------------------
EnumNoSupportStatus UserInterfaceDisplayGetRegionNoSupportStatus(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
    // Add User No Support Check
    return _NO_SUPPORT_FALSE;
}

//--------------------------------------------------
// Description  : For User to Check Whether to Support Current DCLK
// Input Value  : None
// Output Value : _DCLK_NO_SUPPORT_TRUE => No Support
//--------------------------------------------------
EnumDclkNoSupportStatus UserInterfaceDisplayGetDclkNoSupportStatus(void)
{
    if((GET_D_CLK_FREQ() > ((DWORD)_PANEL_PIXEL_CLOCK_MAX_KHZ)) ||
       (GET_D_CLK_FREQ() < ((DWORD)_PANEL_PIXEL_CLOCK_MIN_KHZ)))
    {
        DebugMessageScaler("D Clock Exceed Panel Supported Range", GET_D_CLK_FREQ());
        return _DCLK_NO_SUPPORT_TRUE;
    }

    return _DCLK_NO_SUPPORT_FALSE;
}

#if(_OVERSCAN_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Overscan
// Input Value  : Current Input Timing
// Output Value : Modified Input Timing
//--------------------------------------------------
EnumOverScanStatus UserInterfaceDisplayGetOverScanStatus(EnumDisplayRegion enumDisplayRegion)
{
    EnumOverScanStatus enumDoOverScan = _OVERSCAN_FALSE;
    BYTE ucTemp = 0;
    WORD code tusOverscanEnTable[][3] =
    {
        // VFreq, HWidth, VHeight,
        {600,  640,  480},    // 480p
        {600,  720,  480},    // 480p
        {600,  960,  480},    // 480p
        {600, 1440,  480},    // 480p

        {500,  720,  576},    // 576p
        {500,  768,  576},    // 576p
        {500,  960,  576},    // 576p
        {500, 1280,  576},    // 576p
        {500, 1440,  576},    // 576p
        {500, 1280,  720},    // 720p
        {600, 1280,  720},    // 720p
        {500, 1920,  1080},   // 1080p
        {600, 1920,  1080},   // 1080p

        // Don't delete it, and place it at last.
        {  0,    0,    0},
    };
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumDisplayRegion, &stTimingInfo);

    if(GET_OSD_OVERSCAN_STATUS(SysRegionGetInputPort(enumDisplayRegion)) == _OFF)
    {
        return _OVERSCAN_FALSE;
    }

    // Decide whether to do over scan
    switch(SysRegionGetSourceType(enumDisplayRegion))
    {
#if(_OVERSCAN_VGA_SUPPORT == _ON)
        case _SOURCE_VGA:

            // Interlaced and YUV Timing Always do overscan
            if(stTimingInfo.b1Interlace == _TRUE)
            {
                enumDoOverScan = _OVERSCAN_TRUE;
                break;
            }

            if(GET_VGA_COLOR_FORMAT_STATUS() == _COLOR_SPACE_RGB)
            {
                break;
            }

            while(tusOverscanEnTable[ucTemp][0] != 0)
            {
                if((abs(stTimingInfo.usVFreq - tusOverscanEnTable[ucTemp][0]) < 10) &&
                   (abs(stTimingInfo.usHWidth - tusOverscanEnTable[ucTemp][1]) < 2) &&
                   (stTimingInfo.usVHeight == tusOverscanEnTable[ucTemp][2]))
                {
                    enumDoOverScan = _OVERSCAN_TRUE;
                    break;
                }

                ucTemp++;
            }

            break;
#endif // End of #if(_OVERSCAN_VGA_SUPPORT == _ON)

#if(_OVERSCAN_DVI_SUPPORT != _ON)
        case _SOURCE_DVI:
            break;
#endif

#if(_OVERSCAN_HDMI_SUPPORT != _ON)
        case _SOURCE_HDMI:
            break;
#endif

#if(_OVERSCAN_DP_SUPPORT != _ON)
        case _SOURCE_DP:
            break;
#endif

        default:
#if((_OVERSCAN_DVI_SUPPORT == _ON) || (_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON))
            // Interlaced and YUV Timing Always do overscan
            if(stTimingInfo.b1Interlace == _TRUE)
            {
                enumDoOverScan = _OVERSCAN_TRUE;
                break;
            }

            if((UserCommonColorGetColorSpaceRGB(UserCommonColorGetColorSpace(SysRegionGetInputPort(enumDisplayRegion))) == _TRUE))
            {
                break;
            }

            while(tusOverscanEnTable[ucTemp][0] != 0)
            {
                if((abs(stTimingInfo.usVFreq - tusOverscanEnTable[ucTemp][0]) < 10) &&
                   (abs(stTimingInfo.usHWidth - tusOverscanEnTable[ucTemp][1]) < 2) &&
                   (stTimingInfo.usVHeight == tusOverscanEnTable[ucTemp][2]))
                {
                    enumDoOverScan = _OVERSCAN_TRUE;
                    break;
                }

                ucTemp++;
            }
#endif // End of #if((_OVERSCAN_DVI_SUPPORT == _ON) || (_OVERSCAN_HDMI_SUPPORT == _ON) || (_OVERSCAN_DP_SUPPORT == _ON))

            break;
    }

    return enumDoOverScan;
}
#endif // End of #if(_OVERSCAN_SUPPORT == _ON)

#if(_ASPECT_RATIO_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Modify Timing For Aspect Ratio
// Input Value  : enumSelRegion --> select region
// Output Value : aspect ration type
//--------------------------------------------------
EnumAspectRatioType UserInterfaceDisplayGetAspectRatioType(EnumDisplayRegion enumDisplayRegion)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE(SysRegionGetInputPort(enumDisplayRegion)))
    {
        case _OSD_ASPECT_RATIO_16_BY_9:
        case _OSD_ASPECT_RATIO_4_BY_3:
        case _OSD_ASPECT_RATIO_5_BY_4:

            return _ASPECT_RATIO_FIXED;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
        case _OSD_ASPECT_RATIO_ORIGIN:
        case _OSD_ASPECT_RATIO_REDUCE:
        case _OSD_ASPECT_RATIO_ENLARGE:

#endif
            return _ASPECT_RATIO_ORIGIN;

        case _OSD_ASPECT_RATIO_USER:

            return _ASPECT_RATIO_USER;

        default:
        case _OSD_ASPECT_RATIO_FULL:

            return _ASPECT_RATIO_FULL;
    }
}

//--------------------------------------------------
// Description  : Get user H/V aspect ratio values
// Input Value  : enumSelRegion --> select region
//                usHRatio, usVRatio --> aspect ratio
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayGetAspectRatio(EnumDisplayRegion enumDisplayRegion, WORD *pusHRatio, WORD *pusVRatio)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE(SysRegionGetInputPort(enumDisplayRegion)))
    {
        default:
            break;

        case _OSD_ASPECT_RATIO_16_BY_9:
            *pusHRatio = 16;
            *pusVRatio = 9;
            break;

        case _OSD_ASPECT_RATIO_4_BY_3:
            *pusHRatio = 4;
            *pusVRatio = 3;
            break;

        case _OSD_ASPECT_RATIO_5_BY_4:
            *pusHRatio = 5;
            *pusVRatio = 4;
            break;
    }
}

//--------------------------------------------------
// Description  : User defined aspect ratio process
// Input Value  : display region
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayAdjustAspectRatio(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
    {
        UserCommonMDomainAspectOriginMode(_TRUE);

        PDATA_WORD(0) = _PANEL_DV_HEIGHT / 2;
        SET_MDOMAIN_OUTPUT_VHEIGHT(_PANEL_DV_HEIGHT / 2);

        PDATA_WORD(0) &= 0xFFFC; // V start should be even
        SET_MDOMAIN_OUTPUT_VSTART(GET_MDOMAIN_OUTPUT_VSTART() + (PDATA_WORD(0) / 2));

        PDATA_WORD(0) = _PANEL_DH_WIDTH / 2;
        PDATA_WORD(0) &= 0xFFFC; // H start should be even
        SET_MDOMAIN_OUTPUT_HSTART(GET_MDOMAIN_OUTPUT_HSTART() + (PDATA_WORD(0) / 2));
        SET_MDOMAIN_OUTPUT_HWIDTH(_PANEL_DH_WIDTH / 2);
    }
#endif
}

#if(_ASPECT_RATIO_WITHOUT_MUTE == _ON)
//--------------------------------------------------
// Description  : User defined minimum dvheight for aspect ratio
//                use 1:1 for example
// Input Value  : None
// Output Value : usMinDvheight
//--------------------------------------------------
WORD UserInterfaceDisplayGetAspectRatioMinDVHeight(void)
{
    EnumDisplayRegion enumRegion = SysRegionGetMeasureResultPointerRegion();
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

    WORD usMinDvheight = (stTimingInfo.usVHeight < GET_MDOMAIN_OUTPUT_VHEIGHT()) ? stTimingInfo.usVHeight : GET_MDOMAIN_OUTPUT_VHEIGHT();
    // return 0 if disable the function
    return usMinDvheight;
}
#endif

#if(_ASPECT_ORIGINAL_MODE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get aspect original mode ratio
// Input Value  : select region
// Output Value : Retion display ratio in aspect ratio original mode (0x00 ~ 0xFF)
//--------------------------------------------------
WORD UserInterfaceDisplayGetAspectRatioOriginalRatio(EnumDisplayRegion enumDisplayRegion)
{
    switch(GET_OSD_ASPECT_RATIO_TYPE(SysRegionGetInputPort(enumDisplayRegion)))
    {
        case _OSD_ASPECT_RATIO_REDUCE:

            return 0xCC;

        case _OSD_ASPECT_RATIO_ENLARGE:

            return 0x132;

        default:
        case _OSD_ASPECT_RATIO_ORIGIN:

            return 0xFF;
    }
}

#endif
#endif // End of #if(_ASPECT_RATIO_SUPPORT == _ON)

#if(_DISPLAY_ROTATION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get current rotation degree
// Input Value  : None
// Output Value : rotation degree
//--------------------------------------------------
EnumRotationType UserInterfaceDisplayGetRotationDegree(void)
{
    switch(GET_OSD_DISP_ROTATE())
    {
        default:
        case _DISP_ROTATE_0:
            return _ROT_DISABLE;
#if(_HW_DISPLAY_ROTATION_180_SUPPORT == _ON)
        case _DISP_ROTATE_180:
            return _ROT_CW180;
#endif
#if(_HW_DISPLAY_ROTATION_270_SUPPORT == _ON)
        case _DISP_ROTATE_270:
            return _ROT_CW270;
#endif
#if(_HW_DISPLAY_ROTATION_90_SUPPORT == _ON)
        case _DISP_ROTATE_90:
            return _ROT_CW90;
#endif
#if(_DISPLAY_HOR_MIRROR_SUPPORT == _ON)
        case _DISP_ROTATE_HOR_MIRROR:
            return _ROT_HOR_MIRROR;
#endif
#if(_DISPLAY_VER_MIRROR_SUPPORT == _ON)
        case _DISP_ROTATE_VER_MIRROR:
            return _ROT_VER_MIRROR;
#endif
    }
}

//--------------------------------------------------
// Description  : Get current rotation type
// Input Value  : None
// Output Value : rotation type
//--------------------------------------------------
EnumRotationDisplayType UserInterfaceDisplayGetRotationDisplayType(void)
{
    switch(GET_OSD_DISP_ROTATION_SIZE_TYPE())
    {
        default:
        case _OSD_ROTATE_DISPLAY_FULL:
            return _ROT_FULL;

        case _OSD_ROTATE_DISPLAY_PIXEL_BY_PIXEL:
            return _ROT_PIXEL_BY_PIXEL;

        case _OSD_ROTATE_DISPLAY_KEEP_SRC_ASPECT_RATIO:
            return _ROT_KEEP_SRC_ASPECT_RATIO;
    }
}
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Display Latency Ratio
// Input Value  : None
// Output Value : Latency 0~100%
//--------------------------------------------------
BYTE UserInterfaceDisplayGetLatencyRatio(void)
{
    switch(GET_OSD_LATENCY())
    {
        default:
        case _LATENCY_L:
            return 0;   // 0%

        case _LATENCY_M:
            return 50;  // 50%

        case _LATENCY_H:
            return 100; // 100%
    }
}
#endif

#if(_HDMI21_ALLM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get ALLM Off Latency Ratio
// Input Value  : None
// Output Value : Latency 0~100%
//--------------------------------------------------
BYTE UserInterfaceDisplayGetHDMIALLMOffLatencyRatio(void)
{
    return 100; // 100%
}
#endif

#if(_FRC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Max/Min Freq according to latency
// Input Value  : max/min freq
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayGetDVMaxMinFreq(StructDVCustomizedFreq *pstDVCustomizedFreq)
{
    EnumDisplayRegion enumRegion = SysRegionGetMeasureResultPointerRegion();
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

    pstDVCustomizedFreq = pstDVCustomizedFreq;

#if(_PANEL_STYLE != _PANEL_LVDS)
    if((SysSourceGetInputPort() == _A0_INPUT_PORT) ||
       (stTimingInfo.b1Interlace == _TRUE))
    {
        pstDVCustomizedFreq->b1FORCETOFREERUN = _ENABLE;
    }
#endif

#if(_DISP_LATENCY_ADJUST_SUPPORT == _ON)
    switch (GET_OSD_LATENCY())
    {
        default:
        case _LATENCY_H:
        case _LATENCY_M:
        case _LATENCY_L:

            pstDVCustomizedFreq->usTypFreq = _PANEL_TYP_FRAME_RATE;

#if(_DRR_SUPPORT == _ON)
            if(UserCommonDrrGetType() == _DRR_NONE_TYPE)
#endif
            {
                pstDVCustomizedFreq->usMaxFreq = _PANEL_MAX_FRAME_RATE;
                pstDVCustomizedFreq->usMinFreq = _PANEL_MIN_FRAME_RATE;
            }

            break;
    }
#endif

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_COLOR_IP_LSR == _ON))
    for(BYTE ucIndex = 0; ucIndex < (sizeof(tForceFrameBufferTiming) / sizeof(tForceFrameBufferTiming[0])); ucIndex++)
    {
        if((stTimingInfo.usVHeight == tForceFrameBufferTiming[ucIndex].usIVheight) &&
           (_PANEL_DV_HEIGHT == tForceFrameBufferTiming[ucIndex].usDVheight))
        {
            pstDVCustomizedFreq->b1DecideMemoryConfig = _FORCE_FRAME_BUFFER_MODE;
        }
    }
#endif
}
#endif

//--------------------------------------------------
// Description  : Adjust Main Memory Data Bit, including line buffer and frame buffer
// Input Value  : pstCustomizedMdomain
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplaySelectMDomainSettingForMain(StructCustomizedMdomain *pstCustomizedMdomain)
{
    EnumDisplayRegion enumRegion = SysRegionGetMeasureResultPointerRegion();
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

    pstCustomizedMdomain = pstCustomizedMdomain;

#if(_BW_CUSTOME_MODE == _ENABLE) // modify here
    // pstCustomizedMdomain->enumMemoryBitSelect = _MEMORY_REF_SOURCE_BIT;
    // pstCustomizedMdomain->enumBWCustomeModeType = _BW_DEFAULT_TYPE;
#else
    pstCustomizedMdomain->enumMemoryBitSelect = _MEMORY_REF_SOURCE_BIT;
    pstCustomizedMdomain->enumBWCustomeModeType = _BW_DEFAULT_TYPE;
#endif
}

#if(_PANEL_FREE_RUN_M_DOMAIN_SETTING_COMPATIBLE_MODE == _ON)
//--------------------------------------------------
// Description  : Free Run Select Change Dclk
// Input Value  : None
// Output Value : EnumFreeRunDdomainSetting
//--------------------------------------------------
EnumFreeRunDdomainSetting UserInterfaceDisplayFreeRunDclkSettingSelect(void)
{
    return _DEFAULT_FREERUN_DDOMAIN_SETTING;
}
#endif

#if(_MULTI_DISPLAY_MAX > 0x01)
//--------------------------------------------------
// Description  : Adjust Sub Memory Data Bit, including line buffer and frame buffer
// Input Value  : pstCustomizedMdomain
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplaySelectMDomainSettingForSub(StructCustomizedMdomain *pstCustomizedMdomain)
{
    EnumDisplayRegion enumRegion = SysRegionGetMeasureResultPointerRegion();
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

    pstCustomizedMdomain = pstCustomizedMdomain;

    // align setting with UserInterfaceDisplaySelectMDomainSettingForMain
    // if main region size = sub region size (ex 4P, 3p_flag_1_1_1..., pbplr l=r)
#if(_BW_CUSTOME_MODE == _ENABLE) // modify here
    // pstCustomizedMdomain->enumMemoryBitSelect = _MEMORY_REF_SOURCE_BIT;
    // pstCustomizedMdomain->enumBWCustomeModeType = _BW_DEFAULT_TYPE;
#else
    pstCustomizedMdomain->enumMemoryBitSelect = _MEMORY_REF_SOURCE_BIT;
    pstCustomizedMdomain->enumBWCustomeModeType = _BW_DEFAULT_TYPE;
#endif
}
#endif

//--------------------------------------------------
// Description  : Modify Input Timing Based on User Requirement
// Input Value  : Current Input Timing Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayAdjustInputTiming(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
}

//--------------------------------------------------
// Description  : Modify Display Timing Based on User Requirement
// Input Value  : Current Display Timing Info
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayAdjustDisplayTiming(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;
}

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get PIP sub timing format
// Input Value  : None
// Output Value : timing format
//--------------------------------------------------
void UserInterfaceDisplayGetPipSubTimingFormat(StructTimingFormat *pstTimingFormat)
{
    // Min resolution: default 640x480
    // Min resolution: 1/4 screen size
    if(((DWORD)_PANEL_DH_WIDTH * 100 / _OSD_PIP_SIZE_MIN_H_SIZE) < ((DWORD)_PANEL_DV_HEIGHT * 100 / _OSD_PIP_SIZE_MIN_V_SIZE))
    {
        // H limited
        pstTimingFormat->usHWidth = _OSD_PIP_SIZE_MIN_H_SIZE;
        pstTimingFormat->usVHeight = (((DWORD)_PANEL_DV_HEIGHT * _OSD_PIP_SIZE_MIN_H_SIZE * 2 / _PANEL_DH_WIDTH) + 1) / 2;
    }
    else
    {
        // V limited
        pstTimingFormat->usHWidth = (WORD)(((DWORD)_PANEL_DH_WIDTH * _OSD_PIP_SIZE_MIN_V_SIZE / _PANEL_DV_HEIGHT) + 3) & 0xFFFC; // with factors of 4
        pstTimingFormat->usVHeight = _OSD_PIP_SIZE_MIN_V_SIZE;
    }

    pstTimingFormat->usHWidth = pstTimingFormat->usHWidth + (((_PANEL_DH_WIDTH / 2 - pstTimingFormat->usHWidth) / 4) * GET_OSD_PIP_SIZE() / _OSD_PIP_SIZE_MAX) * 4;
    pstTimingFormat->usVHeight = pstTimingFormat->usVHeight + (_PANEL_DV_HEIGHT / 2 - pstTimingFormat->usVHeight) * GET_OSD_PIP_SIZE() / _OSD_PIP_SIZE_MAX;

    // PIP H/V width, height must be even
    pstTimingFormat->usHWidth &= 0xFFFE;
    pstTimingFormat->usVHeight &= 0xFFFE;

    switch(GET_OSD_PIP_POSITION_TYPE())
    {
        case _PIP_POSITON_LT:
            pstTimingFormat->usHStart = _PANEL_DH_START;
            pstTimingFormat->usVStart = _PANEL_DV_START;
            break;

        case _PIP_POSITON_RT:
            pstTimingFormat->usHStart = (_PANEL_DH_START + _PANEL_DH_WIDTH - pstTimingFormat->usHWidth);
            pstTimingFormat->usVStart = (_PANEL_DV_START);
            break;

        case _PIP_POSITON_LB:
            pstTimingFormat->usHStart = (_PANEL_DH_START);
            pstTimingFormat->usVStart = (_PANEL_DV_START + _PANEL_DV_HEIGHT - pstTimingFormat->usVHeight);

            break;

        default:
        case _PIP_POSITON_RB:
            pstTimingFormat->usHStart = (_PANEL_DH_START + _PANEL_DH_WIDTH - pstTimingFormat->usHWidth);
            pstTimingFormat->usVStart = (_PANEL_DV_START + _PANEL_DV_HEIGHT - pstTimingFormat->usVHeight);

            break;

        case _PIP_POSITON_MIDDLE:
            pstTimingFormat->usHStart = (_PANEL_DH_START + (_PANEL_DH_WIDTH / 2) - (pstTimingFormat->usHWidth / 2));
            pstTimingFormat->usVStart = (_PANEL_DV_START + (_PANEL_DV_HEIGHT / 2) - (pstTimingFormat->usVHeight / 2));

            break;

        case _PIP_POSITON_USER:
            pstTimingFormat->usHStart = (_PANEL_DH_START + ((DWORD)_PANEL_DH_WIDTH - pstTimingFormat->usHWidth) * GET_OSD_PIP_USER_POSITION_H() / _OSD_PIP_USER_POSITION_H_MAX);
            pstTimingFormat->usVStart = (_PANEL_DV_START + ((DWORD)_PANEL_DV_HEIGHT - pstTimingFormat->usVHeight) * GET_OSD_PIP_USER_POSITION_V() / _OSD_PIP_USER_POSITION_V_MAX);

            break;
    }

    // PIP H/V start must be even
    pstTimingFormat->usHStart &= 0xFFFE;
    pstTimingFormat->usVStart &= 0xFFFE;
}
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Eagle Sight sub timing format
// Input Value  : None
// Output Value : timing format
//--------------------------------------------------
void UserInterfaceDisplayGetEagleSightSubTimingFormat(StructTimingFormat *pstTimingFormat)
{
    pstTimingFormat->usHStart = _PANEL_DH_START;
    pstTimingFormat->usVStart = _PANEL_DV_START;
    pstTimingFormat->usHWidth = _PANEL_DH_WIDTH / 4;
    pstTimingFormat->usVHeight = _PANEL_DV_HEIGHT / 4;

    // Eagle Sight H/V width, height must be even
    pstTimingFormat->usHWidth &= 0xFFFE;
    pstTimingFormat->usVHeight &= 0xFFFE;
}

//--------------------------------------------------
// Description  : Set Eagle Sight Default Setting: enable, transparent, ratio, position
// Input Value  : pstEagleSightSetting: OSD setting
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplaySetEagleSightSettingDefault(StructEagleSightSetting *pstEagleSightSetting)
{
    pstEagleSightSetting->enumEagleSightEnable = _EAGLE_SIGHT_SETTING_DISABLE;
    pstEagleSightSetting->enumEagleSightRatio = _EAGLE_SIGHT_RATIO_1_5;
    pstEagleSightSetting->enumEagleSightCapPosition = _EAGLE_SIGHT_CAP_CENTER;
    pstEagleSightSetting->enumEagleSightDispPosition = _EAGLE_SIGHT_DISP_CENTER;
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    pstEagleSightSetting->enumEagleSightCircleWinEnable = _EAGLE_SIGHT_CIRCLE_WIN_DISABLE;
#endif
    pstEagleSightSetting->ucTransparencyLevel = 0xFF; // Transparency off, Main Cover Sub
}

//--------------------------------------------------
// Description  : Get Eagle Sight Setting: enable, transparent, ratio, position
// Input Value  : pstEagleSightSetting: OSD setting
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayGetEagleSightSetting(StructEagleSightSetting *pstEagleSightSetting)
{
    WORD usLevel = 0;

    pstEagleSightSetting->enumEagleSightEnable = GET_EAGLE_SIGHT_STATUS();
    pstEagleSightSetting->enumEagleSightRatio = GET_EAGLE_SIGHT_ZOOM();
    pstEagleSightSetting->enumEagleSightDispPosition = GET_EAGLE_SIGHT_DISP_POSITION();
    pstEagleSightSetting->enumEagleSightCapPosition = GET_EAGLE_SIGHT_CAP_POSITION();
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
    pstEagleSightSetting->enumEagleSightCircleWinEnable = GET_EAGLE_SIGHT_CIRCLE_WIN_STATUS();
#endif
    // There are 256 register transparency levels.
    // Convert OSD Transparency Level to Register Transparency Level.
    usLevel = GET_EAGLE_SIGHT_TRANSPARENCY() * ((256 * 2 / (_OSD_EAGLE_SIGHT_TRANSPARENCY_MAX - _OSD_EAGLE_SIGHT_TRANSPARENCY_MIN)) + 1) >> 1;
    if(usLevel > 0xFF)
    {
        usLevel = 0xFF;
    }
    pstEagleSightSetting->ucTransparencyLevel = (BYTE)usLevel;
}

//--------------------------------------------------
// Description  : User defined Eagle Sight Input Capture
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayAdjustEagleSightInputCapturePosition(StructEagleSightPosition *pstEagleSightPosition)
{
    pstEagleSightPosition->usHstart = GET_MDOMAIN_INPUT_HSTART();
    pstEagleSightPosition->usVstart = GET_MDOMAIN_INPUT_VSTART();
    pstEagleSightPosition->usHwidth = (GET_MDOMAIN_INPUT_HWIDTH() >> 2);
    pstEagleSightPosition->usVheight = (GET_MDOMAIN_INPUT_VHEIGHT() >> 2);

#if(_OVERSCAN_SUPPORT == _ON) // ref: SysModeEagleSightInputCapture
    if(GET_OSD_OVERSCAN_STATUS(_DISPLAY_RGN_EAGLE_SIGHT_MAIN) == _ON)
    {
        StructTimingInfo stTimingInfo;

        memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));

        // Read timing info
        SysRegionGetMeasureResultByRegion(SysRegionGetDisplayRegion(_REGION_INDEX_0), &stTimingInfo);
        // Eagle sight with Overscan need to consider H/V shifting
        pstEagleSightPosition->usHstart += ((stTimingInfo.usHWidth - GET_MDOMAIN_INPUT_HWIDTH()) / 2);
        pstEagleSightPosition->usVstart += ((stTimingInfo.usVHeight - GET_MDOMAIN_INPUT_VHEIGHT()) / 2);
    }
#endif

    pstEagleSightPosition->usHwidth &= 0xFFFC;
    pstEagleSightPosition->usVheight &= 0xFFFC;
}

//--------------------------------------------------
// Description  : User defined Eagle Sight Display Capture
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayAdjustEagleSightDisplayCapturePosition(StructEagleSightPosition *pstEagleSightPosition)
{
    // pstEagleSightPosition->usHstart = pstEagleSightPosition->usHstart;
    // pstEagleSightPosition->usVstart = pstEagleSightPosition->usVstart;
    pstEagleSightPosition->usHwidth = (pstEagleSightPosition->usHwidth >> 2);
    pstEagleSightPosition->usVheight = (pstEagleSightPosition->usVheight >> 2);

    pstEagleSightPosition->usHwidth &= 0xFFFC;
    pstEagleSightPosition->usVheight &= 0xFFFC;
}
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get PBP LR timing format
// Input Value  : enumSelRegion --> L or R
// Output Value : timing format
//--------------------------------------------------
void UserInterfaceDisplayGetPbpTimingFormat(EnumDisplayRegion enumDisplayRegion, StructTimingFormat *pstTimingFormat)
{
    WORD usStep = 0;
    WORD usMaxLeftSize = 0;
    BYTE ucPbpLrRatio = GET_OSD_PBP_LR_RATIO();

    if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 9 * 16))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 9 * 16);
    }
    else if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 3 * 4))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 3 * 4);
    }
    else if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 4 * 5))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 4 * 5);
    }
    else
    {
        usMaxLeftSize = (_PANEL_DH_WIDTH / 4 * 3);
    }

    // Check R size minimum = 640
    if((_PANEL_DH_WIDTH - usMaxLeftSize) < 640)
    {
        usMaxLeftSize = (_PANEL_DH_WIDTH - 640);
    }

    usStep = ((DWORD)usMaxLeftSize - (_PANEL_DH_WIDTH / 2)) * abs(_OSD_PBP_LR_RATIO_CENTER - ucPbpLrRatio) / _OSD_PBP_LR_RATIO_MAX;
    usStep = usStep & 0xFFFC;

    // Set V timing format
    pstTimingFormat->usVStart = _PANEL_DV_START;
    pstTimingFormat->usVHeight = _PANEL_DV_HEIGHT;

    // Set H timing format
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_PBP_LR_EQUAL_LEFT:
            pstTimingFormat->usHStart = _PANEL_DH_START;
            pstTimingFormat->usHWidth = (_PANEL_DH_WIDTH / 2);
            break;

        case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
            pstTimingFormat->usHStart = _PANEL_DH_START;
            pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
            break;

        case _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT:
            pstTimingFormat->usHStart = _PANEL_DH_START;
            pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
            break;

        case _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT:
            pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2);
            pstTimingFormat->usHWidth = (_PANEL_DH_WIDTH / 2);
            break;

        case _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT:
            pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) + usStep;
            pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
            break;

        case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
            pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) - usStep;
            pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
            break;

        default:
            break;
    }
}
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get PBP LR timing format
// Input Value  : enumSelRegion --> L or R
// Output Value : timing format
//--------------------------------------------------
void UserInterfaceDisplayGet3PFlagTimingFormat(EnumDisplayRegion enumDisplayRegion, StructTimingFormat *pstTimingFormat)
{
    WORD usStep = 0;
    BYTE uc3PFlagRatio = GET_OSD_3P_FLAG_RATIO();

    // Left max size : (_PANEL_DH_WIDTH / 3) --> 3P Flag 1:1:1
    // Left min size : (_PANEL_DH_WIDTH / 4) --> 3P Flag 1:2:1
    usStep = (_PANEL_DH_WIDTH / 4) + ((DWORD)(_PANEL_DH_WIDTH / 3) - (_PANEL_DH_WIDTH / 4)) * (_OSD_3P_FLAG_RATIO_MAX - uc3PFlagRatio) / _OSD_3P_FLAG_RATIO_MAX;
    usStep = usStep & 0xFFFC;

    // Set H timing format
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_FLAG_MAIN:
            pstTimingFormat->usHStart = _PANEL_DH_START + usStep;
            pstTimingFormat->usHWidth = _PANEL_DH_WIDTH - usStep * 2;
            break;

        case _DISPLAY_RGN_FLAG_LEFT:
            pstTimingFormat->usHStart = _PANEL_DH_START;
            pstTimingFormat->usHWidth = usStep;
            break;

        case _DISPLAY_RGN_FLAG_RIGHT:
            pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH - usStep);
            pstTimingFormat->usHWidth = usStep;
            break;

        default:
            break;
    }

    // Set V timing format
    pstTimingFormat->usVStart = _PANEL_DV_START;
    pstTimingFormat->usVHeight = _PANEL_DV_HEIGHT;
}
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get 3P skew LR timing format
// Input Value  : enumDisplayRegion
// Output Value : timing format
//--------------------------------------------------
void UserInterfaceDisplayGet3PSkewLRTimingFormat(EnumDisplayRegion enumDisplayRegion, StructTimingFormat *pstTimingFormat)
{
    WORD usStep = 0;
    WORD usMaxLeftSize = 0;
    BYTE ucSkewLRratio = GET_OSD_3P_SKEW_LR_RATIO();

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(UserCommonRegionGetFrontBackModeSupport() == _TRUE)
    {
        ucSkewLRratio = _OSD_3P_SKEW_LR_RATIO_CENTER;
    }
#endif

    if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 9 * 16))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 9 * 16);
    }
    else if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 3 * 4))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 3 * 4);
    }
    else if(_PANEL_DH_WIDTH > (_PANEL_DV_HEIGHT / 4 * 5))
    {
        usMaxLeftSize = (_PANEL_DV_HEIGHT / 4 * 5);
    }
    else
    {
        usMaxLeftSize = (_PANEL_DH_WIDTH / 4 * 3);
    }

    // Check R size minimum = 640
    if((_PANEL_DH_WIDTH - usMaxLeftSize) < 640)
    {
        usMaxLeftSize = (_PANEL_DH_WIDTH - 640);
    }

    usStep = ((DWORD)usMaxLeftSize - (_PANEL_DH_WIDTH / 2)) * abs(_OSD_3P_SKEW_LR_RATIO_CENTER - ucSkewLRratio) / _OSD_3P_SKEW_LR_RATIO_MAX;
    usStep = usStep & 0xFFFC;

    // Set H timing format
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_SKEW_L_MAIN:
            pstTimingFormat->usHStart = _PANEL_DH_START;
            pstTimingFormat->usVStart = _PANEL_DV_START;
            pstTimingFormat->usVHeight = _PANEL_DV_HEIGHT;
            if(ucSkewLRratio > _OSD_3P_SKEW_LR_RATIO_CENTER)
            {
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
            }
            else
            {
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
            }
            break;

        case _DISPLAY_RGN_SKEW_L_TOP:
            pstTimingFormat->usVStart = _PANEL_DV_START;
            pstTimingFormat->usVHeight = (_PANEL_DV_HEIGHT / 2);
            if(ucSkewLRratio > _OSD_3P_SKEW_LR_RATIO_CENTER)
            {
                pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) + usStep;
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
            }
            else
            {
                pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) - usStep;
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
            }
            break;

        case _DISPLAY_RGN_SKEW_L_BOTTOM:
            pstTimingFormat->usVStart = _PANEL_DV_START + (_PANEL_DV_HEIGHT / 2);
            pstTimingFormat->usVHeight = (_PANEL_DV_HEIGHT / 2);
            if(ucSkewLRratio > _OSD_3P_SKEW_LR_RATIO_CENTER)
            {
                pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) + usStep;
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
            }
            else
            {
                pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) - usStep;
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
            }
            break;

        case _DISPLAY_RGN_SKEW_R_MAIN:
            pstTimingFormat->usVStart = _PANEL_DV_START;
            pstTimingFormat->usVHeight = _PANEL_DV_HEIGHT;
            if(ucSkewLRratio > _OSD_3P_SKEW_LR_RATIO_CENTER)
            {
                pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) + usStep;
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
            }
            else
            {
                pstTimingFormat->usHStart = _PANEL_DH_START + (_PANEL_DH_WIDTH / 2) - usStep;
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
            }
            break;

        case _DISPLAY_RGN_SKEW_R_TOP:
            pstTimingFormat->usHStart = _PANEL_DH_START;
            pstTimingFormat->usVStart = _PANEL_DV_START;
            pstTimingFormat->usVHeight = (_PANEL_DV_HEIGHT / 2);
            if(ucSkewLRratio > _OSD_3P_SKEW_LR_RATIO_CENTER)
            {
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
            }
            else
            {
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
            }
            break;

        case _DISPLAY_RGN_SKEW_R_BOTTOM:
            pstTimingFormat->usHStart = _PANEL_DH_START;

            pstTimingFormat->usVStart = _PANEL_DV_START + (_PANEL_DV_HEIGHT / 2);
            pstTimingFormat->usVHeight = (_PANEL_DV_HEIGHT / 2);
            if(ucSkewLRratio > _OSD_3P_SKEW_LR_RATIO_CENTER)
            {
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) + usStep);
            }
            else
            {
                pstTimingFormat->usHWidth = ((_PANEL_DH_WIDTH / 2) - usStep);
            }
            break;

        default:
            break;
    }
}
#endif

#if(_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust backlight setting
// Input Value  : Backlight Mode, Backlight On/Off
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayMbrBacklightAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl, WORD usDVTotal)
{
    BYTE ucBacklightDuty = 0; // Backlight ON percentage
    BYTE ucBacklightPos = 0; // Backlight Position percentage
    WORD usStrobeVWidth = 0; // Backlight ON lines
    WORD usStrobeVPos = 0; // Backlight ON Position (lines)

    DebugMessageScaler("MBR: bLightCtrl", bLightCtrl);
    DebugMessageScaler("MBR: VTotal", usDVTotal);
    DebugMessageScaler("MBR: ucBacklightDuty", GET_OSD_MBR_DUTY());
    DebugMessageScaler("MBR: ucBacklightPos", GET_OSD_MBR_POSITION());

    switch(enumBacklightMode)
    {
        //=================================================================
        // User stand-alone motion blur reduction mode
        //=================================================================
        case _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR:
            /*
             Strobe Backlight Position
               _____       ________________________     _____
              |     |     |                        |   |     |
              |VSync|_____|         Duty           |___|VSync|___
                         Pos                   Pos + Duty

               _____                        ________________________
              |     |                      |                        |
              |VSync|______________________|         Duty           |___
                                          Pos                  Pos + Duty
            */

            if(bLightCtrl == _LIGHT_CONTROL_ON)
            {
                // Backlight strobe ctrl (Tcon local enable...)
                ucBacklightDuty = GET_OSD_MBR_DUTY();
                ucBacklightPos = GET_OSD_MBR_POSITION();
                usStrobeVPos = (WORD)((DWORD)ucBacklightPos * usDVTotal / 100L);
                usStrobeVWidth = (WORD)((DWORD)ucBacklightDuty * usDVTotal / 100L);
                if(ucBacklightDuty == 100)
                {
                    UserCommonTconAdjustByIndex(_PCB_MBR_TCON_PIN, 0x0000, 0x1FFF, 0x0000, 0x3FFF);
                }
                else
                {
                    UserCommonTconAdjustByIndex(_PCB_MBR_TCON_PIN, 0x0000, 0x1FFF, usStrobeVPos, (usStrobeVPos + usStrobeVWidth) % usDVTotal);
                }
                UserCommonTconEnableByIndex(_PCB_MBR_TCON_PIN, _ENABLE);
            }
            else
            {
                // Setting in _LIGHT_CONTROL_OFF case
                UserCommonTconEnableByIndex(_PCB_MBR_TCON_PIN, _DISABLE);
            }
            break;

        //=================================================================
        // Constant backlight mode
        //=================================================================
        default:
        case _BACKLIGHT_MODE_CONSTANT:
            if(bLightCtrl == _LIGHT_CONTROL_ON)
            {
#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
                // Local Dimming MBR mode dosen't need to use TCON in case _BACKLIGHT_MODE_CONSTANT
                UserCommonTconEnableByIndex(_PCB_MBR_TCON_PIN, _DISABLE);
#else
                // Backlight Ctrl
                // Set TCON to always ON and/or disable strobe ctrl pins...
                UserCommonTconAdjustByIndex(_PCB_MBR_TCON_PIN, 0x0000, 0x1FFF, 0x0000, 0x3FFF);

                UserCommonTconEnableByIndex(_PCB_MBR_TCON_PIN, _ENABLE);
#endif
            }
            else
            {
                // Setting in _LIGHT_CONTROL_OFF case
                UserCommonTconEnableByIndex(_PCB_MBR_TCON_PIN, _DISABLE);
            }
            break;
    }
}

//--------------------------------------------------
// Description  : Adjust Backlight ADIM (normally controled by scaler PWM)
// Input Value  : Current backlight mode and backlight on/off status
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayMbrAdimAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        switch(enumBacklightMode)
        {
            // In strobe backlight case, set scaler PWM to full duty
            case _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR:
            case _BACKLIGHT_MODE_STROBE_DRR_MBR:
            case _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR:
                PCB_PWM_SETTING();
                PCB_BACKLIGHT_PWM(0xFF);
                break;

            // In constant backlight case, set scaler PWM according to user setting
            case _BACKLIGHT_MODE_CONSTANT:
            default:
                PCB_PWM_SETTING();
                UserAdjustBacklight(GET_OSD_BACKLIGHT());
                break;
        }
    }
    else
    {
        PCB_BACKLIGHT_PWM(0x00);
    }
}

//--------------------------------------------------
// Description  : Adjust Backlight PDIM
// Input Value  : Current backlight mode and backlight on/off status
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayMbrPdimAdjust(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl)
{
    enumBacklightMode = enumBacklightMode;
    bLightCtrl = bLightCtrl;

    // User can modify PDIM control setting here
    // e.g.
    // when using AS3824, MBR P-dimming setting may not required to be controled by TCON in Constant Mode
    // User can place additional setting here(switch Pinshare, Send I2C Command to driver...etc.)
    // ---
    // For TCON enable setting, kernel set accrording to the result of UserInterfaceDisplayMbrGetPdimControl()
}

//--------------------------------------------------
// Description  : Get backlight PDIM control method
// Input Value  : Current backlight mode and backlight on/off status
// Output Value : PDIM control method
//--------------------------------------------------
EnumMbrPDimCtrl UserInterfaceDisplayMbrGetPdimControl(EnumMbrBacklightMode enumBacklightMode, bit bLightCtrl)
{
    enumBacklightMode = enumBacklightMode;
    bLightCtrl = bLightCtrl;

    // User can specify PDIM control method here
    // e.g.
    // when using AS3824, MBR P-dimming setting may not required to be controled by TCON in Constant Mode
    // User can return _BACKLIGHT_PDIM_CTRL_BY_USER and place additional setting in UserInterfaceDisplayMbrPdimAdjust()
    // ---
    // _BACKLIGHT_PDIM_CTRL_BY_TCON => kernel WILL enable/disable TCON at current status
    // _BACKLIGHT_PDIM_CTRL_BY_USER => kernel WILL NOT enable/disable TCON at current status

    return _BACKLIGHT_PDIM_CTRL_BY_TCON;
}

#if((_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON) || (_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Get MBR OSD Duty
// Input Value  : Backlight Mode, Backlight On/Off
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceDisplayMbrGetBacklightDuty(void)
{
    return (BYTE)GET_OSD_MBR_DUTY();
}

//--------------------------------------------------
// Description  : Get MBR OSD Duty
// Input Value  : Backlight Mode, Backlight On/Off
// Output Value : None
//--------------------------------------------------
BYTE UserInterfaceDisplayMbrGetBacklightPosition(void)
{
    return (BYTE)GET_OSD_MBR_POSITION();
}
#endif

//--------------------------------------------------
// Description  : Judge MBR Backlight Mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
EnumMbrBacklightMode UserInterfaceDisplayMbrGetBacklightMode(void)
{
    if(GET_OSD_MBR_MODE() == _OSD_MBR_OFF) // Constant backlight
    {
        return _BACKLIGHT_MODE_CONSTANT;
    }
    else if(GET_OSD_MBR_MODE() == _OSD_MBR_USERMODE) // User want to control backlight
    {
        return _BACKLIGHT_MODE_STROBE_USER_CUSTOMIZE_MBR;
    }
    else if(GET_OSD_MBR_MODE() == _OSD_MBR_RTK_ADV)
    {
#if((_DRR_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
        if((UserCommonDrrGetType() != _DRR_NONE_TYPE) && (UserCommonDisplayMbrDrrGetHWSupport() == _TRUE))
        {
            return _BACKLIGHT_MODE_STROBE_DRR_MBR;
        }
#endif
#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
        if(UserCommonDisplayGetAdvMbrStatus() == _ENABLE)
        {
            return _BACKLIGHT_MODE_STROBE_RTK_ADV_MBR;
        }
#endif
        return _BACKLIGHT_MODE_CONSTANT;
    }
    return _BACKLIGHT_MODE_CONSTANT;
}

//--------------------------------------------------
// Description  : Get backlight off PDIM/ADIM sequence
// Input Value  : None
// Output Value : Backlight adjust sequence
//--------------------------------------------------
EnumMbrBacklightSeq UserInterfaceDisplayMbrGetBacklightSequence(bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        if(UserCommonDisplayMbrGetCurrentBacklightMode() == _BACKLIGHT_MODE_CONSTANT)
        {
            return _BACKLIGHT_SEQ_ADIM_PDIM;
        }
        else
        {
            return _BACKLIGHT_SEQ_PDIM_ADIM;
        }
    }
    else
    {
        return _BACKLIGHT_SEQ_PDIM_ADIM;
    }
}

//--------------------------------------------------
// Description  : Get backlight off PDIM/ADIM delay
// Input Value  : None
// Output Value : xx ms delay between PDIM/ADIM
//--------------------------------------------------
WORD UserInterfaceDisplayMbrGetBacklightSequenceDelay(bit bLightCtrl)
{
    if(bLightCtrl == _LIGHT_CONTROL_ON)
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

#if(_RTK_ADVANCED_MOTION_BLUR_REDUCTION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Adjust Motion Blur Reduction Function
//                Accroding to User Selection
// Input Value  : None
// Output Value : _RTK_ADV_MBR_USER_DISABLE/_RTK_ADV_MBR_USER_ENABLE
//--------------------------------------------------
EnumRtkAdvMbrUserStatus UserInterfaceDisplayGetRtkAdvMbrSetting(void)
{
    EnumDisplayRegion enumRegion = SysRegionGetMeasureResultPointerRegion();
    StructTimingInfo stTimingInfo;
    memset(&stTimingInfo, 0x00, sizeof(StructTimingInfo));
    SysRegionGetMeasureResultByRegion(enumRegion, &stTimingInfo);

    if((GET_OSD_MBR_MODE() == _OSD_MBR_RTK_ADV) && (stTimingInfo.usVFreq >= _RTK_ADV_MBR_MIN_ENABLE_IVF))
    {
        return _RTK_ADV_MBR_USER_ENABLE;
    }

    return _RTK_ADV_MBR_USER_DISABLE;
}
#endif

#elif(_MOTION_BLUR_REDUCTION_OLED_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Black Frame Insertion Function
// Input Value  : None
// Output Value : EnumMbrBFIMode
//--------------------------------------------------
EnumMbrBFIMode UserInterfaceDisplayMbrGetBlackFrameInsertMode(void)
{
    if(GET_OSD_MBR_MODE() == _OSD_MBR_OFF)
    {
        return _BFI_MODE_OFF;
    }
    else if(GET_OSD_MBR_MODE() == _OSD_MBR_USERMODE)
    {
        return _BFI_MODE_ON;
    }
    else
    {
        return _BFI_MODE_OFF;
    }
}

//--------------------------------------------------
// Description  : User customerized adjustment with black frame insertion
// Input Value  : EnumMbrBFIMode
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplayMbrBlackFrameInsertCtrl(EnumMbrBFIMode enumMbrBFIMode)
{
    if(enumMbrBFIMode == _BFI_MODE_ON)
    {
        // user customerized brightness adjustment here
        enumMbrBFIMode = enumMbrBFIMode;
    }
    else
    {
        // user customerized brightness adjustment here
        enumMbrBFIMode = enumMbrBFIMode;
    }
}
#endif

#if(_DP_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Dp FreeSync Get IVFmax From Look Up Table
// Input Value  : IVF(unit: 0.1Hz)
// Output Value : _DP_FREESYNC_WITH_IVF_MAX: Get IVF
//--------------------------------------------------
EnumDrrFreeSyncDpGetIVF UserInterfaceDisplayDpFreeSyncGetIVFmaxFromLut(WORD *pusVfreqMax)
{
    BYTE ucIndex = 0;
    WORD usPixelClk = UserCommonSourceGetInputPixelClk(SysRegionGetInputPort(SysModeGetDisplayTarget()));
    WORD usRefHtotalHBound = 0;
    WORD usRefHtotalLBound = 0;
    WORD usPixelClkHBound = usPixelClk;
    WORD usPixelClkLBound = usPixelClk;
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(stTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(SysRegionGetDisplayRegion(_REGION_INDEX_0), &stTimingInfo);

    // Htotal margin
    PDATA_WORD(0) = ((DWORD)_USER_DRR_HTOTAL_MARGIN * stTimingInfo.usHTotal / 100);
    usRefHtotalHBound = (stTimingInfo.usHTotal + PDATA_WORD(0));
    usRefHtotalLBound = (stTimingInfo.usHTotal - PDATA_WORD(0));

    // Pixel clk margin
    PDATA_WORD(0) = ((DWORD)_USER_DRR_CLK_MARGIN * usPixelClk / 100);
    usPixelClkHBound += PDATA_WORD(0);
    usPixelClkLBound -= PDATA_WORD(0);

    for(ucIndex = 0; ucIndex < (sizeof(tDrrFreeSyncDpTimingInfo) / sizeof(tDrrFreeSyncDpTimingInfo[0])); ucIndex++)
    {
        if((GET_DP_FREESYNC_IHWIDTH(ucIndex) == stTimingInfo.usHWidth) && (GET_DP_FREESYNC_IVHEIGHT(ucIndex) == stTimingInfo.usVHeight) &&
           ((GET_DP_FREESYNC_IHTOTAL(ucIndex) <= usRefHtotalHBound) && (GET_DP_FREESYNC_IHTOTAL(ucIndex) >= usRefHtotalLBound)) &&
           ((GET_DP_FREESYNC_ICLK(ucIndex) <= usPixelClkHBound) && (GET_DP_FREESYNC_ICLK(ucIndex) >= usPixelClkLBound)))
        {
            *pusVfreqMax = GET_DP_FREESYNC_IVFREQ(ucIndex);

            DebugMessageScaler("ucIndex if Drr user define timing ", ucIndex);
            return _DP_FREESYNC_WITH_IVF_MAX;
        }
    }

    *pusVfreqMax = 0;
    return _DP_FREESYNC_WITHOUT_IVF_MAX;
}
#endif

#if(_HDMI_FREESYNC_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI FreeSync Get IVFmax From Look Up Table
// Input Value  : IVF(unit: 0.1Hz)
// Output Value : _HDMI_FREESYNC_WITH_IVF_MAX: Get IVF
//--------------------------------------------------
EnumDrrFreeSyncHdmiGetIVF UserInterfaceDisplayHdmiFreeSyncGetIVFmaxFromLut(WORD *pusVfreqMax)
{
    BYTE ucIndex = 0;
    WORD usPixelClk = UserCommonSourceGetInputPixelClk(SysRegionGetInputPort(SysModeGetDisplayTarget()));
    WORD usRefHtotalHBound = 0;
    WORD usRefHtotalLBound = 0;
    WORD usPixelClkHBound = usPixelClk;
    WORD usPixelClkLBound = usPixelClk;
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(stTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(SysRegionGetDisplayRegion(_REGION_INDEX_0), &stTimingInfo);

    // Htotal margin
    PDATA_WORD(0) = ((DWORD)_USER_DRR_HTOTAL_MARGIN * stTimingInfo.usHTotal / 100);
    usRefHtotalHBound = (stTimingInfo.usHTotal + PDATA_WORD(0));
    usRefHtotalLBound = (stTimingInfo.usHTotal - PDATA_WORD(0));

    // Pixel clk margin
    PDATA_WORD(0) = ((DWORD)_USER_DRR_CLK_MARGIN * usPixelClk / 100);
    usPixelClkHBound += PDATA_WORD(0);
    usPixelClkLBound -= PDATA_WORD(0);

    for(ucIndex = 0; ucIndex < (sizeof(tDrrFreeSyncHdmiTimingInfo) / sizeof(tDrrFreeSyncHdmiTimingInfo[0])); ucIndex++)
    {
        if((GET_HDMI_FREESYNC_IHWIDTH(ucIndex) == stTimingInfo.usHWidth) && (GET_HDMI_FREESYNC_IVHEIGHT(ucIndex) == stTimingInfo.usVHeight) &&
           ((GET_HDMI_FREESYNC_IHTOTAL(ucIndex) <= usRefHtotalHBound) && (GET_HDMI_FREESYNC_IHTOTAL(ucIndex) >= usRefHtotalLBound)) &&
           ((GET_HDMI_FREESYNC_ICLK(ucIndex) <= usPixelClkHBound) && (GET_HDMI_FREESYNC_ICLK(ucIndex) >= usPixelClkLBound)))
        {
            *pusVfreqMax = GET_HDMI_FREESYNC_IVFREQ(ucIndex);

            DebugMessageScaler("ucIndex if Drr user define timing ", ucIndex);
            return _HDMI_FREESYNC_WITH_IVF_MAX;
        }
    }

    *pusVfreqMax = 0;
    return _HDMI_FREESYNC_WITHOUT_IVF_MAX;
}
#endif

#if(_HDMI21_VRR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : HDMI Vrr Get IVFmax From Look Up Table
// Input Value  : IVF(unit: 0.1Hz)
// Output Value : _HDMI21_VRR_WITH_IVF_MAX: Get IVF
//--------------------------------------------------
EnumDrrVrrHdmiGetIVF UserInterfaceDisplayHdmiVrrGetIVFmaxFromLut(WORD *pusVfreqMax)
{
    BYTE ucIndex = 0;
    WORD usPixelClk = UserCommonSourceGetInputPixelClk(SysRegionGetInputPort(SysModeGetDisplayTarget()));
    WORD usRefHtotalHBound = 0;
    WORD usRefHtotalLBound = 0;
    WORD usPixelClkHBound = usPixelClk;
    WORD usPixelClkLBound = usPixelClk;
    StructTimingInfo stTimingInfo;

    memset(&stTimingInfo, 0x00, sizeof(stTimingInfo));

    // Read timing info
    SysRegionGetMeasureResultByRegion(SysRegionGetDisplayRegion(_REGION_INDEX_0), &stTimingInfo);

    // Htotal margin
    PDATA_WORD(0) = ((DWORD)_USER_DRR_HTOTAL_MARGIN * stTimingInfo.usHTotal / 100);
    usRefHtotalHBound = (stTimingInfo.usHTotal + PDATA_WORD(0));
    usRefHtotalLBound = (stTimingInfo.usHTotal - PDATA_WORD(0));

    // Pixel clk margin
    PDATA_WORD(0) = ((DWORD)_USER_DRR_CLK_MARGIN * usPixelClk / 100);
    usPixelClkHBound += PDATA_WORD(0);
    usPixelClkLBound -= PDATA_WORD(0);

    for(ucIndex = 0; ucIndex < (sizeof(tDrrVrrHdmiTimingInfo) / sizeof(tDrrVrrHdmiTimingInfo[0])); ucIndex++)
    {
        if((GET_HDMI_VRR_IHWIDTH(ucIndex) == stTimingInfo.usHWidth) && (GET_HDMI_VRR_IVHEIGHT(ucIndex) == stTimingInfo.usVHeight) &&
           ((GET_HDMI_VRR_IHTOTAL(ucIndex) <= usRefHtotalHBound) && (GET_HDMI_VRR_IHTOTAL(ucIndex) >= usRefHtotalLBound)) &&
           ((GET_HDMI_VRR_ICLK(ucIndex) <= usPixelClkHBound) && (GET_HDMI_VRR_ICLK(ucIndex) >= usPixelClkLBound)))
        {
            *pusVfreqMax = GET_HDMI_VRR_IVFREQ(ucIndex);

            DebugMessageScaler("ucIndex if Drr user define timing ", ucIndex);
            return _HDMI21_VRR_WITH_IVF_MAX;
        }
    }

    *pusVfreqMax = 0;
    return _HDMI21_VRR_WITHOUT_IVF_MAX;
}
#endif

//--------------------------------------------------
// Description  : Get extended wait time to active state from user
// Input Value  : None
// Output Value : Extended wait time (ms)
//--------------------------------------------------
WORD UserInterfaceDisplayGetExtendedActiveWaitTime(void)
{
    return 0;
}

#if(_PIXEL_SHIFT_SUPPORT == _ON)
//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserInterfaceDisplaySetPixelOrbitingOff(void)
{
    SET_OSD_PIXELSHIFT_STATUS(_OFF);

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_DDOMAIN)
    // capture H start/end
    UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_START, 0x00, _DB_APPLY_NONE);
    UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_H_END, 0x00, _DB_APPLY_NONE);

    // capture V start/end
    UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_START, 0x00, _DB_APPLY_NONE);
    UserCommonDDomainSetCaptureWindowActiveRegion(_DISPLAY_FORMAT_V_END, 0x00, _DB_APPLY_NONE);

    // Capture Disable
    UserCommonDDomainSetCaptureWindowEnable(_DISABLE, _DB_APPLY_NO_POLLING);
#endif

    g_enumPixelShiftState = _PIXEL_SHIFT_DEFAULT;
}

#if(_FW_PIXEL_SHIFT_MODE == _PIXEL_SHIFT_IN_IDOMAIN)
//--------------------------------------------------
// Description  : Rotation get pixel shift number info
// Input Value  : None
// Output Value : pixel shift v number
//--------------------------------------------------
WORD UserInterfaceDisplayRotationSetPixelShiftNumInfo(void)
{
    return (_PIXEL_SHIFT_NUM_V);
}
#endif
#endif

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
//--------------------------------------------------
// Description  : PIP Sub Adjust Mute or not
// Input Value  : None
// Output Value : EnumPIPSubAdjustMute
//--------------------------------------------------
EnumPIPSubAdjustMute UserInterfaceDisplayPIPSubAdjustMute(void)
{
    return _PIP_SUB_ADJUST_WITHOUT_MUTE;
}
#endif

#if(_DRR_SUPPORT == _ON)
#if(_SEARCH_DRR_IVF_PRIORITY_BY_USER == _ON)
//--------------------------------------------------
// Description  : Get DRR IVF From User
// Input Value  : enumInputPort, usIVfreq == 0x00: not receive DRR source IVF
// Output Value : IVF from user, if not search IVF, return _DRR_GET_IVF_PRIORITY_KERNEL
//--------------------------------------------------
EnumDrrGetIVFPriority UserInterfaceDisplayGetDrrIVFByUser(EnumInputPort enumInputPort, WORD *pusIVfreq)
{
    enumInputPort = enumInputPort;
    *pusIVfreq = *pusIVfreq;

    return _DRR_GET_IVF_PRIORITY_KERNEL;
}
#endif
#endif
#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)

