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
// ID Code      : ExternalDeviceLedDriverInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------



//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
typedef enum
{
    _PWMTOSPI_INTERFACE_0 = 0x00,
    _PWMTOSPI_INTERFACE_1 = 0x01,
    _PWMTOSPI_INTERFACE_2 = 0x02,
} EnumPwmToSpiInterface;

#endif

#if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)
typedef enum
{
    _DEVICE_LED_DRIVER_001 = 1,
    _DEVICE_LED_DRIVER_002,
    _DEVICE_LED_DRIVER_003,
    _DEVICE_LED_DRIVER_004,
    _DEVICE_LED_DRIVER_005,
    _DEVICE_LED_DRIVER_006,
    _DEVICE_LED_DRIVER_007,
    _DEVICE_LED_DRIVER_008,
    _DEVICE_LED_DRIVER_009,
    _DEVICE_LED_DRIVER_010,
    _DEVICE_LED_DRIVER_011,
    _DEVICE_LED_DRIVER_012,
    _DEVICE_LED_DRIVER_013,
    _DEVICE_LED_DRIVER_014,
    _DEVICE_LED_DRIVER_015,
    _DEVICE_LED_DRIVER_016,
    _DEVICE_LED_DRIVER_017,
    _DEVICE_LED_DRIVER_018,
    _DEVICE_LED_DRIVER_019,
    _DEVICE_LED_DRIVER_020,
    _DEVICE_LED_DRIVER_021,
    _DEVICE_LED_DRIVER_022,
    _DEVICE_LED_DRIVER_023,
    _DEVICE_LED_DRIVER_024,
    _DEVICE_LED_DRIVER_025,
    _DEVICE_LED_DRIVER_026,
    _DEVICE_LED_DRIVER_027,
    _DEVICE_LED_DRIVER_028,
    _DEVICE_LED_DRIVER_029,
    _DEVICE_LED_DRIVER_030,
    _DEVICE_LED_DRIVER_031,
    _DEVICE_LED_DRIVER_032,
    _DEVICE_LED_DRIVER_033,
    _DEVICE_LED_DRIVER_034,
    _DEVICE_LED_DRIVER_035,
    _DEVICE_LED_DRIVER_036,
    _DEVICE_LED_DRIVER_037,
    _DEVICE_LED_DRIVER_038,
    _DEVICE_LED_DRIVER_039,
    _DEVICE_LED_DRIVER_040,
    _DEVICE_LED_DRIVER_041,
    _DEVICE_LED_DRIVER_042,
    _DEVICE_LED_DRIVER_043,
    _DEVICE_LED_DRIVER_044,
    _DEVICE_LED_DRIVER_045,
    _DEVICE_LED_DRIVER_046,
    _DEVICE_LED_DRIVER_047,
    _DEVICE_LED_DRIVER_048,
    _DEVICE_LED_DRIVER_049,
    _DEVICE_LED_DRIVER_050,
    _DEVICE_LED_DRIVER_051,
    _DEVICE_LED_DRIVER_052,
    _DEVICE_LED_DRIVER_053,
    _DEVICE_LED_DRIVER_054,
    _DEVICE_LED_DRIVER_055,
    _DEVICE_LED_DRIVER_056,
    _DEVICE_LED_DRIVER_057,
    _DEVICE_LED_DRIVER_058,
    _DEVICE_LED_DRIVER_059,
    _DEVICE_LED_DRIVER_060,
    _DEVICE_LED_DRIVER_061,
    _DEVICE_LED_DRIVER_062,
    _DEVICE_LED_DRIVER_063,
    _DEVICE_LED_DRIVER_064,
    _DEVICE_LED_DRIVER_065,
    _DEVICE_LED_DRIVER_066,
    _DEVICE_LED_DRIVER_067,
    _DEVICE_LED_DRIVER_068,
    _DEVICE_LED_DRIVER_069,
    _DEVICE_LED_DRIVER_070,
    _DEVICE_LED_DRIVER_071,
    _DEVICE_LED_DRIVER_072,
    _DEVICE_LED_DRIVER_073,
    _DEVICE_LED_DRIVER_074,
    _DEVICE_LED_DRIVER_075,
    _DEVICE_LED_DRIVER_076,
    _DEVICE_LED_DRIVER_077,
    _DEVICE_LED_DRIVER_078,
    _DEVICE_LED_DRIVER_079,
    _DEVICE_LED_DRIVER_080,
    _DEVICE_LED_DRIVER_081,
    _DEVICE_LED_DRIVER_082,
    _DEVICE_LED_DRIVER_083,
    _DEVICE_LED_DRIVER_084,
    _DEVICE_LED_DRIVER_085,
    _DEVICE_LED_DRIVER_086,
    _DEVICE_LED_DRIVER_087,
    _DEVICE_LED_DRIVER_088,
    _DEVICE_LED_DRIVER_089,
    _DEVICE_LED_DRIVER_090,
    _DEVICE_LED_DRIVER_091,
    _DEVICE_LED_DRIVER_092,
    _DEVICE_LED_DRIVER_093,
    _DEVICE_LED_DRIVER_094,
    _DEVICE_LED_DRIVER_095,
    _DEVICE_LED_DRIVER_096,
    _DEVICE_LED_DRIVER_097,
    _DEVICE_LED_DRIVER_098,
    _DEVICE_LED_DRIVER_099,
    _DEVICE_LED_DRIVER_100,
    _DEVICE_LED_DRIVER_101,
    _DEVICE_LED_DRIVER_102,
    _DEVICE_LED_DRIVER_103,
    _DEVICE_LED_DRIVER_104,
    _DEVICE_LED_DRIVER_105,
    _DEVICE_LED_DRIVER_106,
    _DEVICE_LED_DRIVER_107,
    _DEVICE_LED_DRIVER_108,
    _DEVICE_LED_DRIVER_109,
    _DEVICE_LED_DRIVER_110,
    _DEVICE_LED_DRIVER_111,
    _DEVICE_LED_DRIVER_112,
    _DEVICE_LED_DRIVER_113,
    _DEVICE_LED_DRIVER_114,
    _DEVICE_LED_DRIVER_115,
    _DEVICE_LED_DRIVER_116,
    _DEVICE_LED_DRIVER_117,
    _DEVICE_LED_DRIVER_118,
    _DEVICE_LED_DRIVER_119,
    _DEVICE_LED_DRIVER_120,
    _DEVICE_LED_DRIVER_121,
    _DEVICE_LED_DRIVER_122,
    _DEVICE_LED_DRIVER_123,
    _DEVICE_LED_DRIVER_124,
    _DEVICE_LED_DRIVER_125,
    _DEVICE_LED_DRIVER_126,
    _DEVICE_LED_DRIVER_127,
    _DEVICE_LED_DRIVER_128,
    _DEVICE_LED_DRIVER_129,
    _DEVICE_LED_DRIVER_130,
    _DEVICE_LED_DRIVER_131,
    _DEVICE_LED_DRIVER_132,
    _DEVICE_LED_DRIVER_133,
    _DEVICE_LED_DRIVER_134,
    _DEVICE_LED_DRIVER_135,
    _DEVICE_LED_DRIVER_136,
    _DEVICE_LED_DRIVER_137,
    _DEVICE_LED_DRIVER_138,
    _DEVICE_LED_DRIVER_139,
    _DEVICE_LED_DRIVER_140,
    _DEVICE_LED_DRIVER_141,
    _DEVICE_LED_DRIVER_142,
    _DEVICE_LED_DRIVER_143,
    _DEVICE_LED_DRIVER_144,
    _DEVICE_LED_DRIVER_145,
    _DEVICE_LED_DRIVER_146,
    _DEVICE_LED_DRIVER_147,
    _DEVICE_LED_DRIVER_148,
    _DEVICE_LED_DRIVER_149,
    _DEVICE_LED_DRIVER_150,
    _DEVICE_LED_DRIVER_151,
    _DEVICE_LED_DRIVER_152,
    _DEVICE_LED_DRIVER_153,
    _DEVICE_LED_DRIVER_154,
    _DEVICE_LED_DRIVER_155,
    _DEVICE_LED_DRIVER_156,
    _DEVICE_LED_DRIVER_157,
    _DEVICE_LED_DRIVER_158,
    _DEVICE_LED_DRIVER_159,
    _DEVICE_LED_DRIVER_160,
    _DEVICE_LED_DRIVER_161,
    _DEVICE_LED_DRIVER_162,
    _DEVICE_LED_DRIVER_163,
    _DEVICE_LED_DRIVER_164,
    _DEVICE_LED_DRIVER_165,
    _DEVICE_LED_DRIVER_166,
    _DEVICE_LED_DRIVER_167,
    _DEVICE_LED_DRIVER_168,
    _DEVICE_LED_DRIVER_169,
    _DEVICE_LED_DRIVER_170,
    _DEVICE_LED_DRIVER_171,
    _DEVICE_LED_DRIVER_172,
    _DEVICE_LED_DRIVER_173,
    _DEVICE_LED_DRIVER_174,
    _DEVICE_LED_DRIVER_175,
    _DEVICE_LED_DRIVER_176,
    _DEVICE_LED_DRIVER_177,
    _DEVICE_LED_DRIVER_178,
    _DEVICE_LED_DRIVER_179,
    _DEVICE_LED_DRIVER_180,
    _DEVICE_LED_DRIVER_181,
    _DEVICE_LED_DRIVER_182,
    _DEVICE_LED_DRIVER_183,
    _DEVICE_LED_DRIVER_184,
    _DEVICE_LED_DRIVER_185,
    _DEVICE_LED_DRIVER_186,
    _DEVICE_LED_DRIVER_187,
    _DEVICE_LED_DRIVER_188,
    _DEVICE_LED_DRIVER_189,
    _DEVICE_LED_DRIVER_190,
    _DEVICE_LED_DRIVER_191,
    _DEVICE_LED_DRIVER_192,
    _DEVICE_LED_DRIVER_193,
    _DEVICE_LED_DRIVER_194,
    _DEVICE_LED_DRIVER_195,
    _DEVICE_LED_DRIVER_196,
    _DEVICE_LED_DRIVER_197,
    _DEVICE_LED_DRIVER_198,
    _DEVICE_LED_DRIVER_199,
    _DEVICE_LED_DRIVER_200,
    _DEVICE_LED_DRIVER_201,
    _DEVICE_LED_DRIVER_202,
    _DEVICE_LED_DRIVER_203,
    _DEVICE_LED_DRIVER_204,
    _DEVICE_LED_DRIVER_205,
    _DEVICE_LED_DRIVER_206,
    _DEVICE_LED_DRIVER_207,
    _DEVICE_LED_DRIVER_208,
    _DEVICE_LED_DRIVER_209,
    _DEVICE_LED_DRIVER_210,
    _DEVICE_LED_DRIVER_211,
    _DEVICE_LED_DRIVER_212,
    _DEVICE_LED_DRIVER_213,
    _DEVICE_LED_DRIVER_214,
    _DEVICE_LED_DRIVER_215,
    _DEVICE_LED_DRIVER_216,
    _DEVICE_LED_DRIVER_217,
    _DEVICE_LED_DRIVER_218,
    _DEVICE_LED_DRIVER_219,
    _DEVICE_LED_DRIVER_220,
    _DEVICE_LED_DRIVER_221,
    _DEVICE_LED_DRIVER_222,
    _DEVICE_LED_DRIVER_223,
    _DEVICE_LED_DRIVER_224,
    _DEVICE_LED_DRIVER_225,
    _DEVICE_LED_DRIVER_226,
    _DEVICE_LED_DRIVER_227,
    _DEVICE_LED_DRIVER_228,
    _DEVICE_LED_DRIVER_229,
    _DEVICE_LED_DRIVER_230,
    _DEVICE_LED_DRIVER_231,
    _DEVICE_LED_DRIVER_232,
    _DEVICE_LED_DRIVER_233,
    _DEVICE_LED_DRIVER_234,
    _DEVICE_LED_DRIVER_235,
    _DEVICE_LED_DRIVER_236,
    _DEVICE_LED_DRIVER_237,
    _DEVICE_LED_DRIVER_238,
    _DEVICE_LED_DRIVER_239,
    _DEVICE_LED_DRIVER_240,
    _DEVICE_LED_DRIVER_241,
    _DEVICE_LED_DRIVER_242,
    _DEVICE_LED_DRIVER_243,
    _DEVICE_LED_DRIVER_244,
    _DEVICE_LED_DRIVER_245,
    _DEVICE_LED_DRIVER_246,
    _DEVICE_LED_DRIVER_247,
    _DEVICE_LED_DRIVER_248,
    _DEVICE_LED_DRIVER_249,
    _DEVICE_LED_DRIVER_250,
    _DEVICE_LED_DRIVER_251,
    _DEVICE_LED_DRIVER_252,
    _DEVICE_LED_DRIVER_253,
    _DEVICE_LED_DRIVER_254,
    _DEVICE_LED_DRIVER_ALL,
} EnumDeviceLedDriver;

