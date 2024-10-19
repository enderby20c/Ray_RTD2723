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
// ID Code      : ScalerDscDecoderInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DSC_DECODER_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_DSC_D0_SUPPORT()                            (g_stDscDecoderEnableSupport.b1D0)
#define SET_DSC_D0_SUPPORT(x)                           (g_stDscDecoderEnableSupport.b1D0 = (x))

#define GET_DSC_D1_SUPPORT()                            (g_stDscDecoderEnableSupport.b1D1)
#define SET_DSC_D1_SUPPORT(x)                           (g_stDscDecoderEnableSupport.b1D1 = (x))

#define GET_DSC_D2_SUPPORT()                            (g_stDscDecoderEnableSupport.b1D2)
#define SET_DSC_D2_SUPPORT(x)                           (g_stDscDecoderEnableSupport.b1D2 = (x))

#define GET_DSC_D3_SUPPORT()                            (g_stDscDecoderEnableSupport.b1D3)
#define SET_DSC_D3_SUPPORT(x)                           (g_stDscDecoderEnableSupport.b1D3 = (x))

#define GET_DSC_D4_SUPPORT()                            (g_stDscDecoderEnableSupport.b1D4)
#define SET_DSC_D4_SUPPORT(x)                           (g_stDscDecoderEnableSupport.b1D4 = (x))

#define GET_DSC_D5_SUPPORT()                            (g_stDscDecoderEnableSupport.b1D5)
#define SET_DSC_D5_SUPPORT(x)                           (g_stDscDecoderEnableSupport.b1D5 = (x))

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
#define SET_DSC_DP_MST2SST_BRANCH_SUPPORT(x)            (g_bDscDecoderMstToSstEnable = (x))
#define GET_DSC_DP_MST2SST_BRANCH_SUPPORT()             (g_bDscDecoderMstToSstEnable)

#define SET_DSC_DP_MST2SST_CAPABILITY_SWITCH(x)         (g_bDscDecoderMstToSstEnableChange = (x))
#define GET_DSC_DP_MST2SST_CAPABILITY_SWITCH()          (g_bDscDecoderMstToSstEnableChange)
#endif

#define GET_DX_PORT_DSC_MAC_X_MAPPING(x)                (\
                                                            (((x) == _D0_INPUT_PORT) ?\
                                                                g_stDscDecoderMacMapping.b2D0 :\
                                                            (((x) == _D1_INPUT_PORT) ?\
                                                                g_stDscDecoderMacMapping.b2D1 :\
                                                            (((x) == _D2_INPUT_PORT) ?\
                                                                g_stDscDecoderMacMapping.b2D2 :\
                                                            (((x) == _D3_INPUT_PORT) ?\
                                                                g_stDscDecoderMacMapping.b2D3 :\
                                                            (((x) == _D4_INPUT_PORT) ?\
                                                                g_stDscDecoderMacMapping.b2D4 :\
                                                            (((x) == _D5_INPUT_PORT) ?\
                                                                g_stDscDecoderMacMapping.b2D5 : _DSC_MAC_NONE))))))\
                                                        )

#define SET_DX_PORT_DSC_MAC_X_MAPPING(x, y)             {\
                                                            if((x) == _D0_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderMacMapping.b2D0 = (y);\
                                                            }\
                                                            else if((x) == _D1_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderMacMapping.b2D1 = (y);\
                                                            }\
                                                            else if((x) == _D2_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderMacMapping.b2D2 = (y);\
                                                            }\
                                                            else if((x) == _D3_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderMacMapping.b2D3 = (y);\
                                                            }\
                                                            else if((x) == _D4_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderMacMapping.b2D4 = (y);\
                                                            }\
                                                            else if((x) == _D5_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderMacMapping.b2D5 = (y);\
                                                            }\
                                                        }

#define SET_MST2SST_BRANCH_DSC_X_MAPPING(x)             (g_stDscDecoderMacMapping.b2Mst2sst = (x))
#define GET_MST2SST_BRANCH_DSC_X_MAPPING()              (g_stDscDecoderMacMapping.b2Mst2sst)

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
#define SET_BG_DETECTION_DSC_X_MAPPING(x)               (g_stDscDecoderMacMapping.b2BgDetect = (x))
#define GET_BG_DETECTION_DSC_X_MAPPING()                (g_stDscDecoderMacMapping.b2BgDetect)

