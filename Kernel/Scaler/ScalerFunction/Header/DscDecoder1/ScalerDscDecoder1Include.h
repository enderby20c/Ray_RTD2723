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
// ID Code      : ScalerDscDecoder1Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DSC_MAC_DECODER_1_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DSC_MAC_1_DPF_CTRL_REG                             PF5_30_DPF_CTRL_0

#define GET_DSC1_VERSION_CURRENT()                          (ScalerGetByte(PF4_00_DSC_PPS_00))
#define GET_DSC1_PIC_HEIGHT_CURRENT()                       (ScalerGetWord(PF4_06_DSC_PPS_06))
#define GET_DSC1_PIC_WIDTH_CURRENT()                        (ScalerGetWord(PF4_08_DSC_PPS_08))
#define GET_DSC1_SLICE_HEIGHT_CURRENT()                     (ScalerGetWord(PF4_0A_DSC_PPS_10))
#define GET_DSC1_SLICE_WIDTH_CURRENT()                      (ScalerGetWord(PF4_0C_DSC_PPS_12))
#define GET_DSC1_CHUNK_SIZE_CURRENT()                       (ScalerGetWord(PF4_0E_DSC_PPS_14))
#define GET_DSC1_INIT_DEC_DELAY_CURRENT()                   (ScalerGetWord(PF4_12_DSC_PPS_18))
#define GET_DSC1_RC_MODEL_SIZE_CURRENT()                    (ScalerGetWord(PF4_26_DSC_PPS_38))
#define GET_DSC1_COLOR_BPP_CURRENT()                        ((WORD)(((ScalerGetByte(PF4_04_DSC_PPS_04) & 0x03) << 8) | ScalerGetByte(PF4_05_DSC_PPS_05)))
#define GET_DSC1_COLOR_BPC_CURRENT()                        (ScalerGetBit(PF4_03_DSC_PPS_03, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
#define GET_DSC1_COLOR_NATIVE_420_CURRENT()                 ((ScalerGetBit(PF4_58_DSC_PPS_88, _BIT1) == _BIT1) ? _TRUE : _FALSE)
#define GET_DSC1_COLOR_NATIVE_422_CURRENT()                 ((ScalerGetBit(PF4_58_DSC_PPS_88, _BIT0) == _BIT0) ? _TRUE : _FALSE)
#define GET_DSC1_COLOR_SIMPLE_422_CURRENT()                 ((ScalerGetBit(PF4_04_DSC_PPS_04, _BIT3) == _BIT3) ? _TRUE : _FALSE)
#define GET_DSC1_COLOR_RGB_CURRENT()                        ((ScalerGetBit(PF4_04_DSC_PPS_04, _BIT4) == _BIT4) ? _TRUE : _FALSE)

#define GET_DSC1_2X_SPEED()                                 (ScalerGetBit(PF5_01_DSC_DEC_CTRL_01, _BIT0) >> 0)
#define SET_DSC1_2X_SPEED()                                 {ScalerSetBit(PF5_01_DSC_DEC_CTRL_01, ~_BIT0, _BIT0);}
#define CLR_DSC1_2X_SPEED()                                 {ScalerSetBit(PF5_01_DSC_DEC_CTRL_01, ~_BIT0, 0x00);}

#define GET_DSC1_VERSION()                                  (g_stDscDecoder1MacInfo.ucDscVersion)
#define SET_DSC1_VERSION(x)                                 (g_stDscDecoder1MacInfo.ucDscVersion = (x))
#define CLR_DSC1_VERSION()                                  (g_stDscDecoder1MacInfo.ucDscVersion = 0)

#define GET_DSC1_PIC_HEIGHT()                               (g_stDscDecoder1MacInfo.usDscPicHeight)
#define SET_DSC1_PIC_HEIGHT(x)                              (g_stDscDecoder1MacInfo.usDscPicHeight = (x))
#define CLR_DSC1_PIC_HEIGHT()                               (g_stDscDecoder1MacInfo.usDscPicHeight = 0)

#define GET_DSC1_PIC_WIDTH()                                (g_stDscDecoder1MacInfo.usDscPicWidth)
#define SET_DSC1_PIC_WIDTH(x)                               (g_stDscDecoder1MacInfo.usDscPicWidth = (x))
#define CLR_DSC1_PIC_WIDTH()                                (g_stDscDecoder1MacInfo.usDscPicWidth = 0)

