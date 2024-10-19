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
// ID Code      : ScalerDscDecoder0Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DSC_MAC_DECODER_0_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DSC_MAC_0_DPF_CTRL_REG                             P7_30_DPF_CTRL_0

#define GET_DSC0_VERSION_CURRENT()                          (ScalerGetByte(P6_00_DSC_PPS_00))
#define GET_DSC0_PIC_HEIGHT_CURRENT()                       (ScalerGetWord(P6_06_DSC_PPS_06))
#define GET_DSC0_PIC_WIDTH_CURRENT()                        (ScalerGetWord(P6_08_DSC_PPS_08))
#define GET_DSC0_SLICE_HEIGHT_CURRENT()                     (ScalerGetWord(P6_0A_DSC_PPS_10))
#define GET_DSC0_SLICE_WIDTH_CURRENT()                      (ScalerGetWord(P6_0C_DSC_PPS_12))
#define GET_DSC0_CHUNK_SIZE_CURRENT()                       (ScalerGetWord(P6_0E_DSC_PPS_14))
#define GET_DSC0_INIT_DEC_DELAY_CURRENT()                   (ScalerGetWord(P6_12_DSC_PPS_18))
#define GET_DSC0_RC_MODEL_SIZE_CURRENT()                    (ScalerGetWord(P6_26_DSC_PPS_38))
#define GET_DSC0_COLOR_BPP_CURRENT()                        ((WORD)(((ScalerGetByte(P6_04_DSC_PPS_04) & 0x03) << 8) | ScalerGetByte(P6_05_DSC_PPS_05)))
#define GET_DSC0_COLOR_BPC_CURRENT()                        (ScalerGetBit(P6_03_DSC_PPS_03, (_BIT7 | _BIT6 | _BIT5 | _BIT4)) >> 4)
#define GET_DSC0_COLOR_NATIVE_420_CURRENT()                 ((ScalerGetBit(P6_58_DSC_PPS_88, _BIT1) == _BIT1) ? _TRUE : _FALSE)
#define GET_DSC0_COLOR_NATIVE_422_CURRENT()                 ((ScalerGetBit(P6_58_DSC_PPS_88, _BIT0) == _BIT0) ? _TRUE : _FALSE)
#define GET_DSC0_COLOR_SIMPLE_422_CURRENT()                 ((ScalerGetBit(P6_04_DSC_PPS_04, _BIT3) == _BIT3) ? _TRUE : _FALSE)
#define GET_DSC0_COLOR_RGB_CURRENT()                        ((ScalerGetBit(P6_04_DSC_PPS_04, _BIT4) == _BIT4) ? _TRUE : _FALSE)

#define GET_DSC0_2X_SPEED()                                 (ScalerGetBit(P7_01_DSC_DEC_CTRL_01, _BIT0) >> 0)
#define SET_DSC0_2X_SPEED()                                 {ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~_BIT0, _BIT0);}
#define CLR_DSC0_2X_SPEED()                                 {ScalerSetBit(P7_01_DSC_DEC_CTRL_01, ~_BIT0, 0x00);}

#define GET_DSC0_VERSION()                                  (g_stDscDecoder0MacInfo.ucDscVersion)
#define SET_DSC0_VERSION(x)                                 (g_stDscDecoder0MacInfo.ucDscVersion = (x))
#define CLR_DSC0_VERSION()                                  (g_stDscDecoder0MacInfo.ucDscVersion = 0)

#define GET_DSC0_PIC_HEIGHT()                               (g_stDscDecoder0MacInfo.usDscPicHeight)
#define SET_DSC0_PIC_HEIGHT(x)                              (g_stDscDecoder0MacInfo.usDscPicHeight = (x))
#define CLR_DSC0_PIC_HEIGHT()                               (g_stDscDecoder0MacInfo.usDscPicHeight = 0)

#define GET_DSC0_PIC_WIDTH()                                (g_stDscDecoder0MacInfo.usDscPicWidth)
#define SET_DSC0_PIC_WIDTH(x)                               (g_stDscDecoder0MacInfo.usDscPicWidth = (x))
#define CLR_DSC0_PIC_WIDTH()                                (g_stDscDecoder0MacInfo.usDscPicWidth = 0)

#define GET_DSC0_SLICE_HEIGHT()                             (g_stDscDecoder0MacInfo.usDscSliceHeight)
#define SET_DSC0_SLICE_HEIGHT(x)                            (g_stDscDecoder0MacInfo.usDscSliceHeight = (x))
#define CLR_DSC0_SLICE_HEIGHT()                             (g_stDscDecoder0MacInfo.usDscSliceHeight = 0)

