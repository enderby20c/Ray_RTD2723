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
// ID Code      : ScalerDpStream.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "DpStream/ScalerDpStream.h"

#if(_DP_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
StructDpStreamInfo g_stDpStreamInterfaceInfo;
StructDpStreamInfo g_pstDpStreamInputPreInfoType[_STREAM_SOURCE_NUM];


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DP Stream Data Path Judge Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDpStreamJudgeHandler(void)
{
    BYTE ucDpStreamIndex = 0;
    EnumDpStreamInfoType enumDpStreamInfoType = _INFO_TYPE_NONE;
    EnumDpStreamDataPath enumDpStreamDataPath = _DATA_PATH_NONE;

    for(ucDpStreamIndex = 0; ucDpStreamIndex < _STREAM_SOURCE_NUM; ucDpStreamIndex++)
    {
        enumDpStreamInfoType = ScalerDpStreamGetInfoType(ucDpStreamIndex);
        enumDpStreamDataPath = ScalerDpStreamGetDataPath(ucDpStreamIndex);

        if(ScalerDpStreamJudgePreCheck(ucDpStreamIndex, enumDpStreamInfoType, enumDpStreamDataPath) == _TRUE)
        {
            ScalerDpStreamSetDataPathProc(ucDpStreamIndex, enumDpStreamInfoType);
        }
        else if(ScalerDpStreamStableCheck(ucDpStreamIndex, enumDpStreamInfoType, enumDpStreamDataPath) == _FALSE)
        {
            ScalerDpStreamDataPathReset(ucDpStreamIndex);
        }
    }
}

//--------------------------------------------------
// Description  : DP Stream Data Path Pre Check
// Input Value  : EnumDpStreamType, EnumDpStreamInfoType
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerDpStreamJudgePreCheck(EnumDpStreamType enumDpStreamType, EnumDpStreamInfoType enumDpStreamInfoType, EnumDpStreamDataPath enumDpStreamDataPath)
{
    bit bDpStreamPreJudge = _FALSE;

    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:

            if(enumDpStreamDataPath == _DATA_PATH_NONE)
            {
                // Data Path None & Input Info Type not None Need to Set Data Path
                if(enumDpStreamInfoType != _INFO_TYPE_NONE)
                {
                    bDpStreamPreJudge = _TRUE;
                }
                else
                {
                    bDpStreamPreJudge = _FALSE;
                }
            }
            else
            {
                // Data Path Not None & Input Info Type None Need Reset to None
                bDpStreamPreJudge = _FALSE;
            }

            break;

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_MST2SST:

            if(enumDpStreamDataPath == _DATA_PATH_NONE)
            {
                // Data Path None & Input Info Type not None & Tx Lt Pass Need to Set Data Path
                if(enumDpStreamInfoType != _INFO_TYPE_NONE)
                {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if((GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS) && (GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_READY))
#else
                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
#endif
                    {
                        bDpStreamPreJudge = _TRUE;
                    }
                    else
                    {
                        bDpStreamPreJudge = _FALSE;
                    }
                }
                else
                {
                    bDpStreamPreJudge = _FALSE;
                }
            }
            else
            {
                // Data Path Not None & Input Info Type None or Tx Lt Not Pass Need Reset to None
                bDpStreamPreJudge = _FALSE;
            }

            break;

        case _STREAM_CLONE:

            if(enumDpStreamDataPath == _DATA_PATH_NONE)
            {
                // Data Path None & Input Info Type not None & Tx Lt Pass Need to Set Data Path
                if(enumDpStreamInfoType != _INFO_TYPE_NONE)
                {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
                    if((GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS) && (GET_DP_MAC_TX_LINK_ESTABLISH_STATUS() == _LINK_ESTABLISH_READY))
#else
                    if(GET_DP_TX_LT_RESULT() == _DP_TX_TRAINING_PASS)
#endif
                    {
                        bDpStreamPreJudge = _TRUE;
                    }
                    else
                    {
                        bDpStreamPreJudge = _FALSE;
                    }
                }
                else
                {
                    bDpStreamPreJudge = _FALSE;
                }
            }
            else
            {
                // Data Path Not None & Input Info Type None or Tx Lt Not Pass Need Reset to None
                bDpStreamPreJudge = _FALSE;
            }

            break;
#endif

        default:
            break;
    }

    // Check if Stream Info Type Change need Return True to Set Data Path // delete
    if(enumDpStreamInfoType != GET_DP_STREAM_INPUT_PRE_INFO_TYPE(enumDpStreamType))
    {
        // Backup Current Stream Info Type
        SET_DP_STREAM_INPUT_PRE_INFO_TYPE(enumDpStreamType, enumDpStreamInfoType);

        if(enumDpStreamInfoType != _INFO_TYPE_NONE)
        {
            bDpStreamPreJudge = _TRUE;
        }
    }

    return bDpStreamPreJudge;
}