#define GET_DSC1_SLICE_HEIGHT()                             (g_stDscDecoder1MacInfo.usDscSliceHeight)
#define SET_DSC1_SLICE_HEIGHT(x)                            (g_stDscDecoder1MacInfo.usDscSliceHeight = (x))
#define CLR_DSC1_SLICE_HEIGHT()                             (g_stDscDecoder1MacInfo.usDscSliceHeight = 0)

#define GET_DSC1_SLICE_WIDTH()                              (g_stDscDecoder1MacInfo.usDscSliceWidth)
#define SET_DSC1_SLICE_WIDTH(x)                             (g_stDscDecoder1MacInfo.usDscSliceWidth = (x))
#define CLR_DSC1_SLICE_WIDTH()                              (g_stDscDecoder1MacInfo.usDscSliceWidth = 0)

#define GET_DSC1_HOR_SLICE_CNT()                            (g_stDscDecoder1MacInfo.ucDscHorSliceCnt)
#define SET_DSC1_HOR_SLICE_CNT(x)                           (g_stDscDecoder1MacInfo.ucDscHorSliceCnt = (x))
#define CLR_DSC1_HOR_SLICE_CNT()                            (g_stDscDecoder1MacInfo.ucDscHorSliceCnt = 0)

#define GET_DSC1_CHUNK_SIZE()                               (g_stDscDecoder1MacInfo.usDscChunkSize)
#define SET_DSC1_CHUNK_SIZE(x)                              (g_stDscDecoder1MacInfo.usDscChunkSize = (x))
#define CLR_DSC1_CHUNK_SIZE()                               (g_stDscDecoder1MacInfo.usDscChunkSize = 0)

#define GET_DSC1_INIT_DEC_DELAY()                           (g_stDscDecoder1MacInfo.usDscInitDecDelay)
#define SET_DSC1_INIT_DEC_DELAY(x)                          (g_stDscDecoder1MacInfo.usDscInitDecDelay = (x))
#define CLR_DSC1_INIT_DEC_DELAY()                           (g_stDscDecoder1MacInfo.usDscInitDecDelay = 0)

#define GET_DSC1_RC_MODEL_SIZE()                            (g_stDscDecoder1MacInfo.usDscRcModelSize)
#define SET_DSC1_RC_MODEL_SIZE(x)                           (g_stDscDecoder1MacInfo.usDscRcModelSize = (x))
#define CLR_DSC1_RC_MODEL_SIZE()                            (g_stDscDecoder1MacInfo.usDscRcModelSize = 0)

#define GET_DSC1_COLOR_BPP()                                (g_stDscDecoder1MacInfo.usDscBitsPerPixel)
#define SET_DSC1_COLOR_BPP(x)                               (g_stDscDecoder1MacInfo.usDscBitsPerPixel = (x))
#define CLR_DSC1_COLOR_BPP()                                (g_stDscDecoder1MacInfo.usDscBitsPerPixel = 0)

#define GET_DSC1_COLOR_BPC()                                (g_stDscDecoder1MacInfo.b4DscBitPerComponent)
#define SET_DSC1_COLOR_BPC(x)                               (g_stDscDecoder1MacInfo.b4DscBitPerComponent = (x))
#define CLR_DSC1_COLOR_BPC()                                (g_stDscDecoder1MacInfo.b4DscBitPerComponent = 0)

#define GET_DSC1_COLOR_NATIVE_420()                         (g_stDscDecoder1MacInfo.b1DscNative420)
#define SET_DSC1_COLOR_NATIVE_420(x)                        (g_stDscDecoder1MacInfo.b1DscNative420 = (x))
#define CLR_DSC1_COLOR_NATIVE_420()                         (g_stDscDecoder1MacInfo.b1DscNative420 = 0)

#define GET_DSC1_COLOR_NATIVE_422()                         (g_stDscDecoder1MacInfo.b1DscNative422)
#define SET_DSC1_COLOR_NATIVE_422(x)                        (g_stDscDecoder1MacInfo.b1DscNative422 = (x))
#define CLR_DSC1_COLOR_NATIVE_422()                         (g_stDscDecoder1MacInfo.b1DscNative422 = 0)

