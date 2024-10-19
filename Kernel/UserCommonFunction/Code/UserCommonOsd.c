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
// ID Code      : UserCommonOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __USER_COMMON_OSD__

#include "UserCommonInclude.h"
#include "Osd/UserCommonOsd.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Uncall Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonOsdUncallFunction(void)
{
    BYTE ucUncall = _FALSE;

    if(ucUncall == _TRUE)
    {
    }
}

//--------------------------------------------------
// Description  : OSD Handler, executed in the main loop
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonOsdHandler(void)
{
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
    if(UserCommonQCGetEnableStatus() == _TRUE)
    {
        // Skip user flow in QC
        SysModeClrModeStateChange();
        return;
    }
#endif

#if(_URGENT_EVENT_CHECK_MODE == _ON)
    if(ScalerSyncCheckUrgentEvent() == _FALSE)
#endif
    {
        UserInterfaceOsdHandler();
        SysModeClrModeStateChange();

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_USB_HUB_COMMUNICATION_SUPPORT == _ON))
        SysUsbHubOsdProc();
#endif

        if((SysModeGetModeState() == _MODE_STATUS_DISPLAY_CHECK) ||
           (SysModeGetModeState() == _MODE_STATUS_DISPLAY_SETTING))
        {
            // Clear display state change event
            SysRegionClearAllDisplayEvent(_DISPLAY_EVENT_STATE_CHANGE_USR);
        }
    }

#if(_HDMI_CEC_SUPPORT == _ON)
    UserInterfaceCecHighLevelFlow();
#endif

#if(_AUDIO_ARC_SUPPORT == _ON)
    UserCommonArcTxHandler();
#endif

#if(_PANEL_STYLE == _PANEL_VBO)
    ScalerDisplayVboTxPanelBacklightReTurnOn();
#endif

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
    UserCommonFwUpdateHandler();
#endif
}


//--------------------------------------------------
// Description  : Set Osd rotation
// Input Value  : ucRotateFlage -> Rotate status (now)
//                enumOsdRotateType    -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270 or _OSD_ROTATE_DEGREE_180
//                enumOsdRotateMapA    -> _OSD_MAP_A_REMAPPING_DISABLE or _OSD_MAP_A_REMAPPING_ENABLE
//                enumOsdRotateMapB    -> _OSD_MAP_B_REMAPPING_DISABLE or _OSD_MAP_B_REMAPPING_ENABLE
//                enumOsdRotateFontLib -> _OSD_FONT_LIB_ROTATION_DISABLE or _OSD_FONT_LIB_ROTATION_ENABLE
//                usRotateWidth
//                usRotateHeight
// Output Value : None
//--------------------------------------------------
void UserCommonOsdMapRotationAndRotionSize(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, EnumOsdRotateMapB enumOsdRotateMapB, EnumOsdRotateFontLib enumOsdRotateFontLib, WORD usRotateWidth, WORD usRotateHeight)
{
    ScalerOsdMapRotationAndRotionSize(enumOsdRotateType, enumOsdRotateMapA, enumOsdRotateMapB, enumOsdRotateFontLib, usRotateWidth, usRotateHeight);
}

#if((_HW_FOSD_MAP_C_D_SUPPORT == _ON) || (_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Set Osd rotation
// Input Value  : ucRotateFlage -> Rotate status (now)
//                enumOsdRotateType    -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270 or _OSD_ROTATE_DEGREE_180
//                enumOsdRotateMapA    -> _OSD_MAP_A_REMAPPING_DISABLE or _OSD_MAP_A_REMAPPING_ENABLE
//                enumOsdRotateMapB    -> _OSD_MAP_B_REMAPPING_DISABLE or _OSD_MAP_B_REMAPPING_ENABLE
//                enumOsdRotateMapC    -> _OSD_MAP_C_REMAPPING_DISABLE or _OSD_MAP_C_REMAPPING_ENABLE
//                enumOsdRotateMapD    -> _OSD_MAP_D_REMAPPING_DISABLE or _OSD_MAP_D_REMAPPING_ENABLE
//                enumOsdRotateFontLib -> _OSD_FONT_LIB_ROTATION_DISABLE or _OSD_FONT_LIB_ROTATION_ENABLE
//                usRotateWidth
//                usRotateHeight
//                usFontRotateStartAddr
// Output Value : None
//--------------------------------------------------
void UserCommonOsdMapRotationAndRotionSizeAndStart(EnumOsdRotateType enumOsdRotateType,
                                                   EnumOsdRotateMapA enumOsdRotateMapA, EnumOsdRotateMapB enumOsdRotateMapB,
                                                   EnumOsdRotateMapC enumOsdRotateMapC, EnumOsdRotateMapD enumOsdRotateMapD,
                                                   EnumOsdRotateFontLib enumOsdRotateFontLib, WORD usRotateWidth, WORD usRotateHeight, WORD usFontRotateStartAddr)
{
    ScalerOsdMapRotationAndRotionSizeAndStart(enumOsdRotateType,
                                              enumOsdRotateMapA, enumOsdRotateMapB,
                                              enumOsdRotateMapC, enumOsdRotateMapD,
                                              enumOsdRotateFontLib, usRotateWidth, usRotateHeight, usFontRotateStartAddr);
}
#endif

//--------------------------------------------------
// Description  : Set Osd rotation size
// Input Value  : usRotateWidth
//                usRotateHeight
// Output Value : None
//--------------------------------------------------
void UserCommonOsdRotationSize(WORD usRotateWidth, WORD usRotateHeight)
{
    ScalerOsdRotationSize(usRotateWidth, usRotateHeight);
}


//--------------------------------------------------
// Description  : OSD Font Data Port
// Input Value  : ucValue
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetDataPortSram(BYTE ucValue)
{
    ScalerOsdSetDataPortSram(ucValue);
}


//--------------------------------------------------
// Description  : OSD Window Port
// Input Value  : ucValue
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetDataPortWindow(BYTE ucValue)
{
    ScalerOsdSetDataPortWindow(ucValue);
}


//--------------------------------------------------
// Description  : Osd Burst Write to Window (P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT)
// Input Value  : Burst Write Pointer, Length, Bank, Table Type, Location
// Output Value : None
//--------------------------------------------------
void UserCommonOsdBurstWriteDataPortWindow(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation)
{
    ScalerOsdBurstWriteDataPortWindow(pucAddress, usWriteLength, ucBankNum, ucTableType, bTableLocation);
}


//--------------------------------------------------
// Description  : Osd Burst Write to Sram (P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT)
// Input Value  : Burst Write Pointer, Length, Bank, Table Type, Location
// Output Value : None
//--------------------------------------------------
void UserCommonOsdBurstWriteDataPortSram(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation)
{
    ScalerOsdBurstWriteDataPortSram(pucAddress, usWriteLength, ucBankNum, ucTableType, bTableLocation);
}


