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
// ID Code      : ScalerColorSpace.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Color/ScalerColor.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_COLOR_IP_COLOR_CONVERT == _ON)
//--------------------------------------------------
// Code Tables of Color Conversion
//--------------------------------------------------
// I Domain Table to 709 YUV Full

BYTE code tCOLOR_CONV_RGBLIMIT_10BITS[] = // RGBLimit -> ITU709_FullYUV_0-1023
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0xFE, 0x03, 0x57, 0x00, 0x56,
    0xFF, 0x77, 0xFE, 0x33, 0x02, 0x55,
    0x02, 0x55, 0xFD, 0xE0, 0xFF, 0xC9,
    0x22, 0x30, 0x17, 0x77, 0x20,
    _END
};

BYTE code tCOLOR_CONV_RGBFULL_10BITS[] = // RGBFull -> ITU709_FullYUV_0-1023
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0xD9, 0x02, 0xDC, 0x00, 0x49,
    0xFF, 0x8A, 0xFE, 0x75, 0x02, 0x00,
    0x02, 0x00, 0xFE, 0x2E, 0xFF, 0xD1,
    0x63, 0x75, 0x30, 0x07, 0x10,
    _END
};


BYTE code tCOLOR_CONV_YUV709LIMIT_10BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0x00, 0x04, 0xAB, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x91,
    0x04, 0x91, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x01, 0x10, 0x00,
    _END
};

BYTE code tCOLOR_CONV_YUV601LIMIT_10BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0xFF, 0x07, 0x04, 0xAB, 0xFF, 0x75,
    0x00, 0x85, 0x00, 0x00, 0x04, 0xA6,
    0x04, 0xAE, 0x00, 0x00, 0x00, 0x57,
    0x37, 0x77, 0x07, 0x60, 0x70,
    _END
};

BYTE code tCOLOR_CONV_YUV601FULL_10BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0xFF, 0x26, 0x04, 0x00, 0xFF, 0x87,
    0x00, 0x75, 0x00, 0x00, 0x04, 0x13,
    0x04, 0x1A, 0x00, 0x00, 0x00, 0x4C,
    0x20, 0x02, 0x01, 0x00, 0x70,
    _END
};

BYTE code tCOLOR_CONV_YUV2020LIMIT_10BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0xFF, 0x90, 0x04, 0xAB, 0x00, 0x15,
    0x00, 0x3B, 0x00, 0x00, 0x04, 0x96,
    0x04, 0x8D, 0x00, 0x00, 0xFF, 0xF2,
    0x67, 0x27, 0x00, 0x30, 0x50,
    _END
};

BYTE code tCOLOR_CONV_YUV2020FULL_10BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0xFF, 0x9E, 0x04, 0x00, 0x00, 0x12,
    0x00, 0x34, 0x00, 0x00, 0x04, 0x04,
    0x03, 0xFC, 0x00, 0x00, 0xFF, 0xF4,
    0x50, 0x54, 0x02, 0x60, 0x20,
    _END
};

BYTE code tCOLOR_CONV_RGBLIMIT_8BITS[] = // RGBLimit -> ITU709_FullYUV_0-1020
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0xFD, 0x03, 0x54, 0x00, 0x56,
    0xFF, 0x77, 0xFE, 0x34, 0x02, 0x54,
    0x02, 0x54, 0xFD, 0xE2, 0xFF, 0xC9,
    0x46, 0x13, 0x31, 0x13, 0x30,
    _END
};

BYTE code tCOLOR_CONV_RGBFULL_8BITS[] = // RGBFull -> ITU709_FullYUV_0-1020
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0xD9, 0x02, 0xDA, 0x00, 0x49,
    0xFF, 0x8B, 0xFE, 0x76, 0x01, 0xFE,
    0x01, 0xFE, 0xFE, 0x30, 0xFF, 0xD1,
    0x12, 0x60, 0x44, 0x42, 0x20,
    _END
};


BYTE code tCOLOR_CONV_YUV709LIMIT_8BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0x00, 0x04, 0xA8, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x8D,
    0x04, 0x8D, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x06, 0x60, 0x00,
    _END
};

BYTE code tCOLOR_CONV_YUV709FULL_8BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0x00, 0x00, 0x03, 0xFD, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0xFD,
    0x03, 0xFD, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    _END
};

BYTE code tCOLOR_CONV_YUV601LIMIT_8BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0xFF, 0x08, 0x04, 0xA8, 0xFF, 0x76,
    0x00, 0x85, 0x00, 0x00, 0x04, 0xA3,
    0x04, 0xAB, 0x00, 0x00, 0x00, 0x57,
    0x13, 0x24, 0x03, 0x20, 0x50,
    _END
};

BYTE code tCOLOR_CONV_YUV601FULL_8BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0xFF, 0x26, 0x03, 0xFD, 0xFF, 0x87,
    0x00, 0x75, 0x00, 0x00, 0x04, 0x10,
    0x04, 0x16, 0x00, 0x00, 0x00, 0x4C,
    0x70, 0x30, 0x00, 0x70, 0x60,
    _END
};

BYTE code tCOLOR_CONV_YUV2020LIMIT_8BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0xFF, 0x91, 0x04, 0xA8, 0x00, 0x15,
    0x00, 0x3B, 0x00, 0x00, 0x04, 0x92,
    0x04, 0x8A, 0x00, 0x00, 0xFF, 0xF2,
    0x13, 0x16, 0x04, 0x00, 0x50,
    _END
};

BYTE code tCOLOR_CONV_YUV2020FULL_8BITS[] =
{
    26, _NON_AUTOINC, (BYTE)P0_9D_RGB2YCC_COEF_DATA,
    0xFF, 0x9E, 0x03, 0xFD, 0x00, 0x12,
    0x00, 0x34, 0x00, 0x00, 0x04, 0x01,
    0x03, 0xF9, 0x00, 0x00, 0xFF, 0xF4,
    0x70, 0x42, 0x02, 0x60, 0x30,
    _END
};

//--------------------------------------------------
// Pointer of I-Domain Code Table
//--------------------------------------------------
BYTE * code tCOLOR_CONV_IDomain[] =
{
    tCOLOR_CONV_RGBLIMIT_10BITS,
    tCOLOR_CONV_RGBFULL_10BITS,
    tCOLOR_CONV_YUV709LIMIT_10BITS,
    tCOLOR_CONV_YUV601LIMIT_10BITS,
    tCOLOR_CONV_YUV601FULL_10BITS,
    tCOLOR_CONV_YUV2020LIMIT_10BITS,
    tCOLOR_CONV_YUV2020FULL_10BITS,
    tCOLOR_CONV_RGBLIMIT_8BITS,
    tCOLOR_CONV_RGBFULL_8BITS,
    tCOLOR_CONV_YUV709LIMIT_8BITS,
    tCOLOR_CONV_YUV709FULL_8BITS,
    tCOLOR_CONV_YUV601LIMIT_8BITS,
    tCOLOR_CONV_YUV601FULL_8BITS,
    tCOLOR_CONV_YUV2020LIMIT_8BITS,
    tCOLOR_CONV_YUV2020FULL_8BITS,
};

//--------------------------------------------------
// Code Tables of D-Domain Color Conversion
//--------------------------------------------------

BYTE code tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_10BITSFIFO[] = // YCC FULL -> RGB FULL
{
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB_R1_ACTIVE1,
    0x04, 0x00, 0xA6, 0x4C, 0xC0, 0xBF,
    0x61, 0xDF, 0x27, 0x6C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
};

BYTE code tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_8BITSFIFO[] = // YCC FULL -> RGB FULL (include 1020 -> 1023)
{
    25, _AUTOINC, (BYTE)P14_A2_SR_YCC2RGB_COEF_K11_MSB_R1_ACTIVE1,
    0x04, 0x03, 0xC6, 0x57, 0x20, 0xC1,
    0xA1, 0xE2, 0x47, 0x79, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00,
    0x02, 0x00, 0x02, 0x00,
    _END
};

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
BYTE code t3P_OUTSIDE_REGION_INDEX_TABLE[][2] =
{
    {_REGION_INDEX_1, _REGION_INDEX_2, }, // Main outside
    {_REGION_INDEX_0, _REGION_INDEX_2, }, // Left/Top outside
    {_REGION_INDEX_0, _REGION_INDEX_1, }, // Right/Bottom outside
};

BYTE code t4P_OUTSIDE_REGION_INDEX_TABLE[][3] =
{
    {_REGION_INDEX_1, _REGION_INDEX_2, _REGION_INDEX_3, }, // LT outside
    {_REGION_INDEX_0, _REGION_INDEX_2, _REGION_INDEX_3, }, // LB outside
    {_REGION_INDEX_0, _REGION_INDEX_1, _REGION_INDEX_3, }, // RT outside
    {_REGION_INDEX_0, _REGION_INDEX_1, _REGION_INDEX_2, }, // RB outside
};

BYTE code tFULL_REGION_INDEX_TABLE[][4] =
{
    {_REGION_INDEX_0, _REGION_INDEX_1, _REGION_INDEX_2, _REGION_INDEX_3, },
};
#endif
//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//-----------------------------------------------------
// Description  : Get M Domain Color Depth
// Input Value  : EnumDisplayRegion
// Output Value : M Domain Color Depth
//-----------------------------------------------------
BYTE ScalerColorSpaceGetMDomainColorDepth(EnumDisplayRegion enumDisplayRegion)
{
    enumDisplayRegion = enumDisplayRegion;

#if(_FRC_SUPPORT == _ON)
    if((enumDisplayRegion != _DISPLAY_RGN_1P) && (enumDisplayRegion != _DISPLAY_RGN_NONE))
    {
        return GET_FRC_RCP_FIFO_COLOR_DEPTH(GET_MDOMAIN_FRC_CTRL_PARAM_INDEX(ScalerRegionGetIndex(enumDisplayRegion)));
    }
    else
#endif
    {
        return ScalerMDomainGetColorDepth();
    }
}