#define GET_DSC1_COLOR_SIMPLE_422()                         (g_stDscDecoder1MacInfo.b1DscSimple422)
#define SET_DSC1_COLOR_SIMPLE_422(x)                        (g_stDscDecoder1MacInfo.b1DscSimple422 = (x))
#define CLR_DSC1_COLOR_SIMPLE_422()                         (g_stDscDecoder1MacInfo.b1DscSimple422 = 0)

#define GET_DSC1_COLOR_NATIVE_MODE()                        (((GET_DSC1_COLOR_NATIVE_420() == _TRUE) || (GET_DSC1_COLOR_NATIVE_422() == _TRUE)) ? _TRUE : _FALSE)

#define GET_DSC1_PIXEL_CLK()                                (g_stDscDecoder1MacInfo.usDscPixelClk)
#define SET_DSC1_PIXEL_CLK(x)                               (g_stDscDecoder1MacInfo.usDscPixelClk = (x))
#define CLR_DSC1_PIXEL_CLK()                                (g_stDscDecoder1MacInfo.usDscPixelClk = 0)

#define GET_DSC1_BUF_CLK()                                  (g_stDscDecoder1MacInfo.usDscBufClk)
#define SET_DSC1_BUF_CLK(x)                                 (g_stDscDecoder1MacInfo.usDscBufClk = (x))
#define CLR_DSC1_BUF_CLK()                                  (g_stDscDecoder1MacInfo.usDscBufClk = 0)

#define GET_DSC1_CLK()                                      (g_stDscDecoder1MacInfo.usDscClk)
#define SET_DSC1_CLK(x)                                     (g_stDscDecoder1MacInfo.usDscClk = (x))
#define CLR_DSC1_CLK()                                      (g_stDscDecoder1MacInfo.usDscClk = 0)

#define GET_DSC1_PIXEL_MODE()                               (g_stDscDecoder1MacInfo.b2DscPixelMode)
#define SET_DSC1_PIXEL_MODE(x)                              (g_stDscDecoder1MacInfo.b2DscPixelMode = (x))
#define CLR_DSC1_PIXEL_MODE()                               (g_stDscDecoder1MacInfo.b2DscPixelMode = 0)

#define GET_DSC1_OUTPUT_CLK()                               (g_stDscDecoder1MacInfo.usDscOutputClk)
#define SET_DSC1_OUTPUT_CLK(x)                              (g_stDscDecoder1MacInfo.usDscOutputClk = (x))
#define CLR_DSC1_OUTPUT_CLK()                               (g_stDscDecoder1MacInfo.usDscOutputClk = 0)

#define GET_DSC1_STREAM_FRAME_RATE()                        (g_stDscDecoder1MacInfo.usDscStreamFrameRate)
#define SET_DSC1_STREAM_FRAME_RATE(x)                       (g_stDscDecoder1MacInfo.usDscStreamFrameRate = (x))
#define CLR_DSC1_STREAM_FRAME_RATE()                        (g_stDscDecoder1MacInfo.usDscStreamFrameRate = 0)

#define GET_DSC1_STREAM_FRAME_DELAY()                       (g_stDscDecoder1MacInfo.ucDscStreamFrameDelay)
#define SET_DSC1_STREAM_FRAME_DELAY(x)                      (g_stDscDecoder1MacInfo.ucDscStreamFrameDelay = (x))
#define CLR_DSC1_STREAM_FRAME_DELAY()                       (g_stDscDecoder1MacInfo.ucDscStreamFrameDelay = 0)

#define GET_DSC1_HTOTAL()                                   (g_stDscDecoder1MacInfo.usDscHTotal)
#define SET_DSC1_HTOTAL(x)                                  (g_stDscDecoder1MacInfo.usDscHTotal = (x))
#define CLR_DSC1_HTOTAL()                                   (g_stDscDecoder1MacInfo.usDscHTotal = 0)

#define GET_DSC1_HC_ACTIVE()                                (g_stDscDecoder1MacInfo.usDscHcActive)
#define SET_DSC1_HC_ACTIVE(x)                               (g_stDscDecoder1MacInfo.usDscHcActive = (x))
#define CLR_DSC1_HC_ACTIVE()                                (g_stDscDecoder1MacInfo.usDscHcActive = 0)