#define GET_DSC0_SLICE_WIDTH()                              (g_stDscDecoder0MacInfo.usDscSliceWidth)
#define SET_DSC0_SLICE_WIDTH(x)                             (g_stDscDecoder0MacInfo.usDscSliceWidth = (x))
#define CLR_DSC0_SLICE_WIDTH()                              (g_stDscDecoder0MacInfo.usDscSliceWidth = 0)

#define GET_DSC0_HOR_SLICE_CNT()                            (g_stDscDecoder0MacInfo.ucDscHorSliceCnt)
#define SET_DSC0_HOR_SLICE_CNT(x)                           (g_stDscDecoder0MacInfo.ucDscHorSliceCnt = (x))
#define CLR_DSC0_HOR_SLICE_CNT()                            (g_stDscDecoder0MacInfo.ucDscHorSliceCnt = 0)

#define GET_DSC0_CHUNK_SIZE()                               (g_stDscDecoder0MacInfo.usDscChunkSize)
#define SET_DSC0_CHUNK_SIZE(x)                              (g_stDscDecoder0MacInfo.usDscChunkSize = (x))
#define CLR_DSC0_CHUNK_SIZE()                               (g_stDscDecoder0MacInfo.usDscChunkSize = 0)

#define GET_DSC0_INIT_DEC_DELAY()                           (g_stDscDecoder0MacInfo.usDscInitDecDelay)
#define SET_DSC0_INIT_DEC_DELAY(x)                          (g_stDscDecoder0MacInfo.usDscInitDecDelay = (x))
#define CLR_DSC0_INIT_DEC_DELAY()                           (g_stDscDecoder0MacInfo.usDscInitDecDelay = 0)

#define GET_DSC0_RC_MODEL_SIZE()                            (g_stDscDecoder0MacInfo.usDscRcModelSize)
#define SET_DSC0_RC_MODEL_SIZE(x)                           (g_stDscDecoder0MacInfo.usDscRcModelSize = (x))
#define CLR_DSC0_RC_MODEL_SIZE()                            (g_stDscDecoder0MacInfo.usDscRcModelSize = 0)

#define GET_DSC0_COLOR_BPP()                                (g_stDscDecoder0MacInfo.usDscBitsPerPixel)
#define SET_DSC0_COLOR_BPP(x)                               (g_stDscDecoder0MacInfo.usDscBitsPerPixel = (x))
#define CLR_DSC0_COLOR_BPP()                                (g_stDscDecoder0MacInfo.usDscBitsPerPixel = 0)

#define GET_DSC0_COLOR_BPC()                                (g_stDscDecoder0MacInfo.b4DscBitPerComponent)
#define SET_DSC0_COLOR_BPC(x)                               (g_stDscDecoder0MacInfo.b4DscBitPerComponent = (x))
#define CLR_DSC0_COLOR_BPC()                                (g_stDscDecoder0MacInfo.b4DscBitPerComponent = 0)

#define GET_DSC0_COLOR_NATIVE_420()                         (g_stDscDecoder0MacInfo.b1DscNative420)
#define SET_DSC0_COLOR_NATIVE_420(x)                        (g_stDscDecoder0MacInfo.b1DscNative420 = (x))
#define CLR_DSC0_COLOR_NATIVE_420()                         (g_stDscDecoder0MacInfo.b1DscNative420 = 0)

#define GET_DSC0_COLOR_NATIVE_422()                         (g_stDscDecoder0MacInfo.b1DscNative422)
#define SET_DSC0_COLOR_NATIVE_422(x)                        (g_stDscDecoder0MacInfo.b1DscNative422 = (x))
#define CLR_DSC0_COLOR_NATIVE_422()                         (g_stDscDecoder0MacInfo.b1DscNative422 = 0)

#define GET_DSC0_COLOR_SIMPLE_422()                         (g_stDscDecoder0MacInfo.b1DscSimple422)
#define SET_DSC0_COLOR_SIMPLE_422(x)                        (g_stDscDecoder0MacInfo.b1DscSimple422 = (x))
#define CLR_DSC0_COLOR_SIMPLE_422()                         (g_stDscDecoder0MacInfo.b1DscSimple422 = 0)

#define GET_DSC0_COLOR_NATIVE_MODE()                        (((GET_DSC0_COLOR_NATIVE_420() == _TRUE) || (GET_DSC0_COLOR_NATIVE_422() == _TRUE)) ? _TRUE : _FALSE)