typedef enum
{
    _DEVICE_LED_DRIVER_MBR_MODE,
    _DEVICE_LED_DRIVER_LD_MODE,
} EnumDeviceLedDriverMode;

typedef enum
{
    _DEVICE_LED_DRIVER_LOCK,
    _DEVICE_LED_DRIVER_UNLOCK,
} EnumDeviceLedDriverLockUnlock;

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    WORD usDevAddr;                         // SPI Device Address
    WORD usRegStartAddr;                    // SPI Reg R/W Start Address
}StructSpiCmdInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_SPI_SUPPORT == _ON) && (_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON))
extern void ExternalDeviceInterfaceLedDriverInitial(void);
extern void ExternalDeviceInterfaceLedDriverPwmEnable(bit bEnable);
#if((_LOCAL_DIMMING_HDR10_BOOST_SUPPORT == _ON) || (_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON) || (_LOCAL_DIMMING_COMPENSATE_MODE == _LD_COMPENSATE_ADIM))
extern void ExternalDeviceInterfaceLedDriverBoostAdjust(BYTE ucBoostGain);
#endif
extern void ExternalDeviceInterfaceLedDriverBacklight(WORD usBacklight);
extern void ExternalDeviceInterfaceLedDriverModifiedPWM(WORD *pusBlendPWM, WORD *pusHistogramPWM, WORD *pusSmoothPWM, WORD *pusYavg, WORD usMinBlendPWMValue);
extern WORD ExternalDeviceInterfaceLedFormatReadCmdHeader(StructSpiCmdInfo *pstSpiCmdInfo, WORD usSpiReadByteNum, BYTE *pucCmdBuffer);
extern WORD ExternalDeviceInterfaceLedFormatWriteCmdHeader(StructSpiCmdInfo *pstSpiCmdInfo, WORD usPayloadBufferSize, BYTE *pucCmdBuffer);
#if(_LOCAL_DIMMING_USING_EXTRO_INFO == _ON)
extern void ExternalDeviceInterfaceLedDriverModifiedPWMExtroInfo(WORD *pusBlendPWM, WORD usHistogramPWM, WORD usExtroInfo0, WORD usExtroInfo1);
#endif

