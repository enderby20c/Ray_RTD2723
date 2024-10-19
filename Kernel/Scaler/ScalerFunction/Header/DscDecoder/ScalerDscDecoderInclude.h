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
// ID Code      : ScalerDscDecoderInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DSC_DECODER_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DSC_STREAM_CHANGE(x)                        (\
                                                            (((x) == _DSC_STREAM_SOURCE_DP_MAC_RX0) ?\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceDpMacRx0 :\
                                                            (((x) == _DSC_STREAM_SOURCE_DP_MAC_RX1) ?\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceDpMacRx1 :\
                                                            (((x) == _DSC_STREAM_SOURCE_DP_MAC_RX2) ?\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceDpMacRx2 :\
                                                            (((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX3) ?\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceHdmiMacRx3 :\
                                                            (((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX4) ?\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceHdmiMacRx4 :\
                                                            (((x) == _DSC_STREAM_SOURCE_DP_MAC_RX4) ?\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceDpMacRx4 : _FALSE))))))\
                                                        )

#define SET_DSC_STREAM_CHANGE(x, y)                     {\
                                                            if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX0)\
                                                            {\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceDpMacRx0 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX1)\
                                                            {\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceDpMacRx1 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX2)\
                                                            {\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceDpMacRx2 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX3)\
                                                            {\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceHdmiMacRx3 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX4)\
                                                            {\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceHdmiMacRx4 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX4)\
                                                            {\
                                                                g_stDscDecoderStreamChange.b1DscStreamSourceDpMacRx4 = (y);\
                                                            }\
                                                        }

#if(_FW_DP_DSC_MUTE_INSTANT_RECOVER_SUPPORT == _ON)
#define _DSC_FIFO_STABLE_CHECK                          _DSC_FIFO_DELAY_CHECK
#else
#define _DSC_FIFO_STABLE_CHECK                          _DSC_FIFO_POLLING_CHECK
#endif

//--------------------------------------------------
// Macro of DSC D0 Information
//--------------------------------------------------
#define GET_DSC_D0_CAPABILITY_SWITCH()                  ((bit)g_stDscDecoderCapSwitch.b1D0)
#define SET_DSC_D0_CAPABILITY_SWITCH(x)                 (g_stDscDecoderCapSwitch.b1D0 = (x))

//--------------------------------------------------
// Macro of DSC D1 Information
//--------------------------------------------------
#define GET_DSC_D1_CAPABILITY_SWITCH()                  ((bit)g_stDscDecoderCapSwitch.b1D1)
#define SET_DSC_D1_CAPABILITY_SWITCH(x)                 (g_stDscDecoderCapSwitch.b1D1 = (x))

//--------------------------------------------------
// Macro of DSC D2 Information
//--------------------------------------------------
#define GET_DSC_D2_CAPABILITY_SWITCH()                  ((bit)g_stDscDecoderCapSwitch.b1D2)
#define SET_DSC_D2_CAPABILITY_SWITCH(x)                 (g_stDscDecoderCapSwitch.b1D2 = (x))

//--------------------------------------------------
// Macro of DSC D3 Information
//--------------------------------------------------
#define GET_DSC_D3_CAPABILITY_SWITCH()                  ((bit)g_stDscDecoderCapSwitch.b1D3)
#define SET_DSC_D3_CAPABILITY_SWITCH(x)                 (g_stDscDecoderCapSwitch.b1D3 = (x))

//--------------------------------------------------
// Macro of DSC D4 Information
//--------------------------------------------------
#define GET_DSC_D4_CAPABILITY_SWITCH()                  ((bit)g_stDscDecoderCapSwitch.b1D4)
#define SET_DSC_D4_CAPABILITY_SWITCH(x)                 (g_stDscDecoderCapSwitch.b1D4 = (x))

//--------------------------------------------------
// Macro of DSC D5 Information
//--------------------------------------------------
#define GET_DSC_D5_CAPABILITY_SWITCH()                  ((bit)g_stDscDecoderCapSwitch.b1D5)
#define SET_DSC_D5_CAPABILITY_SWITCH(x)                 (g_stDscDecoderCapSwitch.b1D5 = (x))

//--------------------------------------------------
// Macro of DSC Stream Source Dsc Mac Usage
//--------------------------------------------------
#define GET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(x)        (\
                                                            (((x) == _DSC_STREAM_SOURCE_DP_MAC_RX0) ?\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx0 :\
                                                            (((x) == _DSC_STREAM_SOURCE_DP_MAC_RX1) ?\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx1 :\
                                                            (((x) == _DSC_STREAM_SOURCE_DP_MAC_RX2) ?\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx2 :\
                                                            (((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX3) ?\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceHdmiMacRx3 :\
                                                            (((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX4) ?\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceHdmiMacRx4 :\
                                                            (((x) == _DSC_STREAM_SOURCE_DP_MAC_RX4) ?\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx4 : _DSC_MAC_NONE))))))\
                                                        )

#define SET_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(x, y)     {\
                                                            if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX0)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx0 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX1)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx1 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX2)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx2 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX3)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceHdmiMacRx3 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX4)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceHdmiMacRx4 = (y);\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX4)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx4 = (y);\
                                                            }\
                                                        }