//--------------------------------------------------
// Description  : DP Stream Stable Check
// Input Value  : EnumDpStreamType, EnumDpStreamInfoType, EnumDpStreamDataPath
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit ScalerDpStreamStableCheck(EnumDpStreamType enumDpStreamType, EnumDpStreamInfoType enumDpStreamInfoType, EnumDpStreamDataPath enumDpStreamDataPath)
{
    enumDpStreamType = enumDpStreamType;

    if(enumDpStreamDataPath != _DATA_PATH_NONE)
    {
        if(enumDpStreamInfoType == _INFO_TYPE_NONE)
        {
            return _FALSE;
        }

#if(_DP_TX_SUPPORT == _ON)
        else if((enumDpStreamType == _STREAM_MST2SST) || (enumDpStreamType == _STREAM_CLONE))
        {
            if(GET_DP_TX_LT_RESULT() != _DP_TX_TRAINING_PASS)
            {
                return _FALSE;
            }
        }
#endif
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Stream Type Mapping Stream Source Type
// Input Value  : EnumDpStreamType
// Output Value : EnumDpMacStreamSourceType
//--------------------------------------------------
EnumDpMacStreamSourceType ScalerDpStreamTypeSourceTypeMapping(EnumDpStreamType enumDpStreamType)
{
    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
            return _STREAM_SOURCE_D0_DP;

        case _STREAM_D1_DP:
            return _STREAM_SOURCE_D1_DP;

        case _STREAM_D2_DP:
            return _STREAM_SOURCE_D2_DP;

        case _STREAM_PXP:
            return _STREAM_SOURCE_PXP;

        case _STREAM_MST2SST:
            return _STREAM_SOURCE_MST2SST;

        default:
            return _STREAM_SOURCE_NONE;
    }
}

//--------------------------------------------------
// Description  : DP Stream Source Type Mapping Stream Type
// Input Value  : EnumDpMacStreamSourceType
// Output Value : EnumDpStreamType
//--------------------------------------------------
EnumDpStreamType ScalerDpStreamSourceTypeStreamTypeMapping(EnumDpMacStreamSourceType enumDpStreamSourceType)
{
    switch(enumDpStreamSourceType)
    {
        case _STREAM_SOURCE_D0_DP:
            return _STREAM_D0_DP;

        case _STREAM_SOURCE_D1_DP:
            return _STREAM_D1_DP;

        case _STREAM_SOURCE_D2_DP:
            return _STREAM_D2_DP;

        case _STREAM_SOURCE_PXP:
            return _STREAM_PXP;

        case _STREAM_SOURCE_MST2SST:
            return _STREAM_MST2SST;

        default:
            return _STREAM_D0_DP;
    }
}

//--------------------------------------------------
// Description  : DP Stream Set Data Path Proc
// Input Value  : EnumDpStreamType, EnumDpStreamInfoType
// Output Value : None
//--------------------------------------------------
void ScalerDpStreamSetDataPathProc(EnumDpStreamType enumDpStreamType, EnumDpStreamInfoType enumDpStreamInfoType)
{
    EnumDpStreamDataPath enumDataPath = _DATA_PATH_NONE;
    enumDataPath = enumDataPath;

    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:

            if(enumDpStreamInfoType == _INFO_TYPE_VIDEO)
            {
                ScalerDpStreamSetDataPath(enumDpStreamType, _DATA_PATH_VESA);
            }
            else if(enumDpStreamInfoType == _INFO_TYPE_DSC)
            {
                ScalerDpStreamSetDataPath(enumDpStreamType, _DATA_PATH_DSC_DECODER);
            }

            break;

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_MST2SST:
        case _STREAM_CLONE:

            if(enumDpStreamInfoType == _INFO_TYPE_VIDEO)
            {
                enumDataPath = ScalerDpStreamVideoDataPathJudge(enumDpStreamType);
            }
            else if(enumDpStreamInfoType == _INFO_TYPE_DSC)
            {
                enumDataPath = ScalerDpStreamDscDataPathJudge(enumDpStreamType);
            }

            if(ScalerDpStreamBandWidthCheck(enumDpStreamType, enumDataPath) == _TRUE)
            {
                ScalerDpStreamSetDataPath(enumDpStreamType, enumDataPath);
            }
            else
            {
                ScalerDpStreamSetDataPath(enumDpStreamType, _DATA_PATH_INVALID);
            }

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Stream Get Info Type
// Input Value  : EnumDpStreamType
// Output Value : EnumDpStreamInfoType
//--------------------------------------------------
EnumDpStreamInfoType ScalerDpStreamGetInfoType(EnumDpStreamType enumDpStreamType)
{
    EnumDpStreamInfoType enumDpStreamInfoType = _INFO_TYPE_NONE;

    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_MST2SST:
        case _STREAM_PXP:

            enumDpStreamInfoType = ScalerDpMacStreamRxGetStreamInfoType(ScalerDpStreamTypeSourceTypeMapping(enumDpStreamType));

            break;

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_CLONE:

            enumDpStreamInfoType = GET_DP_MAC_TX_CLONE_STREAM_INFO_TYPE();

            break;
#endif

        default:
            break;
    }

    return enumDpStreamInfoType;
}

//--------------------------------------------------
// Description  : DP Stream Get Data Path
// Input Value  : EnumDpStreamType
// Output Value : EnumDpStreamDataPath
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpStreamGetDataPath(EnumDpStreamType enumDpStreamType)
{
    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:
        case _STREAM_MST2SST:
            return ScalerDpMacStreamRxGetDataPath(ScalerDpStreamTypeSourceTypeMapping(enumDpStreamType));

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_CLONE:

            return ScalerDpMacTxCloneGetDataPath();
#endif

        default:
            break;
    }
    return _DATA_PATH_NONE;
}