//-----------------------------------------------------
// Description  : Color Conversion Force YUV Status
// Input Value  : EnumDisplayRegion
// Output Value : TRUE/FALSE
//-----------------------------------------------------
bit ScalerColorSpaceForceYUVStatus(EnumDisplayRegion enumDisplayRegion)
{
    if((_ULTRA_VIVID_FUNCTION == _ON) || // Ultra Vivid Support ON
       (_M_DOMAIN_IMG_CMP_SUPPORT == _ON) || // return TRUE when PQC Support ON,PQC input must be YUV format
       (_COLOR_IP_LOCAL_CONTRAST == _ON) || // Local Contrast ON
       (_M_DOMAIN_FORCE_YUV_FORMAT == _ON) ||
       (_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON) || // use color convert to adjust global hue & sat
       (GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE) || // Interlace Mode
       (enumDisplayRegion != _DISPLAY_RGN_1P)) // not 1P mode
    {
        return _TRUE;
    }
    else
    {
        return _FALSE;
    }
}

//--------------------------------------------------
// Description  : Set Colorimetry
// Input Value  : EnumInputPort, bHDTVMode ---> HD TV Mode Flag
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceSetColorimetry(EnumInputPort enumInputPort, bit bHDTVMode)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return;
    }

    if(bHDTVMode == _TRUE)
    {
        SET_COLORIMETRY(enumInputPort, _COLORIMETRY_YCC_ITUR_BT709);
    }
    else
    {
        SET_COLORIMETRY(enumInputPort, _COLORIMETRY_YCC_SMPTE_170M);
    }
}

//--------------------------------------------------
// Description  : Get Colorimetry
// Input Value  : EnumInputPort
// Output Value : EnumColorimetry
//--------------------------------------------------
EnumColorimetry ScalerColorSpaceGetColorimetry(EnumInputPort enumInputPort)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _COLORIMETRY_RGB_SRGB;
    }

    return GET_COLORIMETRY(enumInputPort);
}

//--------------------------------------------------
// Description  : Get Ext Colorimetry
// Input Value  : EnumInputPort
// Output Value : EnumColorimetryExt
//--------------------------------------------------
EnumColorimetryExt ScalerColorSpaceGetExtColorimetry(EnumInputPort enumInputPort)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _COLORIMETRY_EXT_RGB_SRGB;
    }

    return GET_EXT_COLORIMETRY(enumInputPort);
}

//--------------------------------------------------
// Description  : Get Add Ext Colorimetry
// Input Value  : EnumInputPort
// Output Value : EnumColorimetryAddExt
//--------------------------------------------------
EnumColorimetryAddExt ScalerColorSpaceGetAddExtColorimetry(EnumInputPort enumInputPort)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _COLORIMETRY_ADD_EXT_RGB_SMPTE_ST2113_P3D65;
    }

    return GET_ADD_EXT_COLORIMETRY(enumInputPort);
}

//--------------------------------------------------
// Description  : Get RGB Quantization Limit Range
// Input Value  : EnumInputPort
// Output Value : EnumColorRGBQuantization
//--------------------------------------------------
EnumColorRGBQuantization ScalerColorSpaceGetRGBQuantizationRange(EnumInputPort enumInputPort)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _RGB_QUANTIZATION_FULL_RANGE;
    }

    return GET_COLOR_RGB_QUANTIZATION_RANGE(enumInputPort);
}

//--------------------------------------------------
// Description  : Get YCC Quantization Full Range
// Input Value  : EnumInputPort
// Output Value : _TRUE/_FLASE
//--------------------------------------------------
EnumColorYCCQuantization ScalerColorSpaceGetYCCQuantizationRange(EnumInputPort enumInputPort)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _YCC_QUANTIZATION_FULL_RANGE;
    }

    return GET_COLOR_YCC_QUANTIZATION_RANGE(enumInputPort);
}

//--------------------------------------------------
// Description  : Set RGB Quantization Limit Range
// Input Value  : EnumInputPort,
//                EnumRGBQuantLimitRangeStatus ---> Input RGB Range is Full or Limit
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceSetRGBLimitRange(EnumInputPort enumInputPort, EnumRGBQuantLimitRangeStatus enumRGBLimitRange)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return;
    }

    SET_COLOR_RGB_LIMIT_RANGE_USER(enumInputPort, (BYTE)enumRGBLimitRange);
}

//--------------------------------------------------
// Description  : Set YCC Quantization Full Range
// Input Value  : EnumInputPort,
//                EnumYccQuantFullRangeStatus ---> Input YCC Range is Limit or Full
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceSetYCCFullRange(EnumInputPort enumInputPort, EnumYccQuantFullRangeStatus enumYCCFullRange)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return;
    }

    SET_COLOR_YCC_FULL_RANGE_USER(enumInputPort, (BYTE)enumYCCFullRange);
}

//--------------------------------------------------
// Description  : Get I-Domain Color Conv Table
// Input Value  : Display Region, Input Port, Input Color Space
// Output Value : EnumIColorConvTable
//--------------------------------------------------
EnumIColorConvTable ScalerColorSpaceGetRgb2YuvTableIndex(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _COLOR_CONV_NONE;
    }

    if(GET_COLOR_SPACE_RGB(enumColorSpace) == _TRUE) // RGB Input
    {
        if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS) // FIFO 8bits
        {
            if(GET_COLOR_RGB_LIMIT_RANGE_USER(enumInputPort) == _RGB_QUANT_LIMIT_RANGE_TRUE) // Limit RGB Input
            {
                // I-Domain Limit RGB to FullY_0-1020_UV_4-1020
                return _COLOR_CONV_RGBLIMIT_8BITS;
            }
            else// Full RGB Input
            {
                return _COLOR_CONV_RGBFULL_8BITS;
            }
        }
        else// FIFO 10bits
        {
            if(GET_COLOR_RGB_LIMIT_RANGE_USER(enumInputPort) == _RGB_QUANT_LIMIT_RANGE_TRUE)// Limit RGB Input
            {
                return _COLOR_CONV_RGBLIMIT_10BITS;
            }
            else// Full RGB Input
            {
                if(ScalerColorSpaceForceYUVStatus(enumDisplayRegion) == _TRUE)
                {
                    return _COLOR_CONV_RGBFULL_10BITS;
                }
                else
                {
                    return _COLOR_CONV_NONE;
                }
            }
        }
    }
    else// YCC Input
    {
        switch(GET_COLORIMETRY(enumInputPort))
        {
            case _COLORIMETRY_YCC_SMPTE_170M:
            case _COLORIMETRY_YCC_ITUR_BT601:
            case _COLORIMETRY_YCC_XVYCC601:
                if(GET_COLOR_YCC_FULL_RANGE_USER(enumInputPort) == _YCC_QUANT_FULL_RANGE_TRUE)// 601 full
                {
                    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                    {
                        return _COLOR_CONV_YUV601FULL_8BITS;
                    }
                    else
                    {
                        return _COLOR_CONV_YUV601FULL_10BITS;
                    }
                }
                else// 601 limit
                {
                    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                    {
                        return _COLOR_CONV_YUV601LIMIT_8BITS;
                    }
                    else
                    {
                        return _COLOR_CONV_YUV601LIMIT_10BITS;
                    }
                }
                break;

            case _COLORIMETRY_EXT:
                switch(GET_EXT_COLORIMETRY(enumInputPort))
                {
                    case _COLORIMETRY_EXT_YCC_ITUR_BT601:
                    case _COLORIMETRY_EXT_YCC_XVYCC601:
                    case _COLORIMETRY_EXT_YCC_SYCC601:
                    case _COLORIMETRY_EXT_YCC_ADOBEYCC601:
                        if(GET_COLOR_YCC_FULL_RANGE_USER(enumInputPort) == _YCC_QUANT_FULL_RANGE_TRUE)// 601 full
                        {
                            if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                            {
                                return _COLOR_CONV_YUV601FULL_8BITS;
                            }
                            else
                            {
                                return _COLOR_CONV_YUV601FULL_10BITS;
                            }
                        }
                        else// 601 limit
                        {
                            if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                            {
                                return _COLOR_CONV_YUV601LIMIT_8BITS;
                            }
                            else
                            {
                                return _COLOR_CONV_YUV601LIMIT_10BITS;
                            }
                        }

                    case _COLORIMETRY_EXT_YCC_ITUR_BT2020_CL:
                    case _COLORIMETRY_EXT_YCC_ITUR_BT2020_NCL:
                        if(GET_COLOR_YCC_FULL_RANGE_USER(enumInputPort) == _YCC_QUANT_FULL_RANGE_TRUE)// 2020 full
                        {
                            if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                            {
                                return _COLOR_CONV_YUV2020FULL_8BITS;
                            }
                            else
                            {
                                return _COLOR_CONV_YUV2020FULL_10BITS;
                            }
                        }
                        else// 2020 limit
                        {
                            if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                            {
                                return _COLOR_CONV_YUV2020LIMIT_8BITS;
                            }
                            else
                            {
                                return _COLOR_CONV_YUV2020LIMIT_10BITS;
                            }
                        }

                    case _COLORIMETRY_EXT_ADD:
                        switch(GET_ADD_EXT_COLORIMETRY(enumInputPort))
                        {
                            case _COLORIMETRY_ADD_EXT_YCC_ITUR_BT2100:
                                if(GET_COLOR_YCC_FULL_RANGE_USER(enumInputPort) == _YCC_QUANT_FULL_RANGE_TRUE)// 2020 full
                                {
                                    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                                    {
                                        return _COLOR_CONV_YUV2020FULL_8BITS;
                                    }
                                    else
                                    {
                                        return _COLOR_CONV_YUV2020FULL_10BITS;
                                    }
                                }
                                else// 2020 limit
                                {
                                    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                                    {
                                        return _COLOR_CONV_YUV2020LIMIT_8BITS;
                                    }
                                    else
                                    {
                                        return _COLOR_CONV_YUV2020LIMIT_10BITS;
                                    }
                                }
                            default:
                                return _COLOR_CONV_NONE;
                        }

                    case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                    case _COLORIMETRY_EXT_YCC_XVYCC709:
                    default:
                        if(GET_COLOR_YCC_FULL_RANGE_USER(enumInputPort) == _YCC_QUANT_FULL_RANGE_TRUE)// 709 full
                        {
                            if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                            {
                                return _COLOR_CONV_YUV709FULL_8BITS;
                            }
                            else
                            {
                                return _COLOR_CONV_NONE;
                            }
                        }
                        else// 709 limit
                        {
                            if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                            {
                                return _COLOR_CONV_YUV709LIMIT_8BITS;
                            }
                            else
                            {
                                return _COLOR_CONV_YUV709LIMIT_10BITS;
                            }
                        }
                }

            case _COLORIMETRY_YCC_ITUR_BT709:
            case _COLORIMETRY_YCC_XVYCC709:
            default:
                if(GET_COLOR_YCC_FULL_RANGE_USER(enumInputPort) == _YCC_QUANT_FULL_RANGE_TRUE)// 709 full
                {
                    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                    {
                        return _COLOR_CONV_YUV709FULL_8BITS;
                    }
                    else
                    {
                        return _COLOR_CONV_NONE;
                    }
                }
                else// 709 limit
                {
                    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS)
                    {
                        return _COLOR_CONV_YUV709LIMIT_8BITS;
                    }
                    else
                    {
                        return _COLOR_CONV_YUV709LIMIT_10BITS;
                    }
                }
        }
    }
    return _COLOR_CONV_NONE;
}