#define CLR_DSC_STREAM_SOURCE_DSC_MAC_X_USAGE(x)        {\
                                                            if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX0)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx0 = _DSC_MAC_NONE;\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX1)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx1 = _DSC_MAC_NONE;\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX2)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx2 = _DSC_MAC_NONE;\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX3)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceHdmiMacRx3 = _DSC_MAC_NONE;\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_HDMI_MAC_RX4)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceHdmiMacRx4 = _DSC_MAC_NONE;\
                                                            }\
                                                            else if((x) == _DSC_STREAM_SOURCE_DP_MAC_RX4)\
                                                            {\
                                                                g_stDscDecoderStreamSourceDscMacUsage.b2DscStreamSourceDpMacRx4 = _DSC_MAC_NONE;\
                                                            }\
                                                        }

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1D0 : 1;
    BYTE b1D1 : 1;
    BYTE b1D2 : 1;
    BYTE b1D3 : 1;
    BYTE b1D4 : 1;
    BYTE b1D5 : 1;
}StructDscCapSwitch;

typedef struct
{
    BYTE ucDscVersion;
    WORD usDscPicHeight;
    WORD usDscPicWidth;
    WORD usDscSliceHeight;
    WORD usDscSliceWidth;
    BYTE ucDscHorSliceCnt;
    WORD usDscChunkSize;
    WORD usDscInitDecDelay;
    WORD usDscRcModelSize;
    WORD usDscBitsPerPixel;
    BYTE b4DscBitPerComponent : 4;
    BYTE b1DscNative420 : 1;
    BYTE b1DscNative422 : 1;
    BYTE b1DscSimple422 : 1;
    WORD usDscPixelClk;
    WORD usDscBufClk;
    WORD usDscClk;
    WORD usDscOutputClk;
    BYTE b2DscPixelMode : 2;
    WORD usDscStreamFrameRate;
    BYTE ucDscStreamFrameDelay;
    WORD usDscHTotal;
    WORD usDscHcActive;
    WORD usDscHcBlank;
    BYTE b1DscCrcDone : 1;
    BYTE b1DscForceBgEn : 1;
}StructDscMacInfo;

typedef struct
{
    BYTE b1HSP : 1;             // HSP
    BYTE b1VSP : 1;             // VSP
    BYTE b1Interlace : 1;       // Interlace
    BYTE b1DpInterlaceVBID : 1; // Interlace For Dp VBID
    BYTE b1VideoField : 1;      // Field for video compensation
    WORD usHFreq;               // Horizontal Freq. (unit: 0.1kHz)
    WORD usHTotal;              // Horizontal Total length (unit: Pixel)
    WORD usHTotalAfterDSC;      // Horizontal Total length after DSC compression (unit: Tri-bytes)
    WORD usHWidth;              // Horizontal Active Width (unit: Pixel)
    WORD usHStart;              // Horizontal Start (unit: Pixel)
    WORD usHSWidth;             // Horizontal Sync Pulse Count (unit: SyncProc Clock)
    WORD usHFrontPorch;         // Vertical Front Porch (unit: Pixel)

    WORD usVTotal;              // Vertical Total length (unit: HSync)
    WORD usVTotalOdd;           // Vertical Total Odd length (unit: HSync)
    WORD usVHeight;             // Vertical Active Height (unit: HSync)
    WORD usVStart;              // Vertical Start (unit: HSync)
    WORD usVSWidth;             // Vertical Sync Width    (unit: HSync)
    WORD usVFrontPorch;         // Vertical Front Porch (unit: HSync)

    DWORD ulLinkClockHz;        // Link Clock
    DWORD ulCompStreamClockHz;  // Compression Stream Clock
    DWORD ulStreamClockHz;      // Stream Clock
    DWORD ulBufferClockHz;      // Stream Clock
    WORD usHBsToBsCount;        // H BS to BS Count
    DWORD ulVBsToBsCountN;      // V BS to BS Count of The Nth Frame
    DWORD ulVBsToBsCountN1;     // V BS to BS Count of The (N+1)th Frame
    BYTE b1InterlaceFieldN : 1;  // VBID[1] Inerlace Field Flag of The Nth Frame
    BYTE b1InterlaceFieldN1 : 1; // VBID[1] Inerlace Field Flag of The (N+1)th Frame
    BYTE b1InterlaceOddMode : 1; // VBID[1] Inerlace Field Mode (Even or Odd)
}StructDscTimingInfo;

