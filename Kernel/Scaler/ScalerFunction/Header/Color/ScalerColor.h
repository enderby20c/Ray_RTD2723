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
// ID Code      : ScalerColor.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_COLOR_H__
#define __SCALER_COLOR_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Color info size
//--------------------------------------------------
#define _COLOR_INFO_SIZE                            (_NO_INPUT_PORT)

//--------------------------------------------------
// Definitions of Digital Filter
//--------------------------------------------------
#define _DIG_FILTER_NSMEAR_THD                      4 // effective:0~7
#define _DIG_FILTER_NSMEAR_DIV_VALUE                1 // effective:0~3

#define _DIG_FILTER_PSMEAR_THD                      4 // effective:0~7
#define _DIG_FILTER_PSMEAR_DIV_VALUE                1 // effective:0~3

#define _DIG_FILTER_NRING_THD                       4 // effective:0~7
#define _DIG_FILTER_NRING_DIV_VALUE                 1 // effective:0~3

#define _DIG_FILTER_PRING_THD                       4 // effective:0~7
#define _DIG_FILTER_PRING_DIV_VALUE                 1 // effective:0~3

#define _DIG_FILTER_BGAIN                           0
#define _DIG_FILTER_GGAIN                           1
#define _DIG_FILTER_RGAIN                           2
#define _DIG_FILTER_RGB_CHANNEL                     3

#define _DIG_FILTER_THRESHOLD1                      30
#define _DIG_FILTER_OFFSET                          5
#define _DIG_FILTER_DELTA                           5

#define _RINGING_FILTER_THRESHOLD                   30
#define _RINGING_FILTER_THD_RANGE                   4
#define _RINGING_JUMP_JUDGEMENT_EN                  _DISABLE
#define _RINGING_JUMP_DIFF_THD_UB                   1  // reg value
#define _RINGING_JUMP_DIFF_THD_LB                   1  // reg value
#define _RINGING_FILTER_DELTA                       5

//--------------------------------------------------
// Definitions of I-dither Option
//--------------------------------------------------
#define _IDITHER_DITHER_TABLE_LENGTH                (24)
#define _IDITHER_TEMPORAL_TABLE_LENGTH              (4)

//--------------------------------------------------
// Definitions of ultra vivid Option
//--------------------------------------------------
#define _ULTRAVIVID_TABLE_SIZE                      234
#define _ULTRAVIVID_TABLE_SIZE_CDS                  29
#define _REG_SUB3_SD_PAGE                           0x1700U

//--------------------------------------------------
// Definitions of local contrast Option
//--------------------------------------------------
#define _MIN_BLKSIZE                                (40)
#define _MIN_BLKSIZE_FB                             (53)
#define _BLK_TABHNUM                                (8)
#define _BLK_TABVNUM                                (19)
#define _SU_FACTOR_BIT                              (21)
#define _MAX_HBLKNUM                                (48)
#define _MAX_VBLKNUM                                (27)
#define _MAX_VBLKNUM_3K_OVER                        (54)
#define _MAX_HBLKNUM_5K                             (64)
#define _MAX_VBLKNUM_2K_OVER                        (40)
#define _LOCAL_CONTRAST_CYCLE_NUM                   (22)
#define _LOCAL_CONTRAST_INTERPOLATION_PREDO         (80)
#define _LOCAL_CONTRAST_TFILTER_SHIFT               (20)
#define _LOCAL_CONTRAST_SRAM_SHIFT_CONSTANT         (6)
#define _LOCAL_CONTRAST_FB_MIN_BLKNUM               (5)
#define _LOCAL_CONTRAST_MIN_HWIDTH                  (200)
#define _LOCAL_CONTRAST_MIN_VHEIGHT                 (40)
#define _LOCAL_CONTRAST_R1_PART1_PAGE_SHIFT         (0x0000U)
#define _LOCAL_CONTRAST_R1_PART1_PAGE               (0x3200U)
#define _LOCAL_CONTRAST_R1_PART2_PAGE               (0x4200U)
#define _LOCAL_CONTRAST_R3_PART1_PAGE               (0xDD00U)
#define _LOCAL_CONTRAST_R3_PART2_PAGE               (0xDB00U)
#define _LOCAL_CONTRAST_R3_PART1_PAGE_SHIFT         (_LOCAL_CONTRAST_R3_PART1_PAGE - _LOCAL_CONTRAST_R1_PART1_PAGE)
#define _LOCAL_CONTRAST_R3_PART2_PAGE_SHIFT         (_LOCAL_CONTRAST_R3_PART2_PAGE - _LOCAL_CONTRAST_R1_PART2_PAGE)
#define _LOCAL_CONTRAST_HBLKNUM_4K_HWIDTH           (4096)
#define _LOCAL_CONTRAST_HBLKNUM_5K_HWIDTH           (5120)
#define _LOCAL_CONTRAST_VBLKNUM_3K_VHEIGHT          (3200)
#define _LOCAL_CONTRAST_VBLKNUM_2K_VHEIGHT          (2160)
#define _LOCAL_CONTRAST_YDIFF_CURVE_TABLE_START     (_HW_LOCAL_CONTRAST_TM_BLENDINGFACTOR_START + 50)
#define _LOCAL_CONTRAST_YDIFF_CURVE_TABLE_OFFSET    (19)
#define _LOCAL_CONTRAST_YDIFFDEVISOR_START          (_LOCAL_CONTRAST_YDIFF_CURVE_TABLE_START + _LOCAL_CONTRAST_YDIFF_CURVE_TABLE_OFFSET * 2 + 4)
#define _LOCAL_CONTRAST_GLOBALSC_HWIDTH             (1920)
#define _LOCAL_CONTRAST_GLOBALSC_VHEIGHT            (1080)
#define _LOCAL_CONTRAST_BLOCKSC_HBLKNUM             (48)
#define _LOCAL_CONTRAST_BLOCKSC_VBLKNUM             (27)

