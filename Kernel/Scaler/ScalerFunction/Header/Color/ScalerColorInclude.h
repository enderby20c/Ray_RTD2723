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
// ID Code      : ScalerColorInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of LocalContrast Option
//--------------------------------------------------

//--------------------------------------------------
// Macro of Color Space
//--------------------------------------------------
#define GET_COLOR_SPACE(port)                       (g_pstColorInfo[port].b3ColorSpace)
#define SET_COLOR_SPACE(port, x)                    (g_pstColorInfo[port].b3ColorSpace = (x))
#define CLR_COLOR_SPACE(port)                       (g_pstColorInfo[port].b3ColorSpace = 0)
#define GET_COLOR_SPACE_RGB(x)                      (((x) == _COLOR_SPACE_RGB) ||\
                                                     ((x) == _COLOR_SPACE_Y_ONLY) ||\
                                                     ((x) == _COLOR_SPACE_RAW))

//--------------------------------------------------
// Macro of Colorimetry Data
//--------------------------------------------------
#define GET_COLORIMETRY(port)                       (g_pstColorInfo[port].b4Colorimetry)
#define SET_COLORIMETRY(port, x)                    (g_pstColorInfo[port].b4Colorimetry = (x))
#define CLR_COLORIMETRY(port)                       (g_pstColorInfo[port].b4Colorimetry = 0)

//--------------------------------------------------
// Macro of Extended Colorimetry
//--------------------------------------------------
#define GET_EXT_COLORIMETRY(port)                   (g_pstColorInfo[port].b5ExtColorimetry)
#define SET_EXT_COLORIMETRY(port, x)                (g_pstColorInfo[port].b5ExtColorimetry = (x))
#define CLR_EXT_COLORIMETRY(port)                   (g_pstColorInfo[port].b5ExtColorimetry = 0)

//--------------------------------------------------
// Macro of Additional Extended Colorimetry
//--------------------------------------------------
#define GET_ADD_EXT_COLORIMETRY(port)               (g_pstColorInfo[port].b3AddExtColorimetry)
#define SET_ADD_EXT_COLORIMETRY(port, x)            (g_pstColorInfo[port].b3AddExtColorimetry = (x))
#define CLR_ADD_EXT_COLORIMETRY(port)               (g_pstColorInfo[port].b3AddExtColorimetry = 0)

//--------------------------------------------------
// Macro of Color Depth
//--------------------------------------------------
#define GET_COLOR_DEPTH(port)                       (g_pstColorInfo[port].b5ColorDepth)
#define SET_COLOR_DEPTH(port, x)                    (g_pstColorInfo[port].b5ColorDepth = (x))
#define CLR_COLOR_DEPTH(port)                       (g_pstColorInfo[port].b5ColorDepth = 0)

//--------------------------------------------------
// Macro of RGB Quantization Range
//--------------------------------------------------
#define GET_COLOR_RGB_QUANTIZATION_RANGE(port)      (g_pstColorInfo[port].b2RgbQuantizationRange)
#define SET_COLOR_RGB_QUANTIZATION_RANGE(port, x)   (g_pstColorInfo[port].b2RgbQuantizationRange = (x))
#define CLR_COLOR_RGB_QUANTIZATION_RANGE(port)      (g_pstColorInfo[port].b2RgbQuantizationRange = 0)

//--------------------------------------------------
// Macro of RGB Limit Range User
//--------------------------------------------------
#define GET_COLOR_RGB_LIMIT_RANGE_USER(port)        (g_pstColorInfo[port].b1RgbLimitRangeUser)
#define SET_COLOR_RGB_LIMIT_RANGE_USER(port, x)     (g_pstColorInfo[port].b1RgbLimitRangeUser = (x))

//--------------------------------------------------
// Macro of YCC Quantization Range
//--------------------------------------------------
#define GET_COLOR_YCC_QUANTIZATION_RANGE(port)      (g_pstColorInfo[port].b2YccQuantizationRange)
#define SET_COLOR_YCC_QUANTIZATION_RANGE(port, x)   (g_pstColorInfo[port].b2YccQuantizationRange = (x))

//--------------------------------------------------
// Macro of YCC Full Range User
//--------------------------------------------------
#define GET_COLOR_YCC_FULL_RANGE_USER(port)         (g_pstColorInfo[port].b1YccFullRangeUser)
#define SET_COLOR_YCC_FULL_RANGE_USER(port, x)      (g_pstColorInfo[port].b1YccFullRangeUser = (x))