//--------------------------------------------------
// Description  : OSD Addr: 0x90[6:0], 0x91[7:0]
// Input Value  : ucAddrIndicator -> _OSD_WIN_CONTROL or _OSD_SRAM
//                ucByteSel       -> _OSD_BYTE0       or _OSD_BYTE1       or _OSD_BYTE2       or
//                                   _OSD_BYTE0_BYTE1 or _OSD_BYTE0_BYTE2 or _OSD_BYTE1_BYTE2 or _OSD_BYTEALL
//                usAddress       -> SRAM address
//                ucDbufEnable    -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void UserCommonOsdAddrSet(EnumOsdAddrIndicateType enumAddrIndicator, EnumOsdWriteType enumByteSel, WORD usAddress, EnumOsdDBufType enumDbufEnable)
{
    ScalerOsdAddrSet(enumAddrIndicator, enumByteSel, usAddress, enumDbufEnable);
}


//--------------------------------------------------
// Description  : Set OSD Write Byte
// Input Value  : ucIndicateAndWriteByte -> [7:4] : EnumOsdWriteType
//                                          [3:0] : EnumOsdAddrIndicateType
//                usAddr                 -> SRAM address
//                ucData                 -> ucIndicate's Data
// Output Value :
//--------------------------------------------------
void UserCommonOsdWriteByte(BYTE ucWriteByteAndIndicate, EnumOsdDBufType enumDBuf, WORD usAddr, BYTE ucData)
{
    ScalerOsdWriteByte(ucWriteByteAndIndicate, enumDBuf, usAddr, ucData);
}


//--------------------------------------------------
// Description  : Set OSD Write All Byte
// Input Value  : ucIndicateAndDbuf -> CM_90_OSD_ADDR_MSB Hight Byte
//                usAddr            -> SRAM or Window address
//                ucByte0           -> Byte0 Data
//                ucByte1           -> Byte1 Data
//                ucByte2           -> Byte2 Data
// Output Value :
//--------------------------------------------------
void UserCommonOsdWriteAllByte(BYTE ucIndicate, WORD usAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2)
{
    ScalerOsdWriteAllByte(ucIndicate, usAddr, ucByte0, ucByte1, ucByte2);
}


//--------------------------------------------------
// Description  : Set write protection for SRAM when OSD is on
// Input Value  : bEnable          -> _ENABLE or _DISABLE
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
//                ucBitSelect      -> (_BIT7 | _BIT6 | _BIT5 |_BIT4 | _BIT3 |_BIT2 | _BIT1 | _BIT0)
// Output Value :
//--------------------------------------------------
void UserCommonOsdWriteProtection(bit bEnable, EnumOsdWriteType enumOsdWriteType, BYTE ucBitSelect)
{
    ScalerOsdWriteProtection(bEnable, enumOsdWriteType, ucBitSelect);
}


//--------------------------------------------------
// Description  : Get OSD Frame Control Byte (Window)
// Input Value  : usAddr           -> WindowControl address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value : FrameControl Value
//--------------------------------------------------
BYTE UserCommonOsdFrameControlByteGet(WORD usAddr, EnumOsdWriteType enumOsdWriteType)
{
    return ScalerOsdFrameControlByteGet(usAddr, enumOsdWriteType);
}


//--------------------------------------------------
// Description  : Set OSD Frame Control Byte
// Input Value  : usAddr           -> WindowControl address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
//                ucData           -> ucByteSelect's Data
// Output Value :
//--------------------------------------------------
void UserCommonOsdFrameControlByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData)
{
    ScalerOsdFrameControlByte(usAddr, enumOsdWriteType, ucData);
}


//--------------------------------------------------
// Description  : Set window gradient saturated color
// Input Value  : enumOsdWindowsType ->
//                bversedGradient    -> _ENABLE or _DISABLE
//                ucColorR           -> window RED saturated color (0 ~ 255)
//                ucColorG           -> window GRN saturated color (0 ~ 255)
//                ucColorB           -> window BLU saturated color (0 ~ 255)
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindowSaturatedColorSelectIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB)
{
    ScalerOsdWindowSaturatedColorSelectIndex(enumOsdWinGradientIdx, ucColorR, ucColorG, ucColorB);
}


//--------------------------------------------------
// Description  : Set window extension gradient level for R/G/B channel
// Input Value  : enumOsdWinGradientIdx
//                ucLevelR           -> window RED extension gradient level (0 ~ 255)
//                ucLevelG           -> window GRN extension gradient level (0 ~ 255)
//                ucLevelB           -> window BLU extension gradient level (0 ~ 255)
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindowGradientLevelIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucLevelR, BYTE ucLevelG, BYTE ucLevelB)
{
    ScalerOsdWindowGradientLevelIndex(enumOsdWinGradientIdx, ucLevelR, ucLevelG, ucLevelB);
}


//--------------------------------------------------
// Description  : Set window gradient step extension
// Input Value  : enumOsdWinGradientIdx
//                ucStep
//                ucDecimal
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindowGradientStepIndex(EnumOsdWinGradientType enumOsdWinGradientIdx, BYTE ucStep, BYTE ucDecimal)
{
    ScalerOsdWindowGradientStepIndex(enumOsdWinGradientIdx, ucStep, ucDecimal);
}


//--------------------------------------------------
// Description  : Draw window Gradient Size
// Input Value  : usXStart -> Horizontal start address
//                usYStart -> Vertical start address
//                usXEnd   -> Horizontal end address
//                usYEnd   -> Vertical end address
// Output Value :
//--------------------------------------------------
void UserCommonOsdDrawWindowGradientSize(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    ScalerOsdDrawWindowGradientSize(usXStart, usYStart, usXEnd, usYEnd);
}


//--------------------------------------------------
// Description  : Disable Gradient Window
// Input Value  : emunWindowGradientIndex
// Output Value :
//--------------------------------------------------
void UserCommonOsdDrawWindowGradientDisableIndex(EnumOsdWinGradientType enumWindowGradientIndex)
{
    ScalerOsdDrawWindowGradientDisableIndex(enumWindowGradientIndex);
}


//--------------------------------------------------
// Description  : Draw window
// Input Value  : usXStart -> Horizontal start address
//                usYStart -> Vertical start address
//                usXEnd   -> Horizontal end address
//                usYEnd   -> Vertical end address
// Output Value :
//--------------------------------------------------
void UserCommonOsdDrawWindowGradient(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    ScalerOsdDrawWindowGradient(usXStart, usYStart, usXEnd, usYEnd);
}


//--------------------------------------------------
// Description  : Set window Priority
// Input Value  : EnumOsdFontPriorityType        ->    _OSD_FONT_ABOVE_WIN_31, _OSD_FONT_ABOVE_WIN_30,  _OSD_FONT_ABOVE_WIN_29,
//                                                     _OSD_FONT_ABOVE_WIN_28, _OSD_FONT_ABOVE_WIN_27, _OSD_FONT_ABOVE_WIN_26,
//                                                     _OSD_FONT_ABOVE_WIN_25,  _OSD_FONT_ABOVE_WIN_24,
// Output Value :
//--------------------------------------------------
void UserCommonOsdFontPriority(EnumOsdFontPriorityType enumOsdFontPriorityType)
{
    ScalerOsdFontPriority(enumOsdFontPriorityType);
}