#define _LOCAL_CONTRAST_GLOBALSC_THD                (555)
#define _LOCAL_CONTRAST_BLOCKSC_THD                 (6114)

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
#define _LOCAL_CONTRAST_FB_EXTENSION_HBLKNUM        (3)
#endif
#define _LOCAL_CONTRAST_YAVG_TYPE0                  0    // (32/64) * 2
#define _LOCAL_CONTRAST_YAVG_TYPE1                  1    // (63/64) * 1
#define _LOCAL_CONTRAST_YAVG_TYPE                   _LOCAL_CONTRAST_YAVG_TYPE0
#define _LOCAL_CONTRAST_YAVG_GAIN                   4    // Mapping Histogram data from (0~1023) to (0~4095)
#endif
#endif
//-------------------------------------------------
// DCR Source Option
//-------------------------------------------------
#define _DCR_BEFORE_DCC                             0
#define _DCR_BEFORE_IAPSGAIN                        1
#define _DCR_SOURCE                                 _DCR_BEFORE_DCC

//--------------------------------------------------
// DCC Table Length
//--------------------------------------------------
#define _DCC_TABLE_SIZE_CTRL                        9
#define _DCC_TABLE_SIZE_CTRL_LSB                    5
#define _DCC_TABLE_SIZE_CRV                         23
#define _DCC_TABLE_SIZE_CRV_LSB                     54
#define _DCC_ADJOPTION_TABLE_OFFSET                 1
#define _DCC_CONTORL_TABLE_OFFSET                   3
#define _DCC_CONTORL_LSB_TABLE_OFFSET               12
#define _DCC_CURVE_TABLE_OFFSET                     17
#define _DCC_CURVE_LSB_TABLE_OFFSET                 40

//--------------------------------------------------
// Definitions of DCC Histogram
//--------------------------------------------------
#define _DCC_HISTO_YMAX_LB                          0x00
#define _DCC_HISTO_YMIN_HB                          0x3FF
#define _DCC_HISTO_NF                               (26)

//--------------------------------------------------
// Definitions of ICM Adjust Option
//--------------------------------------------------
#define _CM0_ENABLE                                 _BIT0
#define _CM1_ENABLE                                 _BIT1
#define _CM2_ENABLE                                 _BIT2
#define _CM3_ENABLE                                 _BIT3
#define _CM4_ENABLE                                 _BIT4
#define _CM5_ENABLE                                 _BIT5
#define _Y_CORRECTION_MODE                          _BIT6
#define _UV_DELTA_RANGE                             _BIT7
#define _UV_DELTA_RANGE_EXTEND                      _BIT0

#define _ICM_UVOFFSET_TABLE_SIZE                    108
#define _ICM_UVOFFSET_TABLE_SIZE_LSB                25
#define _ONE_CM_TABLE_SIZE                          134
#define _CMN_INDEX_OFFSET                           3
#define _CMN_UV_TABLE_OFFSET                        4
#define _CMN_UV_LSB_TABLE_OFFSET                    112

