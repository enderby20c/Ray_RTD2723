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
// ID Code      : UserCommonOsdInterface_User.h No.0000
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
extern void UserCommonOsdMapRotationAndRotionSize(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, EnumOsdRotateMapB enumOsdRotateMapB, EnumOsdRotateFontLib enumOsdRotateFontLib, WORD usRotateWidth, WORD usRotateHeight);
#if((_HW_FOSD_MAP_C_D_SUPPORT == _ON) || (_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON))
extern void UserCommonOsdMapRotationAndRotionSizeAndStart(EnumOsdRotateType enumOsdRotateType,
                                                          EnumOsdRotateMapA enumOsdRotateMapA, EnumOsdRotateMapB enumOsdRotateMapB,
                                                          EnumOsdRotateMapC enumOsdRotateMapC, EnumOsdRotateMapD enumOsdRotateMapD,
                                                          EnumOsdRotateFontLib enumOsdRotateFontLib, WORD usRotateWidth, WORD usRotateHeight, WORD usFontRotateStartAddr);
#endif
extern void UserCommonOsdRotationSize(WORD usRotateWidth, WORD usRotateHeight);
extern void UserCommonOsdGlobalOsdInitial(void);

//--------------------------------------------------
// Command
//--------------------------------------------------
extern void UserCommonOsdSetDataPortSram(BYTE ucValue);
extern void UserCommonOsdSetDataPortWindow(BYTE ucValue);
extern void UserCommonOsdBurstWriteDataPortWindow(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation);
extern void UserCommonOsdBurstWriteDataPortSram(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation);
extern void UserCommonOsdAddrSet(EnumOsdAddrIndicateType enumAddrIndicator, EnumOsdWriteType enumByteSel, WORD usAddress, EnumOsdDBufType enumDbufEnable);
extern void UserCommonOsdWriteByte(BYTE ucWriteByteAndIndicate, EnumOsdDBufType enumDBuf, WORD usAddr, BYTE ucData);
extern void UserCommonOsdWriteAllByte(BYTE ucIndicate, WORD usAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2);
extern void UserCommonOsdWriteProtection(bit bEnable, EnumOsdWriteType enumOsdWriteType, BYTE ucBitSelect);
extern BYTE UserCommonOsdFrameControlByteGet(WORD usAddr, EnumOsdWriteType enumOsdWriteType);
extern void UserCommonOsdFrameControlByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData);