#if(_LOCAL_DIMMING_REGION_BOOST_SUPPORT == _ON)
extern void ExternalDeviceInterfaceLedDriverRegionBoostAdjust(WORD *pusBoostGainData);
#endif

extern WORD ExternalDeviceInterfaceLedConvertPwmToSpiFormat(WORD usOrgPwmValue);
extern WORD ExternalDeviceInterfaceLedConvertADimFormat(WORD usOrgADimValue);
#if(_DEVICE_LED_DRIVER_CHECKSUM_BYTE_NUM != 0)
extern void ExternalDeviceInterfaceLedDriverCalcChecksum(BYTE *pucSpiCmdBuffer, WORD usCmdDataByteLength);
#endif
#if(_LOCAL_DIMMING_LED_DRIVER_VALID_BY_CS == _ON)
extern WORD ExternalDeviceInterfaceLedUpdateSyncbySpiCE(BYTE *pucSpiCmdBuffer);
extern WORD ExternalDeviceInterfaceLedUpdateSyncbySpiVS(BYTE *pucSpiCmdBuffer);
#endif
#if(_LOCAL_DIMMING_MBR_MODE_SUPPORT == _ON)
extern void ExternalDeviceInterfaceLedDriverModeSwitch(EnumDeviceLedDriverMode enumDeviceLedDriverMode);
extern void ExternalDeviceInterfaceLedDriverAdimSpiFormat(WORD *pusColorApplyADim);
#endif
#endif

#endif // End of #if(_DEVICE_LED_DRIVER_TYPE != _DEVICE_LED_DRIVER_NONE)