#define _SCM_TABLE_SIZE                             78
#define _SCMN_INDEX_OFFSET                          3
#define _SCMN_TABLE_OFFSET                          4

//--------------------------------------------------
// ICM Table Length
//--------------------------------------------------
#define _SIXCOLOR_TABLE_SIZE_MSB                    64
#define _SIXCOLOR_TABLE_SIZE_LSB                    16
#define _SIXCOLOR_TABLE_SIZE_AXIS                   16

//--------------------------------------------------
// Definitions of Six Color
//--------------------------------------------------
#define _SIX_COLOR_RIGHTBUFFER                      0
#define _SIX_COLOR_RIGHTWIDTH                       1
#define _SIX_COLOR_CENTER                           2
#define _SIX_COLOR_LEFTWIDTH                        3
#define _SIX_COLOR_LEFTBUFFER                       4

//--------------------------------------------------
// Table Length
//--------------------------------------------------
#define _SIXCOLOR_TABLE_SIZE_MSB_BRI_COMPENSATE     (16)
#define _SIXCOLOR_TABLE_SIZE_LSB_BRI_COMPENSATE     (4)
#define _SIXCOLOR_TABLE_SIZE_AXIS_BRI_COMPENSATE    (16)
#define _SIXCOLOR_TO_GRAY_TABLE_SIZE_LSB_BRI_COMPENSATE\
                                                    (20)

//--------------------------------------------------
// Definitions of Six Color
//--------------------------------------------------
#define _SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE       0
#define _SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE        1
#define _SIX_COLOR_CENTER_BRI_COMPENSATE            2
#define _SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE         3
#define _SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE        4

//--------------------------------------------------
// Definitions of Six Color
//--------------------------------------------------
#define _SIX_COLOR_RIGHTBUFFER                      0
#define _SIX_COLOR_RIGHTWIDTH                       1
#define _SIX_COLOR_CENTER                           2
#define _SIX_COLOR_LEFTWIDTH                        3
#define _SIX_COLOR_LEFTBUFFER                       4

//--------------------------------------------------
// Definitions of Six Color
//--------------------------------------------------
#define _SIX_COLOR_RIGHTBUFFER_BRI_COMPENSATE       0
#define _SIX_COLOR_RIGHTWIDTH_BRI_COMPENSATE        1
#define _SIX_COLOR_CENTER_BRI_COMPENSATE            2
#define _SIX_COLOR_LEFTWIDTH_BRI_COMPENSATE         3
#define _SIX_COLOR_LEFTBUFFER_BRI_COMPENSATE        4

//--------------------------------------------------
// Definitions of ICM Chameleon Mode
//--------------------------------------------------
#define _CHAMELEON_HUE_DELTA_STEP                   50

//--------------------------------------------------
// Definitions of ICM Night Sniper Mode
//--------------------------------------------------
#define _ICM_NIGHT_SNIPER_HUE                       100
#define _ICM_NIGHT_SNIPER_HUE_MAX                   300

//--------------------------------------------------
// Definitions of 3D gamma Options
//--------------------------------------------------
#define _3DGAMMA_TABLE_SIZE                         29478

//--------------------------------------------------
// Definitions of PCM Option
//--------------------------------------------------
#define _PCM_INPUTGAMMA_TABLE_SIZE                  195
#define _PCM_R_CHANNEL_IG_START                     0
#define _PCM_G_CHANNEL_IG_START                     (_PCM_R_CHANNEL_IG_START + _PCM_INPUTGAMMA_TABLE_SIZE + 2)
#define _PCM_B_CHANNEL_IG_START                     (_PCM_G_CHANNEL_IG_START + _PCM_INPUTGAMMA_TABLE_SIZE + 2)

#define _PCM_INPUTGAMMA_1025_NODE_TABLE_SIZE        1539
#define _PCM_R_CHANNEL_IG_1025_NODE_START           0
#define _PCM_G_CHANNEL_IG_1025_NODE_START           (_PCM_R_CHANNEL_IG_1025_NODE_START + _PCM_INPUTGAMMA_1025_NODE_TABLE_SIZE + 3)
#define _PCM_B_CHANNEL_IG_1025_NODE_START           (_PCM_G_CHANNEL_IG_1025_NODE_START + _PCM_INPUTGAMMA_1025_NODE_TABLE_SIZE + 3)