//--------------------------------------------------
// Description  : Get Ctrl Byte of I-Domain Color Space Conversion
// Input Value  : EnumIColorConvTable
// Output Value : I-Domain Color Space Conversion Ctrl reg value
//--------------------------------------------------
BYTE ScalerColorSpaceGetRgb2YuvCtrlValue(EnumIColorConvTable enumIColorConvTable)
{
    switch(enumIColorConvTable)
    {
        case _COLOR_CONV_YUV601FULL_10BITS:
        case _COLOR_CONV_YUV2020FULL_10BITS:
        case _COLOR_CONV_YUV709FULL_8BITS:
        case _COLOR_CONV_YUV601FULL_8BITS:
        case _COLOR_CONV_YUV2020FULL_8BITS:
            return (_BIT6 | _BIT3 | _BIT2);

        case _COLOR_CONV_YUV709LIMIT_10BITS:
        case _COLOR_CONV_YUV601LIMIT_10BITS:
        case _COLOR_CONV_YUV2020LIMIT_10BITS:
        case _COLOR_CONV_YUV709LIMIT_8BITS:
        case _COLOR_CONV_YUV601LIMIT_8BITS:
        case _COLOR_CONV_YUV2020LIMIT_8BITS:
            return (_BIT6 | _BIT3 | _BIT2 | _BIT1);

        case _COLOR_CONV_RGBFULL_10BITS:
        case _COLOR_CONV_RGBFULL_8BITS:
            return (_BIT6 | _BIT3);

        case _COLOR_CONV_RGBLIMIT_10BITS:
        case _COLOR_CONV_RGBLIMIT_8BITS:
            return (_BIT6 | _BIT4 | _BIT3 | _BIT1);

        case _COLOR_CONV_NONE:
        default:
            // Disable I-Domain RGB2YUV
            return (0x00);
    }
}

//--------------------------------------------------
// Description  : Get I-Domain Color Conv Table Param
// Input Value  : EnumDisplayRegion, EnumInputPort, EnumColorSpace, Table point
// Output Value : TRUE/FALSE
//--------------------------------------------------
bit ScalerColorSpaceGetRgb2YuvTable(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, BYTE *pucIColorConvTable, BYTE *pucIColorConvCtrlValue)
{
    if(pucIColorConvTable != _NULL_POINTER)
    {
        EnumIColorConvTable enumIColorConvTable = ScalerColorSpaceGetRgb2YuvTableIndex(enumDisplayRegion, enumInputPort, enumColorSpace);

        if(enumIColorConvTable != _COLOR_CONV_NONE)
        {
            memcpy(pucIColorConvTable, tCOLOR_CONV_IDomain[enumIColorConvTable], _COLOR_CONV_RGB2YUV_TABLE_SIZE);


            if(pucIColorConvCtrlValue != _NULL_POINTER)
            {
                (*pucIColorConvCtrlValue) = ScalerColorSpaceGetRgb2YuvCtrlValue(enumIColorConvTable);

                return _TRUE;
            }
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Mapping DDomain Color Conversion Page From DDomain Region Before Blending
// Input Value  : EnumDDomainRegion
// Output Value : DDomain Color Conversion Page
//--------------------------------------------------
WORD ScalerColorSpaceConvertDDomainPageMapping(EnumDDomainRegion enumDDomainRegion)
{
    switch(enumDDomainRegion)
    {
        case _DDOMAIN_RGN_R1_A1:
        default:
            return 0x0000U;

        case _DDOMAIN_RGN_R1_A2:
            return 0x4000U;

        case _DDOMAIN_RGN_R2_A1:
            return 0x8000U;

        case _DDOMAIN_RGN_R2_A2:
            return 0x4900U;

        case _DDOMAIN_RGN_R3_A1:
            return 0xD500U;

        case _DDOMAIN_RGN_R3_A2:
            return 0xD600U;
    }
}

//--------------------------------------------------
// Description  : Get if any region in current display mode are in F/B mode
// Input Value  : EnumDisplayRegion
// Output Value : _TRUE if front-back mode should be enabled
//--------------------------------------------------
bit ScalerColorSpaceConvertIDomainFBGetStatus(EnumDisplayRegion enumDisplayRegion)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        switch(enumDisplayRegion)
        {
            case _DISPLAY_RGN_1P:
                return _TRUE;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_PIP_MAIN:
                return _TRUE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
                return _TRUE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
                return _TRUE;

            case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
                return _TRUE;
#endif

            default:
                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get if any region in current display mode are in F/B mode
// Input Value  : EnumDisplayRegion
// Output Value : _TRUE if front-back mode should be enabled
//--------------------------------------------------
bit ScalerColorSpaceConvertDDomainFBGetStatus(EnumDisplayRegion enumDisplayRegion)
{
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        switch(enumDisplayRegion)
        {
            case _DISPLAY_RGN_1P:
                return _TRUE;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_PIP_MAIN:
                return _TRUE;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
            case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
                return _TRUE;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
            case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
                return _TRUE;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_TOP:
            case _DISPLAY_RGN_BOTTOM:
                return _TRUE;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
            case _DISPLAY_RGN_SKEW_T_MAIN:
            case _DISPLAY_RGN_SKEW_B_MAIN:
                return _TRUE;
#endif

            default:
                break;
        }
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : Get D-Domain region in current display mode when in F/B mode
// Input Value  : EnumDisplayRegion
// Output Value : D-Domain region
//--------------------------------------------------
EnumDDomainRegion ScalerColorSpaceConvertDDomainGetBackRegion(EnumDisplayRegion enumDisplayRegion)
{
    switch(enumDisplayRegion)
    {
        case _DISPLAY_RGN_1P:
            return _DDOMAIN_RGN_R3_A1;

#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PIP_MAIN:
            return _DDOMAIN_RGN_R3_A1;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_RGN_EAGLE_SIGHT_MAIN:
            return _DDOMAIN_RGN_R3_A1;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT:
        case _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT:
            return _DDOMAIN_RGN_R3_A1;
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_TOP:
            return _DDOMAIN_RGN_R3_A1;

        case _DISPLAY_RGN_BOTTOM:
            return _DDOMAIN_RGN_R3_A2;
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_RGN_SKEW_T_MAIN:
            return _DDOMAIN_RGN_R3_A1;

        case _DISPLAY_RGN_SKEW_B_MAIN:
            return _DDOMAIN_RGN_R3_A2;
#endif

        default:
            break;
    }

    return _DDOMAIN_RGN_NONE;
}

//--------------------------------------------------
// Description  : Get IDomain Color Conversion Function ON/OFF
// Input Value  : EnumDisplayRegion, EnumInputPort, EnumColorSpace
// Output Value : _TRUE if IDomain Color Conversion should be enabled
//--------------------------------------------------
bit ScalerColorSpaceConvertIDomainEnableStatus(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace)
{
#if(_COLOR_IP_3DDI == _ON)
    // 3DDI ON
    if(GET_3DDI_STATUS(ScalerRegionGetInputDataPath(enumDisplayRegion)) == _TRUE)
    {
        return _FALSE;
    }
#endif

    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_10_BITS)
    {
        if(enumInputPort >= _NO_INPUT_PORT)
        {
            return _FALSE;
        }

        // RGB full with FIFO 10 bit
        if((GET_COLOR_SPACE_RGB(enumColorSpace) == _TRUE) &&
           (GET_COLOR_RGB_LIMIT_RANGE_USER(enumInputPort) == _RGB_QUANT_LIMIT_RANGE_FALSE))
        {
            if(ScalerColorSpaceForceYUVStatus(enumDisplayRegion) == _FALSE)
            {
                return _FALSE;
            }
            else
            {
                return _TRUE;
            }
        }

        // 709 full with FIFO 10 bit
        if((GET_COLOR_SPACE_RGB(enumColorSpace) == _FALSE) &&
           (GET_COLOR_YCC_FULL_RANGE_USER(enumInputPort) == _YCC_QUANT_FULL_RANGE_TRUE))
        {
            switch(GET_COLORIMETRY(enumInputPort))
            {
                case _COLORIMETRY_YCC_ITUR_BT709:
                case _COLORIMETRY_YCC_XVYCC709:
                // RGB cases for unmatched source and OSD setting
                case _COLORIMETRY_RGB_SRGB:
                case _COLORIMETRY_RGB_ADOBERGB:
                case _COLORIMETRY_RGB_XRRGB:
                case _COLORIMETRY_RGB_SCRGB:
                case _COLORIMETRY_RGB_DCI_P3:
                case _COLORIMETRY_RGB_COLOR_PROFILE:
                case _COLORIMETRY_Y_ONLY:
                case _COLORIMETRY_RAW:
                    return _FALSE;

                case _COLORIMETRY_EXT:
                    switch(GET_EXT_COLORIMETRY(enumInputPort))
                    {
                        case _COLORIMETRY_EXT_YCC_ITUR_BT709:
                        case _COLORIMETRY_EXT_YCC_XVYCC709:
                        // RGB cases for unmatched source and OSD setting
                        case _COLORIMETRY_EXT_RGB_SRGB:
                        case _COLORIMETRY_EXT_RGB_XRRGB:
                        case _COLORIMETRY_EXT_RGB_SCRGB:
                        case _COLORIMETRY_EXT_RGB_ADOBERGB:
                        case _COLORIMETRY_EXT_RGB_DCI_P3:
                        case _COLORIMETRY_EXT_RGB_CUSTOM_COLOR_PROFILE:
                        case _COLORIMETRY_EXT_RGB_ITUR_BT2020:
                        case _COLORIMETRY_EXT_Y_ONLY_DICOM_PART14:
                        case _COLORIMETRY_EXT_RAW_CUSTOM_COLOR_PROFILE:
                            return _FALSE;
                        default:
                            return _TRUE;
                    }
                default:
                    return _TRUE;
            }
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Get DDomain Color Conversion Function ON/OFF
// Input Value  :  EnumDisplayRegion, EnumInputPort, EnumColorSpace
// Output Value : _TRUE if DDomain Color Conversion should be enabled
//--------------------------------------------------
bit ScalerColorSpaceConvertDDomainEnableStatus(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace)
{
    if(enumInputPort >= _NO_INPUT_PORT)
    {
        return _FALSE;
    }

    // FIFO 10bits && Full RGB -> Full RGB
    if((GET_COLOR_SPACE_RGB(enumColorSpace) == _TRUE) &&
       (ScalerColorSpaceForceYUVStatus(enumDisplayRegion) == _FALSE) &&
       (GET_COLOR_RGB_LIMIT_RANGE_USER(enumInputPort) == _RGB_QUANT_LIMIT_RANGE_FALSE) &&
       (ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_10_BITS))
    {
        return _FALSE;
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Color Space Conversion function On/Off
// Input Value  : Display Region, Input Port, Input Color Space, EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvert(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, EnumDBApply enumDBApply)
{
    BYTE ucCnt = 0;
    WORD usIdomainPage = 0;
    WORD usDdomainPage = 0;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
    BYTE ucDVSCnt = ScalerColorSpaceConvertIDomainWaitEventForAutoBlockToggle();
#endif

#if(_HW_I_DOMAIN_PATH_COUNT > 1)
    usIdomainPage = ScalerRegionGetIDomainRegisterPage((EnumSelRegion)enumDisplayRegion);
#endif

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerRegionGetDDomainRegion(enumDisplayRegion));
#endif

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ucCnt == 0)
        {
            // Load I-Domain RGB2YUV Table
            ScalerColorSpaceLoadRgb2YuvTable(enumDisplayRegion, enumInputPort, enumColorSpace);

            //////////////////////////////
            // I-Domain Color Conversion//
            //////////////////////////////
            if(ScalerColorSpaceConvertIDomainEnableStatus(enumDisplayRegion, enumInputPort, enumColorSpace) == _FALSE)
            {
                // Disable I-Domain RGB2YUV
                ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, 0x00);
            }
            else
            {
                // Enable I-Domain RGB2YUV
                ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, _BIT0);
            }

            //////////////////////////////
            // D-Domain Color Conversion//
            //////////////////////////////

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
            ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(ucDVSCnt);
#endif

            if(ScalerColorSpaceConvertDDomainEnableStatus(enumDisplayRegion, enumInputPort, enumColorSpace) == _FALSE)
            {
                // Disable D-Domain YUV2RGB
                ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, 0x00);
            }
            else
            {
                // Enable D-Domain YUV2RGB
                ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, _BIT0);
            }
        }
        else // front back mode
        {
            if(ScalerColorSpaceConvertIDomainFBGetStatus(enumDisplayRegion) == _TRUE)
            {
                // Set Sub1 regs
                usIdomainPage = _REG_SUB1_PAGE;

                //////////////////////////////
                // I-Domain Color Conversion//
                //////////////////////////////
                if(ScalerColorSpaceConvertIDomainEnableStatus(enumDisplayRegion, enumInputPort, enumColorSpace) == _FALSE)
                {
                    // Disable I-Domain RGB2YUV
                    ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, 0x00);
                }
                else
                {
                    // Enable I-Domain RGB2YUV
                    ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, _BIT0);
                }
            }

            if(ScalerColorSpaceConvertDDomainFBGetStatus(enumDisplayRegion) == _TRUE) // DDomain FB mode
            {
                // Set D-Domain Back regs
                usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerColorSpaceConvertDDomainGetBackRegion(enumDisplayRegion));
                //////////////////////////////
                // D-Domain Color Conversion//
                //////////////////////////////

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
                ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(ucDVSCnt);
#endif

                if(ScalerColorSpaceConvertDDomainEnableStatus(enumDisplayRegion, enumInputPort, enumColorSpace) == _FALSE)
                {
                    // Disable D-Domain YUV2RGB
                    ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, 0x00);
                }
                else
                {
                    // Enable D-Domain YUV2RGB
                    ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, _BIT0);
                }
            }
        }
    }

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
    if(ScalerFRCGetAutoBlkToggleEn() == _DISABLE)