//--------------------------------------------------
// Windows
//--------------------------------------------------
extern void UserCommonOsdWindowSaturatedColorSelectIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB);
extern void UserCommonOsdWindowGradientLevelIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucLevelR, BYTE ucLevelG, BYTE ucLevelB);
extern void UserCommonOsdWindowGradientStepIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucStep, BYTE ucDecimal);
extern void UserCommonOsdDrawWindowGradientSize(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
extern void UserCommonOsdDrawWindowGradientDisableIndex(EnumOsdWinGradientType enumWindowGradientIndex);
extern void UserCommonOsdDrawWindowGradient(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
extern void UserCommonOsdFontPriority(EnumOsdFontPriorityType enumOsdFontPriorityType);
extern void UserCommonOsdWindow29SpecialFunction(EnumOsdWindow29FunctionType enumOsdWindow29FunctionType);
extern void UserCommonOsdWindow28SpecialFunction(EnumOsdWindow28FunctionType enumOsdWindow28FunctionType);
extern void UserCommonOsdWindowSpecialColorMaskANDOperation(bit bEnable, EnumOsdWindowsType enumOsdWindowsType);
extern void UserCommonOsdWindowDisable(EnumOsdWindowsType enumOsdWindowsType);
extern WORD UserCommonOsdWindowRegisterMapping(EnumOsdWindowsType enumOsdWindowsType);
extern void UserCommonOsdDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd);
extern void UserCommonOsdWindowChessboard(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucChessBoardColor1, BYTE ucChessBoardColor2);
extern void UserCommonOsdWindowHighlightFunction(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucForegroundColor, BYTE ucBackgroundColor, BYTE ucCharactorBorderColor);
extern void UserCommonOsdDrawGridLine(WORD usPitchHorizontal, WORD usPitchVertical);
extern void UserCommonOsdRoundedWindowOnOff(EnumOsdWindowsType enumOsdWindowsType, bit bOnOff, bit bUpperLeftEnable, bit bLowerLeftEnable, bit bUpperRightEnable, bit bLowerRightEnable);
extern void UserCommonOsdRoundedWindowPattern8x8(BYTE ucIdx, BYTE ucType);
extern void UserCommonOsdRoundedWindowPattern16x16(BYTE ucIdx, BYTE ucType);
extern void UserCommonOsdRoundedWindowSize(EnumOsdWindowsType enumOsdWindowsType, EnumOsdRoundedWindowType enumRoundedWinSize);
extern void UserCommonOsdWindowOnOFF(EnumOsdWindowsType enumOsdWindowsType, bit bWinOnOff);
#if(_HW_OSD_ROUND_WIN_0_PIXEL_SUPPORT == _ON)
extern void UserCommonOsdRoundedWindowPattern16x16_0Pixel(BYTE ucIdx, bit bEnable);
extern void UserCommonOsdRoundedWindowPattern8x8_0Pixel(BYTE ucIdx, bit bEnable);
#endif

//--------------------------------------------------
// SRAM
//--------------------------------------------------
extern void UserCommonOsdHardwareCompressionFont(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, EnumOsdRotateType enumOsdRotateType, bit bTableLocation);
extern void UserCommonOsdSetDoubleBufferReady(void);
extern void UserCommonOsdWaitDoubleBufferReady(void);
extern void UserCommonOsdFontRotateCtrlAuto(EnumOsdRotateType enumRotType, BYTE ucFontDownloadRotEn);
extern void UserCommonOsdHardwareVLCFont(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, EnumOsdRotateType enumOsdRotateType, bit bTableLocation);
extern void UserCommonOsdHardwareVLCCommand(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, bit bTableLocation);
extern void UserCommonOsdSramAddressSetCommand(WORD usSramAddress, EnumOsdWriteType enumOsdWriteType);
extern void UserCommonOsdSramGetDataFont(WORD usFontIdx, BYTE ucFontLen, BYTE *pucData);
extern void UserCommonOsdSramGetDataCommand(EnumOsdWriteType enumOsdWriteType, WORD usSramAddress, WORD usLength, BYTE *pucData);
extern void UserCommonOsdSramBaseAddressSet(EnumOsdMapType enumOsdMapType, WORD usRowCommandStart, WORD usCharactorCommandStart, DWORD ulFontStart);
extern void UserCommonOsdSramAddressCount(WORD usRow, WORD usCol, EnumOsdWriteType enumOsdWriteType);
extern void UserCommonOsdCommandByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData);
extern void UserCommonOsdCommandAllByte(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2);
extern void UserCommonOsdCharCommandByteSeries(WORD usCharAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData, WORD usLength);
extern void UserCommonOsdCharCommandAllByteSeries(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2, WORD usLength);
extern void UserCommonOsd2BitFontOffset(WORD usOffset);
extern void UserCommonOsd4BitFontOffset(WORD usOffset);
extern void UserCommonOsdSramDataValue(WORD usRow, WORD usCol, WORD usLength, BYTE ucValue, EnumOsdWriteType enumOsdWriteType);
extern void UserCommonOsdSramDataValue2Byte(WORD usRow, WORD usCol, WORD usLength, BYTE ucValue1, BYTE ucValue2, EnumOsdWriteType enumOsdWriteType);
extern void UserCommonOsdBlankFont(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, WORD usPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType);
extern void UserCommonOsdChange1BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucForegroundColor, BYTE ucBackgroundColor);
extern void UserCommonOsdChange2BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void UserCommonOsdChange4BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucBackgroundColor, BYTE ucColorPaletteType);
extern void UserCommonOsdRowHeight(WORD usRow, BYTE ucHeight, WORD usLength);
extern void UserCommonOsdFontLibraryRotation(void);
extern void UserCommonOsdFontMaskRegionSet(EnumOsdMapType enumOsdMapType, WORD usRowStart, WORD usRowEnd, WORD usColumnStart, WORD usColumnEnd);
extern void UserCommonOsdFontMaskRegionOnOff(EnumOsdMapType enumOsdMapType, bit bOnOff);
extern void UserCommonOsdChange2BitColor16_31(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3);
extern void UserCommonOsdCompressionCtrl(EnumOsdDecodeCompressionType enumDecodeCompression, bit bCompressionEnable);
extern DWORD UserCommonOsdGetFontBaseAddr(void);
#if(_HW_OSD_DISP_FONT_BASE_ADDR_SUPPORT == _ON)
extern DWORD UserCommonOsdSramBaseAddressGetDispFontAddr(void);
extern void UserCommonOsdSramBaseAddressSetDispFontAddr(DWORD ulDispFontBaseAddr);
#endif
#if(_HW_OSD_8_BIT_FONT_SUPPORT == _ON)
extern void UserCommonOsd8BitFontOffset(WORD usOffset);
#endif
#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
extern void UserCommonOsdSramSetHWPutStringAddress(WORD usAddr);
extern void UserCommonOsdSramSetHWPutStringFontData(BYTE ucData);
extern void UserCommonOsdSramSetHWPutStringFontSelect(EnumOsdHWPutStringFontSelType enumFontSel);
extern void UserCommonOsdSramSetHWPutStringFontWidth(BYTE ucFontWidth);
extern void UserCommonOsdSramSetHWPutStringLastFont(bit bLastFont, BYTE ucWidth);
extern void UserCommonOsdSramSetHWPutStringApply(void);
extern void UserCommonOsdSramSetHWPutStringApplyPollingFinish(void);
extern void UserCommonOsdSramSetHWPutStringEnable(bit bEnable);
#endif // end of #if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
extern bit UserCommonOsdSramGet4ByteCmdEnable(void);
extern void UserCommonOsdSramSet4ByteCmdEnable(bit bEnable);
#endif


