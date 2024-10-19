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
// ID Code      : ScalerDpStreamInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro of Stream Internal Data Path
//--------------------------------------------------
#define GET_DP_STREAM_INPUT_PIXEL_CLK_BW()                  (g_stDpStreamInterfaceInfo.usDpStreamInputPixelClkBw)
#define SET_DP_STREAM_INPUT_PIXEL_CLK_BW(x)                 (g_stDpStreamInterfaceInfo.usDpStreamInputPixelClkBw = (x))

#define GET_DP_STREAM_INPUT_PIXEL_MODE()                    (g_stDpStreamInterfaceInfo.enumPixelMode)
#define SET_DP_STREAM_INPUT_PIXEL_MODE(x)                   (g_stDpStreamInterfaceInfo.enumPixelMode = (x))

#define GET_DP_STREAM_INPUT_PRE_INFO_TYPE(x)                (g_pstDpStreamInputPreInfoType[x].enumDpStreamInfoType)
#define SET_DP_STREAM_INPUT_PRE_INFO_TYPE(x, y)             (g_pstDpStreamInputPreInfoType[x].enumDpStreamInfoType = (y))

#define GET_DP_STREAM_MAX_PIXEL_CLK_BW()                    (g_stDpStreamInterfaceInfo.usMaxPixelClkBw)
#define SET_DP_STREAM_MAX_PIXEL_CLK_BW(x)                   (g_stDpStreamInterfaceInfo.usMaxPixelClkBw = (x))


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Data Path Pixel Mode
//--------------------------------------------------
typedef enum
{
    _1_PIXEL_MODE = 0x00,
    _2_PIXEL_MODE = 0x01,
    _4_PIXEL_MODE = 0x02,
    _NONE_PIXEL_MODE = 0xFF,
} EnumDpStreamPixelMode;

//--------------------------------------------------
// Enum of Dp Stream Type
//--------------------------------------------------
typedef enum
{
    _STREAM_D0_DP = 0x00,
    _STREAM_D1_DP,
    _STREAM_D2_DP,
    _STREAM_PXP,
    _STREAM_MST2SST,
    _STREAM_CLONE,
    _STREAM_SOURCE_NUM,
}EnumDpStreamType;

//--------------------------------------------------
// Enumerations Dp Stream Field Type
//--------------------------------------------------
typedef enum
{
    _INFO_TYPE_NONE = 0x00,
    _INFO_TYPE_VIDEO, // Main link Normal DP Stream
    _INFO_TYPE_DSC,
    _INFO_TYPE_MST2MST,
} EnumDpStreamInfoType;

typedef enum
{
    _DATA_PATH_NONE = 0x00,
    _DATA_PATH_VESA,
    _DATA_PATH_VIDEO_REORDER,
    _DATA_PATH_VIDEO_BYPASS,
    _DATA_PATH_DSC_DECODER,
    _DATA_PATH_DSC_REORDER,
    _DATA_PATH_DSC_BYPASS,
    _DATA_PATH_MST2MST,
    _DATA_PATH_INVALID,
} EnumDpStreamDataPath;

typedef enum
{
    _COLOR_SPACE,
    _COLOR_DEPTH,
    _PIXEL_CLOCK,
    _FRAME_RATE,
    _ONE_FRAME_DELAY,
    _DIGITAL_QUANTIZATION_PREVALUE,
    _COLORIMETRY,
    _COLOR_RGB_QUANTIZATION_RANGE,
    _COLOR_YCC_QUANTIZATION_RANGE,
    _EXT_COLORIMETRY,
    _INTERLACE_INFO,
    _INTERLACE_NUMBER,
    _OUTPUT_PIXEL_MODE,
    _DSC_BYPASS_PIXEL_CLK,
    _DSC_PPS_STATUS,
} EnumDpStreamElement;

//--------------------------------------------------
// Enumerations PPS Info
//--------------------------------------------------
typedef enum
{
    _PPS_PIC_HEIGHT,
    _PPS_PIC_WIDTH,
    _PPS_SLICE_HEIGHT,
    _PPS_SLICE_WIDTH,
    _PPS_HOR_SLICE_COUNT,
    _PPS_CHUNK_SIZE,
    _PPS_INIT_DEC_DELAY,
    _PPS_DSC_VERSION,
    _PPS_BITS_PER_PIXEL,
    _PPS_BIT_PER_COMPONENT,
    _PPS_NATIVE_MODE,
    _PPS_NATIVE_420,
    _PPS_NATIVE_422,
    _PPS_SIMPLE_422,
    _PPS_CONVERT_RGB,
    _PPS_DSC_STABLE_STATUS,
    _PPS_COLOR_SPACE,
    _PPS_COLOR_DEPTH,
    _PPS_RECEIVE_FINISH,
    _PPS_DSC_BUFFER_CLOCK,
    _PPS_DSC_CLOCK,
    _PPS_DSC_OUTPUT_CLOCK,
    _PPS_DSC_PIXEL_CLOCK,
    _PPS_IDENTIFIER,
    _PPS_LINEBUFFER_DEPTH,
    _PPS_BLOCK_PREDICTION_ENABLE,
    _PPS_DSC_VBR_ENABLE,
} EnumDpStreamPpsElement;

//--------------------------------------------------
// Structure of Dp Stream Info
//--------------------------------------------------
typedef struct
{
    EnumDpStreamDataPath enumDpStreamDataPath;
    EnumDpStreamInfoType enumDpStreamInfoType;
    EnumDpStreamPixelMode enumPixelMode;
    WORD usMaxPixelClkBw;
    WORD usDpStreamInputPixelClkBw;
    WORD usDpStreamOutputPixelClkBw;
    DWORD ulStreamPreDetectPixelClock;
    DWORD ulDpStreamNativePixelClock;
    BYTE b1StreamPreDetectFlag : 1;
    BYTE b1StreamInfoTypeChangeFlag : 1;
    BYTE b1FreeSyncEnable : 1;
    BYTE b1DpStreamOutputX2Clk : 1;
} StructDpStreamInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDpStreamInfo g_stDpStreamInterfaceInfo;
extern StructDpStreamInfo g_pstDpStreamInputPreInfoType[_STREAM_SOURCE_NUM];


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDpStreamJudgeHandler(void);
extern EnumDpStreamDataPath ScalerDpStreamGetDataPath(EnumDpStreamType enumDpStreamType);
extern void ScalerDpStreamDataPathReset(EnumDpStreamType enumDpStreamType);
extern EnumDpLinkChannelCodingType ScalerDpStreamGetRxCodingType(EnumDpStreamType enumDpStreamType);
extern EnumDpLaneCount ScalerDpStreamGetRxLaneCount(EnumDpStreamType enumDpStreamType);
#endif