//--------------------------------------------------
// Macro of Content Type
//--------------------------------------------------
#define GET_CONTENT_TYPE(port)                      (g_pstColorInfo[port].b3ContentType)
#define SET_CONTENT_TYPE(port, x)                   (g_pstColorInfo[port].b3ContentType = (x))

#if(_HDMI21_CCBPC_SUPPORT == _ON)
//--------------------------------------------------
// Macro of CCBPC Value
//--------------------------------------------------
#define GET_COLOR_HDMI21_CCBPC_VALUE(port)          (g_pstColorInfo[port].b4CcbpcValue)
#define SET_COLOR_HDMI21_CCBPC_VALUE(port, x)       (g_pstColorInfo[port].b4CcbpcValue = (x))
#endif

#if(_DM_FUNCTION == _ON)
//--------------------------------------------------
// Macro of DM Detect DRAM received
//--------------------------------------------------
#define GET_DRAM_RECEIVED_FROM_DM_DETECT(port)      (g_pstColorInfo[port].b1DramReceivedfromDmDetect)
#define SET_DRAM_RECEIVED_FROM_DM_DETECT(port)      (g_pstColorInfo[port].b1DramReceivedfromDmDetect = _TRUE)
#define CLR_DRAM_RECEIVED_FROM_DM_DETECT(port)      (g_pstColorInfo[port].b1DramReceivedfromDmDetect = _FALSE)
#endif

//--------------------------------------------------
// Definitions of SCM Adjust Option
//--------------------------------------------------
#define _SCM0_BLOCK0_ENABLE                         _BIT0
#define _SCM0_BLOCK1_ENABLE                         _BIT1
#define _SCM1_BLOCK0_ENABLE                         _BIT2
#define _SCM1_BLOCK1_ENABLE                         _BIT3
#define _SCM2_BLOCK0_ENABLE                         _BIT4
#define _SCM2_BLOCK1_ENABLE                         _BIT5
#define _SCM3_BLOCK0_ENABLE                         _BIT6
#define _SCM3_BLOCK1_ENABLE                         _BIT7
#define _SCMN_SHARE_REG                             _BIT0

//--------------------------------------------------
// Definitions of Out Gamma Info
//--------------------------------------------------
#define _GAMMA_TABLE_SIZE                           2052
#define _GAMMA_WRITE_TO_SRAM                        0
#define _GAMMA_WRITE_TO_LATCH                       1

//--------------------------------------------------
// Definitions of Post Gamma Info
//--------------------------------------------------
#define _POST_GAMMA_TABLE_SIZE                      2052

//--------------------------------------------------
// Definitions of Color conversion Info
//--------------------------------------------------
#define _COLOR_CONV_RGB2YUV_TABLE_SIZE              (27)
#define _COLOR_CONV_YUV2RGB_TABLE_SIZE              (26)

//--------------------------------------------------
// Definitions of Color conversion Night Sniper mode
//--------------------------------------------------
#define _COLOR_CONV_NIGHT_SNIPER_GAIN_R             (1535)
#define _COLOR_CONV_NIGHT_SNIPER_GAIN_G             (640)
#define _COLOR_CONV_NIGHT_SNIPER_GAIN_B             (1536)
#define _COLOR_CONV_NIGHT_SNIPER_TABLE_OFFSET       (19)
#define _COLOR_CONV_NIGHT_SNIPER_TABLE_SIZE         (6)
#define _COLOR_CONV_NIGHT_SNIPER_BACK_PAGESHIFT     (0xD500U)

//--------------------------------------------------
// Definitions of Local Dimming Info
//--------------------------------------------------
#define _LOCAL_DIMMING_SPI_FW_WAIT_TIMEOUT          65

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Structure of Color Info
//--------------------------------------------------
typedef struct
{
    EnumColorSpace b3ColorSpace : 3;
    BYTE b5ColorDepth : 5;
    EnumColorimetryExt b5ExtColorimetry : 5;
    EnumColorRGBQuantization b2RgbQuantizationRange : 2;
    EnumRGBQuantLimitRangeStatus b1RgbLimitRangeUser : 1;
    EnumColorYCCQuantization b2YccQuantizationRange : 2;
    EnumYccQuantFullRangeStatus b1YccFullRangeUser : 1;
    EnumColorimetry b4Colorimetry : 4;
    BYTE b3ContentType : 3;
    EnumColorimetryAddExt b3AddExtColorimetry : 3;
#if(_HDMI21_CCBPC_SUPPORT == _ON)
    BYTE b4CcbpcValue : 4;
#endif
#if(_DM_FUNCTION == _ON)
    BYTE b1DramReceivedfromDmDetect : 1;
#endif
} StructColorInfo;