//--------------------------------------------------
// Description  : Set window 29 Special function
// Input Value  : EnumOsdWindow29FunctionType   -> _OSD_WINDOW_29_FUNCTION_DISABLE                        or _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BOTH                  or
//                                                 _OSD_WINDOW_29_FUNCTION_NO_BLENDING_FOREGROUND         or _OSD_WINDOW_29_FUNCTION_NO_BLENDING_BACKGROUND            or
//                                                 _OSD_WINDOW_29_FUNCTION_BLENDING_BOTH                  or _OSD_WINDOW_29_FUNCTION_MASK_REGION_APPEAR                or
//                                                 _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_ALL    or _OSD_WINDOW_29_FUNCTION_MASK_REGION_TRANSPARENT_FONT
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindow29SpecialFunction(EnumOsdWindow29FunctionType enumOsdWindow29FunctionType)
{
    ScalerOsdWindow29SpecialFunction(enumOsdWindow29FunctionType);
}


//--------------------------------------------------
// Description  : Set window 28 Special function
// Input Value  : enumOsdWindow28FunctionType   -> _OSD_WINDOW_28_FUNCTION_DISABLE                    or _OSD_WINDOW_28_FUNCTION_NO_BLENDING_BOTH                  or
//                                                 _OSD_WINDOW_28_FUNCTION_NO_BLENDING_FOREGROUND     or _OSD_WINDOW_28_FUNCTION_NO_BLENDING_BACKGROUND            or
//                                                 _OSD_WINDOW_28_FUNCTION_BLENDING_BOTH
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindow28SpecialFunction(EnumOsdWindow28FunctionType enumOsdWindow28FunctionType)
{
    ScalerOsdWindow28SpecialFunction(enumOsdWindow28FunctionType);
}


//--------------------------------------------------
// Description  : Set window special color mask : _OSD_SPECIAL_COLOR_MASK_AND_OPERATION
// Input Value  : bEnable            -> _ENABLE or _DISABLE
//                enumOsdWindowsType
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindowSpecialColorMaskANDOperation(bit bEnable, EnumOsdWindowsType enumOsdWindowsType)
{
    ScalerOsdWindowSpecialColorMaskANDOperation(bEnable, enumOsdWindowsType);
}


//--------------------------------------------------
// Description  : Disable window
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0,   _OSD_WINDOW_1,   _OSD_WINDOW_2,   _OSD_WINDOW_3,   _OSD_WINDOW_4,   _OSD_WINDOW_5,
//                                      _OSD_WINDOW_6,   _OSD_WINDOW_7,   _OSD_WINDOW_8,   _OSD_WINDOW_9,   _OSD_WINDOW_4_1, _OSD_WINDOW_4_2,
//                                      _OSD_WINDOW_4_3, _OSD_WINDOW_4_4, _OSD_WINDOW_4_5, _OSD_WINDOW_4_6, _OSD_WINDOW_4_7, _OSD_WINDOW_4_8
//                                      _OSD_WINDOW_5_1, _OSD_WINDOW_5_2, _OSD_WINDOW_5_3, _OSD_WINDOW_5_4, _OSD_WINDOW_5_5, _OSD_WINDOW_5_6,
//                                      _OSD_WINDOW_5_7, _OSD_WINDOW_5_8
//                                      _OSD_WINDOW_ALL,
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindowDisable(EnumOsdWindowsType enumOsdWindowsType)
{
    ScalerOsdWindowDisable(enumOsdWindowsType);
}


//--------------------------------------------------
// Description  : window number mapping to register address
// Input Value  : enumOsdWindowsTyp
// Output Value :
//--------------------------------------------------
WORD UserCommonOsdWindowRegisterMapping(EnumOsdWindowsType enumOsdWindowsType)
{
    return ScalerOsdWindowRegisterMapping(enumOsdWindowsType);
}


//--------------------------------------------------
// Description  : Draw window
// Input Value  : usXStart -> Horizontal start address
//                usYStart -> Vertical start address
//                usXEnd   -> Horizontal end address
//                usYEnd   -> Vertical end address
// Output Value :
//--------------------------------------------------
void UserCommonOsdDrawWindow(WORD usXStart, WORD usYStart, WORD usXEnd, WORD usYEnd)
{
    ScalerOsdDrawWindow(usXStart, usYStart, usXEnd, usYEnd);
}


//--------------------------------------------------
// Description  : Set window 6 Special function
// Input Value  : bEnable            -> _ENABLE or _DISABLE
//                enumOsdWindowsType -> _OSD_WINDOW_8   or _OSD_WINDOW_9   or _OSD_WINDOW_4_1 or _OSD_WINDOW_4_2 or _OSD_WINDOW_4_3 or
//                                      _OSD_WINDOW_4_4 or _OSD_WINDOW_4_5 or _OSD_WINDOW_4_6 or _OSD_WINDOW_4_7 or _OSD_WINDOW_4_8
//                ChessBoardColor1   -> Color (0 ~ 63)
//                ChessBoardColor2   -> Color (0 ~ 63)
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindowChessboard(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucChessBoardColor1, BYTE ucChessBoardColor2)
{
    ScalerOsdWindowChessboard(bEnable, enumOsdWindowsType, ucChessBoardColor1, ucChessBoardColor2);
}


//--------------------------------------------------
// Description  : Set window highlight function
// Input Value  : bEnable              -> _ENABLE or _DISABLE
//                enumOsdWindowsType   -> _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8
//                ucForegroundColor    -> 0 ~ 63
//                BackgroundColor      -> 0 ~ 63
//                CharactorBorderColor -> 0 ~ 63
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindowHighlightFunction(bit bEnable, EnumOsdWindowsType enumOsdWindowsType, BYTE ucForegroundColor, BYTE ucBackgroundColor, BYTE ucCharactorBorderColor)
{
    ScalerOsdWindowHighlightFunction(bEnable, enumOsdWindowsType, ucForegroundColor, ucBackgroundColor, ucCharactorBorderColor);
}


//--------------------------------------------------
// Description  : Draw grid line
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdDrawGridLine(WORD usPitchHorizontal, WORD usPitchVertical)
{
    ScalerOsdDrawGridLine(usPitchHorizontal, usPitchVertical);
}


//--------------------------------------------------
// Description  : Set Window Rounded On/Off
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0 or _OSD_WINDOW_5 or _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8 or _OSD_WINDOW_5_1 ~ _OSD_WINDOW_5_8
//                bOnOff             -> _ENABLE or _DISABLE
//                bUpperLeftEnable  - > _ENABLE or _DISABLE
//                bLowerLeftEnable   -> _ENABLE or _DISABLE
//                bUpperRightEnable  -> _ENABLE or _DISABLE
//                bLowerRightEnable  -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void UserCommonOsdRoundedWindowOnOff(EnumOsdWindowsType enumOsdWindowsType, bit bOnOff, bit bUpperLeftEnable, bit bLowerLeftEnable, bit bUpperRightEnable, bit bLowerRightEnable)
{
    ScalerOsdRoundedWindowOnOff(enumOsdWindowsType, bOnOff, bUpperLeftEnable, bLowerLeftEnable, bUpperRightEnable, bLowerRightEnable);
}