#define GET_DSC0_PIXEL_CLK()                                (g_stDscDecoder0MacInfo.usDscPixelClk)
#define SET_DSC0_PIXEL_CLK(x)                               (g_stDscDecoder0MacInfo.usDscPixelClk = (x))
#define CLR_DSC0_PIXEL_CLK()                                (g_stDscDecoder0MacInfo.usDscPixelClk = 0)

#define GET_DSC0_BUF_CLK()                                  (g_stDscDecoder0MacInfo.usDscBufClk)
#define SET_DSC0_BUF_CLK(x)                                 (g_stDscDecoder0MacInfo.usDscBufClk = (x))
#define CLR_DSC0_BUF_CLK()                                  (g_stDscDecoder0MacInfo.usDscBufClk = 0)

#define GET_DSC0_CLK()                                      (g_stDscDecoder0MacInfo.usDscClk)
#define SET_DSC0_CLK(x)                                     (g_stDscDecoder0MacInfo.usDscClk = (x))
#define CLR_DSC0_CLK()                                      (g_stDscDecoder0MacInfo.usDscClk = 0)

#define GET_DSC0_PIXEL_MODE()                               (g_stDscDecoder0MacInfo.b2DscPixelMode)
#define SET_DSC0_PIXEL_MODE(x)                              (g_stDscDecoder0MacInfo.b2DscPixelMode = (x))
#define CLR_DSC0_PIXEL_MODE()                               (g_stDscDecoder0MacInfo.b2DscPixelMode = 0)

#define GET_DSC0_OUTPUT_CLK()                               (g_stDscDecoder0MacInfo.usDscOutputClk)
#define SET_DSC0_OUTPUT_CLK(x)                              (g_stDscDecoder0MacInfo.usDscOutputClk = (x))
#define CLR_DSC0_OUTPUT_CLK()                               (g_stDscDecoder0MacInfo.usDscOutputClk = 0)

#define GET_DSC0_STREAM_FRAME_RATE()                        (g_stDscDecoder0MacInfo.usDscStreamFrameRate)
#define SET_DSC0_STREAM_FRAME_RATE(x)                       (g_stDscDecoder0MacInfo.usDscStreamFrameRate = (x))
#define CLR_DSC0_STREAM_FRAME_RATE()                        (g_stDscDecoder0MacInfo.usDscStreamFrameRate = 0)

#define GET_DSC0_STREAM_FRAME_DELAY()                       (g_stDscDecoder0MacInfo.ucDscStreamFrameDelay)
#define SET_DSC0_STREAM_FRAME_DELAY(x)                      (g_stDscDecoder0MacInfo.ucDscStreamFrameDelay = (x))
#define CLR_DSC0_STREAM_FRAME_DELAY()                       (g_stDscDecoder0MacInfo.ucDscStreamFrameDelay = 0)

#define GET_DSC0_HTOTAL()                                   (g_stDscDecoder0MacInfo.usDscHTotal)
#define SET_DSC0_HTOTAL(x)                                  (g_stDscDecoder0MacInfo.usDscHTotal = (x))
#define CLR_DSC0_HTOTAL()                                   (g_stDscDecoder0MacInfo.usDscHTotal = 0)

#define GET_DSC0_HC_ACTIVE()                                (g_stDscDecoder0MacInfo.usDscHcActive)
#define SET_DSC0_HC_ACTIVE(x)                               (g_stDscDecoder0MacInfo.usDscHcActive = (x))
#define CLR_DSC0_HC_ACTIVE()                                (g_stDscDecoder0MacInfo.usDscHcActive = 0)

#define GET_DSC0_HC_BLANK()                                 (g_stDscDecoder0MacInfo.usDscHcBlank)
#define SET_DSC0_HC_BLANK(x)                                (g_stDscDecoder0MacInfo.usDscHcBlank = (x))
#define CLR_DSC0_HC_BLANK()                                 (g_stDscDecoder0MacInfo.usDscHcBlank = 0)