#endif
    {
        if(GET_INPUT_TIMING_INTERLACE_FLG() == _FALSE)
        {
            if(enumDBApply == _DB_APPLY_NO_POLLING)
            {
                enumDBApply = _DB_APPLY_POLLING;
            }

            ScalerGlobalIDDomainDBApply(enumInputDataPath, enumDBApply);
        }
        else
        {
#if(_3DDI_FUNCTION == _ON)
            if(GET_3DDI_STATUS(enumInputDataPath) == _TRUE)
            {
                if(enumDBApply == _DB_APPLY_NO_POLLING)
                {
                    enumDBApply = _DB_APPLY_POLLING;
                }

                ScalerGlobalIDDomainDBApply(enumInputDataPath, enumDBApply);
            }
            else
#endif
            {
                ScalerGlobalIDomainDBApply(enumInputDataPath, enumDBApply);
                ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), enumDBApply);
            }
        }
    }
}

//--------------------------------------------------
// Description  : D Color Conversion Status
// Input Value  : Display Region
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
EnumFunctionOnOFF ScalerColorSpaceConvertDDomainCheckEnableStatus(EnumDisplayRegion enumDisplayRegion)
{
    WORD usDdomainPage = 0x0000U;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerRegionGetDDomainRegion(enumDisplayRegion));
#endif

    if(ScalerGetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), _BIT0) == _TRUE)
    {
        return _FUNCTION_ON;
    }
    else
    {
        return _FUNCTION_OFF;
    }
}

//--------------------------------------------------
// Description  : D-Domain Color Space Conversion function On/Off
// Input Value  : EnumDisplayRegion,
//                bOn ---> function On/Off
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertDDomainEnable(EnumDisplayRegion enumDisplayRegion, bit bOn)
{
    BYTE ucCnt = 0;
#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    WORD usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerRegionGetDDomainRegion(enumDisplayRegion));
#endif

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ucCnt == 1) // FB Mode
        {
            // FB Mode
            if(ScalerColorSpaceConvertDDomainFBGetStatus(enumDisplayRegion) == _TRUE)
            {
                // Get D-Domain Page in Back Mode
                usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerColorSpaceConvertDDomainGetBackRegion(enumDisplayRegion));
            }
            else
            {
                break;
            }
        }

        // Set D-Domain YUV2RGB Enable Bit ON/OFF
        ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, (BYTE)bOn);
    }

    ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), _DB_APPLY_POLLING);
}

//--------------------------------------------------
// Description  : I-Domain Color Space Conversion function On/Off
// Input Value  : EnumDisplayRegion
//                bOn ---> function On/Off
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertIDomainEnable(EnumDisplayRegion enumDisplayRegion, bit bOn)
{
    BYTE ucCnt = 0;
    WORD usIdomainPage = _REG_MAIN1_PAGE;
#if(_HW_I_DOMAIN_PATH_COUNT > 1)
    usIdomainPage = ScalerRegionGetIDomainRegisterPage((EnumSelRegion)enumDisplayRegion);
#endif

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ucCnt == 1)
        {
            // FB Mode
            if(ScalerColorSpaceConvertIDomainFBGetStatus(enumDisplayRegion) == _TRUE)
            {
                usIdomainPage = _REG_SUB1_PAGE;
            }
            else
            {
                break;
            }
        }

        // Set I Domain RGB2YCC Enable Bit ON/OFF
        ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, (BYTE)bOn);
    }

    // Set Global I Domain DBApply Path
    ScalerGlobalIDomainDBApply(ScalerRegionGetInputDataPath(enumDisplayRegion), _DB_APPLY_POLLING);
}