//--------------------------------------------------
// Description  : Set Window Rounded Pattern 8x8
// Input Value  : ucIdx -> Pattern Index 0~7
// Input Value  : ucType -> Pattern Type
// Output Value :
//--------------------------------------------------
void UserCommonOsdRoundedWindowPattern8x8(BYTE ucIdx, BYTE ucType)
{
    ScalerOsdRoundedWindowPattern8x8(ucIdx, ucType);
}


//--------------------------------------------------
// Description  : Set Window Rounded Pattern 16x16
// Input Value  : ucIdx -> Pattern Index 0~15
// Input Value  : ucType -> Pattern Type
// Output Value :
//--------------------------------------------------
void UserCommonOsdRoundedWindowPattern16x16(BYTE ucIdx, BYTE ucType)
{
    ScalerOsdRoundedWindowPattern16x16(ucIdx, ucType);
}


//--------------------------------------------------
// Description  : Set Window Rounded Window Size
// Input Value  : enumOsdWindowsType -> _OSD_WINDOW_0 or _OSD_WINDOW_5 or _OSD_WINDOW_4_1 ~ _OSD_WINDOW_4_8 or _OSD_WINDOW_5_1 ~ _OSD_WINDOW_5_8
//                enumRoundedWinSize -> _OSD_ROUNDED_WIN_SIZE_8x8 or _OSD_ROUNDED_WIN_SIZE_16x16 or _OSD_ROUNDED_WIN_SIZE_32x32
// Output Value :
//--------------------------------------------------
void UserCommonOsdRoundedWindowSize(EnumOsdWindowsType enumOsdWindowsType, EnumOsdRoundedWindowType enumRoundedWinSize)
{
    ScalerOsdRoundedWindowSize(enumOsdWindowsType, enumRoundedWinSize);
}


//--------------------------------------------------
// Description  : Enable/Disable window
// Input Value  : enumOsdWindowsType
// Input Value  : bWinOnOff
// Output Value :
//--------------------------------------------------
void UserCommonOsdWindowOnOFF(EnumOsdWindowsType enumOsdWindowsType, bit bWinOnOff)
{
    ScalerOsdWindowOnOFF(enumOsdWindowsType, bWinOnOff);
}

#if(_HW_OSD_ROUND_WIN_0_PIXEL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Window Rounded Pattern 16x16 0_Pixel Enable/Disable
// Input Value  : ucIdx -> Pattern Index 0~15
// Input Value  : bEnable -> _ENABLE, _DISABLE
// Output Value :
//--------------------------------------------------
void UserCommonOsdRoundedWindowPattern16x16_0Pixel(BYTE ucIdx, bit bEnable)
{
    ScalerOsdRoundedWindowPattern16x16_0Pixel(ucIdx, bEnable);
}


//--------------------------------------------------
// Description  : Set Window Rounded Pattern 8x8 0_Pixel Enable/Disable
// Input Value  : ucIdx -> Pattern Index 0~7
// Input Value  : bEnable -> _ENABLE, _DISABLE
// Output Value :
//--------------------------------------------------
void UserCommonOsdRoundedWindowPattern8x8_0Pixel(BYTE ucIdx, bit bEnable)
{
    ScalerOsdRoundedWindowPattern8x8_0Pixel(ucIdx, bEnable);
}
#endif


//--------------------------------------------------
// Description  : Osd Load Hardware VLC : Font data
// Input Value  : *pArray          -> VLC table
//                usVLCTableSize   -> Use VLC_TABLE_SIZE(VLC table)
//                ucBankNum        -> Bank number (GET_CURRENT_BANK_NUMBER())
//                usOffset         -> Font address
//                usFontTableStart -> Font base address
//                ucOsdRotateType  -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270 or _OSD_ROTATE_DEGREE_180
//                bTableLocation   ->
// Output Value :
//--------------------------------------------------
void UserCommonOsdHardwareCompressionFont(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, EnumOsdRotateType enumOsdRotateType, bit bTableLocation)
{
    ScalerOsdHardwareCompressionFont(pucArray, usVLCTableSize, ucBankNum, usOffset, enumOsdRotateType, bTableLocation);
}


//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetDoubleBufferReady(void)
{
    ScalerOsdSetDoubleBufferReady();
}


//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value :
//--------------------------------------------------
void UserCommonOsdWaitDoubleBufferReady(void)
{
    ScalerOsdWaitDoubleBufferReady();
}


//--------------------------------------------------
// Description  : Set Osd Font Rotation
// Input Value  : enumRotType
// Input Value  : ucFontDownloadRotEn
// Output Value :
//--------------------------------------------------
void UserCommonOsdFontRotateCtrlAuto(EnumOsdRotateType enumRotType, BYTE ucFontDownloadRotEn)
{
    ScalerOsdFontRotateCtrlAuto(enumRotType, ucFontDownloadRotEn);
}


//--------------------------------------------------
// Description  : Osd Load Hardware VLC : Font
// Input Value  : *pArray          -> VLC table
//                usVLCTableSize   -> Use VLC_TABLE_SIZE(VLC table)
//                ucBankNum        -> Bank number (GET_CURRENT_BANK_NUMBER())
//                usOffset         -> Font address
//                usFontTableStart -> Font base address
//                ucOsdRotateType  -> _OSD_ROTATE_DEGREE_0 or _OSD_ROTATE_DEGREE_90 or _OSD_ROTATE_DEGREE_270 or _OSD_ROTATE_DEGREE_180
//                enumSramType --> _OSD_SRAM_FONT or _OSD_SRAM_COMMAND
// Output Value :
//--------------------------------------------------
void UserCommonOsdHardwareVLCFont(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, EnumOsdRotateType enumOsdRotateType, bit bTableLocation)
{
    ScalerOsdHardwareVLCFont(pucArray, usVLCTableSize, ucBankNum, usOffset, enumOsdRotateType, bTableLocation);
}


