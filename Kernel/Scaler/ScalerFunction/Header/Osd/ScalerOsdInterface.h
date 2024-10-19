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
// ID Code      : ScalerOsdInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerOsdMapRotationAndRotionSize(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, EnumOsdRotateMapB enumOsdRotateMapB, EnumOsdRotateFontLib enumOsdRotateFontLib, WORD usRotateWidth, WORD usRotateHeight);
#if((_HW_FOSD_MAP_C_D_SUPPORT == _ON) || (_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON))
extern void ScalerOsdMapRotationAndRotionSizeAndStart(EnumOsdRotateType enumOsdRotateType,
                                                      EnumOsdRotateMapA enumOsdRotateMapA, EnumOsdRotateMapB enumOsdRotateMapB,
                                                      EnumOsdRotateMapC enumOsdRotateMapC, EnumOsdRotateMapD enumOsdRotateMapD,
                                                      EnumOsdRotateFontLib enumOsdRotateFontLib, WORD usRotateWidth, WORD usRotateHeight, WORD usFontRotateStartAddr);
#endif

extern void ScalerOsdRotationSize(WORD usRotateWidth, WORD usRotateHeight);

//--------------------------------------------------
// Command
//--------------------------------------------------
extern void ScalerOsdSetDataPortSram(BYTE ucValue);
extern void ScalerOsdSetDataPortWindow(BYTE ucValue);
extern void ScalerOsdBurstWriteDataPortWindow(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation);
extern void ScalerOsdBurstWriteDataPortSram(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation);
extern void ScalerOsdAddrSet(EnumOsdAddrIndicateType enumAddrIndicator, EnumOsdWriteType enumByteSel, WORD usAddress, EnumOsdDBufType enumDbufEnable);
extern void ScalerOsdWriteByte(BYTE ucWriteByteAndIndicate, EnumOsdDBufType enumDBuf, WORD usAddr, BYTE ucData);
extern void ScalerOsdWriteAllByte(BYTE ucIndicate, WORD usAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2);
extern void ScalerOsdWriteProtection(bit bEnable, EnumOsdWriteType enumOsdWriteType, BYTE ucBitSelect);
extern BYTE ScalerOsdFrameControlByteGet(WORD usAddr, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdFrameControlByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData);