//--------------------------------------------------
// Enumerations of Highlight Window IP Selection
//--------------------------------------------------
typedef enum
{
    _IP_SRGB,
    _IP_DCR,
    _IP_DSHP,
    _IP_CONTRAST,
    _IP_GAMMA,
    _IP_3DGAMMA,
    _IP_DCC,
    _IP_UNIFORMITY,
    _IP_IAPSGAIN,
    _IP_ICM,
    _IP_LIVESHOWTM,
} EnumHLWIPSel;

//--------------------------------------------------
// Enumerations of Register Select
//--------------------------------------------------
typedef enum
{
    _REG_MAIN1,
    _REG_MAIN2,
    _REG_SUB1,
    _REG_SUB2,
} EnumRegSel;

//--------------------------------------------------
// Structure of DCR Store Info
//--------------------------------------------------
typedef struct
{
    DWORD ulDCR_LD_ABOVE_TH1_NUM;
    DWORD ulDCR_LD_ABOVE_TH2_NUM;
    BYTE pucWinMaxRGB[16];
} StructDCRStoreInfo;

//--------------------------------------------------
// Structure of CRC
//--------------------------------------------------
typedef struct
{
    BYTE pucValue[6];
} StructCRCInfo;

//--------------------------------------------------
// Enumerations of CRC
//--------------------------------------------------
typedef enum
{
    _I_CRC_M1 = 0x01,
    _I_CRC_M2 = 0x02,
    _I_CRC_S1 = 0x04,
    _I_CRC_S2 = 0x08,
    _I_CRC_S3 = 0x10,
    _I_CRC_S4 = 0x20,
} EnumICRCPath;

typedef enum
{
    _M_CRC_M1 = 0x01,
    _M_CRC_M2 = 0x02,
    _M_CRC_S1 = 0x04,
    _M_CRC_S2 = 0x08,
    _M_CRC_S3 = 0x10,
    _M_CRC_S4 = 0x20,
} EnumMCRCPath;

typedef enum
{
    _D_CRC_M1 = 0x01,
    _D_CRC_M2 = 0x02,
    _D_CRC_M3 = 0x04,
    _D_CRC_M4 = 0x08,
    _D_CRC_S1 = 0x10,
    _D_CRC_S2 = 0x20,
} EnumDCRCPath;

typedef enum
{
    _CRC_IDOMAIN = 0,
    _CRC_MDOMAIN_CAP,
    _CRC_MDOMAIN_DISP,
    _CRC_DDOMAIN,
} EnumCRCDomain;

typedef enum
{
    _I_CRC_AFTER_VGIP = 0,
    _I_CRC_AFTER_IDITHER,
    _I_CRC_BEFORE_FIFO,
} EnumICRCPosition;

typedef enum
{
    _M_CRC_AFTER_FIFO = 0,
    _M_CRC_BEFORE_FB2EO,
} EnumMCRCDispPosition;

typedef enum
{
    _D_CRC_BEFORE_BLENDING = 0,
    _D_CRC_AFTER_DDITHER,
    _D_CRC_AFTER_OD,
} EnumDCRCPosition;

//--------------------------------------------------
// Enumerations of SU Page
//--------------------------------------------------
typedef enum
{
    _SU_BYPASS_R1_A1_PAGE = 0x0000,
    _SU_BYPASS_R1_A2_PAGE = 0x0006,
    _SU_BYPASS_R2_A1_PAGE = 0x8000,
    _SU_BYPASS_R2_A2_PAGE = 0x8006,
    _SU_BYPASS_R3_A1_PAGE = 0xC000,
    _SU_BYPASS_R3_A2_PAGE = 0xC006,
    _SU_BYPASS_NONE_PAGE = 0xFFFF,
} EnumSUBypassPage;