//--------------------------------------------------
// Description  : Osd Load Hardware VLC : Command
// Input Value  : *pArray          -> VLC table
//                usVLCTableSize   -> Use VLC_TABLE_SIZE(VLC table)
//                ucBankNum        -> Bank number (GET_CURRENT_BANK_NUMBER())
//                usOffset         -> Font address
//                usFontTableStart -> Font base address
//                enumSramType --> _OSD_SRAM_FONT or _OSD_SRAM_COMMAND
// Output Value :
//--------------------------------------------------
void UserCommonOsdHardwareVLCCommand(BYTE *pucArray, WORD usVLCTableSize, BYTE ucBankNum, WORD usOffset, bit bTableLocation)
{
    ScalerOsdHardwareVLCCommand(pucArray, usVLCTableSize, ucBankNum, usOffset, bTableLocation);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte : Row/Character Command
// Input Value  : usSramAddress -> SRAM address
//                enumOsdWriteType    -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2 or _OSD_BYTEALL
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramAddressSetCommand(WORD usSramAddress, EnumOsdWriteType enumOsdWriteType)
{
    ScalerOsdSramAddressSetCommand(usSramAddress, enumOsdWriteType);
}


//--------------------------------------------------
// Description  : Get SRAM address value : Font
// Input Value  : usFontIdx
//                ucFontLen
// Output Value : pucData -> Data
//--------------------------------------------------
void UserCommonOsdSramGetDataFont(WORD usFontIdx, BYTE ucFontLen, BYTE *pucData)
{
    ScalerOsdSramGetDataFont(usFontIdx, ucFontLen, pucData);
}


//--------------------------------------------------
// Description  : Get SRAM address value : Command
// Input Value  : enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
//                enumSramType -> Row, Char command Or Font Data
//                usSramAddress -> address
//                usLength -> Length
// Output Value : pucData -> Data
//--------------------------------------------------
void UserCommonOsdSramGetDataCommand(EnumOsdWriteType enumOsdWriteType, WORD usSramAddress, WORD usLength, BYTE *pucData)
{
    ScalerOsdSramGetDataCommand(enumOsdWriteType, usSramAddress, usLength, pucData);
}


//--------------------------------------------------
// Description  : Row command & Charactor command & Font base address
// Input Value  : enumOsdMapType          -> _OSD_A or _OSD_B
//                ucRowCommandStart       -> Row command start address
//                ucCharactorCommandStart -> Charactor command start address
//                ulFontStart             -> Font start address
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramBaseAddressSet(EnumOsdMapType enumOsdMapType, WORD usRowCommandStart, WORD usCharactorCommandStart, DWORD ulFontStart)
{
    ScalerOsdSramBaseAddressSet(enumOsdMapType, usRowCommandStart, usCharactorCommandStart, ulFontStart);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol.     -> Just that !!
//                enumOsdWriteType  -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramAddressCount(WORD usRow, WORD usCol, EnumOsdWriteType enumOsdWriteType)
{
    ScalerOsdSramAddressCount(usRow, usCol, enumOsdWriteType);
}


//--------------------------------------------------
// Description  : Set OSD Command Byte
// Input Value  : usAddr           -> SRAM address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2 or _OSD_BYTEALL
//                ucData           -> ucByteSelect's data
// Output Value :
//--------------------------------------------------
void UserCommonOsdCommandByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData)
{
    ScalerOsdCommandByte(usAddr, enumOsdWriteType, ucData);
}


//--------------------------------------------------
// Description  : Set OSD Command All Byte
// Input Value  : usCharAddr   -> SRAM address
//                ucByte0      -> Byte0 data
//                ucByte1      -> Byte1 data
//                ucByte2      -> Byte2 data
// Output Value :
//--------------------------------------------------
void UserCommonOsdCommandAllByte(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2)
{
    ScalerOsdCommandAllByte(usCharAddr, ucByte0, ucByte1, ucByte2);
}


//--------------------------------------------------
// Description  : Set OSD Char Command Byte Series
// Input Value  : usCharAddr       -> SRAM address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2 or _OSD_BYTEALL
//                ucData           -> ucByteSelect' data
//                usLength         -> Length
// Output Value :
//--------------------------------------------------
void UserCommonOsdCharCommandByteSeries(WORD usCharAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData, WORD usLength)
{
    ScalerOsdCharCommandByteSeries(usCharAddr, enumOsdWriteType, ucData, usLength);
}


//--------------------------------------------------
// Description  : Set OSD Char Command All Byte Series
// Input Value  : usCharAddr -> SRAM address
//                ucByte0      -> Byte0 data
//                ucByte1      -> Byte1 data
//                ucByte2      -> Byte2 data
//                usLength     -> Length
// Output Value :
//--------------------------------------------------
void UserCommonOsdCharCommandAllByteSeries(WORD usCharAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2, WORD usLength)
{
    ScalerOsdCharCommandAllByteSeries(usCharAddr, ucByte0, ucByte1, ucByte2, usLength);
}


//--------------------------------------------------
// Description  : Set OSD 2 bit font offset
// Input Value  : ucOffset -> 0 ~ 511
// Output Value :
//--------------------------------------------------
void UserCommonOsd2BitFontOffset(WORD usOffset)
{
    ScalerOsd2BitFontOffset(usOffset);
}


//--------------------------------------------------
// Description  : Set OSD 4 bit font offset
// Input Value  : ucOffset -> 0 ~ 511
// Output Value :
//--------------------------------------------------
void UserCommonOsd4BitFontOffset(WORD usOffset)
{
    ScalerOsd4BitFontOffset(usOffset);
}


#if(_HW_OSD_8_BIT_FONT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set OSD 8 bit font offset
// Input Value  : ucOffset
// Output Value :
//--------------------------------------------------
void UserCommonOsd8BitFontOffset(WORD usOffset)
{
    ScalerOsd8BitFontOffset(usOffset);
}
#endif


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol.    -> Just that !!
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramDataValue(WORD usRow, WORD usCol, WORD usLength, BYTE ucValue, EnumOsdWriteType enumOsdWriteType)
{
    ScalerOsdSramDataValue(usRow, usCol, usLength, ucValue, enumOsdWriteType);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol.    -> Just that !!
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramDataValue2Byte(WORD usRow, WORD usCol, WORD usLength, BYTE ucValue1, BYTE ucValue2, EnumOsdWriteType enumOsdWriteType)
{
    ScalerOsdSramDataValue2Byte(usRow, usCol, usLength, ucValue1, ucValue2, enumOsdWriteType);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight. -> Just that !!
//                ucPixelLength                     -> BLANK_FONT : 4 ~ 255 other 0 ~ 255
//                ucBackgroundColor                 -> Color number
//                enumOsdBlinkingType               -> _OSD_BLANK_FONT or _OSD_BLANK_ALIGN
// Output Value :
//--------------------------------------------------
void UserCommonOsdBlankFont(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, WORD usPixelLength, BYTE ucBackgroundColor, EnumOsdBlankType enumOsdBlankingType)
{
    ScalerOsdBlankFont(usRow, usCol, usLength, usHeight, usPixelLength, ucBackgroundColor, enumOsdBlankingType);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight.     -> Just that !!
//                ucForegroundColor. ucBackgroundColor  -> Color number
// Output Value :
//--------------------------------------------------
void UserCommonOsdChange1BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucForegroundColor, BYTE ucBackgroundColor)
{
    ScalerOsdChange1BitColor(usRow, usCol, usLength, usHeight, ucForegroundColor, ucBackgroundColor);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight.       -> Just that !!
//                ucColor0. ucColor1. ucColor2. ucColor3  -> Color number
// Output Value :
//--------------------------------------------------
void UserCommonOsdChange2BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)
{
    ScalerOsdChange2BitColor(usRow, usCol, usLength, usHeight, ucColor0, ucColor1, ucColor2, ucColor3);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight.  -> Just that !!
//                ucBackgroundColor                  -> Color number
//                ucColorPaletteType                 -> _OSD_4BIT_PALETTE_00_01_02_03 | _OSD_4BIT_PALETTE_04_05_06_07 | _OSD_4BIT_PALETTE_08_09_10_11 | _OSD_4BIT_PALETTE_12_13_14_15
//                                                     (_OSD_4BIT_PALETTE_16_17_18_19   _OSD_4BIT_PALETTE_20_21_22_23   _OSD_4BIT_PALETTE_24_25_26_27   _OSD_4BIT_PALETTE_28_29_30_31)
//                                                     (_OSD_4BIT_PALETTE_32_33_34_35   _OSD_4BIT_PALETTE_36_37_38_39   _OSD_4BIT_PALETTE_40_41_42_43   _OSD_4BIT_PALETTE_44_45_46_47)
//                                                     (_OSD_4BIT_PALETTE_48_49_50_51   _OSD_4BIT_PALETTE_52_53_54_55   _OSD_4BIT_PALETTE_56_57_58_59   _OSD_4BIT_PALETTE_50_61_62_63)
// Output Value :
//--------------------------------------------------
void UserCommonOsdChange4BitColor(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucBackgroundColor, BYTE ucColorPaletteType)
{
    ScalerOsdChange4BitColor(usRow, usCol, usLength, usHeight, ucBackgroundColor, ucColorPaletteType);
}


//--------------------------------------------------
// Description  :
// Input Value  : usRow -> ROW_MAPA(x), ROW_MAPB(x)
//                ucHeight -> 1 ~ 64
//                usLength -> number of row to be changed
// Output Value :
//--------------------------------------------------
void UserCommonOsdRowHeight(WORD usRow, BYTE ucHeight, WORD usLength)
{
    ScalerOsdRowHeight(usRow, ucHeight, usLength);
}


//--------------------------------------------------
// Description  : None
// Input Value  : None
// Output Value :
//--------------------------------------------------
void UserCommonOsdFontLibraryRotation(void)
{
    ScalerOsdFontLibraryRotation();
}


//--------------------------------------------------
// Description  : MASK Specific Region of Font A/B
// Input Value  : usRowStart
// Input Value  : usRowEnd
// Input Value  : usColumnStart
// Input Value  : usColumnEnd
// Output Value :
//--------------------------------------------------
void UserCommonOsdFontMaskRegionSet(EnumOsdMapType enumOsdMapType, WORD usRowStart, WORD usRowEnd, WORD usColumnStart, WORD usColumnEnd)
{
    ScalerOsdFontMaskRegionSet(enumOsdMapType, usRowStart, usRowEnd, usColumnStart, usColumnEnd);
}


//--------------------------------------------------
// Description  : MASK Specific Region of Font A/B Enable/Disable
// Input Value  : bOnOff
// Output Value :
//--------------------------------------------------
void UserCommonOsdFontMaskRegionOnOff(EnumOsdMapType enumOsdMapType, bit bOnOff)
{
    ScalerOsdFontMaskRegionOnOff(enumOsdMapType, bOnOff);
}


//--------------------------------------------------
// Description  : SRAM address value and which byte
// Input Value  : usRow. usCol. usLength. usHeight.       -> Just that !!
//                ucColor0. ucColor1. ucColor2. ucColor3  -> Color number
// Output Value :
//--------------------------------------------------
void UserCommonOsdChange2BitColor16_31(WORD usRow, WORD usCol, WORD usLength, WORD usHeight, BYTE ucColor0, BYTE ucColor1, BYTE ucColor2, BYTE ucColor3)
{
    ScalerOsdChange2BitColor16_31(usRow, usCol, usLength, usHeight, ucColor0, ucColor1, ucColor2, ucColor3);
}


//--------------------------------------------------
// Description  : Set decode compression data or not, Compression enable/disable
// Input Value  : enumDecodeCompression -> _OSD_DECODE_COMPRESSED or _OSD_DECODE_NON_COMPRESSED
// Input Value  : ucConpressionEn -> _OSD_COMPRESSION_DISABLE or _OSD_COMPRESSION_ENABLE
// Output Value :
//--------------------------------------------------
void UserCommonOsdCompressionCtrl(EnumOsdDecodeCompressionType enumDecodeCompression, bit bCompressionEnable)
{
    ScalerOsdCompressionCtrl(enumDecodeCompression, bCompressionEnable);
}


//--------------------------------------------------
// Description  : Set Map Enable
// Input Value  : enumMapSel -> _OSD_A or _OSD_B
// Input Value  : bEnable -> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonOsdMapABFunctionEnable(EnumOsdMapType enumMapSel, bit bEnable)
{
    ScalerOsdMapABFunctionEnable(enumMapSel, bEnable);
}


#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Map Enable
// Input Value  : enumMapSel -> _OSD_A or _OSD_B or _OSD_C or _OSD_D
// Input Value  : bEnable -> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonOsdMapFunctionEnable(EnumOsdMapType enumMapSel, bit bEnable)
{
    // Map priority : map D > C > A or B
    ScalerOsdMapFunctionEnable(enumMapSel, bEnable);
}
#endif


//--------------------------------------------------
// Description  : Osd double buufer mode
// Input Value  : enumDB
// Output Value :
//--------------------------------------------------
void UserCommonOsdGlobalDoubleBufferSel(EnumOsdDoubleBufferType enumDB)
{
    ScalerOsdGlobalDoubleBufferSel(enumDB);
}


//--------------------------------------------------
// Description  : Get OSD H Double Enable Or Disable
// Input Value  :
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserCommonOsdGetDoubleFunctionH(EnumOsdPositionType enumDelaySel)
{
    return ScalerOsdGetDoubleFunctionH(enumDelaySel);
}


//--------------------------------------------------
// Description  : Get OSD V Double Enable Or Disable
// Input Value  :
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserCommonOsdGetDoubleFunctionV(EnumOsdPositionType enumDelaySel)
{
    return ScalerOsdGetDoubleFunctionV(enumDelaySel);
}


//--------------------------------------------------
// Description  : OSD Scale Up - Double
// Input Value  : enumDelaySel
// Input Value  : ucHoriEnable
// Input Value  : ucVerEnable
// Output Value :
//--------------------------------------------------
void UserCommonOsdScalingUpDoubleEn(EnumOsdPositionType enumDelaySel, BYTE ucHoriEnable, BYTE ucVerEnable)
{
    ScalerOsdScalingUpDoubleEn(enumDelaySel, ucHoriEnable, ucVerEnable);
}


//--------------------------------------------------
// Description  : OSD Scale Up - Interpolation
// Input Value  : enumDelaySel
// Input Value  : ucEn
// Output Value :
//--------------------------------------------------
void UserCommonOsdScalingUpIptEn(EnumOsdPositionType enumDelaySel, BYTE ucEn)
{
    ScalerOsdScalingUpIptEn(enumDelaySel, ucEn);
}


//--------------------------------------------------
// Description  : OSD Scale Up Factor
// Input Value  : ucHFactor = H input/ H output * 2^6. ucVFactor = V input/ V output * 2^6
// Output Value :
// Note         :
//--------------------------------------------------
void UserCommonOsdScalingUpIptFactor(BYTE ucHFactor, BYTE ucVFactor)
{
    ScalerOsdScalingUpIptFactor(ucHFactor, ucVFactor);
}


//--------------------------------------------------
// Description  : OSD Scale Up Initial Vale
// Input Value  : ucHInitValue
// Input Value  : ucVInitValue
// Output Value :
//--------------------------------------------------
void UserCommonOsdScalingUpIptInitialValue(BYTE ucHInitValue, BYTE ucVInitValue)
{
    ScalerOsdScalingUpIptInitialValue(ucHInitValue, ucVInitValue);
}


//--------------------------------------------------
// Description  : OSD Scale Up End Position
// Input Value  : enumOsdPositionType
// Input Value  : usHEnd
// Input Value  : usHEnd
// Output Value :
//--------------------------------------------------
void UserCommonOsdScalingUpIptSize(EnumOsdPositionType enumOsdPositionType, WORD usHEnd, WORD usVEnd)
{
    ScalerOsdScalingUpIptSize(enumOsdPositionType, usHEnd, usVEnd);
}


//--------------------------------------------------
// Description  : OSD Scale Up Boundary Condition
// Input Value  : enumRatio
// Output Value :
//--------------------------------------------------
void UserCommonOsdScalingUpIptBoundaryCodition(EnumOsdFontScalingBoundaryType enumBoundary)
{
    ScalerOsdScalingUpIptBoundaryCodition(enumBoundary);
}


//--------------------------------------------------
// Description  : Set OSD Fisrt Block in Font Back Mode
// Input Value  : ucOn
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetFBFirstBlock(EnumOsdFBSel enumPath, BYTE ucOn)
{
    ScalerOsdSetFBFirstBlock(enumPath, ucOn);
}


//--------------------------------------------------
// Description  : Set OSD Start Address in Font Back mode
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetFBFirstStartAddr(EnumOsdFBSel enumPath, WORD usAddr)
{
    ScalerOsdSetFBFirstStartAddr(enumPath, usAddr);
}


//--------------------------------------------------
// Description  : Set OSD Font Library Rotation End Address
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetFontRotEndAddress(WORD usAddr)
{
    ScalerOsdSetFontRotEndAddress(usAddr);
}


#if(_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set OSD Font Library Rotation Start Address
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetFontRotStartAddress(WORD usAddr)
{
    ScalerOsdSetFontRotStartAddress(usAddr);
}
#endif


//--------------------------------------------------
// Description  : Set Dclk Range
// Input Value  : uldclk
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetDCLKSpeedRange(DWORD ulDclk)
{
    ScalerOsdSetDCLKSpeedRange(ulDclk);
}


//--------------------------------------------------
// Description  : Get osd max H position
// Input Value  : enumOsdPositionType
// Output Value :
//--------------------------------------------------
WORD UserCommonOsdGetMaxHPos(EnumOsdPositionType enumOsdPositionType)
{
    return ScalerOsdGetMaxHPos(enumOsdPositionType);
}


//--------------------------------------------------
// Description  : Set osd position
// Input Value  : enumOsdPositionType -> _OSD_POSITION_GLOBAL_1 or _OSD_POSITION_GLOBAL_2 or _OSD_POSITION_FONT_A or _OSD_POSITION_FONT_B
//                usX                 -> Horizontal delay value
//                usY                 -> Vertical  delay value
// Output Value :
//--------------------------------------------------
void UserCommonOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY)
{
    ScalerOsdPosition(enumOsdPositionType, usX, usY);
}


//--------------------------------------------------
// Description  : Set OSD Transparency
// Input Value  : ucTransparency -> 0 ~ 255
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetTransparency(BYTE ucTransparency)
{
#if(_GOSD_SUPPORT == _ON)
    ScalerOsdSubBlendingSetGlobalAlpha(_ENABLE, ucTransparency);
#else
    ScalerOsdSetTransparency(ucTransparency);
#endif
}


//--------------------------------------------------
// Description  : Set OSD Transparency for Timer Interrupt
// Input Value  : ucTransparency -> 0 ~ 255
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetTransparency_T0INT(BYTE ucTransparency)
{
#if(_GOSD_SUPPORT == _ON)
    ScalerOsdSubBlendingSetGlobalAlpha_T0INT(_ENABLE, ucTransparency);
#else
    ScalerOsdSetTransparency_T0INT(ucTransparency);
#endif
}


//--------------------------------------------------
// Description  : Activate OSD circuit enable disable
// Input Value  : bEnable      -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void UserCommonOsdCircuitActivated(bit bEnable)
{
    ScalerOsdCircuitActivated(bEnable);
}


//--------------------------------------------------
// Description  : Get OSD Enable Or Disable
// Input Value  :
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit UserCommonOsdGetOsdEnable(void)
{
    return ScalerOsdGetOsdEnable();
}


//--------------------------------------------------
// Description  : Enable Display OSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdEnableOsd(void)
{
#if(_GOSD_SUPPORT == _ON)
    ScalerGosdDispOsdSetTimingGenEn(_ENABLE);
#endif

    ScalerOsdEnableOsd();
}

#if(_GOSD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Enable FontOSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdEnableFosd(void)
{
    ScalerOsdSubBlendingSetFosdMixerEnable(_ENABLE);
}

//--------------------------------------------------
// Description  : Enable GraphicOSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdEnableGosd(void)
{
    ScalerGosdDispOsdSetTimingGenEn(_ENABLE);
    ScalerOsdSubBlendingSetGosdMixerEnable(_ENABLE);
}
#endif

//--------------------------------------------------
// Description  : Disable Display OSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdDisableOsd(void)
{
    ScalerOsdDisableOsd();
#if(_GOSD_SUPPORT == _ON)
    UserCommonOsdDisableGosd();
#endif
}

#if(_GOSD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Disable FOSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdDisableFosd(void)
{
    ScalerOsdSubBlendingSetFosdMixerEnable(_DISABLE);
}

//--------------------------------------------------
// Description  : Disable GOSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdDisableGosd(void)
{
    ScalerGosdContinuousDisable(_GOSD_PLANE_ALL);
    ScalerGosdDispOsdSetGdmaOsdDisable(_GOSD_PLANE_ALL, _DB_APPLY_NO_POLLING);
    g_pulGosdDispOsdDisplayingSurfaceId[_GOSD_PLANE_OSD1] = _GOSD_SURFACE_NUMBER;
    g_pulGosdDispOsdDisplayingSurfaceId[_GOSD_PLANE_OSD2] = _GOSD_SURFACE_NUMBER;
    g_pulGosdDispOsdDisplayingSurfaceId[_GOSD_PLANE_OSD3] = _GOSD_SURFACE_NUMBER;
    ScalerGosdDispOsdSetTimingGenEn(_DISABLE);
}
#endif

//--------------------------------------------------
// Description  : Set Osd transparency type
// Input Value  : enumOsdTransparencyType -> _OSD_TRANSPARENCY_DISABLE or _OSD_TRANSPARENCY_ONLY_WINDOW                      or
//                                           _OSD_TRANSPARENCY_ALL     or _OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetTransparencyType(EnumOsdTransparencyType enumOsdTransparencyType)
{
    ScalerOsdSetTransparencyType(enumOsdTransparencyType);
}


//--------------------------------------------------
// Description  : Set OSD Color Palette
// Input Value  : ucIndex  -> Which palette
//                ucColorR -> Palette red data   (0 ~ 255)
//                ucColorG -> Palette green data (0 ~ 255)
//                ucColorB -> Palette blue data  (0 ~ 255)
// Output Value :
//--------------------------------------------------
void UserCommonOsdSetColorPalette(BYTE ucIndex, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB)
{
    ScalerOsdSetColorPalette(ucIndex, ucColorR, ucColorG, ucColorB);
}


//--------------------------------------------------
// Description  : Set specific color blending
// Input Value  :     bEnable -> _ENABLE or _DISABLE
//                    ucIndex -> BlendingColor LUT index (0~63)
// Output Value :
//--------------------------------------------------
void UserCommonOsdSpecificColorBlending(bit bEnable, BYTE ucIndex)
{
    ScalerOsdSpecificColorBlending(bEnable, ucIndex);
}


//--------------------------------------------------
// Description  : Set MapA high than mapB
// Input Value  : bEnable -> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonOsdMapAHighThanMapB(bit bEnable)
{
    ScalerOsdMapAHighThanMapB(bEnable);
}


//--------------------------------------------------
// Description  : Reset OSD register
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonOsdResetToDefaultValue(void)
{
    ScalerOsdResetToDefaultValue();
}


//--------------------------------------------------
// Description  : Initialize Osd
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void UserCommonOsdGlobalOsdInitial(void)
{
    ScalerGlobalOsdInitial();
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Fosd FB mode Sepatate enable/disable
// Input Value  : ucEn
// Output Value : None
//--------------------------------------------------
void UserCommonOsdSetFosdFBSeparateEn(BYTE ucEn)
{
    ScalerOsdSetFosdFBSeparateEn(ucEn);
}
#endif

#if(_HW_GOSD_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Mixer Factor
// Input Value  : ucK1
//                ucK2
//                ucK3
//                ucK4
// Output Value : None
//--------------------------------------------------
void UserCommonOsdSubBlendingSetMixerFactor(BYTE ucK1, BYTE ucK2, BYTE ucK3, BYTE ucK4)
{
    ScalerOsdSubBlendingSetMixerFactor(ucK1, ucK2, ucK3, ucK4);
}


//--------------------------------------------------
// Description  : Set Bypass Fosd
// Input Value  : ucBypassEn
// Output Value : None
//--------------------------------------------------
void UserCommonOsdSubBlendingSetBypassFosdEnable(BYTE ucBypassEn)
{
    ScalerOsdSubBlendingSetBypassFosdEnable(ucBypassEn);
}

//--------------------------------------------------
// Description  : Get Bypass Fosd
// Input Value  : None
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
bit UserCommonOsdSubBlendingGetBypassFosdEnable(void)
{
    return ScalerOsdSubBlendingGetBypassFosdEnable();
}

//--------------------------------------------------
// Description  : Set mixer fosd enable/disable
// Input Value  :  _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonOsdSubBlendingSetFosdMixerEnable(bit bFosdEn)
{
    ScalerOsdSubBlendingSetFosdMixerEnable(bFosdEn);
}

//--------------------------------------------------
// Description  : Get mixer fosd enable/disable
// Input Value  : None
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
bit UserCommonOsdSubBlendingGetFosdMixerEnable(void)
{
    return ScalerOsdSubBlendingGetFosdMixerEnable();
}
//--------------------------------------------------
// Description  : Set mixer gosd enable/disable
// Input Value  :  _ENABLE / _DISABLE
// Output Value : None
//--------------------------------------------------
void UserCommonOsdSubBlendingSetGosdMixerEnable(bit bGosdEn)
{
    ScalerOsdSubBlendingSetGosdMixerEnable(bGosdEn);
}

//--------------------------------------------------
// Description  : Get mixer gosd enable/disable
// Input Value  : None
// Output Value : _ENABLE / _DISABLE
//--------------------------------------------------
bit UserCommonOsdSubBlendingGetGosdMixerEnable(void)
{
    return ScalerOsdSubBlendingGetGosdMixerEnable();
}
#endif

//--------------------------------------------------
// Description  : Get Font Base Addr
// Input Value  :
// Output Value :
//--------------------------------------------------
DWORD UserCommonOsdGetFontBaseAddr(void)
{
    return ScalerOsdGetFontBaseAddr();
}


#if(_HW_OSD_DISP_FONT_BASE_ADDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Display Font Base Addr
// Input Value  :
// Output Value :
//--------------------------------------------------
DWORD UserCommonOsdSramBaseAddressGetDispFontAddr(void)
{
    return ScalerOsdSramBaseAddressGetDispFontAddr();
}


//--------------------------------------------------
// Description  : Set Display Font Base Addr
// Input Value  : ulDispFontBaseAddr
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramBaseAddressSetDispFontAddr(DWORD ulDispFontBaseAddr)
{
    return ScalerOsdSramBaseAddressSetDispFontAddr(ulDispFontBaseAddr);
}
#endif // end of #if(_HW_OSD_DISP_FONT_BASE_ADDR_SUPPORT == _ON)


#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
//--------------------------------------------------
// Description  : Set HW put string address
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSetHWPutStringAddress(WORD usAddr)
{
    ScalerOsdSramSetHWPutStringAddress(usAddr);
}


//--------------------------------------------------
// Description  : Set HW put string font data
// Input Value  : ucData
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSetHWPutStringFontData(BYTE ucData)
{
    ScalerOsdSramSetHWPutStringFontData(ucData);
}


//--------------------------------------------------
// Description  : Set HW put string font select
// Input Value  : enumFontSel
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSetHWPutStringFontSelect(EnumOsdHWPutStringFontSelType enumFontSel)
{
    ScalerOsdSramSetHWPutStringFontSelect(enumFontSel);
}


//--------------------------------------------------
// Description  : Set HW put string font width
// Input Value  : ucFontWidth
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSetHWPutStringFontWidth(BYTE ucFontWidth)
{
    ScalerOsdSramSetHWPutStringFontWidth(ucFontWidth);
}


//--------------------------------------------------
// Description  : Set HW put string last font
// Input Value  : bLastFont -> last font or not
//                ucWidth -> font width
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSetHWPutStringLastFont(bit bLastFont, BYTE ucWidth)
{
    ScalerOsdSramSetHWPutStringLastFont(bLastFont, ucWidth);
}


//--------------------------------------------------
// Description  : Set HW put string apply
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSetHWPutStringApply(void)
{
    ScalerOsdSramSetHWPutStringApply();
}


//--------------------------------------------------
// Description  : Set HW put string apply polling finish
// Input Value  :
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSetHWPutStringApplyPollingFinish(void)
{
    ScalerOsdSramSetHWPutStringApplyPollingFinish();
}


//--------------------------------------------------
// Description  : Set HW put string enable
// Input Value  : bEnable
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSetHWPutStringEnable(bit bEnable)
{
    ScalerOsdSramSetHWPutStringEnable(bEnable);
}
#endif // end of #if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)


#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
//--------------------------------------------------
// Description  : Get 4 byte command enable/disable
// Input Value  :
// Output Value :
//--------------------------------------------------
bit UserCommonOsdSramGet4ByteCmdEnable(void)
{
    return ScalerOsdSramGet4ByteCmdEnable();
}


//--------------------------------------------------
// Description  : Set 4 byte command enable
// Input Value  : bEnable
// Output Value :
//--------------------------------------------------
void UserCommonOsdSramSet4ByteCmdEnable(bit bEnable)
{
    ScalerOsdSramSet4ByteCmdEnable(bEnable);
}
#endif