//--------------------------------------------------
// Windows
//--------------------------------------------------
extern void ScalerOsdWindowSaturatedColorSelectIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB);
extern void ScalerOsdWindowGradientLevelIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucLevelR, BYTE ucLevelG, BYTE ucLevelB);
extern void ScalerOsdWindowGradientStepIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucStep, BYTE ucDecimal);
extern void ScalerOsdDrawWindowGradientSize(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
extern void ScalerOsdDrawWindowGradientDisableIndex(EnumOsdWinGradientType enumWindowGradientIndex);
extern void ScalerOsdDrawWindowGradient(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);

extern void ScalerOsdFontPriority(EnumOsdFontPriorityType enumOsdFontPriorityType);
extern void ScalerOsdWindow29SpecialFunction(EnumOsdWindow29FunctionType enumOsdWindow29FunctionType);
extern void ScalerOsdWindow28SpecialFunction(EnumOsdWindow28FunctionType enumOsdWindow28FunctionType);
extern void ScalerOsdWindowSpecialColorMaskANDOperation(bit bEnable, EnumOsdWindowsType enumOsdWindowsType);
extern void ScalerOsdWindowDisable(EnumOsdWindowsType enumOsdWindowsType);
extern WORD ScalerOsdWindowRegisterMapping(EnumOsdWindowsType enumOsdWindowsType);
extern void ScalerOsdDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
extern void ScalerOsdWindowChessboard(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucChessBoardColor1, BYTE ucChessBoardColor2);
extern void ScalerOsdWindowHighlightFunction(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucForegroundColor, BYTE ucBackgroundColor, BYTE ucCharactorBorderColor);
extern void ScalerOsdWindowHighlightWinSwitch(bit bSwitchEnable, EnumOsdWindowsType enumOsdWindowsType);
extern void ScalerOsdDrawGridLine(WORD usPitchHorizontal, WORD usPitchVertical);
extern void ScalerOsdRoundedWindowOnOff(EnumOsdWindowsType enumOsdWindowsType, bit bOnOff, bit bUpperLeftEnable, bit bLowerLeftEnable, bit bUpperRightEnable, bit bLowerRightEnable);
extern void ScalerOsdRoundedWindowPattern8x8(BYTE ucIdx, BYTE ucType);
extern void ScalerOsdRoundedWindowPattern16x16(BYTE ucIdx, BYTE ucType);
extern void ScalerOsdRoundedWindowSize(EnumOsdWindowsType enumOsdWindowsType, EnumOsdRoundedWindowType enumRoundedWinSize);
extern void ScalerOsdWindowOnOFF(EnumOsdWindowsType enumOsdWindowsType, bit bWinOnOff);
#if(_HW_OSD_ROUND_WIN_0_PIXEL_SUPPORT == _ON)
extern void ScalerOsdRoundedWindowPattern16x16_0Pixel(BYTE ucIdx, bit bEnable);
extern void ScalerOsdRoundedWindowPattern8x8_0Pixel(BYTE ucIdx, bit bEnable);
#endif

//--------------------------------------------------
// SRAM
//--------------------------------------------------
extern void ScalerOsdHardwareCompressionFont(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, EnumOsdRotateType enumOsdRotateType, bit bTableLocation);
extern void ScalerOsdSetDoubleBufferReady(void);
extern void ScalerOsdWaitDoubleBufferReady(void);
extern void ScalerOsdFontRotateCtrlAuto(EnumOsdRotateType enumRotType, BYTE ucFontDownloadRotEn);
extern void ScalerOsdHardwareVLCFont(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, EnumOsdRotateType enumOsdRotateType, bit bTableLocation);
extern void ScalerOsdHardwareVLCCommand(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, bit bTableLocation);
extern void ScalerOsdSramAddressSetCommand(WORD usSramAddress, EnumOsdWriteType enumOsdWriteType);

extern void ScalerOsdSramGetDataFont(WORD usFontIdx, BYTE ucFontLen, BYTE *pucData);
extern void ScalerOsdSramGetDataCommand(EnumOsdWriteType enumOsdWriteType, WORD usSramAddress, WORD usLength, BYTE *pucData);
extern void ScalerOsdSramBaseAddressSet(EnumOsdMapType enumOsdMapType, WORD usRowCommandStart, WORD usCharactorCommandStart, DWORD ulFontStart);
extern void ScalerOsdSramAddressCount(WORD usRow, WORD usCol, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdCommandByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData);
extern void ScalerOsdCommandAllByte(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2);
extern void ScalerOsdCharCommandByteSeries(WORD usCharAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData, WORD usLength);
extern void ScalerOsdCharCommandAllByteSeries(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2, WORD usLength);
extern void ScalerOsd2BitFontOffset(WORD usOffset);
extern void ScalerOsd4BitFontOffset(WORD usOffset);
extern void ScalerOsdSramDataValue(WORD usRow, WORD usCol, WORD usLength, BYTE ucValue, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdSramDataValue2Byte(WORD usRow, WORD usCol, WORD usLength, BYTE ucValue1, BYTE ucValue2, EnumOsdWriteType enumOsdWriteType);
extern void ScalerOsdBlankFont(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, WORD usPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType);
extern void ScalerOsdChange1BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void ScalerOsdChange2BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void ScalerOsdChange4BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucBackgroundColor, BYTE ucColorPaletteType);
extern void ScalerOsdRowHeight(WORD usRow, BYTE ucHeight, WORD usLength);
extern void ScalerOsdFontLibraryRotation(void);
extern void ScalerOsdFontMaskRegionSet(EnumOsdMapType enumOsdMapType, WORD usRowStart, WORD usRowEnd, WORD usColumnStart, WORD usColumnEnd);
extern void ScalerOsdFontMaskRegionOnOff(EnumOsdMapType enumOsdMapType, bit bOnOff);
extern void ScalerOsdChange2BitColor16_31(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void ScalerOsdCompressionCtrl(EnumOsdDecodeCompressionType enumDecodeCompression, bit bCompressionEnable);
extern DWORD ScalerOsdGetFontBaseAddr(void);
#if(_HW_OSD_DISP_FONT_BASE_ADDR_SUPPORT == _ON)
extern void ScalerOsdSramBaseAddressSetDispFontAddr(DWORD ulDispFontAddr);
extern DWORD ScalerOsdSramBaseAddressGetDispFontAddr(void);
extern void ScalerOsdSramBaseAddressSetDispFontAddrEnable(bit bDispFontAddrEnable);
#endif
#if(_HW_OSD_8_BIT_FONT_SUPPORT == _ON)
extern void ScalerOsd8BitFontOffset(WORD usOffset);
#endif
#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
extern void ScalerOsdSramSetHWPutStringAddress(WORD usAddr);
extern void ScalerOsdSramSetHWPutStringFontData(BYTE ucData);
extern void ScalerOsdSramSetHWPutStringFontSelect(EnumOsdHWPutStringFontSelType enumFontSel);
extern void ScalerOsdSramSetHWPutStringFontWidth(BYTE ucFontWidth);
extern void ScalerOsdSramSetHWPutStringLastFont(bit bLastFont, BYTE ucWidth);
extern void ScalerOsdSramSetHWPutStringApply(void);
extern void ScalerOsdSramSetHWPutStringApplyPollingFinish(void);
extern void ScalerOsdSramSetHWPutStringEnable(bit bEnable);
#endif
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
extern bit ScalerOsdSramGet4ByteCmdEnable(void);
extern void ScalerOsdSramSet4ByteCmdEnable(bit bEnable);
#endif


//--------------------------------------------------
// Function
//--------------------------------------------------
extern void ScalerOsdMapABFunctionEnable(EnumOsdMapType enumMapSel, bit bEnable);
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
extern void ScalerOsdMapFunctionEnable(EnumOsdMapType enumMapSel, bit bEnable);
#endif
extern void ScalerOsdGlobalDoubleBufferSel(EnumOsdDoubleBufferType enumDB);
extern bit ScalerOsdGetDoubleFunctionH(EnumOsdPositionType enumDelaySel);
extern bit ScalerOsdGetDoubleFunctionV(EnumOsdPositionType enumDelaySel);
extern void ScalerOsdScalingUpDoubleEn(EnumOsdPositionType enumDelaySel, BYTE ucHoriEnable, BYTE ucVerEnable);
extern void ScalerOsdScalingUpIptEn(EnumOsdPositionType enumDelaySel, BYTE ucEn);
extern void ScalerOsdScalingUpIptFactor(BYTE ucHFactor, BYTE ucVFactor);
extern void ScalerOsdScalingUpIptInitialValue(BYTE ucHInitValue, BYTE ucVInitValue);
extern void ScalerOsdScalingUpIptSize(EnumOsdPositionType enumOsdPositionType, WORD usHEnd, WORD usVEnd);
extern void ScalerOsdScalingUpIptBoundaryCodition(EnumOsdFontScalingBoundaryType enumBoundary);
extern void ScalerOsdSetFBFirstBlock(EnumOsdFBSel enumPath, BYTE ucOn);
extern void ScalerOsdSetFBFirstStartAddr(EnumOsdFBSel enumPath, WORD usAddr);
extern void ScalerOsdSetFontRotEndAddress(WORD usAddr);
#if(_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON)
extern void ScalerOsdSetFontRotStartAddress(WORD usAddr);
#endif
extern void ScalerOsdSetDCLKSpeedRange(DWORD ulDclk);

extern void ScalerOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern WORD ScalerOsdGetMaxHPos(EnumOsdPositionType enumOsdPositionType);
extern void ScalerOsdSetTransparency(BYTE ucTransparency);
extern void ScalerOsdSetTransparency_T0INT(BYTE ucTransparency);
extern void ScalerOsdCircuitActivated(bit bEnable);
extern bit  ScalerOsdGetOsdEnable(void);
extern void ScalerOsdEnableOsd(void);
extern void ScalerOsdDisableOsd(void);
extern void ScalerOsdSetTransparencyType(EnumOsdTransparencyType enumOsdTransparencyType);
extern void ScalerOsdSetColorPalette(BYTE ucIndex, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB);
extern void ScalerOsdSpecificColorBlending(bit bEnable, BYTE ucIndex);
extern void ScalerOsdMapAHighThanMapB(bit bEnable);
extern void ScalerOsdResetToDefaultValue(void);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerOsdSetFosdFBSeparateEn(BYTE ucEn);
#endif
extern void ScalerOsdSetMouseFunEnable(bit bEn);

extern void ScalerOsdSetOsdHPorchAdjust(void);