#define _PCM_POSTGAMMA_LATCH_TABLE_SIZE             148
#define _PCM_POSTGAMMA_SRAM_TABLE_SIZE              2052
#define _PCM_OUTPUTGAMMA_LATCH_TABLE_SIZE           148
#define _PCM_OUTPUTGAMMA_SRAM_TABLE_SIZE            2052
#define _PCM_IG_DOUBLE_BUFFER_WAIT_TIME             168
#define _YM_DOUBLE_BUFFER_WAIT_TIME                 168
#define _ADVANCED_HDR10_YM_TABLE_READY_WAIT_TIME    17
#define _ADVANCED_HDR10_IG_NORM_SIZE                40
#define _YMAPPING_SINGLE_TABLE_STEP                 2

//--------------------------------------------------
// Definitions of sRGB Option
//--------------------------------------------------
#define _SRGB_TABLE_SIZE                            24

//--------------------------------------------------
// Definitions of local dimming Option
//--------------------------------------------------
#define _LDADJUST_TABLE_SIZE_DIRECTMASK             56
#if(_HW_LOCAL_DIMMING_GEN_SEL == _HW_LOCAL_DIMMING_GEN1)
#define _LDHISTO_TABLE_SIZE_LUT                     32
#else
#define _LDHISTO_TABLE_SIZE_LUT                     256
#endif

#define _LDADJUST_ADJUST_RATE                       5
#define _LDADJUST_CORRECT_RATE                      5
#define _LDBLM_GAIN_TABLE_LENGTH                    4608
#define _BLM_TIMEOUT                                2
#define _SMOOTH_TIMEOUT                             2
#define _BLM_S1LUTOFFSET                            0x1080
#define _BLM_S2LUTOFFSET                            0x1940
#if(_LOCAL_DIMMING_UP_REGION_SUPPORT == _ON)
#define _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE         MINOF(_LOCAL_DIMMING_TOTAL_REGION_UP, _HW_LOCAL_DIMMING_TABLE0_SIZE)
#define _LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE         ((_LOCAL_DIMMING_TOTAL_REGION_UP < _HW_LOCAL_DIMMING_TABLE0_SIZE) ? 0 : (_LOCAL_DIMMING_TOTAL_REGION_UP - _HW_LOCAL_DIMMING_TABLE0_SIZE))
#define _LOCAL_DIMMING_MAX_TABLE_BLOCK_SIZE         MAXOF(_LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE, _LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE)
#else
#define _LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE         MINOF(_LOCAL_DIMMING_TOTAL_REGION, _HW_LOCAL_DIMMING_TABLE0_SIZE)
#define _LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE         ((_LOCAL_DIMMING_TOTAL_REGION < _HW_LOCAL_DIMMING_TABLE0_SIZE) ? 0 : (_LOCAL_DIMMING_TOTAL_REGION - _HW_LOCAL_DIMMING_TABLE0_SIZE))
#define _LOCAL_DIMMING_MAX_TABLE_BLOCK_SIZE         MAXOF(_LOCAL_DIMMING_PWM0_MAX_ACCESS_SIZE, _LOCAL_DIMMING_PWM1_MAX_ACCESS_SIZE)
#endif
//--------------------------------------------------
// Definitions of Dither Options
//--------------------------------------------------
#if(_D_DITHER_FUNCTION == _ON)
#if((_HW_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_3_6BIT_DITHERTBL_6BIT_PANEL) ||\
    (_HW_DDITHER_TYPE == _DDITHER_GEN_4_6BIT_DITHERTBL_6BIT_PANEL_S2))

#define _DDITHER_TEMPORAL_ENABLE                    _ENABLE

#else // else of #if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)

#define _DDITHER_TEMPORAL_ENABLE                    ((_PANEL_DISP_BIT_MODE == _PANEL_DISP_18_BIT) ? _ENABLE : _D_DITHER_TEMP)

#endif // end of #if(_DDITHER_TYPE == _DDITHER_GEN_1_6BIT_DITHERTBL)
#endif // end of #if(_D_DITHER_SUPPORT == _ON)

#define _DDITHER_KEEP_1_FRAME                       0
#define _DDITHER_KEEP_2_FRAME                       1
#define _DDITHER_KEEP_4_FRAME                       2
#define _DDITHER_KEEP_8_FRAME                       3
#define _DDITHER_KEEP_16_FRAME                      4