//--------------------------------------------------
// Description  : Load Table for Color Space Conversion
// Input Value  : EnumDisplayRegion, EnumInputPort, EnumColorSpace
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceLoadRgb2YuvTable(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace)
{
    WORD usPage = _REG_MAIN1_PAGE;
    WORD usBackPage = usPage;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    EnumIColorConvTable enumIColorConvTable = ScalerColorSpaceGetRgb2YuvTableIndex(enumDisplayRegion, enumInputPort, enumColorSpace);
    BYTE ucCtrlValue = ScalerColorSpaceGetRgb2YuvCtrlValue(enumIColorConvTable);

#if(_HW_I_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetIDomainRegisterPage((EnumSelRegion)enumDisplayRegion);
    usBackPage = usPage;
#endif

    // FB Mode
    if(ScalerColorSpaceConvertIDomainFBGetStatus(enumDisplayRegion) == _TRUE)
    {
        usBackPage = _REG_SUB1_PAGE;
    }

    if(enumIColorConvTable != _COLOR_CONV_NONE)
    {
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, enumInputDataPath);

        // Set I-Domain color conversion Ctrl Reg
        ScalerSetBit((P0_9C_RGB2YCC_CTRL + usPage), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ucCtrlValue);

        // Load I-Domain color conversion table
        ScalerBurstWrite(tCOLOR_CONV_IDomain[enumIColorConvTable], _COLOR_CONV_RGB2YUV_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), (P0_9C_RGB2YCC_CTRL + usPage), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // Disable I-Domain color conversion coefficient Access
        ScalerSetBit((P0_9C_RGB2YCC_CTRL + usPage), ~_BIT3, 0x00);

        if(usBackPage != usPage) // FB Mode
        {
            // Set I-Domain color conversion Ctrl Reg
            ScalerSetBit((P0_9C_RGB2YCC_CTRL + usBackPage), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ucCtrlValue);

            // Load I-Domain color conversion table
            ScalerBurstWrite(tCOLOR_CONV_IDomain[enumIColorConvTable], _COLOR_CONV_RGB2YUV_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), (P0_9C_RGB2YCC_CTRL + usBackPage), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

            // Disable I-Domain color conversion coefficient Access
            ScalerSetBit((P0_9C_RGB2YCC_CTRL + usBackPage), ~_BIT3, 0x00);
        }
    }
    else
    {
        // Disable I-Domain RGB2YUV
        ScalerSetBit((P0_9C_RGB2YCC_CTRL + usPage), ~_BIT0, 0x00);

        if(usBackPage != usPage) // FB Mode
        {
            ScalerSetBit((P0_9C_RGB2YCC_CTRL + usBackPage), ~_BIT0, 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Color Space Load YUV2RGB table
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceLoadYuv2RgbTable(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply)
{
    WORD usDdomainPage = 0;
    BYTE *pucYUV2RGBTable = _NULL_POINTER;
    BYTE ucCnt = 0;
    enumDBApply = enumDBApply;

#if(_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_1)
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
#endif

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerRegionGetDDomainRegion(enumDisplayRegion));
#endif

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ucCnt == 0)
        {
            if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS) // FIFO 8Bits
            {
                pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_8BITSFIFO;
            }
            else // FIFO 10Bits
            {
                pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_10BITSFIFO;
            }

            ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~(_BIT5 | _BIT4 | _BIT2 | _BIT1), _BIT2);


            ScalerBurstWrite(pucYUV2RGBTable, _COLOR_CONV_YUV2RGB_TABLE_SIZE,
                             GET_CURRENT_BANK_NUMBER(), (P14_A2_SR_YCC2RGB_COEF_K11_MSB_R1_ACTIVE1 + usDdomainPage),
                             _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
        }
        else // FB mode, back Region
        {
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
            if(ScalerColorSpaceConvertDDomainFBGetStatus(enumDisplayRegion) == _TRUE)
            {
                usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerColorSpaceConvertDDomainGetBackRegion(enumDisplayRegion));
                if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS) // FIFO 8Bits
                {
                    pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_8BITSFIFO;
                }
                else // FIFO 10Bits
                {
                    pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_10BITSFIFO;
                }

                ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~(_BIT5 | _BIT4 | _BIT2 | _BIT1), _BIT2);


                ScalerBurstWrite(pucYUV2RGBTable, _COLOR_CONV_YUV2RGB_TABLE_SIZE,
                                 GET_CURRENT_BANK_NUMBER(), (P14_A2_SR_YCC2RGB_COEF_K11_MSB_R1_ACTIVE1 + usDdomainPage),
                                 _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);
            }
#endif
        }
    }

#if(_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_1)
#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
    if(ScalerFRCGetAutoBlkToggleEn() == _DISABLE)
#endif
    {
        if(GET_INPUT_TIMING_INTERLACE_FLG() == _FALSE)
        {
            if(enumDBApply == _DB_APPLY_NO_POLLING)
            {
                enumDBApply = _DB_APPLY_POLLING;
            }

            ScalerGlobalIDDomainDBApply(enumInputDataPath, enumDBApply);
        }
        else
        {
#if(_3DDI_FUNCTION == _ON)
            if(GET_3DDI_STATUS(enumInputDataPath) == _TRUE)
            {
                if(enumDBApply == _DB_APPLY_NO_POLLING)
                {
                    enumDBApply = _DB_APPLY_POLLING;
                }

                ScalerGlobalIDDomainDBApply(enumInputDataPath, enumDBApply);
            }
            else
#endif
            {
                ScalerGlobalIDomainDBApply(enumInputDataPath, enumDBApply);
                ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), enumDBApply);
            }
        }
    }
#endif
}

#if(_COLOR_IP_DM == _ON)
//--------------------------------------------------
// Description  : Get I/D Domain Color Conversion Function ON/OFF for DM ON
// Input Value  : EnumDisplayRegion
// Output Value : _TRUE if I/D Domain Color Conversion should be enabled
//--------------------------------------------------
bit ScalerColorSpaceConvertEnableStatusDM(EnumDisplayRegion enumDisplayRegion)
{
    if((ScalerColorSpaceForceYUVStatus(enumDisplayRegion) == _FALSE) &&
       (ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_10_BITS))
    {
        return _FALSE;
    }
    else
    {
        return _TRUE;
    }
}

//--------------------------------------------------
// Description  : Get I-Domain Color Conv Table for DM ON
// Input Value  : Display Region
// Output Value : EnumIColorConvTable
//--------------------------------------------------
EnumIColorConvTable ScalerColorSpaceGetRgb2YuvTableIndexDM(EnumDisplayRegion enumDisplayRegion)
{
    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS) // FIFO 8bits
    {
        return _COLOR_CONV_RGBFULL_8BITS;
    }
    else// FIFO 10bits
    {
        if(ScalerColorSpaceForceYUVStatus(enumDisplayRegion) == _TRUE)
        {
            return _COLOR_CONV_RGBFULL_10BITS;
        }
        else
        {
            return _COLOR_CONV_NONE;
        }
    }
}

//--------------------------------------------------
// Description  : Color Space Conversion function On/Off for DM ON
// Input Value  : Display Region, EnumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertDM(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply)
{
    BYTE ucCnt = 0;
    WORD usIdomainPage = 0;
    WORD usDdomainPage = 0;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
    BYTE ucDVSCnt = ScalerColorSpaceConvertIDomainWaitEventForAutoBlockToggle();
#endif

#if(_HW_I_DOMAIN_PATH_COUNT > 1)
    usIdomainPage = ScalerRegionGetIDomainRegisterPage((EnumSelRegion)enumDisplayRegion);
#endif

#if(_HW_D_DOMAIN_PATH_COUNT > 1)
    usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerRegionGetDDomainRegion(enumDisplayRegion));
#endif

    for(ucCnt = 0; ucCnt < 2; ucCnt++)
    {
        if(ucCnt == 0)
        {
            // Load I-Domain RGB2YUV Table
            ScalerColorSpaceLoadRgb2YuvTableDM(enumDisplayRegion);

            //////////////////////////////
            // I-Domain Color Conversion//
            //////////////////////////////
            if(ScalerColorSpaceConvertEnableStatusDM(enumDisplayRegion) == _FALSE)
            {
                // Disable I-Domain RGB2YUV
                ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, 0x00);
            }
            else
            {
                // Enable I-Domain RGB2YUV
                ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, _BIT0);
            }

            //////////////////////////////
            // D-Domain Color Conversion//
            //////////////////////////////

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
            ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(ucDVSCnt);
#endif

            if(ScalerColorSpaceConvertEnableStatusDM(enumDisplayRegion) == _FALSE)
            {
                // Disable D-Domain YUV2RGB
                ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, 0x00);
            }
            else
            {
                // Enable D-Domain YUV2RGB
                ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, _BIT0);
            }
        }
        else // front back mode
        {
            if(ScalerColorSpaceConvertIDomainFBGetStatus(enumDisplayRegion) == _TRUE)
            {
                // Set Sub1 regs
                usIdomainPage = _REG_SUB1_PAGE;

                //////////////////////////////
                // I-Domain Color Conversion//
                //////////////////////////////
                if(ScalerColorSpaceConvertEnableStatusDM(enumDisplayRegion) == _FALSE)
                {
                    // Disable I-Domain RGB2YUV
                    ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, 0x00);
                }
                else
                {
                    // Enable I-Domain RGB2YUV
                    ScalerSetBit((P0_9C_RGB2YCC_CTRL + usIdomainPage), ~_BIT0, _BIT0);
                }
            }

            if(ScalerColorSpaceConvertDDomainFBGetStatus(enumDisplayRegion) == _TRUE) // DDomain FB mode
            {
                // Set D-Domain Back regs
                usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerColorSpaceConvertDDomainGetBackRegion(enumDisplayRegion));
                //////////////////////////////
                // D-Domain Color Conversion//
                //////////////////////////////

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
                ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(ucDVSCnt);
#endif

                if(ScalerColorSpaceConvertEnableStatusDM(enumDisplayRegion) == _FALSE)
                {
                    // Disable D-Domain YUV2RGB
                    ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, 0x00);
                }
                else
                {
                    // Enable D-Domain YUV2RGB
                    ScalerSetBit((P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage), ~_BIT0, _BIT0);
                }
            }
        }
    }

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
    if(ScalerFRCGetAutoBlkToggleEn() == _DISABLE)
#endif
    {
        if(enumDBApply == _DB_APPLY_NO_POLLING)
        {
            enumDBApply = _DB_APPLY_POLLING;
        }

        ScalerGlobalIDDomainDBApply(enumInputDataPath, enumDBApply);
    }
}