//--------------------------------------------------
// Function
//--------------------------------------------------
extern void UserCommonOsdMapABFunctionEnable(EnumOsdMapType enumMapSel, bit bEnable);
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
extern void UserCommonOsdMapFunctionEnable(EnumOsdMapType enumMapSel, bit bEnable);
#endif
extern void UserCommonOsdGlobalDoubleBufferSel(EnumOsdDoubleBufferType enumDB);
extern bit UserCommonOsdGetDoubleFunctionH(EnumOsdPositionType enumDelaySel);
extern bit UserCommonOsdGetDoubleFunctionV(EnumOsdPositionType enumDelaySel);
extern void UserCommonOsdScalingUpDoubleEn(EnumOsdPositionType enumDelaySel, BYTE ucHoriEnable, BYTE ucVerEnable);
extern void UserCommonOsdScalingUpIptEn(EnumOsdPositionType enumDelaySel, BYTE ucEn);
extern void UserCommonOsdScalingUpIptFactor(BYTE ucHFactor, BYTE ucVFactor);
extern void UserCommonOsdScalingUpIptInitialValue(BYTE ucHInitValue, BYTE ucVInitValue);
extern void UserCommonOsdScalingUpIptSize(EnumOsdPositionType enumOsdPositionType, WORD usHEnd, WORD usVEnd);
extern void UserCommonOsdScalingUpIptBoundaryCodition(EnumOsdFontScalingBoundaryType enumBoundary);
extern void UserCommonOsdSetFBFirstBlock(EnumOsdFBSel enumPath, BYTE ucOn);
extern void UserCommonOsdSetFBFirstStartAddr(EnumOsdFBSel enumPath, WORD usAddr);
extern void UserCommonOsdSetFontRotEndAddress(WORD usAddr);
extern void UserCommonOsdSetDCLKSpeedRange(DWORD ulDclk);
extern WORD UserCommonOsdGetMaxHPos(EnumOsdPositionType enumOsdPositionType);
extern void UserCommonOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY);
extern void UserCommonOsdSetTransparency(BYTE ucTransparency);
extern void UserCommonOsdSetTransparency_T0INT(BYTE ucTransparency);
extern void UserCommonOsdCircuitActivated(bit bEnable);
extern bit UserCommonOsdGetOsdEnable(void);
extern void UserCommonOsdEnableOsd(void);
extern void UserCommonOsdDisableOsd(void);
#if(_GOSD_SUPPORT == _ON)
extern void UserCommonOsdEnableFosd(void);
extern void UserCommonOsdDisableFosd(void);
extern void UserCommonOsdEnableGosd(void);
extern void UserCommonOsdDisableGosd(void);
#endif
extern void UserCommonOsdSetTransparencyType(EnumOsdTransparencyType enumOsdTransparencyType);
extern void UserCommonOsdSetColorPalette(BYTE ucIndex, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB);
extern void UserCommonOsdSpecificColorBlending(bit bEnable, BYTE ucIndex);
extern void UserCommonOsdMapAHighThanMapB(bit bEnable);
extern void UserCommonOsdResetToDefaultValue(void);
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void UserCommonOsdSetFosdFBSeparateEn(BYTE ucEn);
#endif


//--------------------------------------------------
// OSD sub blending
//--------------------------------------------------
#if(_HW_GOSD_SUPPORT == _ON)
extern void UserCommonOsdSubBlendingSetMixerFactor(BYTE ucK1, BYTE ucK2, BYTE ucK3, BYTE ucK4);
extern void UserCommonOsdSubBlendingSetBypassFosdEnable(BYTE ucBypassEn);
extern bit UserCommonOsdSubBlendingGetBypassFosdEnable(void);
extern void UserCommonOsdSubBlendingSetFosdMixerEnable(bit bFosdEn);
extern bit UserCommonOsdSubBlendingGetFosdMixerEnable(void);
extern void UserCommonOsdSubBlendingSetGosdMixerEnable(bit bGosdEn);
extern bit UserCommonOsdSubBlendingGetGosdMixerEnable(void);
#endif