#define GET_DSC1_HC_BLANK()                                 (g_stDscDecoder1MacInfo.usDscHcBlank)
#define SET_DSC1_HC_BLANK(x)                                (g_stDscDecoder1MacInfo.usDscHcBlank = (x))
#define CLR_DSC1_HC_BLANK()                                 (g_stDscDecoder1MacInfo.usDscHcBlank = 0)

#define GET_DSC1_CRC_CALCULATE_DONE()                       (g_stDscDecoder1MacInfo.b1DscCrcDone)
#define SET_DSC1_CRC_CALCULATE_DONE()                       (g_stDscDecoder1MacInfo.b1DscCrcDone = _TRUE)
#define CLR_DSC1_CRC_CALCULATE_DONE()                       (g_stDscDecoder1MacInfo.b1DscCrcDone = _FALSE)

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
#define GET_DSC1_FORCE_BG_ENABLE()                          (g_stDscDecoder1MacInfo.b1DscForceBgEn)
#define SET_DSC1_FORCE_BG_ENABLE()                          (g_stDscDecoder1MacInfo.b1DscForceBgEn = _TRUE)
#define CLR_DSC1_FORCE_BG_ENABLE()                          (g_stDscDecoder1MacInfo.b1DscForceBgEn = _FALSE)
#endif

#define SET_DSC1_PORCH_COLOR_RGB()                          {\
                                                                ScalerSetByte(PF5_51_MN_DPF_BG_RED_M, 0x00);\
                                                                ScalerSetByte(PF5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(PF5_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                ScalerSetByte(PF5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(PF5_55_MN_DPF_BG_BLU_M, 0x00);\
                                                                ScalerSetByte(PF5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }

#define SET_DSC1_PORCH_COLOR_YCC_LIMIT()                    {\
                                                                if(GET_DSC1_COLOR_NATIVE_420() == _TRUE)\
                                                                {\
                                                                    ScalerSetBit(PF5_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(PF5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetBit(PF5_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(PF5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetBit(PF5_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(PF5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetBit(PF5_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(PF5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetBit(PF5_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(PF5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetBit(PF5_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(PF5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                            }

#define SET_DSC1_PORCH_COLOR_YCC_FULL()                     {\
                                                                if(GET_DSC1_COLOR_NATIVE_420() == _TRUE)\
                                                                {\
                                                                    ScalerSetBit(PF5_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(PF5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetBit(PF5_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(PF5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetBit(PF5_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(PF5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetBit(PF5_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(PF5_52_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetBit(PF5_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                    ScalerSetByte(PF5_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetBit(PF5_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(PF5_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                            }

#define SET_DSC_DECODER_MAC_1_STREAM_SOURCE(x)              {ScalerSetBit(P31_73_FB_ALL_DSC_SEL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), (x) << 4)}
#define GET_DSC_DECODER_MAC_1_STREAM_SOURCE()               ((ScalerGetByte(P31_73_FB_ALL_DSC_SEL) & (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDscMacInfo g_stDscDecoder1MacInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDscDecoder1MacReset(void);
extern void ScalerDscDecoder1SetDecodeType(void);
extern bit ScalerDscDecoder1MacScanInputPort(void);
extern void ScalerDscDecoder1SetFifoIRQ(bit bEn);
extern bit ScalerDscDecoder1CheckFifoIRQ(void);
extern BYTE ScalerDscDecoder1GetFifoStatus(void);
extern void ScalerDscDecoder1SetFifoWD(bit bEn);
extern void ScalerDscDecoder1SetForceToBackGround(bit bEn);
extern void ScalerDscDecoder1IntHandler_EXINT0(void);
extern bit ScalerDscDecoder1FifoCheck(EnumDscFifoCheckCondition enumDscFifoCheckCondition);
extern bit ScalerDscDecoder1PpsChangeCheck(void);
extern void ScalerDscDecoder1DecEnable(void);
extern void ScalerDscDecoder1ForceBackgroundSetting(bit bEnable);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoder1DpCrcCalculate(void);
extern bit ScalerDscDecoder1CheckVgipVsBypass(void);
#endif

extern bit ScalerDscDecoder1TimingInfoCheck(StructDscTimingInfo *pstDscTimingInfo);
extern WORD ScalerDscDecoder1GetElement(EnumDpStreamPpsElement enumElement);
extern BYTE ScalerDscDecoder1GetPixelMode(void);

#endif // End of #if(_DSC_MAC_DECODER_1_SUPPORT == _ON)