//--------------------------------------------------
// Description  : Load Table for Color Space Conversion for DM ON
// Input Value  : EnumDisplayRegion
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceLoadRgb2YuvTableDM(EnumDisplayRegion enumDisplayRegion)
{
    WORD usPage = _REG_MAIN1_PAGE;
    WORD usBackPage = usPage;
    EnumInputDataPath enumInputDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    EnumIColorConvTable enumIColorConvTable = ScalerColorSpaceGetRgb2YuvTableIndexDM(enumDisplayRegion);
    BYTE ucCtrlValue = ScalerColorSpaceGetRgb2YuvCtrlValue(enumIColorConvTable);

#if(_HW_I_DOMAIN_PATH_COUNT > 1)
    usPage = ScalerRegionGetIDomainRegisterPage((EnumSelRegion)enumDisplayRegion);
    usBackPage = usPage;
#endif

    // FB Mode
    if(ScalerColorSpaceConvertIDomainFBGetStatus(enumDisplayRegion) == _TRUE)
    {
        usBackPage = _REG_SUB1_PAGE;
    }

    if(enumIColorConvTable != _COLOR_CONV_NONE)
    {
        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, enumInputDataPath);

        // Set I-Domain color conversion Ctrl Reg
        ScalerSetBit((P0_9C_RGB2YCC_CTRL + usPage), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ucCtrlValue);

        // Load I-Domain color conversion table
        ScalerBurstWrite(tCOLOR_CONV_IDomain[enumIColorConvTable], _COLOR_CONV_RGB2YUV_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), (P0_9C_RGB2YCC_CTRL + usPage), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

        // Disable I-Domain color conversion coefficient Access
        ScalerSetBit((P0_9C_RGB2YCC_CTRL + usPage), ~_BIT3, 0x00);

        if(usBackPage != usPage) // FB Mode
        {
            // Set I-Domain color conversion Ctrl Reg
            ScalerSetBit((P0_9C_RGB2YCC_CTRL + usBackPage), ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), ucCtrlValue);

            // Load I-Domain color conversion table
            ScalerBurstWrite(tCOLOR_CONV_IDomain[enumIColorConvTable], _COLOR_CONV_RGB2YUV_TABLE_SIZE, GET_CURRENT_BANK_NUMBER(), (P0_9C_RGB2YCC_CTRL + usBackPage), _BURSTWRITE_COMMAND, _BURSTWRITE_FROM_FLASH);

            // Disable I-Domain color conversion coefficient Access
            ScalerSetBit((P0_9C_RGB2YCC_CTRL + usBackPage), ~_BIT3, 0x00);
        }
    }
    else
    {
        // Disable I-Domain RGB2YUV
        ScalerSetBit((P0_9C_RGB2YCC_CTRL + usPage), ~_BIT0, 0x00);

        if(usBackPage != usPage) // FB Mode
        {
            ScalerSetBit((P0_9C_RGB2YCC_CTRL + usBackPage), ~_BIT0, 0x00);
        }
    }
}
#endif

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Wait for event before setting I color space for FRC auto block toggle case
// Input Value  : None
// Output Value : DVS current count
//--------------------------------------------------
BYTE ScalerColorSpaceConvertIDomainWaitEventForAutoBlockToggle(void)
{
    BYTE ucDVSCnt = 0;

    if(ScalerFRCGetAutoBlkToggleEn() == _ENABLE)
    {
        if(GET_FS_ACTIVE_INFO_DVF_SELECT() == _2_5_IVF)
        {
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
            ucDVSCnt = ScalerGetDataPortSingleByte(P0_2A_DISPLAY_FORMAT_ADDR_PORT, _P0_2B_PT_28_FREE_RUN_DVS_CNT);
        }

        ScalerTimerWaitForIDomainEvent(_EVENT_IEN_STOP, GET_MDOMAIN_INPUT_DATA_PATH());
    }

    return ucDVSCnt;
}

//--------------------------------------------------
// Description  : Wait for event before setting D color space for FRC auto block toggle case
// Input Value  : DVS current count
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(BYTE ucDVSCnt)
{
    if(ScalerFRCGetAutoBlkToggleEn() == _ENABLE)
    {
        switch(GET_FS_ACTIVE_INFO_DVF_SELECT())
        {
            case _3_IVF:
            default:

                ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                break;

            case _2_5_IVF:

                switch(ucDVSCnt)
                {
                    case 0:
                    case 1:
                    default:

                        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);
                        break;

                    case 2:
                    case 3:
                    case 4:

                        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_START);

                        break;
                }
                break;
        }
    }
}
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Night Sniper Function On/Off
// Input Value  : enumSelRegion, bOn, bOn_Inverse, bOn_Apply_both
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertNightSniperEnable(EnumSelRegion enumSelRegion, bit bOn, bit bOn_Inverse, bit bOn_Apply_both)
{
    BYTE ucIndex = 0;
    WORD usDdomainPage = 0;
    WORD usDdomainPage2 = 0;
    BYTE pucNightSniperGain[6] = {0};
    BYTE pucNightSniperGain2[6] = {0};
    EnumDisplayRegion enumDisplayRegion = _DISPLAY_RGN_NONE;
    EnumDisplayRegion enumDisplayRegion2 = _DISPLAY_RGN_NONE;

    for(ucIndex = 0; ucIndex < 2; ucIndex++)
    {
        if(ucIndex == 0)
        {
            enumDisplayRegion = ScalerColorSpaceConvertGetNightSniperRegionStatus(ucIndex, enumSelRegion);
            usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerRegionGetDDomainRegion(enumDisplayRegion));

            if(bOn == _ON)
            {
                ScalerColorSpaceConvertNightSniperSetGain(enumDisplayRegion, pucNightSniperGain);
            }
            else
            {
                ScalerColorSpaceConvertNightSniperRecover(enumDisplayRegion, pucNightSniperGain);
            }
        }
        else
        {
            enumDisplayRegion2 = ScalerColorSpaceConvertGetNightSniperRegionStatus(ucIndex, enumSelRegion);
            if(enumDisplayRegion2 == _DISPLAY_RGN_NONE)
            {
                break;
            }
            else
            {
                usDdomainPage2 = ScalerColorSpaceConvertDDomainPageMapping(ScalerRegionGetDDomainRegion(enumDisplayRegion2));
                if(bOn_Inverse == _ON)
                {
                    ScalerColorSpaceConvertNightSniperSetGain(enumDisplayRegion2, pucNightSniperGain2);
                }
                else
                {
                    ScalerColorSpaceConvertNightSniperRecover(enumDisplayRegion2, pucNightSniperGain2);
                }
            }
        }
    }

#if(_HW_COLOR_CONVERSION_DB_TYPE == _COLOR_CONVERSION_DB_GEN_0)
    // only _DB_GEN_0 HW D_Color_Conv without DB, need to wait DEN_STOP; _DB_GEN_1 HW with DB not need to
    ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
#endif

    if(enumDisplayRegion != _DISPLAY_RGN_NONE)
    {
        ScalerWrite(P14_B2_SR_YCC2RGB_R_GAIN_MSB_R1_ACTIVE1 + usDdomainPage, _COLOR_CONV_NIGHT_SNIPER_TABLE_SIZE, pucNightSniperGain, _AUTOINC);

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
        if(ScalerColorSpaceConvertDDomainFBGetStatus(enumDisplayRegion) == _TRUE) // DDomain FB mode
        {
            // Set D-Domain Back regs
            ScalerWrite(P14_B2_SR_YCC2RGB_R_GAIN_MSB_R1_ACTIVE1 + _COLOR_CONV_NIGHT_SNIPER_BACK_PAGESHIFT, _COLOR_CONV_NIGHT_SNIPER_TABLE_SIZE, pucNightSniperGain, _AUTOINC);
        }
#endif
    }

    if((enumDisplayRegion2 != _DISPLAY_RGN_NONE) && (bOn_Apply_both != _OFF))
    {
        ScalerWrite(P14_B2_SR_YCC2RGB_R_GAIN_MSB_R1_ACTIVE1 + usDdomainPage2, _COLOR_CONV_NIGHT_SNIPER_TABLE_SIZE, pucNightSniperGain2, _AUTOINC);
    }
}

//--------------------------------------------------
// Description  : Night Sniper Function Set D Color Conv Gain
// Input Value  : enumDisplayRegion, pucNightSniperGain
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertNightSniperSetGain(EnumDisplayRegion enumDisplayRegion, BYTE *pucNightSniperGain)
{
    BYTE *pucYUV2RGBTable = _NULL_POINTER;
    WORD usGainR = 0;
    WORD usGainG = 0;
    WORD usGainB = 0;

    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS) // FIFO 8Bits
    {
        pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_8BITSFIFO;
    }
    else // FIFO 10Bits
    {
        pucYUV2RGBTable = tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_10BITSFIFO;
    }

    ScalerFlashRead(GET_CURRENT_BANK_NUMBER(), &pucYUV2RGBTable[_COLOR_CONV_NIGHT_SNIPER_TABLE_OFFSET], _COLOR_CONV_NIGHT_SNIPER_TABLE_SIZE, pData);

    usGainR = ((pData[0] & 0x03) << 9) | (pData[1] << 1) | ((pData[0] & 0x80) >> 7);
    usGainG = ((pData[2] & 0x03) << 9) | (pData[3] << 1) | ((pData[2] & 0x80) >> 7);
    usGainB = ((pData[4] & 0x03) << 9) | (pData[5] << 1) | ((pData[4] & 0x80) >> 7);

    usGainR = (WORD)(((DWORD)usGainR * _COLOR_CONV_NIGHT_SNIPER_GAIN_R + 512) >> 10);
    usGainG = (WORD)(((DWORD)usGainG * _COLOR_CONV_NIGHT_SNIPER_GAIN_G + 512) >> 10);
    usGainB = (WORD)(((DWORD)usGainB * _COLOR_CONV_NIGHT_SNIPER_GAIN_B + 512) >> 10);

    pucNightSniperGain[0] = (BYTE)(((usGainR >> 9) & 0x03) | ((usGainR & 0x01) << 7));
    pucNightSniperGain[1] = (BYTE)((usGainR >> 1) & 0xFF);
    pucNightSniperGain[2] = (BYTE)(((usGainG >> 9) & 0x03) | ((usGainG & 0x01) << 7));
    pucNightSniperGain[3] = (BYTE)((usGainG >> 1) & 0xFF);
    pucNightSniperGain[4] = (BYTE)(((usGainB >> 9) & 0x03) | ((usGainB & 0x01) << 7));
    pucNightSniperGain[5] = (BYTE)((usGainB >> 1) & 0xFF);
}