#define GET_DSC0_CRC_CALCULATE_DONE()                       (g_stDscDecoder0MacInfo.b1DscCrcDone)
#define SET_DSC0_CRC_CALCULATE_DONE()                       (g_stDscDecoder0MacInfo.b1DscCrcDone = _TRUE)
#define CLR_DSC0_CRC_CALCULATE_DONE()                       (g_stDscDecoder0MacInfo.b1DscCrcDone = _FALSE)

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
#define GET_DSC0_FORCE_BG_ENABLE()                          (g_stDscDecoder0MacInfo.b1DscForceBgEn)
#define SET_DSC0_FORCE_BG_ENABLE()                          (g_stDscDecoder0MacInfo.b1DscForceBgEn = _TRUE)
#define CLR_DSC0_FORCE_BG_ENABLE()                          (g_stDscDecoder0MacInfo.b1DscForceBgEn = _FALSE)
#endif

#define SET_DSC0_PORCH_COLOR_RGB()                          {\
                                                                ScalerSetByte(P7_51_MN_DPF_BG_RED_M, 0x00);\
                                                                ScalerSetByte(P7_52_MN_DPF_BG_RED_L, 0x00);\
                                                                ScalerSetByte(P7_53_MN_DPF_BG_GRN_M, 0x00);\
                                                                ScalerSetByte(P7_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                ScalerSetByte(P7_55_MN_DPF_BG_BLU_M, 0x00);\
                                                                ScalerSetByte(P7_56_MN_DPF_BG_BLU_L, 0x00);\
                                                            }

#define SET_DSC0_PORCH_COLOR_YCC_LIMIT()                    {\
                                                                if(GET_DSC0_COLOR_NATIVE_420() == _TRUE)\
                                                                {\
                                                                    ScalerSetBit(P7_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(P7_52_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetBit(P7_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(P7_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetBit(P7_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(P7_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetBit(P7_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(P7_52_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetBit(P7_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(P7_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetBit(P7_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(P7_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                            }

#define SET_DSC0_PORCH_COLOR_YCC_FULL()                     {\
                                                                if(GET_DSC0_COLOR_NATIVE_420() == _TRUE)\
                                                                {\
                                                                    ScalerSetBit(P7_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(P7_52_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetBit(P7_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(P7_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetBit(P7_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT0);\
                                                                    ScalerSetByte(P7_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                                else\
                                                                {\
                                                                    ScalerSetBit(P7_51_MN_DPF_BG_RED_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(P7_52_MN_DPF_BG_RED_L, 0x00);\
                                                                    ScalerSetBit(P7_53_MN_DPF_BG_GRN_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);\
                                                                    ScalerSetByte(P7_54_MN_DPF_BG_GRN_L, 0x00);\
                                                                    ScalerSetBit(P7_55_MN_DPF_BG_BLU_M, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), _BIT3);\
                                                                    ScalerSetByte(P7_56_MN_DPF_BG_BLU_L, 0x00);\
                                                                }\
                                                            }

#define SET_DSC_DECODER_MAC_0_STREAM_SOURCE(x)              {ScalerSetBit(P31_73_FB_ALL_DSC_SEL, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (x))}
#define GET_DSC_DECODER_MAC_0_STREAM_SOURCE()               (ScalerGetByte(P31_73_FB_ALL_DSC_SEL) & (_BIT3 | _BIT2 | _BIT1 | _BIT0))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDscMacInfo g_stDscDecoder0MacInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDscDecoder0MacReset(void);
extern void ScalerDscDecoder0SetDecodeType(void);
extern bit ScalerDscDecoder0MacScanInputPort(void);
extern void ScalerDscDecoder0SetFifoIRQ(bit bEn);
extern bit ScalerDscDecoder0CheckFifoIRQ(void);
extern BYTE ScalerDscDecoder0GetFifoStatus(void);
extern void ScalerDscDecoder0SetFifoWD(bit bEn);
extern void ScalerDscDecoder0SetForceToBackGround(bit bEn);
extern void ScalerDscDecoder0IntHandler_EXINT0(void);
extern bit ScalerDscDecoder0FifoCheck(EnumDscFifoCheckCondition enumDscFifoCheckCondition);
extern bit ScalerDscDecoder0PpsChangeCheck(void);
extern void ScalerDscDecoder0DecEnable(void);
extern void ScalerDscDecoder0ForceBackgroundSetting(bit bEnable);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoder0DpCrcCalculate(void);
extern bit ScalerDscDecoder0CheckVgipVsBypass(void);
#endif

extern bit ScalerDscDecoder0TimingInfoCheck(StructDscTimingInfo *pstDscTimingInfo);
extern WORD ScalerDscDecoder0GetElement(EnumDpStreamPpsElement enumElement);
extern BYTE ScalerDscDecoder0GetPixelMode(void);

#endif // End of #if(_DSC_MAC_DECODER_0_SUPPORT == _ON)