//--------------------------------------------------
// Enumerations of pattern gen.
//--------------------------------------------------
typedef enum
{
    _PG_GRAY = 0,
    _PG_MASS,
} EnumPGType;

typedef enum
{
    _PG_MODE_10 = 0,
    _PG_MODE_12,
} EnumPGBitNode;

//--------------------------------------------------
// Enumerations of Digital Functions Double Buffer in EXINT Function
//--------------------------------------------------
typedef enum
{
    _DB_APPLY_NONE_EXINT,
    _DB_APPLY_NO_POLLING_EXINT,
} EnumDBApply_EXINT;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructColorInfo g_pstColorInfo[];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
#if(_DIGITAL_FILTER_SUPPORT == _ON)
#if(_HW_DIGITAL_FILTER_TYPE != _GEN_NONE)
// Digital Filter
extern void ScalerColorDigitalFilterNSmearAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterNRDisableAdjust(void);
extern void ScalerColorDigitalFilterPSmearAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterNRingAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterPRingAdjust(BYTE ucTHD, BYTE ucDIV);
extern void ScalerColorDigitalFilterExtensionAdjust(void);
#endif
#endif
#endif

// Color Sampling
#if(_COLOR_IP_420_SUPPORT == _ON)
extern bit ScalerColor420To422GetStatusByPort(EnumInputPort enumInputPort);
extern bit ScalerColor420To422GetStatusByPath(EnumInputDataPath enumInputDataPath);
extern bit ScalerColor420To422GetDoublePixelStatusByPath(EnumInputDataPath enumInputDataPath);
extern void ScalerColor420To422FinalSettingByPath(EnumInputDataPath enumInputDataPath, EnumInputPort enumInputPort);
extern void ScalerColor420To422InitialByPath(EnumInputDataPath enumInputDataPath);
extern void ScalerColor420To422P0Enable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422P1Enable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422P2Enable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422P3Enable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422P3RetryEnable(void);
extern void ScalerColor420To422P0DoublePixelEnable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422P1DoublePixelEnable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422P2DoublePixelEnable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422P3DoublePixelEnable(EnumFunctionOnOFF enumFunctionOnOFF);
extern void ScalerColor420To422P0Setting(WORD usHStart, WORD usHWidth);
extern void ScalerColor420To422P1Setting(WORD usHStart, WORD usHWidth);
extern void ScalerColor420To422P2Setting(WORD usHStart, WORD usHWidth);
extern void ScalerColor420To422P3Setting(WORD usHStart, WORD usHWidth);
#endif

// Color Conversion
#if(_COLOR_IP_COLOR_CONVERT == _ON)
extern BYTE ScalerColorSpaceGetMDomainColorDepth(EnumDisplayRegion enumDisplayRegion);
extern bit ScalerColorSpaceForceYUVStatus(EnumDisplayRegion enumDisplayRegion);
extern bit ScalerColorSpaceGetRgb2YuvTable(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace, BYTE *pucIColorConvTable, BYTE *pucIColorConvCtrlValue);
extern void ScalerColorSpaceLoadRgb2YuvTable(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace);
extern bit ScalerColorSpaceConvertIDomainEnableStatus(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace);
extern bit ScalerColorSpaceConvertDDomainEnableStatus(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace);

#if(_COLOR_IP_DM == _ON)
extern void ScalerColorSpaceLoadRgb2YuvTableDM(EnumDisplayRegion enumDisplayRegion);
extern bit ScalerColorSpaceConvertEnableStatusDM(EnumDisplayRegion enumDisplayRegion);
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
extern void ScalerColorSpaceConvertNightSniperSetGain(EnumDisplayRegion enumDisplayRegion, BYTE *pucNightSniperGain);
extern void ScalerColorSpaceConvertNightSniperRecover(EnumDisplayRegion enumDisplayRegion, BYTE *pucNightSniperGain);
extern EnumDisplayRegion ScalerColorSpaceConvertGetNightSniperRegionStatus(BYTE ucIndex, EnumSelRegion enumSelRegion);
#endif