#define _DDITHER_DITHER_TABLE_LENGTH                (144)
#define _DDITHER_TEMPORAL_TABLE_LENGTH              (32)
#define _DDITHER_REALIGN_TABLE_LENGTH               (48)
#define _DDITHER_REALIGN_TEMPO_TABLE_LENGTH         (8)
#define _DDITHER_LSB_TABLE_LENGTH                   (16)
#define _DDITHER_ADVANCESETTING_TABLE_LENGTH        (45)

//--------------------------------------------------
// Definitions of Local Dimming
//--------------------------------------------------
#define _LOCAL_DIMMING_HISTO_LOW                    500

//--------------------------------------------------
// Definitions of anti-aliasing Option
//--------------------------------------------------
#define _ANTIALIASING_TABLE_SIZE_CONTROL            (29)
#define _ANTIALIASING_TABLE_SIZE_DEBUGMODE          (1)
#define _ANTIALIASING_TABLE_SIZE_ONSPEC             (3)
#define _ANTIALIASING_TABLE_SIZE_DETECTOR_P1        (25)
#define _ANTIALIASING_TABLE_SIZE_DETECTOR_P2        (25)
#define _ANTIALIASING_TABLE_SIZE_KERNEL_P1          (50)
#define _ANTIALIASING_TABLE_SIZE_KERNEL_P2          (50)
#define _ANTIALIASING_TABLE_SIZE_KERNEL_P3          (18)
#define _ANTIALIASING_COEF_TABLE_SIZE               (_ANTIALIASING_TABLE_SIZE_CONTROL +\
                                                     _ANTIALIASING_TABLE_SIZE_DEBUGMODE +\
                                                     _ANTIALIASING_TABLE_SIZE_DETECTOR_P1 +\
                                                     _ANTIALIASING_TABLE_SIZE_DETECTOR_P2 +\
                                                     _ANTIALIASING_TABLE_SIZE_KERNEL_P1 +\
                                                     _ANTIALIASING_TABLE_SIZE_KERNEL_P2 +\
                                                     _ANTIALIASING_TABLE_SIZE_KERNEL_P3)



//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _LSR_HLW_TYPE_OFF_OFF = 0x00, // 'b00
    _LSR_HLW_TYPE_OFF_ON = 0x01,  // 'b01
    _LSR_HLW_TYPE_ON_OFF = 0x02,  // 'b10
    _LSR_HLW_TYPE_ON_ON = 0x03,   // 'b11
} EnumLSRHLWType;

//--------------------------------------------------
// Enum of I-Domain Code Table
//--------------------------------------------------
typedef enum
{
    _COLOR_CONV_RGBLIMIT_10BITS,
    _COLOR_CONV_RGBFULL_10BITS,
    _COLOR_CONV_YUV709LIMIT_10BITS,
    _COLOR_CONV_YUV601LIMIT_10BITS,
    _COLOR_CONV_YUV601FULL_10BITS,
    _COLOR_CONV_YUV2020LIMIT_10BITS,
    _COLOR_CONV_YUV2020FULL_10BITS,
    _COLOR_CONV_RGBLIMIT_8BITS,
    _COLOR_CONV_RGBFULL_8BITS,
    _COLOR_CONV_YUV709LIMIT_8BITS,
    _COLOR_CONV_YUV709FULL_8BITS,
    _COLOR_CONV_YUV601LIMIT_8BITS,
    _COLOR_CONV_YUV601FULL_8BITS,
    _COLOR_CONV_YUV2020LIMIT_8BITS,
    _COLOR_CONV_YUV2020FULL_8BITS,
    _COLOR_CONV_NONE,
} EnumIColorConvTable;

//--------------------------------------------------
// Enumerations of Local Dimming Adaptive Smooth Mode
//--------------------------------------------------
typedef enum
{
    _LOCAL_DIMMING_ADAPTIVE_SMOOTH_SMOOTH_ON,
    _LOCAL_DIMMING_ADAPTIVE_SMOOTH_SMOOTH_OFF,
} EnumLDPWMAdaptiveSmoothMode;

//--------------------------------------------------
// Enumerations of Local Dimming PWM SRAM
//--------------------------------------------------
typedef enum
{
    _LOCAL_DIMMING_PWM_SRAM0,
    _LOCAL_DIMMING_PWM_SRAM1,
} EnumLDPWMSRAMIndex;

//--------------------------------------------------
// Enumerations of Anti Aliasing Support
//--------------------------------------------------
typedef enum
{
    _ANTI_ALIASING_NO_SUPPORT = _FALSE,
    _ANTI_ALIASING_SUPPORT = _TRUE,
    _ANTI_ALIASING_NONE,
} EnumAntiAliasingSupportStatus;