#define SET_DX_DSC_DECODER_SUPPORT_CHANGE_FOR_BG(x)     {\
                                                            if((x) == _D0_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D0 = _TRUE;\
                                                            }\
                                                            else if((x) == _D1_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D1 = _TRUE;\
                                                            }\
                                                            else if((x) == _D2_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D2 = _TRUE;\
                                                            }\
                                                            else if((x) == _D3_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D3 = _TRUE;\
                                                            }\
                                                            else if((x) == _D4_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D4 = _TRUE;\
                                                            }\
                                                            else if((x) == _D5_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D5 = _TRUE;\
                                                            }\
                                                        }

#define GET_DX_DSC_DECODER_SUPPORT_CHANGE_FOR_BG(x)     (\
                                                        (((x) == _D0_INPUT_PORT) ?\
                                                            g_stDscDecoderSupportChangeForBG.b1D0 :\
                                                        (((x) == _D1_INPUT_PORT) ?\
                                                            g_stDscDecoderSupportChangeForBG.b1D1 :\
                                                        (((x) == _D2_INPUT_PORT) ?\
                                                            g_stDscDecoderSupportChangeForBG.b1D2 :\
                                                        (((x) == _D3_INPUT_PORT) ?\
                                                            g_stDscDecoderSupportChangeForBG.b1D3 :\
                                                        (((x) == _D4_INPUT_PORT) ?\
                                                            g_stDscDecoderSupportChangeForBG.b1D4 :\
                                                        (((x) == _D5_INPUT_PORT) ?\
                                                            g_stDscDecoderSupportChangeForBG.b1D5 : _FALSE))))))\
                                                        )

#define CLR_DX_DSC_DECODER_SUPPORT_CHANGE_FOR_BG(x)     {\
                                                            if((x) == _D0_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D0 = _FALSE;\
                                                            }\
                                                            else if((x) == _D1_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D1 = _FALSE;\
                                                            }\
                                                            else if((x) == _D2_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D2 = _FALSE;\
                                                            }\
                                                            else if((x) == _D3_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D3 = _FALSE;\
                                                            }\
                                                            else if((x) == _D4_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D4 = _FALSE;\
                                                            }\
                                                            else if((x) == _D5_INPUT_PORT)\
                                                            {\
                                                                g_stDscDecoderSupportChangeForBG.b1D5 = _FALSE;\
                                                            }\
                                                        }
#endif
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b2D0 : 2;
    BYTE b2D1 : 2;
    BYTE b2D2 : 2;
    BYTE b2D3 : 2;
    BYTE b2D4 : 2;
    BYTE b2D5 : 2;
    BYTE b1Dsc0Occupy : 1;
    BYTE b1Dsc1Occupy : 1;
}StructDscUsageInfo;

typedef struct
{
    EnumDscDecoderSupport b1D0 : 1;
    EnumDscDecoderSupport b1D1 : 1;
    EnumDscDecoderSupport b1D2 : 1;
    EnumDscDecoderSupport b1D3 : 1;
    EnumDscDecoderSupport b1D4 : 1;
    EnumDscDecoderSupport b1D5 : 1;
}StructDscSupport;

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
typedef struct
{
    BYTE b1D0 : 1;
    BYTE b1D1 : 1;
    BYTE b1D2 : 1;
    BYTE b1D3 : 1;
    BYTE b1D4 : 1;
    BYTE b1D5 : 1;
}StructDscSupportChangeForBG;
#endif

typedef struct
{
    BYTE b2D0 : 2;
    BYTE b2D1 : 2;
    BYTE b2D2 : 2;
    BYTE b2D3 : 2;
    BYTE b2D4 : 2;
    BYTE b2D5 : 2;
    BYTE b2Mst2sst : 2;
    BYTE b2BgDetect : 2;
}StructDscDecoderMacMapping;

typedef enum
{
    _DSC_STREAM_SOURCE_DP_MAC_RX0 = 0x03,
    _DSC_STREAM_SOURCE_DP_MAC_RX1 = 0x04,
    _DSC_STREAM_SOURCE_DP_MAC_RX2 = 0x05,
    _DSC_STREAM_SOURCE_HDMI_MAC_RX3 = 0x07,
    _DSC_STREAM_SOURCE_HDMI_MAC_RX4 = 0x08,
    _DSC_STREAM_SOURCE_DP_MAC_RX4 = 0x0B,
    _DSC_STREAM_SOURCE_NONE = 0xFF,
} EnumDscDecoderMacStreamSourceType;

typedef struct
{
    BYTE b1DscStreamSourceDpMacRx0 : 1;
    BYTE b1DscStreamSourceDpMacRx1 : 1;
    BYTE b1DscStreamSourceDpMacRx2 : 1;
    BYTE b1DscStreamSourceHdmiMacRx3 : 1;
    BYTE b1DscStreamSourceHdmiMacRx4 : 1;
    BYTE b1DscStreamSourceDpMacRx4 : 1;
}StructDscDecoderStreamChange;