#if(_GLOBAL_COLOR_CONVERT_HUE_SATURATION_FUNCTION == _ON)
extern void ScalerColorSpaceConvertMatrixMultiply(SWORD(*ppshArrayA)[3], SWORD(*ppshArrayB)[3], SDWORD(*pplArrayC)[3]);
extern BYTE ScalerColorSpaceConvertUseDisplayModeToDecideRunTime(EnumSelRegion enumSelRegion);
extern EnumDisplayRegion ScalerColorSpaceConvertChangeSelRegionToDisplayRegion(BYTE ucCurrentIndex, BYTE ucTotalIndex, EnumSelRegion enumSelRegion);
extern void ScalerColorSpaceConvertSetGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shDeltaHue, WORD usDeltaSat);
extern void ScalerColorSpaceConvertCalculateGlobalHueSat(WORD usDdomainPage, SWORD shDeltaHue, WORD usDeltaSat);
#endif
#endif

// IDither
#if(_COLOR_IP_I_DITHER == _ON)
extern void ScalerColorIDitherLoadSeqTable(WORD usPage, BYTE *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress);
extern void ScalerColorIDitherLoadTemporalTable(WORD usPage, BYTE *pucTempoTable, BYTE ucBankAddress);
extern void ScalerColorIDitherLoadSetting(WORD usPage, WORD usAdjustOption);
#endif

// Border Window
#if(_COLOR_IP_BORDER_WIN == _ON)
extern void ScalerColorBorderPositionAdjust(EnumBorderWin enumBorderWin, WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight, EnumDBApply enumDBApply);
extern void ScalerColorBorderAdjust(EnumBorderWin enumBorderWin, BYTE ucBorderWidth, BYTE ucRed, BYTE ucGreen, BYTE ucBlue, EnumDBApply enumDBApply);
#endif

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
// UltraVivid
extern WORD ScalerColorUltraVividPageMapping(EnumDDomainRegion enumDDomainRegion);
extern WORD ScalerColorUltraVividGetIDomainRegisterPage(EnumDDomainRegion enumDDomainRegion);
#endif