//****************************************************************************
// Undefined Reg List
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_COLOR_IP_HL_WIN == _ON)
extern void ScalerColorHLWSetting(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
extern void ScalerColorHLWDDomainAdjustRegister(WORD usHPos, WORD usHWidth, WORD usVPos, WORD usVHeight);
#endif

#if((_COLOR_IP_LSR == _ON) || (_COLOR_IP_DSHP == _ON))
extern BYTE ScalerColorUltraVividGetDDomainRegion(EnumSelRegion enumSelRegion);
#endif

#if(_COLOR_IP_LSR == _ON)
extern EnumLSRHLWType ScalerColorLSRHLWGetStatus(EnumDDomainRegion enumDDomainRegion);
extern void ScalerColorLSRHLWSetting(EnumDDomainRegion enumDDomainRegion, EnumLSRHLWType enumLSRHLWType);
extern EnumLSRHLWType ScalerColorLSRHLWPBPTBGetStatus(void);
extern void ScalerColorLSRHLWPBPTBSetting(EnumLSRHLWType enumLSRHLWType);
extern void ScalerColorLSRRegionEnable(EnumSelRegion enumSelRegion, bit bOn);
#endif

#if(_COLOR_IP_DSHP == _ON)
extern void ScalerColorDSHPEnable(EnumDDomainRegion enumDDomainRegion, EnumSelRegion enumSelRegion, bit bOn);
extern void ScalerColorDSHPSetEffectRegion(EnumDDomainRegion enumDDomainRegion, EnumSelRegion enumSelRegion, bit bOn);
#endif

#if(_COLOR_IP_CONTRAST == _ON)
extern void ScalerColorContrastCoefAdjust(EnumCtsCoefType enumCtsCoefType, WORD *pusData);
#endif

#if(_COLOR_IP_BRIGHTNESS == _ON)
extern void ScalerColorBrightnessCoefAdjust(EnumBriCoefType enumBriCoefType, WORD *pusData);
#endif

#if(_COLOR_IP_ICM == _ON)
extern void ScalerColorICMLoadTable(EnumSelRegion enumSelRegion, BYTE *pucICMTable, BYTE ucBankNum);
extern void ScalerColorICMAdjust(WORD usPage, BYTE ucAdjustOption1, BYTE ucAdjustOption2);
extern void ScalerColorICMUVOffsetLoadTable(WORD usPage, BYTE *pucICMTable, BYTE ucBankNum);
extern void ScalerColorSCMAdjust(WORD usPage, BYTE ucAdjustOption1, BYTE ucAdjustOption2);

#if(_SIX_COLOR_SUPPORT == _ON)
extern void ScalerColorSixColorInitial(EnumSelRegion enumSelRegion);
extern void ScalerColorSixColorAdjust(EnumSelRegion enumSelRegion, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
extern void ScalerColorSixColorICMLoad(WORD usPage, BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect);
extern void ScalerColorSixColorICMLoadBriCompensate(WORD usPage, SWORD shDeltaY, BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect);
extern void ScalerColorSixColorAdjustNormal(WORD usPage, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
extern void ScalerColorSixColorAdjustBriCompensate(WORD usPage, BYTE ucColorIndex, BYTE ucHuePosition, BYTE ucSatPosition);
extern void ScalerColorSixColorInitialNormal(WORD usPage);
extern void ScalerColorSixColorInitialBriCompensate(WORD usPage);
extern void ScalerColorSixColorSetAngleRBBriCompensate(WORD usPage, BYTE ucCMSel);
extern void ScalerColorSixColorSetAngleRB(WORD usPage, BYTE ucCMSel);
#endif

#if(_IMMERSIVE_NIGHT_SNIPER_FUNCTION == _ON)
extern void ScalerColorICMNightSniperAdjust(EnumSelRegion enumSelRegion, BYTE ucSaturation, BYTE ucLightness, BYTE ucDarkOffset);
#endif

#if(_ICM_CHAMELEON_FUNCTION == _ON)
extern void ScalerColorChameleonAdjust(EnumSelRegion enumSelRegion, BYTE ucColorIndex, StructICMChameleonAxisData *pstAxisData, BYTE ucDarkOffset);
extern void ScalerColorChameleonAdjustByAxis(WORD usPage, BYTE ucColorIndex, WORD usHuePosition, BYTE ucSatPosition, BYTE ucLightnessPosition, BYTE ucDarkOffset);
extern void ScalerColorChameleonLoad(WORD usPage, SWORD shDeltaY, BYTE *pucICMData, BYTE ucCMSel, BYTE ucLoadSelect);
extern void ScalerColorChameleonSetAngleRB(WORD usPage, BYTE ucCMSel);
extern void ScalerColorChameleonInitial(EnumSelRegion enumSelRegion);
extern void ScalerColorChameleonInitialAdjust(WORD usPage);
#endif

#endif

#if(_COLOR_OUTPUT_POST_GAMMA_BYPASS_SUPPORT == _ON)
#if((_COLOR_IP_O_GAMMA == _ON) || (_COLOR_IP_P_GAMMA == _ON))
extern BYTE *ScalerColorOutputPostGammaBypassGetTableAddress(EnumPCMModeSelect enumPCMMode);
extern BYTE ScalerColorOutputPostGammaBypassGetTableBank(void);
#endif
#endif

#if(_COLOR_IP_O_GAMMA == _ON)
extern EnumHLWStatus ScalerColorGammaGetHLWRegionStatus(EnumSelRegion enumSelRegion);
#endif

#if(_COLOR_IP_P_GAMMA == _ON)
extern EnumHLWStatus ScalerColorPostGammaGetHLWRegionStatus(EnumSelRegion enumSelRegion);
#endif

extern EnumSUBypassPage ScalerColorScalingGetByPassTableRegPage(EnumSelRegion enumSelRegion);

#if(_COLOR_IP_YMAPPING == _ON)
extern void ScalerColorYMappingSetRGBCoefficient(EnumSelRegion enumSelRegion, WORD usRcoef, WORD usGcoef, WORD usBcoef);
extern void ScalerColorYMappingSetSoftClampParam(EnumSelRegion enumSelRegion, BYTE ucYMappingSoftClampParam);
extern EnumFunctionOnOFF ScalerColorYMappingGetDBStatus(void);
extern void ScalerColorYMappingDBApply(EnumSelRegion enumSelRegion, EnumDBApply enumDBApply);
#endif

#if(_COLOR_IP_I_GAMMA == _ON)
extern void ScalerColorPCMInputGamma129NodeAdjustXRAM(EnumSelRegion enumSelRegion, BYTE *pucGammaTableArray, EnumIGDBEnableStatus enumDbEnable);
extern void ScalerColorPCMInputGammaDBEnable(EnumFunctionOnOFF enumOn);
extern void ScalerColorPCMInputGammaDBApply(EnumDBApply enumDBApply);
extern EnumHLWStatus ScalerColorPCMGetHLWRegionStatus(EnumSelRegion enumSelRegion);
extern EnumHLWStatus ScalerColorPCMInputGammaGetHLWRegionStatus(EnumSelRegion enumSelRegion);
#if(_COLOR_IP_SRGB == _ON)
extern WORD ScalerColorPCMSRGBGetFlashAddress(EnumPCMType enumPCMType, EnumOGCModeSelect enumOGCModeSelect);
extern EnumHLWStatus ScalerColorPCMSRGBGetHLWRegionStatus(EnumSelRegion enumSelRegion);
#if(_HW_D_DOMAIN_RGN_COUNT_MAX > 1)
extern void ScalerColorPCMSRGBSetEffectiveRegion(EnumHLWSetSel enumSetSel, EnumDBApply enumDBApply);
#endif
#if(_OCC_COLORTEMP_TRANSFER_FUNCTION == _ON)
extern void ScalerColorPCMSRGBColorTempTransfer(EnumSelRegion enumSelRegion, EnumPCMType enumPCMMode, WORD *pusTable, EnumSrgbPrecision enumSrgbPrecision, EnumOGCModeSelect enumOGCModeSelect);
#endif
#endif
#if(_COLOR_IP_P_GAMMA == _ON)
extern EnumHLWStatus ScalerColorPCMPostGammaGetHLWRegionStatus(EnumSelRegion enumSelRegion);
#endif
#if(_COLOR_IP_O_GAMMA == _ON)
extern EnumHLWStatus ScalerColorPCMOutputGammaGetHLWRegionStatus(EnumSelRegion enumSelRegion);
#endif
#if(_COLOR_IP_YMAPPING == _ON)
extern EnumHLWStatus ScalerColorPCMYmappingGetHLWRegionStatus(EnumSelRegion enumSelRegion);
#endif
#endif

#if(_COLOR_IP_COLOR_CONVERT == _ON)
extern EnumIColorConvTable ScalerColorSpaceGetRgb2YuvTableIndex(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace);
extern BYTE ScalerColorSpaceGetRgb2YuvCtrlValue(EnumIColorConvTable enumIColorConvTable);
#if(_COLOR_IP_DM == _ON)
extern EnumIColorConvTable ScalerColorSpaceGetRgb2YuvTableIndexDM(EnumDisplayRegion enumDisplayRegion);
#endif
#if((_FRC_SUPPORT == _ON) && (_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON))
extern BYTE ScalerColorSpaceConvertIDomainWaitEventForAutoBlockToggle(void);
extern void ScalerColorSpaceConvertDDomainWaitEventForAutoBlockToggle(BYTE ucDVSCnt);
#endif
#endif

#if(_COLOR_IP_420_SUPPORT == _ON)
extern void ScalerColor420To422P0FinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath);
extern bit ScalerColor420To422P0GetStatus(void);
extern bit ScalerColor420To422P0GetDoublePixelStatus(void);
extern void ScalerColor420To422P0InitialSetting(void);

#if(_HW_FORMAT_CONVERSION_PATH1_SUPPORT == _ON)
extern void ScalerColor420To422P1FinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath);
extern bit ScalerColor420To422P1GetStatus(void);
extern bit ScalerColor420To422P1GetDoublePixelStatus(void);
extern void ScalerColor420To422P1InitialSetting(void);
#endif

#if(_HW_FORMAT_CONVERSION_PATH2_SUPPORT == _ON)
extern void ScalerColor420To422P2FinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath);
extern bit ScalerColor420To422P2GetStatus(void);
extern bit ScalerColor420To422P2GetDoublePixelStatus(void);
extern void ScalerColor420To422P2InitialSetting(void);
#endif