//--------------------------------------------------
// Description  : Night Sniper Function Recover
// Input Value  : enumDisplayRegion, pucNightSniperGain
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertNightSniperRecover(EnumDisplayRegion enumDisplayRegion, BYTE *pucNightSniperGain)
{
    if(ScalerColorSpaceGetMDomainColorDepth(enumDisplayRegion) == _COLOR_DEPTH_8_BITS) // FIFO 8Bits
    {
        ScalerFlashRead(GET_CURRENT_BANK_NUMBER(), &tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_8BITSFIFO[_COLOR_CONV_NIGHT_SNIPER_TABLE_OFFSET], _COLOR_CONV_NIGHT_SNIPER_TABLE_SIZE, pucNightSniperGain);
    }
    else // FIFO 10Bits
    {
        ScalerFlashRead(GET_CURRENT_BANK_NUMBER(), &tCOLOR_CONV_YUV2RGB_ITU709_YUVFULL_10BITSFIFO[_COLOR_CONV_NIGHT_SNIPER_TABLE_OFFSET], _COLOR_CONV_NIGHT_SNIPER_TABLE_SIZE, pucNightSniperGain);
    }
}

//--------------------------------------------------
// Description  : Get Night Sniper Display Region
// Input Value  : ucIndex, enumSelRegion
// Output Value : enumDisplayRegion
//--------------------------------------------------
EnumDisplayRegion ScalerColorSpaceConvertGetNightSniperRegionStatus(BYTE ucIndex, EnumSelRegion enumSelRegion)
{
    // _FULL_REGION case need to set Main/Sub two setting, index = 0: Main setting; index = 1: Sub setting
    if((enumSelRegion == _FULL_REGION) || (enumSelRegion == _DEMO_INSIDE) || (enumSelRegion == _DEMO_OUTSIDE))
    {
        switch(ucIndex)
        {
            case 0:
                switch(GET_DISPLAY_MODE())
                {
                    case _DISPLAY_MODE_1P:
                        return _DISPLAY_RGN_1P;
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP:
                        return _DISPLAY_RGN_PIP_MAIN;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                        return _DISPLAY_RGN_EAGLE_SIGHT_MAIN;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                        return _DISPLAY_RGN_PBP_LR_EQUAL_LEFT;
                    case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                        return _DISPLAY_RGN_PBP_LR_L_LARGE_LEFT;
                    case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                        return _DISPLAY_RGN_PBP_LR_R_LARGE_RIGHT;
#endif

                    default:
                        return _DISPLAY_RGN_NONE;
                }

            case 1:
                switch(GET_DISPLAY_MODE())
                {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP:
                        return _DISPLAY_RGN_PIP_SUB;
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
                        return _DISPLAY_RGN_EAGLE_SIGHT_SUB;
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
                    case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
                        return _DISPLAY_RGN_PBP_LR_EQUAL_RIGHT;
                    case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
                        return _DISPLAY_RGN_PBP_LR_L_LARGE_RIGHT;
                    case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
                        return _DISPLAY_RGN_PBP_LR_R_LARGE_LEFT;
#endif
                    case _DISPLAY_MODE_1P:
                    default:
                        return _DISPLAY_RGN_NONE;
                }

            default:
                return _DISPLAY_RGN_NONE;
        }
    }

    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
#endif
            if(ucIndex == 0)
            {
                return (EnumDisplayRegion)enumSelRegion;
            }
            else
            {
                return (EnumDisplayRegion)(ScalerRegionGetInverse(enumSelRegion));
            }


        default:
            return _DISPLAY_RGN_NONE;
    }

    return _DISPLAY_RGN_NONE;
}

#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
//--------------------------------------------------
// Description  : Do matrix multiply(3x3)  C = A*B
// Input Value  : shArrayA, shArrayB
// Output Value : shArrayC (SDWORD)
//--------------------------------------------------
void ScalerColorSpaceConvertMatrixMultiply(SWORD(*ppshArrayA)[3], SWORD(*ppshArrayB)[3], SDWORD(*pplArrayC)[3])
{
    BYTE ucI = 0;
    BYTE ucJ = 0;
    SDWORD plTempBuff[3] = {0};
    for(ucJ = 0; ucJ < 3; ucJ++)
    {
        for(ucI = 0; ucI < 3; ucI++)
        {
            plTempBuff[ucI] = (((SDWORD)ppshArrayA[ucI][0] * ppshArrayB[0][ucJ] + 2) >> 4) +
                              (((SDWORD)ppshArrayA[ucI][1] * ppshArrayB[1][ucJ] + 2) >> 4) +
                              (((SDWORD)ppshArrayA[ucI][2] * ppshArrayB[2][ucJ] + 2) >> 4);
        }

        for(ucI = 0; ucI < 3; ucI++)
        {
            pplArrayC[ucI][ucJ] = (SDWORD)((plTempBuff[ucI] + 256) >> 9);
        }
    }
}

//--------------------------------------------------
// Description  : According to the Display Mode to decide how many time need to run
// Input Value  : enumSelRegion
// Output Value : None
//--------------------------------------------------
BYTE ScalerColorSpaceConvertUseDisplayModeToDecideRunTime(EnumSelRegion enumSelRegion)
{
    switch(GET_DISPLAY_MODE())
    {
#if(_2P_PIP_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP:
#if(_EAGLE_SIGHT_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
#endif
            return ((enumSelRegion == _FULL_REGION) ? 2 : 1);
#endif

#if(_2P_PBP_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
            return ((enumSelRegion == _FULL_REGION) ? 2 : 1);
#endif

#if(_2P_PBP_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_2P_PBP_TB:
            return ((enumSelRegion == _FULL_REGION) ? 2 : 1);
#endif

#if(_3P_FLAG_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_FLAG:
            return ((enumSelRegion == _FULL_REGION) ? 3 : (((enumSelRegion & 0x0F) >= 0x03) ? 2 : 1));
#endif

#if(_3P_SKEW_LR_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:
            return ((enumSelRegion == _FULL_REGION) ? 3 : (((enumSelRegion & 0x0F) >= 0x03) ? 2 : 1));
#endif

#if(_3P_SKEW_TB_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_3P_SKEW_B:
            return ((enumSelRegion == _FULL_REGION) ? 3 : (((enumSelRegion & 0x0F) >= 0x03) ? 2 : 1));
#endif

#if(_4P_DISPLAY_SUPPORT == _ON)
        case _DISPLAY_MODE_4P:
            return ((enumSelRegion == _FULL_REGION) ? 4 : (((enumSelRegion & 0x0F) >= 0x04) ? 3 : 1));
#endif

        case _DISPLAY_MODE_1P:
        default:
            enumSelRegion = enumSelRegion;
            return 1;
    }
}

//--------------------------------------------------
// Description  : change SelRegion to DisplayRegion
// Input Value  : enumSelRegion
// Output Value : enumDisplayRegion
//--------------------------------------------------
EnumDisplayRegion ScalerColorSpaceConvertChangeSelRegionToDisplayRegion(BYTE ucCurrentIndex, BYTE ucTotalIndex, EnumSelRegion enumSelRegion)
{
    BYTE ucJ = 0;
    EnumDisplayMode enumDisplayMode = GET_DISPLAY_MODE();

    // decide which case
    if(enumSelRegion == _FULL_REGION) // full region
    {
        ucCurrentIndex = ((ucCurrentIndex > 3) ? 3 : ucCurrentIndex);
        return ((EnumDisplayRegion)((enumDisplayMode) | tFULL_REGION_INDEX_TABLE[0][ucCurrentIndex]));
    }

    if(ucTotalIndex == 0x03) // 4P outside case
    {
        ucJ = ((enumSelRegion & 0x0F) - 4);
        ucCurrentIndex = ((ucCurrentIndex > 2) ? 2 : ucCurrentIndex);
        return ((EnumDisplayRegion)((enumDisplayMode) | t4P_OUTSIDE_REGION_INDEX_TABLE[ucJ][ucCurrentIndex]));
    }
    else if(ucTotalIndex == 0x02) // 3P outside case
    {
        ucJ = ((enumSelRegion & 0x0F) - 3);
        ucCurrentIndex = ((ucCurrentIndex > 1) ? 1 : ucCurrentIndex);
        return ((EnumDisplayRegion)((enumDisplayMode) | t3P_OUTSIDE_REGION_INDEX_TABLE[ucJ][ucCurrentIndex]));
    }
    else // not outside case
    {
        return ((EnumDisplayRegion)enumSelRegion);
    }
}

//--------------------------------------------------
// Description  : use color convertion to set global Hue&Sat
// Input Value  : DeltaHue(-180~180), DeltaSat(0-330)
// Default Value: Delta Hue = 0, Delta Sat = 100;
// Notice !! Rightnow the Hue/Sat value is saved to NVRAM as BYTE, if you
// want to expand the Range, please edit relative functions and parameters.
// Output Value : pColorMatrix(3x3, set to SRGB Matrix)
//--------------------------------------------------
void ScalerColorSpaceConvertSetGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shDeltaHue, WORD usDeltaSat)
{
    WORD usDdomainPage = _REG_MAIN1_PAGE;
    BYTE uck = 0;
    BYTE ucCnt = 0;
    BYTE ucDisplayNumber = 0;
    EnumDisplayRegion enumCurrentDisplayRegion = _DISPLAY_RGN_1P;

    if((enumSelRegion == _DEMO_INSIDE) || (enumSelRegion == _DEMO_OUTSIDE))
    {
        ScalerColorSpaceConvertRecover();
        return;
    }

    ucDisplayNumber = ScalerColorSpaceConvertUseDisplayModeToDecideRunTime(enumSelRegion);

    for(uck = 0; uck < ucDisplayNumber; uck++)
    {
        enumCurrentDisplayRegion = ScalerColorSpaceConvertChangeSelRegionToDisplayRegion(uck, ucDisplayNumber, enumSelRegion);

#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
        usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerRegionGetDDomainRegion(enumCurrentDisplayRegion));
#endif

        for(ucCnt = 0; ucCnt < 2; ucCnt++)
        {
            if(ucCnt == 1) // FB mode, back Region
            {
                if(ScalerColorSpaceConvertDDomainFBGetStatus(enumCurrentDisplayRegion) == _TRUE)
                {
                    // Set D-Domain Back regs
                    usDdomainPage = ScalerColorSpaceConvertDDomainPageMapping(ScalerColorSpaceConvertDDomainGetBackRegion(enumCurrentDisplayRegion));
                }
                else
                {
                    break;
                }
            }
            ScalerColorSpaceConvertCalculateGlobalHueSat(usDdomainPage, shDeltaHue, usDeltaSat);
        }
    }
}