#if(_COLOR_IP_LSR == _ON)
extern WORD ScalerColorLSRPageMapping(EnumDDomainRegion enumDDomainRegion);
extern WORD ScalerColorLSRHLWPageMapping(EnumDDomainRegion enumDDomainRegion);
extern void ScalerColorLSRHLWAdjust(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
extern void ScalerColorLSRHLWEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorLSREnable(EnumDDomainRegion enumDDomainRegion, bit bOn);
#endif

#if(_COLOR_IP_DSHP == _ON)
extern WORD ScalerColorDSHPPageMapping(EnumDDomainRegion enumDDomainRegion);
extern void ScalerColorDSHPRegionEnable(EnumSelRegion enumSelRegion, bit bOn);
#endif

//Local Contrast
#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
extern void ScalerColorLocalContrastGlobalSceneChangeThdAdjust(EnumSelRegion enumSelRegion);
extern void ScalerColorLocalContrastBlockSceneChangeThdAdjust(EnumSelRegion enumSelRegion);
extern void ScalerColorLocalContrastHBlkAdjust(WORD usDHWidth, BYTE ucBlkHnumMax, BYTE ucBlkHSizeMin, StructColorLocalContrastHblkSetting *pstLocalContrastHBlkSetting);
extern void ScalerColorLocalContrastHBlknumSpecialAdjust(WORD usDHWidth, BYTE ucBlkHSize, StructColorLocalContrastHblkSetting *pstLocalContrastHBlkSetting);
extern void ScalerColorLocalContrastVBlkAdjust(WORD usDVHeight, BYTE ucBlkVnumMax, BYTE ucBlkVSizeMin, StructColorLocalContrastVblkSetting *pstLocalContrastVBlkSetting);
extern bit ScalerColorLocalContrastCheckPorchStatus(WORD usPage, WORD usTargetTotalPorch, BYTE ucPathCount);
extern WORD ScalerColorLocalContrastSfilterPredoAdjust(BYTE ucPathCount, BYTE ucHBlknum, BYTE ucVBlknum, WORD usDHtotal, WORD usVHeight);
extern EnumSelRegion ScalerColorLocalContrastGetRegionStatus(BYTE ucIndex, EnumSelRegion enumSelRegion);
extern WORD ScalerColorLocalContrastPagePart1Mapping(EnumSelRegion enumSelRegion);
extern WORD ScalerColorLocalContrastPagePart2Mapping(EnumSelRegion enumSelRegion);
extern void ScalerColorLocalContrastAdjustHtotal(WORD usPage, WORD *pusDHtotal);

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
extern BYTE ScalerColorLocalContrastHBlkInitial(WORD usPage);
extern BYTE ScalerColorLocalContrastVBlkInitial(WORD usPage);
extern void ScalerColorLocalContrastGetHblknumRefSize(StructColorLocalContrastHblkSetting *pstLocalContrastHBlkSetting);
extern void ScalerColorLocalContrastGetVblknumRefSize(StructColorLocalContrastVblkSetting *pstLocalContrastVBlkSetting);
extern bit ScalerColorLocalContrastBlksizeAdjustCheck(EnumSelRegion enumSelRegion);
extern void ScalerColorLocalContrastHBlkAdjust_Yavg(WORD usDHWidth, BYTE ucBlkHnumMax, BYTE ucBlkHSizeMin, StructColorLocalContrastHblkSetting *pstLocalContrastHBlkSetting);
extern void ScalerColorLocalContrastVBlkAdjust_Yavg(WORD usDVHeight, BYTE ucBlkVnumMax, BYTE ucBlkVSizeMin, StructColorLocalContrastVblkSetting *pstLocalContrastVBlkSetting);
#endif
#endif

// DCC
#if((_COLOR_IP_DCC_HISTOGRAM == _ON) || (_COLOR_IP_DCC == _ON))
extern void ScalerColorDCCSetMeasureRegion(EnumHLWType enumHLWType);
#endif

// 3D Gamma
#if(_COLOR_IP_RGB_3D_GAMMA == _ON)
#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern BYTE *ScalerColorRGB3DGammaGetAdvancedHDR10TableAddress(void);
extern BYTE ScalerColorRGB3DGammaGetAdvancedHDR10TableBank(void);
#endif
#endif

// InputGamma Gamma
#if(_COLOR_IP_I_GAMMA == _ON)
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern void ScalerColorPCMSetHLWDBEventSel(EnumPCMHLWDBEventSel enumPCMHLWDBEventSel);
#endif
#endif
#endif

// Ymapping
#if(_COLOR_IP_YMAPPING == _ON)
extern bit ScalerColorYMappingLoadGainTable(EnumSelRegion enumSelRegion, BYTE *pucYMappingGainLUT, WORD usYMappingGainLUTSize, BYTE ucBankNum, bit bBurstWriteFrom);
extern void ScalerColorYMappingDBEnable(EnumFunctionOnOFF enumOn);
#endif

// Global Hue/Sat
#if(_COLOR_IP_SRGB == _ON)
extern SWORD ScalerColorSRGBCosine(SWORD shDegree);
extern SWORD ScalerColorSRGBSine(SWORD shDegree);
extern void ScalerColorSRGBMatrixMultiply(SWORD(*ppshArrayA)[3], SWORD(*ppshArrayB)[3], SWORD(*ppshArrayC)[3]);
extern void ScalerColorSRGBSetGlobalHueSat(EnumSelRegion enumSelRegion, SWORD shDeltaHue, WORD usDeltaSat);
#endif

// Post Gamma
#if(_COLOR_IP_P_GAMMA == _ON)
extern void ScalerColorPostGammaChannelCtrl(WORD usPage, BYTE ucColorChannel, WORD usOffset, bit bLocation);
#endif

// Local dimming
#if(_COLOR_IP_LOCAL_DIMMING == _ON)
extern void ScalerColorLDInitial(void);
#endif

// Output Gamma
#if(_COLOR_IP_O_GAMMA == _ON)
extern void ScalerColorOutputGammaChannelCtrl(WORD usPage, BYTE ucColorChannel, WORD usOffset, bit bLocation);
#endif

// DDither
#if(_COLOR_IP_D_DITHER == _ON)
extern void ScalerColorDDitherLoadDitherTable(BYTE *pucDitherTable, BYTE ucBankAddress);
extern void ScalerColorDDitherLoadSeqTable(BYTE *pucSeqTable, BYTE ucSeqLength, BYTE ucBankAddress);
extern void ScalerColorDDitherLoadTempoTable(BYTE *pucTempoTable, BYTE ucBankAddress);
extern void ScalerColorDDitherLoadSetting(DWORD ulSettingOption);
#endif

// Anti-Aliasing
#if(_COLOR_IP_ANTI_ALIASING == _ON)
extern void ScalerColorAntiAliasingInitialSetting(void);
#endif

// CRC
extern bit ScalerColorCRCCompareIDomain(EnumICRCPosition enumICRCPosition, BYTE ucPathSelect, StructCRCInfo *pstTargetCRC, BYTE ucFrameNum);
extern bit ScalerColorCRCCompareMDomainCap(BYTE ucPathSelect, StructCRCInfo *pstTargetCRC, BYTE ucFrameNum);
extern bit ScalerColorCRCCompareMDomainDisp(EnumMCRCDispPosition enumMCRCDispPosition, BYTE ucPathSelect, StructCRCInfo *pstTargetCRC, BYTE ucFrameNum);
extern bit ScalerColorCRCCompareDDomain(EnumDCRCPosition enumDCRCPosition, BYTE ucPathSelect, StructCRCInfo *pstTargetCRC, BYTE ucFrameNum);
#if(_DEBUG_MESSAGE_SUPPORT == _ON)
extern void ScalerColorCRCPrint(BYTE ucFrame, BYTE ucPath, StructCRCInfo *pstCRC, EnumCRCDomain enumCRCDomain);
#endif

// Pattern gen
#if(_VGA_SUPPORT == _ON)
extern void ScalerColorPatternGenVGATopControl(EnumPGType enumPGType, bit bEnable);
#endif
extern void ScalerColorPatternGenIDomainControl(EnumPGType enumPGType, bit bEnable);
extern void ScalerColorPatternGenDDomainControl(EnumPGType enumPGType, EnumPGBitNode enumPGBitNode, bit bEnable);

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
extern void ScalerColorLocalContrastIntHandler_EXINT0(void);
#endif
#endif

#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern void ScalerColorAdvancedHDR10VSIFHandler_EXINT0(StructAdvancedHDR10MetaData *pstSyncAdvancedHDR10Metadata);
extern bit ScalerColorGetPCMHLWDBStatus(EnumPCMHLWDBSel enumPCMHLWDBSel);
extern void ScalerColorAdvancedHDR10PCMHLWDBErrorStateProc(void);
extern EnumAdvancedHDR10PCMHLWDBStatus ScalerColorAdvancedHDR10GetPCMHLWDBStatus(EnumAdvancedHDR10PCMHLWDBProc enumAdvancedHDR10PCMHLWDBProc);
#if(_ADVANCED_HDR10_DHDR_SUPPORT == _ON)
extern void ScalerColorAdvancedHDR10DHDRHandler_EXINT0(BYTE *pucDHDRMetaData);
extern bit ScalerColorAdvancedHDR10CheckDHDRMetadta_EXINT0(BYTE ucContryCode, WORD usProviderCode, WORD usProviderOrientedCode, BYTE ucAppIdentifier, BYTE ucAppVersion);
#endif
#endif
#if(_HDR10_SUPPORT == _ON)
#if(_HDR10_MASTERING_LV_STEPLESS_TM_SUPPORT == _ON)
extern WORD ScalerColorHDRGetMasteringLvSteplessTMIGLUTAddr(EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, EnumHDR10MaxMasteringSteplessLvType enumHDR10MaxMasteringSteplessLvType);
extern WORD ScalerColorHDR10GetMasteringLvSteplessTMBoundAddress(void);
#endif
#if(_HDR10_BACKLIGHT_ADAPTIVE_TM_SUPPORT == _ON)
extern WORD ScalerColorHDR10GetBacklightAdaptivTMTable(EnumHDR10DarkEnhanceStatus enumHDR10DarkEnhanceStatus, EnumHDR10BacklightAdaptiveTMType enumHDR10BacklightAdaptiveTMType);
extern WORD ScalerColorHDR10GetBacklightAdaptivTMBoundAddress(void);
#endif
#endif

#if(_EAGLE_SIGHT_SUPPORT == _ON)
#if(_EAGLE_SIGHT_CIRCLE_WIN_SUPPORT == _ON)
extern void ScalerColorPIPBlendingSetCircleWindow(WORD usHCenter, WORD usVCenter, WORD usHStart, WORD usVStart);
extern void ScalerColorPIPBlendingSetCircleWindowBorder(WORD usBorder_HStart, WORD usBorder_VStart);
#endif
#endif