#if(_HW_FORMAT_CONVERSION_PATH3_SUPPORT == _ON)
extern void ScalerColor420To422P3FinalSetting(EnumInputPort enumInputPort, EnumInputDataPath enumInputDataPath);
extern bit ScalerColor420To422P3GetStatus(void);
extern bit ScalerColor420To422P3GetDoublePixelStatus(void);
extern void ScalerColor420To422P3InitialSetting(void);
#endif
#endif // End of #if(_COLOR_IP_420_SUPPORT == _ON)

#if(_ADVANCED_HDR10_SUPPORT == _ON)
extern bit ScalerColorGetPCMHLWDBApply(EnumPCMHLWDBSel enumPCMHLWDBSel);
extern bit ScalerColorPCMHLWDBPolling(EnumPCMHLWDBSel enumPCMHLWDBSel);
extern void ScalerColorPCMHLWDBReInitial(EnumPCMHLWDBSel enumPCMHLWDBSel);
#endif

#if(_COLOR_IP_LOCAL_CONTRAST == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern bit ScalerColorLocalContrastCheckR1FBStatus(WORD usShfitPage);
#endif
#endif

#if(_COLOR_IP_LOCAL_DIMMING == _ON)
#if(_HW_LOCAL_DIMMING_GEN_SEL != _HW_LOCAL_DIMMING_GEN1)
extern void ScalerColorLDSmoothSetShiftGain(WORD usSmoothParaGain);
#endif
extern void ScalerColorLDPWMProcReadPWMTableSub(WORD *pusPWMTable, WORD usPWMTableSize, EnumLDPWMSRAMIndex enumLDPWMSRAMIndex);
extern void ScalerColorLDPWMProcWritePWMTableSub(WORD *pusPWMTable, WORD usPWMTableSize, BYTE ucBankNum, EnumLDPWMSRAMIndex enumLDPWMSRAMIndex);
#endif

#if(_COLOR_IP_ANTI_ALIASING == _ON)
extern void ScalerColorAntiAliasingOnCtrlInitialSetting(StructColorAntiAliasingSetting *pstAntiAliasingData);
extern void ScalerColorAntiAliasingGetInterfaceInform(StructColorAntiAliasingSetting *pstAntiAliasingData);
extern void ScalerColorAntiAliasingSetBypassEn(bit bOn);
extern bit ScalerColorAntiAliasingGetMeasureTimingInfo(void);
#endif

extern bit ScalerColorScalingGetScalingUpBypassStatus(EnumSelRegion enumSelRegion);
extern bit ScalerColorScalingGetScalingDownBypassStatus(EnumSelRegion enumSelRegion);


#endif // End of #ifndef __SCALER_COLOR_H__