//--------------------------------------------------
// Description  : use color convertion to set global Hue&Sat
// Input Value  : DeltaHue(-180~180), DeltaSat(0-330)
// Default Value: Delta Hue = 0, Delta Sat = 100;
// Notice !! Rightnow the Hue/Sat value is saved to NVRAM as BYTE, if you
// want to expand the Range, please edit relative functions and parameters.
// Output Value : pColorMatrix(3x3, set to SRGB Matrix)
//--------------------------------------------------
void ScalerColorSpaceConvertCalculateGlobalHueSat(WORD usDdomainPage, SWORD shDeltaHue, WORD usDeltaSat)
{
    SWORD ppshTempBuff[3][3] = {{0}};
    SDWORD pplTempBuff2[3][3] = {{0}};
    BYTE ucI = 0;
    BYTE ucJ = 0;

    if((shDeltaHue == 0) && (usDeltaSat == 100))
    {
        ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage, ~(_BIT5 | _BIT4), 0x00);
    }
    else
    {
        if(_TRUE)
        {
            SWORD ppshMATRIX[3][3] = {{0}};
            SWORD ppshMATRIX2[3][3] = {{0}};

            ppshMATRIX[0][0] = 4096;
            ppshMATRIX[0][1] = 0;
            ppshMATRIX[0][2] = 0;
            ppshMATRIX[1][0] = 0;
            ppshMATRIX[1][1] = (DWORD)usDeltaSat * 4096 / 100;
            ppshMATRIX[1][2] = 0;
            ppshMATRIX[2][0] = 0;
            ppshMATRIX[2][1] = 0;
            ppshMATRIX[2][2] = ppshMATRIX[1][1];

            // tRGB2YUV
            ppshMATRIX2[0][0] = 1224;
            ppshMATRIX2[0][1] = 2405;
            ppshMATRIX2[0][2] = 467;
            ppshMATRIX2[1][0] = -691;
            ppshMATRIX2[1][1] = -1357;
            ppshMATRIX2[1][2] = 2048;
            ppshMATRIX2[2][0] = 2048;
            ppshMATRIX2[2][1] = -1715;
            ppshMATRIX2[2][2] = -333;

            ScalerColorSRGBMatrixMultiply(ppshMATRIX, ppshMATRIX2, ppshTempBuff);

            ppshMATRIX[0][0] = 4096;
            ppshMATRIX[0][1] = 0;
            ppshMATRIX[0][2] = 0;
            ppshMATRIX[1][0] = 0;
            ppshMATRIX[1][1] = ScalerColorSRGBCosine(shDeltaHue);
            ppshMATRIX[1][2] = ((SWORD)(-1) * (SWORD)ScalerColorSRGBSine(shDeltaHue));
            ppshMATRIX[2][0] = 0;
            ppshMATRIX[2][1] = ((SWORD)(-1) * (SWORD)ppshMATRIX[1][2]);
            ppshMATRIX[2][2] = ppshMATRIX[1][1];

            ScalerColorSRGBMatrixMultiply(ppshMATRIX, ppshTempBuff, ppshTempBuff);

            // tYUV2RGB
            ppshMATRIX2[0][0] = 4096;
            ppshMATRIX2[0][1] = 0;
            ppshMATRIX2[0][2] = 5744;
            ppshMATRIX2[1][0] = 4096;
            ppshMATRIX2[1][1] = -1408;
            ppshMATRIX2[1][2] = -2924;
            ppshMATRIX2[2][0] = 4096;
            ppshMATRIX2[2][1] = 7260;
            ppshMATRIX2[2][2] = 0;

            ScalerColorSRGBMatrixMultiply(ppshMATRIX2, ppshTempBuff, ppshTempBuff);

            for (ucI = 0; ucI < 3; ucI++)
            {
                for (ucJ = 0; ucJ < 3; ucJ++)
                {
                    ppshTempBuff[ucI][ucJ] = ppshTempBuff[ucI][ucJ] << 1;
                }
            }

            ScalerRead(P14_A2_SR_YCC2RGB_COEF_K11_MSB_R1_ACTIVE1 + usDdomainPage, 10, pData, _AUTOINC);

            ppshMATRIX[0][0] = ((pData[0] & 0x0F) << 11) | (pData[1] << 3) | ((pData[0] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
            ppshMATRIX[0][1] = 0;
            ppshMATRIX[0][2] = ((pData[2] & 0x0F) << 11) | (pData[3] << 3) | ((pData[2] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
            ppshMATRIX[1][0] = ppshMATRIX[0][0];
            ppshMATRIX[1][1] = ((SWORD)(-1) * (SWORD)(((pData[4] & 0x0F) << 11) | (pData[5] << 3) | ((pData[4] & (_BIT7 | _BIT6 | _BIT5)) >> 5)));
            ppshMATRIX[1][2] = ((SWORD)(-1) * (SWORD)(((pData[6] & 0x0F) << 11) | (pData[7] << 3) | ((pData[6] & (_BIT7 | _BIT6 | _BIT5)) >> 5)));
            ppshMATRIX[2][0] = ppshMATRIX[0][0];
            ppshMATRIX[2][1] = ((pData[8] & 0x0F) << 11) | (pData[9] << 3) | ((pData[8] & (_BIT7 | _BIT6 | _BIT5)) >> 5);
            ppshMATRIX[2][2] = 0;

            ScalerColorSpaceConvertMatrixMultiply(ppshTempBuff, ppshMATRIX, pplTempBuff2);
        }

        if(_TRUE)
        {
            BYTE pucColorMatrix[27] = {0};

            for (ucI = 0; ucI < 3; ucI++)
            {
                for (ucJ = 0; ucJ < 3; ucJ++)
                {
                    pucColorMatrix[3 * (3 * ucI + ucJ)] = (((pplTempBuff2[ucJ][ucI] < 0) ? 1 : 0) << 3) | ((pplTempBuff2[ucJ][ucI] >> 13) & (_BIT2 | _BIT1 | _BIT0)); // [3] sign
                    pucColorMatrix[3 * (3 * ucI + ucJ) + 1] = ((pplTempBuff2[ucJ][ucI] >> 5) & 0xFF); // bit5~12
                    pucColorMatrix[3 * (3 * ucI + ucJ) + 2] = ((pplTempBuff2[ucJ][ucI] & 0x1F) << 3); // bit0~4
                }
            }
            ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
            ScalerWrite(P14_40_SR_BT2020_COEF_H11_HSB_R1_ACTIVE1 + usDdomainPage, 27, pucColorMatrix, _AUTOINC);
            ScalerSetByte(P14_6D_SR_BT2020_COEF_CB_THD_MSB_R1_ACTIVE1 + usDdomainPage, 0xFF);
            ScalerSetByte(P14_6E_SR_BT2020_COEF_CB_THD_LSB_R1_ACTIVE1 + usDdomainPage, 0xFF);
            ScalerSetByte(P14_6F_SR_BT2020_COEF_CR_THD_MSB_R1_ACTIVE1 + usDdomainPage, 0xFF);
            ScalerSetByte(P14_70_SR_BT2020_COEF_CR_THD_LSB_R1_ACTIVE1 + usDdomainPage, 0xFF);
            ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1 + usDdomainPage, ~(_BIT5 | _BIT4), _BIT5);
        }
    }
}


//--------------------------------------------------
// Description  : recover color convertion to standard
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertRecover(void)
{
    ScalerSetBit(P14_A1_SR_YCC2RGB_CTRL_R1_ACTIVE1, ~(_BIT5 | _BIT4), 0x00);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
    ScalerSetBit(P94_A1_SR_YCC2RGB_CTRL_R2_ACTIVE1, ~(_BIT5 | _BIT4), 0x00);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 2)
    ScalerSetBit(P54_A1_SR_YCC2RGB_CTRL_R1_ACTIVE2, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(P5D_A1_SR_YCC2RGB_CTRL_R2_ACTIVE2, ~(_BIT5 | _BIT4), 0x00);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 4)
    ScalerSetBit(PE9_A1_SR_YCC2RGB_CTRL_R3_ACTIVE1, ~(_BIT5 | _BIT4), 0x00);
    ScalerSetBit(PEA_A1_SR_YCC2RGB_CTRL_R3_ACTIVE2, ~(_BIT5 | _BIT4), 0x00);
#endif
#endif
#endif
}

//--------------------------------------------------
// Description  : format Convert DB flow
// Input Value  : enumDisplayRegion, enumDBApply
// Output Value : None
//--------------------------------------------------
void ScalerColorSpaceConvertDBApply(EnumDisplayRegion enumDisplayRegion, EnumDBApply enumDBApply)
{
    EnumInputDataPath enumSelectedDataPath = _INPUT_PATH_M1_M2;

    enumSelectedDataPath = ScalerRegionGetInputDataPath(enumDisplayRegion);

#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
    if(ScalerFRCGetAutoBlkToggleEn() == _DISABLE)
#endif
    {
        if(GET_INPUT_TIMING_INTERLACE_FLG() == _TRUE)
        {
#if(_3DDI_FUNCTION == _ON)
            if(GET_3DDI_STATUS(enumSelectedDataPath) == _TRUE)
            {
                if(enumDBApply == _DB_APPLY_NO_POLLING)
                {
                    enumDBApply = _DB_APPLY_POLLING;
                }

                ScalerGlobalIDDomainDBApply(enumSelectedDataPath, enumDBApply);
            }
            else
#endif
            {
                ScalerGlobalIDomainDBApply(enumSelectedDataPath, enumDBApply);
                ScalerGlobalDDomainDBApply(ScalerRegionGetDDomainDBApplyRegionIndexFromSelRegion((EnumSelRegion)enumDisplayRegion), enumDBApply);
            }
        }
        else
        {
            if(enumDBApply == _DB_APPLY_NO_POLLING)
            {
                enumDBApply = _DB_APPLY_POLLING;
            }

            ScalerGlobalIDDomainDBApply(enumSelectedDataPath, enumDBApply);
        }
    }
}
#endif
#endif// End of #if(_COLOR_IP_COLOR_CONVERT == _ON)