//--------------------------------------------------
// Description  : DP Stream Set Data Path
// Input Value  : EnumDpStreamType, EnumDpStreamDataPath
// Output Value : None
//--------------------------------------------------
void ScalerDpStreamSetDataPath(EnumDpStreamType enumDpStreamType, EnumDpStreamDataPath enumDataPath)
{
    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:
        case _STREAM_MST2SST:
            ScalerDpMacStreamRxSetDataPath(ScalerDpStreamTypeSourceTypeMapping(enumDpStreamType), enumDataPath);

            break;

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_CLONE:

            ScalerDpMacTxCloneSetDataPath(enumDataPath);

            break;
#endif

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : DP Stream Data Path Reset
// Input Value  : EnumDpStreamType
// Output Value : None
//--------------------------------------------------
void ScalerDpStreamDataPathReset(EnumDpStreamType enumDpStreamType)
{
    ScalerDpStreamSetDataPath(enumDpStreamType, _DATA_PATH_NONE);
}

#if(_DP_TX_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Stream Video Data Path Judge
// Input Value  : EnumDpStreamType
// Output Value : EnumDpStreamDataPath
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpStreamVideoDataPathJudge(EnumDpStreamType enumDpStreamType)
{
    EnumDpStreamDataPath enumDataPath = _DATA_PATH_NONE;

    // MST2SST
    // Case 1-1 : DP2.0 to DP2.0 : TxBW >= Video BW, Pixel Clk ">=<" Data Path (4 Pixel Mode) --> Video Bypass
    // Case 1-2 :                  TxBW <  Video BW, Pixel Clk ">=<" Data Path (4 Pixel Mode) --> Error
    // Case 2-1 : DP2.0 to DP1.4 : TxBW >= Video BW, Pixel Clk > Data Path (2 Pixel Mode) --> Video Reorder (4Lane)
    // Case 2-2 :                  TxBW >= Video BW, Pixel Clk < Data Path (2 Pixel Mode) --> Video VESA
    // Case 2-3 :                  TxBW <  Video BW, Pixel Clk ">=<" Data Path (2 Pixel Mode) --> Error
    // Case 3-1 : DP1.4 to DP2.0 : TxBW >= Video BW, Pixel Clk > Data Path (2 Pixel Mode) --> Video Error
    // Case 3-2 :                  TxBW >= Video BW, Pixel Clk < Data Path (2 Pixel Mode) --> Video VESA
    // Case 3-3 :                  TxBW <  Video BW, Pixel Clk ">=<" Data Path (2 Pixel Mode) --> Error
    // Case 4-1 : DP1.4 to DP1.4 : TxBW >= Video BW, Pixel Clk > Data Path (2 Pixel Mode) --> Video Reorder (4Lane)
    // Case 4-2 :                  TxBW >= Video BW, Pixel Clk < Data Path (2 Pixel Mode) --> Video VESA
    // Case 4-3 :                  TxBW <  Video BW,  Pixel Clk ">=<" Data Path (2 Pixel Mode) --> Error

    // Clone
    // Case 1-1 : DP2.0 to DP2.0 : TxBW >= Video BW, Pixel Clk ">=<" Data Path (4 Pixel Mode) --> Video Bypass
    // Case 1-2 :                  TxBW <  Video BW, Pixel Clk ">=<" Data Path (4 Pixel Mode) --> Error
    // Case 2-1 : DP2.0 to DP1.4 : TxBW >= Video BW, Pixel Clk > Data Path (2 Pixel Mode) --> Video Reorder (4Lane)
    // Case 2-2 :                  TxBW >= Video BW, Pixel Clk < Data Path (2 Pixel Mode) --> Video VESA
    // Case 2-3 :                  TxBW <  Video BW, Pixel Clk ">=<" Data Path (2 Pixel Mode) --> Error
    // Case 3-1 : DP1.4 to DP2.0 : TxBW >= Video BW, Pixel Clk > Data Path (2 Pixel Mode) --> Video Error
    // Case 3-2 :                  TxBW >= Video BW, Pixel Clk < Data Path (2 Pixel Mode) --> Video VESA
    // Case 3-3 :                  TxBW <  Video BW, Pixel Clk ">=<" Data Path (2 Pixel Mode) --> Error
    // Case 4-1 : DP1.4 to DP1.4 : TxBW >= Video BW, Pixel Clk > Data Path (2 Pixel Mode) --> Video Reorder (Rx lane = Tx lane)
    // Case 4-2 :                  TxBW >= Video BW, Pixel Clk < Data Path (2 Pixel Mode) --> Video VESA
    // Case 4-3 :                  TxBW <  Video BW, Pixel Clk ">=<" Data Path (2 P l Mode) --> Error


    // Note : Clone BW include FEC 2.4% + SSC 0.5%

    // Compare Pixel Clk & Data Path Max Pixel Clk
    if(ScalerDpStreamDataPathMaxPixelClkCheck(enumDpStreamType) == _TRUE)
    {
        DebugMessageDpRx("[Stream Management] Pixel Clk Less than Data Path Max Pixel Clk", 1);
        enumDataPath = ScalerDpStreamVesaCodingTypeDataPathJudge(enumDpStreamType);
    }
    else
    {
        DebugMessageDpRx("[Stream Management] Pixel Clk Exceed Data Path Max Pixel Clk", 0);
        enumDataPath = ScalerDpStreamVesaPassThroughDataPathJudge(enumDpStreamType);
    }

    return enumDataPath;
}

//--------------------------------------------------
// Description  : DP Stream DSC Data Path Judge
// Input Value  : EnumDpStreamType
// Output Value : EnumDpStreamDataPath
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpStreamDscDataPathJudge(EnumDpStreamType enumDpStreamType)
{
    EnumDpStreamDataPath enumDataPath = _DATA_PATH_NONE;

    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:

            return _DATA_PATH_DSC_DECODER;

        case _STREAM_MST2SST:

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            if(ScalerDpStreamDscDecodeCheck(enumDpStreamType) == _TRUE)
            {
                // Function Pixel Clk Need to be Checked
                if(ScalerDpStreamDataPathMaxPixelClkCheck(enumDpStreamType) == _TRUE)
                {
                    DebugMessageDpRx("[Stream Management] DSC Pixel Clk Less than Data Path Max Pixel Clk, MST2SST DSC Decode Enable", 0);

                    return _DATA_PATH_DSC_DECODER;
                }
                else
                {
                    DebugMessageDpRx("[Stream Management] DSC Pixel Clk Larger than Data Path Max Pixel Clk, Go To Check Passthrough", 0);
                }
            }
#endif
            // MST2SST
            // Case 1-1 : DP2.0 to DP2.0 : DPCD_160[1] = 1 or Sink DPCD_160[0] = 1 --> DSC Bypass
            // Case 2-1 : DP2.0 to DP1.4 : DPCD_160[1] = 1 or Sink DPCD_160[0] = 1 --> DSC Reorder
            // Case 3-1 : DP1.4 to DP1.4 : DPCD_160[1] = 1 or Sink DPCD_160[0] = 1 --> DSC Reorder
            // Other :                                                             --> DSC Error
            if(ScalerDpStreamDscPassThroughEnableCheck(enumDpStreamType) == _TRUE)
            {
                return ScalerDpStreamDscPassThroughDataPathJudge(enumDpStreamType);
            }

            break;

        case _STREAM_CLONE:

            // CLONE
            // Case 1-1 : DP2.0 to DP2.0 : DSC Passthrough Judege OK, VESA BW >= Tx BW >= DSC BW --> DSC Bypass
            // Case 1-2 :                  DSC Passthrough Judege OK, Tx BW >= VESA BW --> VESA
            // Case 1-3 :                  DSC Passthrough Judege Fail, Tx BW >= VESA BW --> VESA
            // Case 2-1 : DP2.0 to DP1.4 : DSC Passthrough Judege OK --> VESA BW >= Tx BW >= DSC BW --> DSC Reorder
            // Case 2-2 :                  DSC Passthrough Judege OK --> Tx BW >= VESA BW --> VESA
            // Case 2-3 :                  DSC Passthrough Judege Fail, Tx BW >= VESA BW --> VESA
            // Case 3-1 : DP1.4 to DP2.0 :                              Tx BW >= VESA BW --> VESA
            // Case 4-1 : DP2.0 to DP1.4 : DSC Passthrough Judege OK --> VESA BW >= Tx BW >= DSC BW --> DSC Reorder
            // Case 4-2 :                  DSC Passthrough Judege OK --> Tx BW >= VESA BW --> VESA
            // Case 4-3 :                  DSC Passthrough Judege Fail, Tx BW >= VESA BW --> VESA
            // Other :                                                                   --> DSC Error
            if((ScalerDpStreamDataPathMaxPixelClkCheck(enumDpStreamType) == _TRUE) && (ScalerDpStreamBandWidthCheck(_STREAM_CLONE, _DATA_PATH_VESA) == _TRUE))
            {
                DebugMessageDpRx("[Stream Management] DSC Pixel Clk Less than Data Path Max Pixel Clk", 1);

                enumDataPath = _DATA_PATH_VESA;
            }
            else
            {
                DebugMessageDpRx("[Stream Management] DSC Pixel Clk Exceed Data Path Max Pixel Clk", 0);

                if(ScalerDpStreamDscPassThroughEnableCheck(enumDpStreamType) == _TRUE)
                {
                    enumDataPath = ScalerDpStreamDscPassThroughDataPathJudge(enumDpStreamType);
                }
                else
                {
                    enumDataPath = _DATA_PATH_INVALID;
                }
            }

            break;

        default:
            break;
    }

    return enumDataPath;
}