typedef enum
{
    _DSC_FIFO_DELAY_CHECK = 0x00,
    _DSC_FIFO_POLLING_CHECK,
} EnumDscFifoCheckCondition;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDscCapSwitch g_stDscDecoderCapSwitch;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDscDecoderDataRecover(void);
extern void ScalerDscDecoderSetFifoIRQ(BYTE ucDscMac, bit bEn);
extern bit ScalerDscDecoderCheckFifoIRQ(BYTE ucDscMac);
extern BYTE ScalerDscDecoderGetFifoStatus(BYTE ucDscMac);
extern void ScalerDscDecoderSetFifoWD(BYTE ucDscMac, bit bEn);
extern void ScalerDscDecoderSetForceToBackGround(BYTE ucDscMac, bit bEn);
extern bit ScalerDscDecoderStreamCheck(BYTE ucDscMac);
extern bit ScalerDscDecoderFifoCheck(BYTE ucDscMac, EnumDscFifoCheckCondition enumDscFifoCheckCondition);
extern bit ScalerDscDecoderPpsChangeCheck(BYTE ucDscMac);
extern void ScalerDscDecoderDecEnable(BYTE ucDscMac);
extern void ScalerDscDecoderReset(EnumInputPort enumInputPort);
extern void ScalerDscDecoderDxMacReset(EnumInputPort enumInputPort);
extern WORD ScalerDscDecoderGetStreamFrameRate(BYTE ucDscMac);
extern void ScalerDscDecoderResetAllPort(void);
extern void ScalerDscDecoderForceBackgroundSetting(BYTE ucDscMac, bit bEnable);

#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
extern bit ScalerDscDecoderDpCapabilitySwitchProc(EnumInputPort enumInputPort);
extern bit ScalerDscDecoderDpCrcCalculate(BYTE ucDscMac);
extern bit ScalerDscDecoderCheckVgipVsBypass(BYTE ucDscMac);
#endif

extern bit ScalerDscDecoderGetChange(EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType);
extern void ScalerDscDecoderSetChange(EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType, bit bEnable);
extern void ScalerDscDecoderSetSupport(EnumInputPort enumInputPort, EnumDscDecoderSupport enumDscDecoderSupport);

extern bit ScalerDscDecoderGetCapSwitch(EnumInputPort enumInputPort);
extern void ScalerDscDecoderSetCapSwitch(EnumInputPort enumInputPort, bit bEnable);
extern void ScalerDscDecoderSetNativeInputPixelClock(EnumInputPort enumInputPort, DWORD ulStreamClk);
extern void ScalerDscDecoderSetChange_EXINT0(EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType, bit bEnable);
extern WORD ScalerDscDecoderGetDscHtotal(BYTE ucDscMac);
extern BYTE ScalerDscDecoderGetPixelMode(BYTE ucDscMac);
extern WORD ScalerDscDecoderGetChunkSizeCurrent(BYTE ucDscMac);
extern BYTE ScalerDscDecoderGetHorSliceCount(BYTE ucDscMac);
extern WORD ScalerDscDecoderGetDscPicWidth(BYTE ucDscMac);
extern bit ScalerDscDecoderGetNative420Mode(BYTE ucDscMac);
extern bit ScalerDscDecoderGetNativeMode(BYTE ucDscMac);

#if(_DP_SUPPORT == _ON)
extern WORD ScalerDscDecoderGetElement(BYTE ucDscMac, EnumDpStreamPpsElement enumElement);
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
extern EnumDscDecoderSupport ScalerDscDecoderDpMstToSstGetSupport(void);
extern void ScalerDscDecoderDpMstToSstSetSupport(EnumDscDecoderSupport enumDscDecoderSupport);
extern void ScalerDscDecoderSetMstToSstCapSwitch(bit bEnable);
extern bit ScalerDscDecoderGetMstToSstCapSwitch(void);
#endif

extern EnumDscDecoderMacStreamSourceType ScalerDscDecoderDxInputPortDscMacStreamSourceMapping(EnumInputPort enumInputPort);
extern EnumDscDecoderMacStreamSourceType ScalerDscDecoderGetDscMacStreamSource(BYTE ucDscMac);

#if((_HDMI_SUPPORT == _ON) && (_HDMI21_RX_DSC_DECODER_SUPPORT == _ON))
extern EnumRx ScalerDscDecoderGetHdmiMacRxxInput(BYTE ucDscMac);
extern BYTE ScalerDscDecoderHdmiFrlMacRxxGetDscDecoderMac(EnumRx enumRx);
extern EnumDscDecoderMacStreamSourceType ScalerDscDecoderHdmiMacRxxDscMacStreamSourceMapping(EnumRx enumRx);
#endif

#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
extern BYTE ScalerDscDecoderDpMacRxxGetDscDecoderMac(EnumDpMacSel enumDpMacSel);
extern EnumDpMacSel ScalerDscDecoderGetDpMacRxxInput(BYTE ucDscMac);
extern EnumDscDecoderMacStreamSourceType ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping(EnumDpMacSel enumDpMacSel);
extern EnumDscDecoderMacStreamSourceType ScalerDscDecoderDpMacRxxDscMacStreamSourceMapping_EXINT0(EnumDpMacSel enumDpMacSel);
extern BYTE ScalerDscDecoderDpMacRxxGetDscDecoderMac_EXINT0(EnumDpMacSel enumDpMacSel);
extern EnumDpMacSel ScalerDscDecoderDscMacStreamSourceDpMacRxxMapping(EnumDscDecoderMacStreamSourceType enumDscDecoderMacStreamSourceType);
#endif

extern EnumInputPort ScalerDscDecoderGetDxInputPort_EXINT0(BYTE ucDscMac);
#endif // End of #if(_DSC_DECODER_SUPPORT == _ON)