typedef struct
{
    BYTE b2DscStreamSourceDpMacRx0 : 2;
    BYTE b2DscStreamSourceDpMacRx1 : 2;
    BYTE b2DscStreamSourceDpMacRx2 : 2;
    BYTE b2DscStreamSourceHdmiMacRx3 : 2;
    BYTE b2DscStreamSourceHdmiMacRx4 : 2;
    BYTE b2DscStreamSourceDpMacRx4 : 2;
}StructDscDecoderStreamSourceDscMacUsage;

typedef enum
{
    _DSC_MAC_APPLY_DX_PORT,
#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
    _DSC_MAC_APPLY_MST2SST,
#endif
}EnumDscDecoderMacApplyType;

typedef enum
{
    _DSC_POWER_CUT_ON = 0x00,
    _DSC_POWER_CUT_OFF,
} EnumDscPowerCut;

extern StructDscDecoderStreamSourceDscMacUsage g_stDscDecoderStreamSourceDscMacUsage;
extern StructDscDecoderMacMapping g_stDscDecoderMacMapping;
extern StructDscDecoderStreamChange g_stDscDecoderStreamChange;

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
extern StructDscSupportChangeForBG g_stDscDecoderSupportChangeForBG;
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
extern bit g_bDscDecoderMstToSstEnable;
extern bit g_bDscDecoderMstToSstEnableChange;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructDscSupport g_stDscDecoderEnableSupport;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDscDecoderInitial(BYTE ucDscMac);
extern EnumSourceType ScalerDscDecoderMacRxScanInputPort(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern bit ScalerDscDecoderMacScanInputPort(BYTE ucDscMac);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDscDecoderGetHdmiDscFlagStatus(EnumInputPort enumHdmiInputPort);
#endif

#if((_DP_SUPPORT == _ON) && (_DP_RX_DSC_DECODER_SUPPORT == _ON))
extern void ScalerDscDecoderSyncDpSupportSwitch(EnumInputPort enumInputPort, EnumDscDecoderSupport enumDscDecoderSupport);
#endif

#if(_DP_MST2SST_BRANCH_DSC_DECODER_SUPPORT == _ON)
extern void ScalerDscDecoderSyncDpMstToSstSupportSwitch(EnumDscDecoderSupport enumDscDecoderSupport);
extern void ScalerDscDecoderMacArbiterDpMstToSst(EnumInputPort enumInputPort);
#endif

extern EnumDscDecoderSupport ScalerDscDecoderGetSupport(EnumInputPort enumInputPort);
extern BYTE ScalerDscDecoderGetDscVersion(BYTE ucDscMac);
extern WORD ScalerDscDecoderGetDscSliceHeight(BYTE ucDscMac);
extern WORD ScalerDscDecoderGetDscSliceWidth(BYTE ucDscMac);
extern WORD ScalerDscDecoderGetDscChunkSize(BYTE ucDscMac);
extern WORD ScalerDscDecoderGetDscBpc(BYTE ucDscMac);
extern WORD ScalerDscDecoderGetDscBitPerPixel(BYTE ucDscMac);

#if(_HDMI21_RX_DSC_DECODER_SUPPORT == _ON)
extern WORD ScalerDscDecoderGetDscHCActive(BYTE ucDscMac);
extern WORD ScalerDscDecoderGetDscHCBlank(BYTE ucDscMac);
#endif

extern void ScalerDscDecoderIntHandler_EXINT0(void);

extern void ScalerDscDecoderMacSetDscStreamSource(EnumInputPort enumInputPort, EnumPortType enumPortType, BYTE ucDscMac, EnumDscDecoderMacApplyType enumDscDecoderMacApplyType);
extern BYTE ScalerDscDecoderDxInputPortGetDscDecoderMac(EnumInputPort enumInputPort);
extern void ScalerDscDecoderPowerCutControl(BYTE ucDscMac, EnumDscPowerCut enumDscPowerCut);
extern bit ScalerDscDecoderGetDscDecoderMacEnable(BYTE ucDscMac);
extern EnumColorSpace ScalerDscDecoderGetPpsColorSpaceInfo(BYTE ucDscMac);
extern EnumInputPort ScalerDscDecoderGetDxInputPort(BYTE ucDscMac);
#endif // End of #if(_DSC_DECODER_SUPPORT == _ON)