//--------------------------------------------------
// Description  : DSC Pass Through Enable Check
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpStreamDscPassThroughEnableCheck(EnumDpStreamType enumDpStreamType)
{
    switch(enumDpStreamType)
    {
        case _STREAM_MST2SST:

            // Check DP Tx Sink DPCD_00060[0] DSC Cap.
            if(ScalerDpMacTxGetDfpDeviceDscCap() == _TRUE)
            {
#if((_DP_MST_MULTI_FUNCTION_SUPPORT == _ON) && (_DP_TX_DSC_PASSTHROUGH_SUPPORT == _ON))
                if(ScalerDpMacMstToSstDscReorderDetect() == _TRUE)
                {
                    return _TRUE;
                }
#endif
                return _FALSE;
            }
            else
            {
                return _FALSE;
            }

        case _STREAM_CLONE:

#if((_DP_TX_SST_CLONE_PATH_TYPE == _DP_TX_CLONE_BOTH_VESA_STREAM_DSC_PASSTHROUGH) && (_DSC_DECODER_SUPPORT == _ON))
            SET_DP_TX_DOWNSTREAM_DSC_PASSTHROUGH();
            return _TRUE;
#else
            return _FALSE;
#endif

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Stream Dsc PassThrough Judge
// Input Value  : EnumDpStreamType
// Output Value : _TRUE, _FALSE
//--------------------------------------------------
bit ScalerDpStreamDscPassThroughJudge(EnumDpStreamType enumDpStreamType)
{
    switch(enumDpStreamType)
    {
        case _STREAM_MST2SST:

            // MST2SST
            // 1. Tx DSC Cap On
            // 2. Virtual_DPCD_160[1] = 1 or Tx Sink DPCD_160[0] = 1

            break;

        case _STREAM_CLONE:

            // CLONE
            // 1. Tx DSC Cap On
            // 2. Tx DSC Cap Match PPS(version/Slice/Buffer...)
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : VESA Pass Through Data Path Judge
// Input Value  : EnumDpStreamType
// Output Value : EnumDpStreamDataPath
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpStreamVesaPassThroughDataPathJudge(EnumDpStreamType enumDpStreamType)
{
    EnumDpLinkChannelCodingType enumDpRxCodingType = _CODING_TYPE_8B10B;
    EnumDpLinkChannelCodingType enumDpTxCodingType = _CODING_TYPE_8B10B;
    EnumDpLinkChannelCodingTypeConversion enumCodingTypeConvert = _CODINT_TYPE_CONVERSION_NODEFINE;
    EnumDpStreamDataPath enumDataPath = _DATA_PATH_NONE;

    // DP2.0 to DP2.0 : VESA Bypass
    // DP2.0 to DP1.4 : VESA Reorder
    // DP1.4 to DP2.0 : No Support Reorder
    // DP1.4 to DP1.4 : VESA Reorder

    if(enumDpStreamType == _STREAM_CLONE)
    {
        if(GET_DP_MAC_TX_CLONE_INPUT_PORT_TYPE() != _PORT_DP)
        {
            DebugMessageDpRx("[Stream Management] Vesa Pass Through Not Dp Clone Case", 1);
            return _DATA_PATH_VESA;
        }
    }

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    enumDpRxCodingType = ScalerDpStreamGetRxCodingType(enumDpStreamType);
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    enumDpTxCodingType = ScalerDpMacTxGetChannelCodingType();
#endif

    enumCodingTypeConvert = (EnumDpLinkChannelCodingTypeConversion)(((enumDpRxCodingType & 0x0F) << 4) | (enumDpTxCodingType & 0x0F));


    switch(enumCodingTypeConvert)
    {
        case _CODING_TYPE_128B132B_TO_128B132B:

            enumDataPath = _DATA_PATH_VIDEO_BYPASS;

            break;

        case _CODING_TYPE_128B132B_TO_8B10B:

            enumDataPath = _DATA_PATH_VIDEO_REORDER;

            break;

        case _CODING_TYPE_8B10B_TO_128B132B:

            DebugMessageDpRx("[Stream Management] Data Path Error : VESA Reorder no support (DP14 to DP20)!", enumDpStreamType);
            enumDataPath = _DATA_PATH_INVALID;

            break;

        case _CODING_TYPE_8B10B_TO_8B10B:

            enumDataPath = _DATA_PATH_VIDEO_REORDER;

            break;

        default:

            enumDataPath = _DATA_PATH_INVALID;
            DebugMessageDpRx("[Stream Management] Data Path Error : no this case", enumDpStreamType);

            break;
    }

    if(enumDataPath == _DATA_PATH_VIDEO_REORDER)
    {
        if(ScalerDpStreamVideoReorderSupportCheck(enumDpStreamType) == _FALSE)
        {
            enumDataPath = _DATA_PATH_INVALID;
        }
    }

    DebugMessageDpRx("[Stream Management] Data Path (VESA Passthrough) Judge Result :", enumDataPath);

    return enumDataPath;
}

//--------------------------------------------------
// Description  : DSC Pass Through Data Path Judge
// Input Value  : ucCodingType
// Output Value : EnumDpStreamDataPath
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpStreamDscPassThroughDataPathJudge(EnumDpStreamType enumDpStreamType)
{
    EnumDpLinkChannelCodingType enumDpRxCodingType = _CODING_TYPE_8B10B;
    EnumDpLinkChannelCodingType enumDpTxCodingType = _CODING_TYPE_8B10B;
    EnumDpLinkChannelCodingTypeConversion enumCodingTypeConvert = _CODINT_TYPE_CONVERSION_NODEFINE;

    enumDpStreamType = enumDpStreamType;

    // DP2.0 to DP2.0 : DSC Bypass
    // DP2.0 to DP1.4 : DSC Reorder
    // DP1.4 to DP2.0 : No Support Reorder, Must Decoder!
    // DP1.4 to DP1.4 : DSC Reorder

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    enumDpRxCodingType = ScalerDpStreamGetRxCodingType(enumDpStreamType);
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    enumDpTxCodingType = ScalerDpMacTxGetChannelCodingType();
#endif

    enumCodingTypeConvert = (EnumDpLinkChannelCodingTypeConversion)(((enumDpRxCodingType & 0x0F) << 4) | (enumDpTxCodingType & 0x0F));

    DebugMessageDpRx("[Stream Management] Data Path Judge:", enumCodingTypeConvert);

    switch(enumCodingTypeConvert)
    {
        case _CODING_TYPE_128B132B_TO_128B132B:
            return _DATA_PATH_DSC_BYPASS;

        case _CODING_TYPE_128B132B_TO_8B10B:
            return _DATA_PATH_DSC_REORDER;

        case _CODING_TYPE_8B10B_TO_8B10B:
            return _DATA_PATH_DSC_REORDER;

        default:
            DebugMessageDpRx("[Stream Management] Data Path Error : no this case", enumCodingTypeConvert);
            return _DATA_PATH_INVALID;
    }
}

//--------------------------------------------------
// Description  : Dp Stream VESA Data Path Judge (Coding Type)
// Input Value  : EnumDpStreamType
// Output Value : EnumDpStreamDataPath
//--------------------------------------------------
EnumDpStreamDataPath ScalerDpStreamVesaCodingTypeDataPathJudge(EnumDpStreamType enumDpStreamType)
{
    EnumDpLinkChannelCodingType enumDpRxCodingType = _CODING_TYPE_8B10B;
    EnumDpLinkChannelCodingType enumDpTxCodingType = _CODING_TYPE_8B10B;
    EnumDpLinkChannelCodingTypeConversion enumCodingTypeConvert = _CODINT_TYPE_CONVERSION_NODEFINE;
    EnumDpStreamDataPath enumDataPath = _DATA_PATH_NONE;

    if(enumDpStreamType == _STREAM_CLONE)
    {
        if(GET_DP_MAC_TX_CLONE_INPUT_PORT_TYPE() != _PORT_DP)
        {
            DebugMessageDpRx("[Stream Management] VESA Not Dp Clone Case", 1);
            return _DATA_PATH_VESA;
        }
    }

    // DP2.0 to DP2.0 : VESA Bypass
    // DP2.0 to DP1.4 : VESA
    // DP1.4 to DP2.0 : VESA
    // DP1.4 to DP1.4 : VESA

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    enumDpRxCodingType = ScalerDpStreamGetRxCodingType(enumDpStreamType);
#endif

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    enumDpTxCodingType = ScalerDpMacTxGetChannelCodingType();
#endif

    enumCodingTypeConvert = (EnumDpLinkChannelCodingTypeConversion)(((enumDpRxCodingType & 0x0F) << 4) | (enumDpTxCodingType & 0x0F));

    switch(enumCodingTypeConvert)
    {
        case _CODING_TYPE_128B132B_TO_128B132B:

            enumDataPath = _DATA_PATH_VIDEO_BYPASS;

            break;

        case _CODING_TYPE_8B10B_TO_128B132B:

            DebugMessageDpRx("[Stream Management] VESA Passthrough no support (DP14 to DP20)!", enumDpStreamType);
            enumDataPath = _DATA_PATH_VESA;

            break;

        case _CODING_TYPE_128B132B_TO_8B10B:
        case _CODING_TYPE_8B10B_TO_8B10B:

            enumDataPath = _DATA_PATH_VESA;

            break;

        default:

            enumDataPath = _DATA_PATH_INVALID;
            DebugMessageDpRx("[Stream Management] Data Path Error : no this case", enumDpStreamType);

            break;
    }

    DebugMessageDpRx("[Stream Management] Data Path (By Coding Type) Judge Result :", enumDataPath);

    return enumDataPath;
}

//--------------------------------------------------
// Description  : VESA Recorder Check
// Input Value  : EnumDpStreamType
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpStreamVideoReorderSupportCheck(EnumDpStreamType enumDpStreamType)
{
    // VESA Reorder Check Start
    // MST Mode (include DP20) : Tx Lane count must 4lane
    // SST Mode : Tx Lane count must equal to Rx Lane count
    EnumDpLaneCount enumRxLaneCount = _DP_LINK_NO_LANE;
    EnumDpLaneCount enumTxLaneCount = _DP_LINK_NO_LANE;

    enumRxLaneCount = ScalerDpStreamGetRxLaneCount(enumDpStreamType);

    enumTxLaneCount = GET_DP_MAC_TX_DOWNSTREAM_LANE_NUM();

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpStreamGetRxCodingType(enumDpStreamType) == _CODING_TYPE_128B132B)
    {
        if(enumTxLaneCount != _DP_LINK_4_LANE)
        {
            DebugMessageDpRx("[Stream Management] Can't Enable VESA Reorder because TX isn't 4 Lane @ DP20 Rx", enumTxLaneCount);
            return _FALSE;
        }
    }
#endif

    if(enumDpStreamType == _STREAM_MST2SST)
    {
        if(enumTxLaneCount != _DP_LINK_4_LANE)
        {
            DebugMessageDpRx("[Stream Management] Can't Enable VESA Reorder because TX isn't 4 Lane @ MST mode", enumTxLaneCount);
            return _FALSE;
        }
    }
    else if(enumDpStreamType == _STREAM_CLONE)
    {
        if(enumTxLaneCount != enumRxLaneCount)
        {
            DebugMessageDpRx("[Stream Management] Can't Enable VESA Reorder because TX Lane != Rx Lane @ SST mode", enumTxLaneCount);
            return _FALSE;
        }
    }

    // HBE
    return _TRUE;
}

//--------------------------------------------------
// Description  : DP Stream Bandwidth Check
// Input Value  : EnumDpStreamType
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpStreamBandWidthCheck(EnumDpStreamType enumDpStreamType, EnumDpStreamDataPath enumDataPath)
{
    EnumColorSpace enumColorSpace = _COLOR_SPACE_RGB;
    DWORD ulTxPortLinkBW = 0x00;
    DWORD ulDataPathLinkBWRequest = 0x00;
    BYTE ucColorDepth = 0x00;
    WORD usDataBitsPerPixel = 0x00;

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    WORD usDataPathPixelClk = 0x00;
#endif

    switch(enumDataPath)
    {
        case _DATA_PATH_VESA:
        case _DATA_PATH_VIDEO_REORDER:
        case _DATA_PATH_VIDEO_BYPASS:
        case _DATA_PATH_DSC_DECODER:

            // Rx VESA BW = Rx Pixel Clk * BitPerPixel (ColorDepth * ColorSpace)
            // Tx Link BW = Tx link Rate * Lane Num *24
            ucColorDepth = ScalerDpStreamGetRxVideoElement(enumDpStreamType, _COLOR_DEPTH);
            enumColorSpace = ScalerDpStreamGetRxVideoElement(enumDpStreamType, _COLOR_SPACE);

            if(enumColorSpace == _COLOR_SPACE_Y_ONLY)
            {
                usDataBitsPerPixel = ucColorDepth;
            }
            else if(enumColorSpace == _COLOR_SPACE_YCBCR422)
            {
                usDataBitsPerPixel = ucColorDepth * 2;
            }
            else if(enumColorSpace == _COLOR_SPACE_YCBCR420)
            {
                usDataBitsPerPixel = ucColorDepth * 3 / 2;
            }
            else
            {
                usDataBitsPerPixel = ucColorDepth * 3;
            }

            ulDataPathLinkBWRequest = (DWORD)GET_DP_STREAM_INPUT_PIXEL_CLK_BW() * usDataBitsPerPixel;

            break;

        case _DATA_PATH_DSC_REORDER:
        case _DATA_PATH_DSC_BYPASS:

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
            // Rx DSC BW = Rx Pixel Clk * BitPerPixel (PPS)
            // Tx Link BW = Tx link Rate * Lane Num *24
            usDataBitsPerPixel = ScalerDpStreamGetRxDscElement(enumDpStreamType, _PPS_BITS_PER_PIXEL);

            usDataPathPixelClk = (WORD)(ScalerDpStreamGetRxVideoElement(enumDpStreamType, _PIXEL_CLOCK));

            // Check DSC PPS Color Space Mode: BPP Need To Div 2 On 422/420 Mode
            if(ScalerDpStreamGetRxDscElement(enumDpStreamType, _PPS_NATIVE_MODE) == _TRUE)
            {
                usDataBitsPerPixel = usDataBitsPerPixel >> 1;
            }

            if(ScalerDpStreamGetRxDscElement(enumDpStreamType, _PPS_NATIVE_420) == _TRUE)
            {
                usDataPathPixelClk *= 2;
            }

            DebugMessageDpRx("[Stream BW] DSC Bit Per Pixel", usDataBitsPerPixel);
            DebugMessageDpRx("[Stream BW] DSC Pixel Clk", usDataPathPixelClk);

            ulDataPathLinkBWRequest = (((DWORD)usDataPathPixelClk * usDataBitsPerPixel) >> 4) + 1;
#endif

            break;

        default:

            return _TRUE;

            break;
    }

    // Tx Link BW = Tx link Rate * Lane Num *24
    ulTxPortLinkBW = (DWORD)ScalerDpMacTxGetLinkBw() * 24;

    if(enumDpStreamType == _STREAM_MST2SST)
    {
        if(ulDataPathLinkBWRequest <= ulTxPortLinkBW)
        {
            return _TRUE;
        }
    }
    else if(enumDpStreamType == _STREAM_CLONE)
    {
#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(GET_DP_MAC_TX_DOWNSTREAM_CODING_TYPE() == _CODING_TYPE_128B132B)
        {
            // Tx Link BW * 10 / 8 * 0.9671 > Input BW ==> Tx Link BW > Input BW * 8000 / 9671
            if(ulTxPortLinkBW >= ScalerGlobalComputeDwordMulDiv(ulDataPathLinkBWRequest, 8000, 9671))
            {
                return _TRUE;
            }
            else
            {
                return _FALSE;
            }
        }
        else
#endif
        {
            switch(enumDataPath)
            {
                case _DATA_PATH_VESA:
                case _DATA_PATH_VIDEO_REORDER:
                case _DATA_PATH_VIDEO_BYPASS:

                    // Rx VESA BW = Rx Pixel Clk * BitPerPixel (ColorDepth * ColorSpace) * (FEC 2.4% + SSC 0.5%)
                    if(ulTxPortLinkBW >= ((GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (ScalerGlobalComputeDwordMulDiv(ulDataPathLinkBWRequest, 1029, 1000)) : (ScalerGlobalComputeDwordMulDiv(ulDataPathLinkBWRequest, 1024, 1000))))
                    {
#if(_DP_TX_FEC_SUPPORT == _ON)
                        SET_DP_TX_FEC_CLONE_ENABLE_8B10B();
#endif
                        return _TRUE;
                    }
                    else if(ulTxPortLinkBW >= ((GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (ScalerGlobalComputeDwordMulDiv(ulDataPathLinkBWRequest, 1005, 1000)) : ulDataPathLinkBWRequest))
                    {
#if(_DP_TX_FEC_SUPPORT == _ON)
                        CLR_DP_TX_FEC_CLONE_ENABLE_8B10B();
#endif
                        return _TRUE;
                    }
                    else
                    {
                        return _FALSE;
                    }

                case _DATA_PATH_DSC_REORDER:
                case _DATA_PATH_DSC_BYPASS:

                    // Rx DSC BW = Rx Pixel Clk * BitPerPixel (PPS) * (FEC 2.4% + SSC 0.5%)
                    if(ulTxPortLinkBW >= ((GET_DP_MAC_TX_DOWNSTREAM_DOWN_SPREAD() == _ENABLE) ? (ScalerGlobalComputeDwordMulDiv(ulDataPathLinkBWRequest, 1029, 1000)) : (ScalerGlobalComputeDwordMulDiv(ulDataPathLinkBWRequest, 1024, 1000))))
                    {
#if(_DP_TX_FEC_SUPPORT == _ON)
                        SET_DP_TX_FEC_CLONE_ENABLE_8B10B();
#endif
                        return _TRUE;
                    }
                    else
                    {
#if(_DP_TX_FEC_SUPPORT == _ON)
                        CLR_DP_TX_FEC_CLONE_ENABLE_8B10B();
#endif
                        return _FALSE;
                    }

                default:
                    break;
            }
        }
    }

    return _FALSE;
}
#endif

//--------------------------------------------------
// Description  : DP Stream Get Rx Coding Type
// Input Value  : EnumDpStreamType
// Output Value : EnumDpLinkChannelCodingType
//--------------------------------------------------
EnumDpLinkChannelCodingType ScalerDpStreamGetRxCodingType(EnumDpStreamType enumDpStreamType)
{
    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:
        case _STREAM_MST2SST:

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
            return ScalerDpAuxRxGetCodingType(ScalerDpRxGetInputPortMappingSourceType(ScalerDpStreamTypeSourceTypeMapping(enumDpStreamType)));
#else
            return _CODING_TYPE_8B10B;
#endif

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_CLONE:

#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
            return ScalerDpAuxRxGetCodingType(GET_DP_RX_MAIN_PORT());
#else
            return _CODING_TYPE_8B10B;
#endif

#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : DP Stream Get Rx Lane Count
// Input Value  : EnumDpStreamType
// Output Value : BYTE
//--------------------------------------------------
EnumDpLaneCount ScalerDpStreamGetRxLaneCount(EnumDpStreamType enumDpStreamType)
{
    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:
        case _STREAM_MST2SST:
            return ScalerDpAuxRxGetLaneCount(ScalerDpRxGetInputPortMappingSourceType(ScalerDpStreamTypeSourceTypeMapping(enumDpStreamType)));

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_CLONE:
            return ScalerDpAuxRxGetLaneCount(GET_DP_MAC_TX_CLONE_INPUT_PORT());
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : DP Stream Get Rx Input Pixel Clk
// Input Value  : EnumDpStreamType
// Output Value : WORD Input Pixel Clk
//--------------------------------------------------
WORD ScalerDpStreamGetRxInputPixelClk(EnumDpStreamType enumDpStreamType)
{
    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:
        case _STREAM_MST2SST:
            return ScalerDpRxGetInputPixelClock(ScalerDpRxGetInputPortMappingSourceType((ScalerDpStreamTypeSourceTypeMapping(enumDpStreamType))));

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_CLONE:
            return ScalerDpRxGetInputPixelClock(GET_DP_MAC_TX_CLONE_INPUT_PORT());
#endif

        default:
            break;
    }

    return 0;
}

//--------------------------------------------------
// Description  : DP Stream Get Rx Video Element
// Input Value  : EnumDpStreamType, EnumDpStreamElement
// Output Value : WORD
//--------------------------------------------------
DWORD ScalerDpStreamGetRxVideoElement(EnumDpStreamType enumDpStreamType, EnumDpStreamElement enumElement)
{
    EnumDpMacStreamSourceType enumMacSource = _STREAM_SOURCE_NONE;

    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:
        case _STREAM_MST2SST:
            enumMacSource = ScalerDpStreamTypeSourceTypeMapping(enumDpStreamType);

            if(enumElement == _PIXEL_CLOCK)
            {
                // Data Path Pixel Clk unit : 0.1MHz
                return (ScalerDpMacStreamRxGetElement(enumMacSource, _PIXEL_CLOCK) / 100000);
            }
            else
            {
                return ScalerDpMacStreamRxGetElement(enumMacSource, enumElement);
            }

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_CLONE:
            enumMacSource = ScalerDpRxDxMacSourceMapping(GET_DP_RX_MAIN_PORT());

            if(enumElement == _PIXEL_CLOCK)
            {
                return (ScalerDpMacStreamRxGetElement(enumMacSource, _PIXEL_CLOCK) / 100000);
            }
            else if(enumElement == _COLOR_DEPTH)
            {
                return ScalerSyncDpGetColorDepthValue(ScalerDpMacStreamRxGetElement(enumMacSource, _COLOR_DEPTH), ScalerDpMacStreamRxGetElement(enumMacSource, _COLOR_SPACE));
            }
            else
            {
                return ScalerDpMacStreamRxGetElement(enumMacSource, enumElement);
            }
#endif

        default:
            break;
    }

    return 0;
}

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
//--------------------------------------------------
// Description  : DP Stream Enable Dsc Decoder Check
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerDpStreamDscDecodeCheck(EnumDpStreamType enumDpStreamType)
{
    switch(enumDpStreamType)
    {
        case _STREAM_MST2SST:

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
            return ScalerDpMacMstToSstDscDecodeCheck();
#endif
            break;

        default:
            break;
    }

    return _FALSE;
}

//--------------------------------------------------
// Description  : DP Stream Get DSC Element
// Input Value  : EnumDpStreamType, EnumDpStreamElement
// Output Value : WORD
//--------------------------------------------------
WORD ScalerDpStreamGetRxDscElement(EnumDpStreamType enumDpStreamType, EnumDpStreamPpsElement enumElement)
{
    EnumDpMacSel enumMacSel = _DP_MAC_NONE;

    switch(enumDpStreamType)
    {
        case _STREAM_D0_DP:
        case _STREAM_D1_DP:
        case _STREAM_D2_DP:
        case _STREAM_PXP:
        case _STREAM_MST2SST:

            enumMacSel = ScalerDpRxGetMacSwitchMappingSourceType((ScalerDpStreamTypeSourceTypeMapping(enumDpStreamType)));
            break;

#if(_DP_TX_SUPPORT == _ON)
        case _STREAM_CLONE:
            enumMacSel = ScalerDpRxGetMacSwitch(GET_DP_MAC_TX_CLONE_INPUT_PORT());
            break;
#endif

        default:
            break;
    }

    if(ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumMacSel) != _DSC_MAC_NONE)
    {
        return ScalerDscDecoderGetElement(ScalerDscDecoderDpMacRxxGetDscDecoderMac(enumMacSel), enumElement);
    }
    else
    {
        return ScalerDpMacStreamRxGetPpsElementInfo(enumMacSel, enumElement);
    }
}
#endif

//--------------------------------------------------
// Description  : DP Stream Data Path Max Pixel Clk Check
// Input Value  : EnumDpStreamType
// Output Value : bit _TRUE or _FALSE
//--------------------------------------------------
bit ScalerDpStreamDataPathMaxPixelClkCheck(EnumDpStreamType enumDpStreamType)
{
    WORD usDataPathPixelClk = 0x00;
    WORD usDataPathMaxBW = 0x00;

    EnumDpStreamPixelMode enumRxOutputPixelMode = _1_PIXEL_MODE;
    EnumDpStreamPixelMode enumTxInputPixelMode = _1_PIXEL_MODE;

    // Data Path Pixel Clk unit : 0.1MHz
    usDataPathPixelClk = (WORD)(ScalerDpStreamGetRxVideoElement(enumDpStreamType, _PIXEL_CLOCK));

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDpStreamGetInfoType(enumDpStreamType) == _INFO_TYPE_DSC)
    {
        if(ScalerDpStreamGetRxDscElement(enumDpStreamType, _PPS_NATIVE_420) == _TRUE)
        {
            // Color Space: YUV420, Stream Pixel ClK for BW Calc Should be 2 Times Rx Pixel Clk
            SET_DP_STREAM_INPUT_PIXEL_CLK_BW(usDataPathPixelClk * 2);
        }
        else
        {
            SET_DP_STREAM_INPUT_PIXEL_CLK_BW(usDataPathPixelClk);
        }
    }
    else
#endif
    {
        // Color Space: YUV420, Stream Pixel ClK for BW Calc Should be 2 Times Rx Pixel Clk
        if(ScalerDpStreamGetRxVideoElement(enumDpStreamType, _COLOR_SPACE) == _COLOR_SPACE_YCBCR420)
        {
            SET_DP_STREAM_INPUT_PIXEL_CLK_BW(usDataPathPixelClk * 2);
        }
        else
        {
            SET_DP_STREAM_INPUT_PIXEL_CLK_BW(usDataPathPixelClk);
        }
    }

    DebugMessageDpRx("[Stream Management] Rx Stream BW (Pixel Clk Domain (0.1MHz))", GET_DP_STREAM_INPUT_PIXEL_CLK_BW());

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    if(ScalerDpStreamGetInfoType(enumDpStreamType) == _INFO_TYPE_DSC)
    {
        if(((ScalerDpStreamGetRxDscElement(enumDpStreamType, _PPS_HOR_SLICE_COUNT) >= 8) && (ScalerDpStreamGetRxDscElement(enumDpStreamType, _PPS_NATIVE_420) != _TRUE)) ||
           (usDataPathPixelClk >= (GET_DWORD_MUL_DIV(_HW_DSC_DATA_PATH_MAX_BOUNDARY, 101, 100) * 2)))
        {
            enumRxOutputPixelMode = _4_PIXEL_MODE;
        }
        else
        {
            enumRxOutputPixelMode = _2_PIXEL_MODE;
        }
    }
    else
#endif
    {
#if(_DP_RX_128B132B_CODING_TYPE_SUPPORT == _ON)
        if(ScalerDpStreamGetRxCodingType(enumDpStreamType) == _CODING_TYPE_128B132B)
        {
            enumRxOutputPixelMode = _4_PIXEL_MODE;
        }
        else
#endif
        {
            enumRxOutputPixelMode = _2_PIXEL_MODE;
        }
    }

#if(_DP_TX_128B132B_CODING_TYPE_SUPPORT == _ON)
    if(ScalerDpMacTxGetChannelCodingType() == _CODING_TYPE_128B132B)
    {
        enumTxInputPixelMode = _4_PIXEL_MODE;
    }
    else
#endif
    {
        enumTxInputPixelMode = _2_PIXEL_MODE;
    }

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
    // Calculate Tx Input Data Path Max Pixel Clk
    if(ScalerDpStreamGetInfoType(enumDpStreamType) == _INFO_TYPE_DSC)
    {
        usDataPathMaxBW = _HW_DSC_DATA_PATH_MAX_BOUNDARY * (_BIT0 << enumTxInputPixelMode);
    }
    else
#endif
    {
        usDataPathMaxBW = _HW_DATA_PATH_SPEED_LIMIT * (_BIT0 << enumTxInputPixelMode);
    }


    if(enumRxOutputPixelMode > enumTxInputPixelMode)
    {
        if(usDataPathPixelClk > usDataPathMaxBW)
        {
            // For Rx DP2.0 PixelClk > 1400MHz @ 4 Pixel Mode, Tx DP1.4 @ 2 Pixel Mode ==> Reorder
            return _FALSE;
        }
        else
        {
            // For Rx DP2.0 PixelClk <= 1400MHz @ 1/2/4 Pixel Mode, Tx DP1.4 @ 2 Pixel Mode ==> VESA
            return _TRUE;
        }
    }
    else
    {
        // For Rx Pixel Mode = Tx Pixel Mode ==> VESA
        return _TRUE;
    }
}
#endif
