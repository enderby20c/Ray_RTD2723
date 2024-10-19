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
// ID Code      : ScalerOsd.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_OSD__

#include "ScalerFunctionInclude.h"
#include "Osd/ScalerOsd.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
WORD g_usOsdTgDBCurDdmVSta;
WORD g_usOsdTgDBCurDdmVEnd;
bit g_bOsdTgDBApply;
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
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
void ScalerOsdMapRotationAndRotionSize(EnumOsdRotateType enumOsdRotateType, EnumOsdRotateMapA enumOsdRotateMapA, EnumOsdRotateMapB enumOsdRotateMapB, EnumOsdRotateFontLib enumOsdRotateFontLib, WORD usRotateWidth, WORD usRotateHeight)
{
    BYTE ucTemp = 0;

#if(_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON)
    // rotate_flib_str_addr = (font_base + n * 9) / 4. n: rotate font number and must be multiple of 4
    ScalerOsdSetFontRotStartAddress(ScalerOsdGetFontBaseAddr() / 4); // n = 0
#endif

    // Get Current Roatation direction
    switch(ScalerGetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, (_BIT3 | _BIT2)))
    {
        default:
        case 0x00:
            ucTemp = _OSD_ROTATE_DEGREE_0;
            break;

        case _BIT2:
            ucTemp = _OSD_ROTATE_DEGREE_90;
            break;

        case _BIT3:
            ucTemp = _OSD_ROTATE_DEGREE_180;
            break;

        case (_BIT3 | _BIT2):
            ucTemp = _OSD_ROTATE_DEGREE_270;
            break;
    }

    // Enable or Disable Map A or B Rotate.
    ScalerSetBit(P3A_24_FRAME_CTRL_F_MAP_ROTATE_EN, ~(_BIT1 | _BIT0), ((enumOsdRotateMapB << 1) | enumOsdRotateMapA));

    // Set Rotate Width/Height
    ScalerOsdRotationSize(usRotateWidth, usRotateHeight);

    // Check Rotation Direction
    if(ucTemp == enumOsdRotateType)
    {
        return;
    }

    // Rotate to target direction
    switch(enumOsdRotateType)
    {
        case _OSD_ROTATE_DEGREE_0:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT6 | _BIT1 | _BIT0), (enumOsdRotateFontLib << 6));
            break;

        case _OSD_ROTATE_DEGREE_90:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT6 | _BIT1 | _BIT0), ((enumOsdRotateFontLib << 6) | _BIT0));
            break;

        case _OSD_ROTATE_DEGREE_270:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT6 | _BIT1 | _BIT0), ((enumOsdRotateFontLib << 6) | _BIT1 | _BIT0));
            break;

        case _OSD_ROTATE_DEGREE_180:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT6 | _BIT1 | _BIT0), ((enumOsdRotateFontLib << 6) | _BIT1));
            break;

        default:
            break;
    }

    ScalerOsdFontLibraryRotation();
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
void ScalerOsdMapRotationAndRotionSizeAndStart(EnumOsdRotateType enumOsdRotateType,
                                               EnumOsdRotateMapA enumOsdRotateMapA, EnumOsdRotateMapB enumOsdRotateMapB,
                                               EnumOsdRotateMapC enumOsdRotateMapC, EnumOsdRotateMapD enumOsdRotateMapD,
                                               EnumOsdRotateFontLib enumOsdRotateFontLib, WORD usRotateWidth, WORD usRotateHeight, WORD usFontRotateStartAddr)
{
    BYTE ucTemp = 0;

#if(_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON)
    // Set Font Libary Rotate Start Address
    ScalerOsdSetFontRotStartAddress(usFontRotateStartAddr);
#endif

    // Enable or Disable Map A or B Rotate.
    ucTemp = (enumOsdRotateMapA == _OSD_MAP_A_REMAPPING_DISABLE) ? (0x00) : (_BIT0);
    ucTemp |= (enumOsdRotateMapB == _OSD_MAP_B_REMAPPING_DISABLE) ? (0x00) : (_BIT1);
    ucTemp |= (enumOsdRotateMapC == _OSD_MAP_C_REMAPPING_DISABLE) ? (0x00) : (_BIT2);
    ucTemp |= (enumOsdRotateMapD == _OSD_MAP_D_REMAPPING_DISABLE) ? (0x00) : (_BIT3);
    ScalerSetBit(P3A_24_FRAME_CTRL_F_MAP_ROTATE_EN, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ucTemp);

    // Set Rotate Width/Height
    ScalerOsdRotationSize(usRotateWidth, usRotateHeight);

    // Get Current Roatation direction
    switch(ScalerGetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, (_BIT3 | _BIT2)))
    {
        default:
        case 0x00:
            ucTemp = _OSD_ROTATE_DEGREE_0;
            break;

        case _BIT2:
            ucTemp = _OSD_ROTATE_DEGREE_90;
            break;

        case _BIT3:
            ucTemp = _OSD_ROTATE_DEGREE_180;
            break;

        case (_BIT3 | _BIT2):
            ucTemp = _OSD_ROTATE_DEGREE_270;
            break;
    }

    // Check Rotation Direction
    if(ucTemp == enumOsdRotateType)
    {
        return;
    }

    // Rotate to target direction
    switch(enumOsdRotateType)
    {
        case _OSD_ROTATE_DEGREE_0:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT6 | _BIT1 | _BIT0), (enumOsdRotateFontLib << 6));
            break;

        case _OSD_ROTATE_DEGREE_90:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT6 | _BIT1 | _BIT0), ((enumOsdRotateFontLib << 6) | _BIT0));
            break;

        case _OSD_ROTATE_DEGREE_270:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT6 | _BIT1 | _BIT0), ((enumOsdRotateFontLib << 6) | _BIT1 | _BIT0));
            break;

        case _OSD_ROTATE_DEGREE_180:
            ScalerSetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, ~(_BIT6 | _BIT1 | _BIT0), ((enumOsdRotateFontLib << 6) | _BIT1));
            break;

        default:
            break;
    }

    ScalerOsdFontLibraryRotation();
}
#endif

//--------------------------------------------------
// Description  : Set Osd rotation size
// Input Value  : usRotateWidth
//                usRotateHeight
// Output Value : None
//--------------------------------------------------
void ScalerOsdRotationSize(WORD usRotateWidth, WORD usRotateHeight)
{
    // Set Rotate Width
    ScalerSetBit(P3A_25_FRAME_CTRL_F_OSD_PANEL_WID_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usRotateWidth >> 8) & 0x3F);
    ScalerSetByte(P3A_26_FRAME_CTRL_F_OSD_PANEL_WID_LSB, (BYTE)usRotateWidth);

    // Set Rotate Height
    ScalerSetBit(P3A_27_FRAME_CTRL_F_OSD_PANEL_HEI_MSB, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usRotateHeight >> 8) & 0x3F);
    ScalerSetByte(P3A_28_FRAME_CTRL_F_OSD_PANEL_HEI_LSB, (BYTE)usRotateHeight);
}

//--------------------------------------------------
// Description  : Reset OSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdReset(void)
{
    // Disable OSD Rotate (CW0)
    // Avoid fake power off to on, osd auto rotate fail.
    ScalerOsdFontRotateCtrlAuto(_OSD_ROTATE_DEGREE_0, _ENABLE);
    ScalerOsdFontRotateCtrlAuto(_OSD_ROTATE_DEGREE_0, _DISABLE);

#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    ScalerOsdSramSet4ByteCmdEnable(_DISABLE);
#endif
}

//--------------------------------------------------
// Description  : Set Osd Timing Gen. VSync Start
// Input Value  : usDVStart
// Output Value :
//--------------------------------------------------
void ScalerOsdSetTimingGen(WORD usDVStart, WORD usDVHeight, WORD usDHStart, bit bForceOsdDisable)
{
    bit bOsdTmingGenEn = _ENABLE;
    bit bOsdOverlayEn = (ScalerGetBit(P80_A0_OVERLAY_CTRL, _BIT0) == 0) ? (_DISABLE) : (_ENABLE);
    WORD usOsdVstart = _OSD_TIMING_GEN_VS_START;
#if(_OSD_H_DELAY_LIMIT_BYPASS == _ON)
    WORD usHDelayMax = 0;
#endif

#if(_ULTRA_VIVID_FUNCTION_WITH_DSHP == _OFF)
    bOsdTmingGenEn = (usDVStart < _OSD_TIMING_GEN_VS_START) ? (_ENABLE) : (_DISABLE);
#else
    usDVStart += 1; // delay 1 line
#endif

#if(_OSD_H_DELAY_LIMIT_BYPASS == _ON)
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        usHDelayMax = _HW_FOSD_H_DELAY_MAX * 2 - 1; // FB mode, panel width = 4091*2 - 1= 8181
    }
    else
#endif
    {
        usHDelayMax = _HW_FOSD_H_DELAY_MAX + 5; // EO mode, 4K panel width = 4096
    }
    if(ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_H_WIDTH) > usHDelayMax)
    {
        bOsdTmingGenEn = _ENABLE;
        usOsdVstart = 6;
    }
#endif

#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
    StructOsdTimingGenDB stCurOsdTgDbStatus = {0};
    StructOsdTimingGenDB stNextOsdTgDbStatus = {0};
    bit bOSDTgDBStatus = _DISABLE;
    g_bOsdTgDBApply = _FALSE;

    bOSDTgDBStatus = ((ScalerGlobalGetDDomainDBStatus() == _ENABLE) && (ScalerOsdGetOsdTimingGenDBEnable() == _ENABLE)) ? (_ENABLE) : (_DISABLE);

    // Check Global DB enable and OSD timing gen DB enable
    if(bOSDTgDBStatus == _ENABLE)
    {
        stCurOsdTgDbStatus.b1RefDmTg = (bit)ScalerGetBit(P3A_D0_OSD_TIMING_GEN_CTRL, _BIT6);
        stCurOsdTgDbStatus.usOsdVsSta = ScalerGetWord(P3A_D5_OSD_TIMING_GEN_VER_SYNC_STA_H) & 0x3FFF;
        stCurOsdTgDbStatus.usOsdBvLast = ScalerGetWord(P3A_DB_OSD_TIMING_GEN_VER_BG_LAST_H) & 0x3FFF;
        stCurOsdTgDbStatus.usOsdBvSta = ScalerGetWord(P3A_D7_OSD_TIMING_GEN_VER_BG_STA_H) & 0x3FFF;
        stCurOsdTgDbStatus.usDdmVsta = g_usOsdTgDBCurDdmVSta;
    }
#endif

    if((bOsdOverlayEn == _ENABLE) && (bForceOsdDisable == _ENABLE))
    {
        ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT0, 0x00);
    }

    if(bOsdTmingGenEn == _ENABLE)
    {
        WORD usVSyncStart = 0;

        // Set OSD Timing Gen HStart
        ScalerSetBit(P3A_D3_OSD_TIMING_GEN_HOR_BG_STA_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usDHStart) & 0x3F));
        ScalerSetByte(P3A_D4_OSD_TIMING_GEN_HOR_BG_STA_L, LOBYTE(usDHStart));

        // Set OSD Timing Gen VStart = 0x06
        ScalerSetBit(P3A_D7_OSD_TIMING_GEN_VER_BG_STA_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usOsdVstart) & 0x03F));
        ScalerSetByte(P3A_D8_OSD_TIMING_GEN_VER_BG_STA_L, LOBYTE(usOsdVstart));

        // Set OSD Timing Gen VEnd
        ScalerSetBit(P3A_D9_OSD_TIMING_GEN_VER_BG_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usOsdVstart + usDVHeight) & 0x3F));
        ScalerSetByte(P3A_DA_OSD_TIMING_GEN_VER_BG_END_L, LOBYTE(usOsdVstart + usDVHeight));

        // Set Even/Odd Swap by OSD Timing Gen. VStart
        ScalerSetBit(P3A_D0_OSD_TIMING_GEN_CTRL, ~_BIT0, ((usOsdVstart % 2) == 0) ? (0) : (_BIT0));

        if((GET_MEMORY_CONFIG_SELECT() == _FREE_RUN_MEMORY) ||
           (GET_MEMORY_CONFIG_SELECT() == _FREE_RUN_NO_INPUT))
        {
            // Set Mask Last Line Disable
            ScalerSetBit(P3A_D0_OSD_TIMING_GEN_CTRL, ~_BIT4, 0x00);

            // Set Mask Last Line
            ScalerSetBit(P3A_DB_OSD_TIMING_GEN_VER_BG_LAST_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
            ScalerSetByte(P3A_DC_OSD_TIMING_GEN_VER_BG_LAST_L, 0x00);

            // Set VSync Start
            if(usDVStart >= usOsdVstart)
            {
                usVSyncStart = usDVStart - usOsdVstart;
            }
            else
            {
                // VS start  = vtotal(d_timing) - vstart (osd_timing) + vstart (d_timing) + 1
                usVSyncStart = GET_FREE_RUN_DVTOTAL() - usOsdVstart + usDVStart + 1;
            }
            ScalerSetBit(P3A_D5_OSD_TIMING_GEN_VER_SYNC_STA_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usVSyncStart) & 0x3F));
            ScalerSetByte(P3A_D6_OSD_TIMING_GEN_VER_SYNC_STA_L, LOBYTE(usVSyncStart));
        }
        else
        {
            WORD usMaskLine = MAXOF(usDVStart, usOsdVstart) + usDVHeight + _PANEL_FRONT_PORCH_LIMIT;

            if(_PANEL_DV_TOTAL_MIN <= usMaskLine)
            {
                DebugMessageOsd("[Error] OSD Timing Gen.--Display Front Proch Should Be Larger than 4", _PANEL_DV_TOTAL_MIN);
                DebugMessageOsd("[Error] OSD Timing Gen.--DVStart", usDVStart);
                DebugMessageOsd("[Error] OSD Timing Gen.--DVHeight", usDVHeight);
                usMaskLine = _PANEL_DV_TOTAL_MIN;
            }

            // Set Mask Last Line Enable
            ScalerSetBit(P3A_D0_OSD_TIMING_GEN_CTRL, ~_BIT4, _BIT4);

            // Set Mask Last Line
            ScalerSetBit(P3A_DB_OSD_TIMING_GEN_VER_BG_LAST_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usMaskLine) & 0x3F));
            ScalerSetByte(P3A_DC_OSD_TIMING_GEN_VER_BG_LAST_L, LOBYTE(usMaskLine));

            // Set VSync Start
            if(usDVStart >= usOsdVstart)
            {
                usVSyncStart = usDVStart - usOsdVstart;
            }
            else
            {
                // VS start  = vtotal(d_timing) - vstart (osd_timing) + vstart (d_timing) + 1
                usVSyncStart = usMaskLine - usOsdVstart + usDVStart + 1;
            }
            ScalerSetBit(P3A_D5_OSD_TIMING_GEN_VER_SYNC_STA_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usVSyncStart) & 0x3F));
            ScalerSetByte(P3A_D6_OSD_TIMING_GEN_VER_SYNC_STA_L, LOBYTE(usVSyncStart));
        }

        // Set refernece OSD Timing Gen.
        ScalerSetBit(P3A_D0_OSD_TIMING_GEN_CTRL, ~_BIT6, 0x00);
    }
#if(_ULTRA_VIVID_FUNCTION_WITH_DSHP == _OFF)
    else
    {
        // Set Mask Last Line Disable
        ScalerSetBit(P3A_D0_OSD_TIMING_GEN_CTRL, ~_BIT4, 0x00);

        // Set Mask Last Line
        ScalerSetBit(P3A_DB_OSD_TIMING_GEN_VER_BG_LAST_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P3A_DC_OSD_TIMING_GEN_VER_BG_LAST_L, 0x00);

        // Set Even/Odd Swap
        ScalerSetBit(P3A_D0_OSD_TIMING_GEN_CTRL, ~_BIT0, ((usDVStart % 2) == 0) ? (0x00) : (_BIT0));

        // Set refernece D-domain Timing Gen.
        ScalerSetBit(P3A_D0_OSD_TIMING_GEN_CTRL, ~_BIT6, _BIT6);

        // Set VSync Start
        ScalerSetBit(P3A_D5_OSD_TIMING_GEN_VER_SYNC_STA_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x00);
        ScalerSetByte(P3A_D6_OSD_TIMING_GEN_VER_SYNC_STA_L, 0x00);
    }
#endif

#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
    if(bOSDTgDBStatus == _ENABLE)
    {
        stNextOsdTgDbStatus.b1RefDmTg = (bit)ScalerGetBit(P3A_D0_OSD_TIMING_GEN_CTRL, _BIT6);
        stNextOsdTgDbStatus.usOsdVsSta = ScalerGetWord(P3A_D5_OSD_TIMING_GEN_VER_SYNC_STA_H) & 0x3FFF;
        stNextOsdTgDbStatus.usOsdBvLast = ScalerGetWord(P3A_DB_OSD_TIMING_GEN_VER_BG_LAST_H) & 0x3FFF;
        stNextOsdTgDbStatus.usOsdBvSta = ScalerGetWord(P3A_D7_OSD_TIMING_GEN_VER_BG_STA_H) & 0x3FFF;
        stNextOsdTgDbStatus.usDdmVsta = usDVStart;

        if(ScalerOsdCalOsdTimingGenGlobalDBParam(&stCurOsdTgDbStatus, &stNextOsdTgDbStatus) == _TRUE)
        {
            g_bOsdTgDBApply = _TRUE;
        }
    }
#endif

    if((bOsdOverlayEn == _ENABLE) && (bForceOsdDisable == _ENABLE))
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT0, _BIT0);
    }
}

//--------------------------------------------------
// Description  : Reset OSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdResetToDefaultValue(void)
{
    WORD usRegIdx = 0;
    EnumOsdWindowsType enumWin = _OSD_WINDOW_0;
    BYTE ucTemp = 0;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    BYTE ucFBSepatateBackup = ScalerGetBit(P3A_EC_OSD_FRONT_BACK_REG_SEP_CTRL_GLOBAL, _BIT7);
#endif

    // OSD Timing Gen.
    // By system setting
    // for(usRegIdx = 0xD0; usRegIdx <= 0xDF; usRegIdx++)
    // {
    // ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx + pusPageOffset[ucPathIdx], 0x00);
    // }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    ScalerSetBit(P3A_EC_OSD_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, 0x00);
#endif

    // 1. Page 3A
    ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN, 0x00);
    ScalerSetByte(P3A_01_FRAME_CTRL_F_MAP_EN, 0x00);

#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    for(usRegIdx = 0x03; usRegIdx <= 0x3C; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#else
    for(usRegIdx = 0x03; usRegIdx <= 0x0A; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
    for(usRegIdx = 0x13; usRegIdx <= 0x1A; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
    for(usRegIdx = 0x23; usRegIdx <= 0x38; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#endif // end of #if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    for(usRegIdx = 0x3D; usRegIdx <= 0x40; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#if(_HW_OSD_DISP_FONT_BASE_ADDR_SUPPORT == _ON)
    for(usRegIdx = 0x41; usRegIdx <= 0x43; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#endif
#if(_HW_OSD_FONT_BASE_ADDR_BIT == _19_BIT)
    ScalerSetByte(P3A_44_FRAME_CTRL_F_FONT_BASE_H, 0x00);
#endif
    for(usRegIdx = 0x45; usRegIdx <= 0x5C; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    for(usRegIdx = 0x5D; usRegIdx <= 0x68; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#endif
    // ScalerSetByte(P3A_69_FRAME_CTRL_F_FB_INIT_CNT_H, 0x80); // By system setting
    // ScalerSetByte(P3A_6B_FRAME_CTRL_F_WD_0, 0x80); // By system setting
    for(usRegIdx = 0x6B; usRegIdx <= 0x6D; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#if(_HW_OSD_8_BIT_FONT_SUPPORT == _ON)
    ScalerSetByte(P3A_6E_FRAME_CTRL_F_FONT_8BIT_OFFSET_H, 0x00);
    ScalerSetByte(P3A_6F_FRAME_CTRL_F_FONT_8BIT_OFFSET_L, 0x00);
#endif
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    for(usRegIdx = 0x71; usRegIdx <= 0x74; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#endif
#if(_HW_WRITE_PEOTECT_GEN_TYPE == _OSD_WRITE_PROTECT_GEN_1)
    ScalerSetByte(P3A_7C_FRAME_CTRL_F_WRI_PROTECT_BIT_BYTE1, 0x00);
    ScalerSetByte(P3A_7D_FRAME_CTRL_F_WRI_PROTECT_BIT_BYTE2, 0x00);
    ScalerSetByte(P3A_7E_FRAME_CTRL_F_WRI_PROTECT_BIT_BYTE3, 0x00);
#endif
#if(_HW_FOSD_HW_PUT_STRING_GEN_TYPE == _OSD_HW_PUT_STRING_GEN_1)
    ScalerSetByte(P3A_80_FRAME_CTRL_F_PUT_STRING_CTRL, 0x10);
    ScalerSetByte(P3A_81_FRAME_CTRL_F_PUT_STRING_CTRL2, 0x00);
#endif
#if(_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON)
    ScalerSetByte(P3A_B0_FRAME_CTRL_F_FONT_ROT_STR_ADDR_H, 0x00);
    ScalerSetByte(P3A_B1_FRAME_CTRL_F_FONT_ROT_STR_ADDR_L, 0x00);
#endif
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    ScalerSetByte(P3A_B2_FRAME_CTRL_F_FONT_BASE_H_2, 0x00);
    ScalerSetByte(P3A_B3_FRAME_CTRL_F_FONT_BASE_M_2, 0x00);
    ScalerSetByte(P3A_B4_FRAME_CTRL_F_FONT_BASE_L_2, 0x00);
#endif
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
    for(usRegIdx = 0xB8; usRegIdx <= 0xBF; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#endif
    for(usRegIdx = 0xC0; usRegIdx <= 0xCC; usRegIdx++)
    {
        ScalerSetByte(P3A_00_FRAME_CTRL_F_OSD_EN + usRegIdx, 0x00);
    }
#if(_HW_FOSD_SRAM_SIZE == 44032)
    ScalerSetByte(P3A_CD_FRAME_CTRL_F_FONT_ROT_END_ADDR_H, 0x2A);
    ScalerSetByte(P3A_CE_FRAME_CTRL_F_FONT_ROT_END_ADDR_L, 0xFF);
#endif
#if(_HW_FOSD_SRAM_SIZE == 24576)
    ScalerSetByte(P3A_CD_FRAME_CTRL_F_FONT_ROT_END_ADDR_H, 0x17);
    ScalerSetByte(P3A_CE_FRAME_CTRL_F_FONT_ROT_END_ADDR_L, 0xFF);
#endif

    ScalerSetByte(P3A_CF_FRAME_CTRL_F_H_PRE_OP, 0x48);
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    ScalerSetByte(P3A_EA_FRAME_CTRL_F_H_PORCH_DELAY, 0x2D);
    ScalerSetByte(P3A_EB_FRAME_CTRL_F_H_PORCH_MISC, 0x40);

#endif
    // ScalerSetByte(P3A_F0_FRAME_CTRL_F_OSD_MAP_ADR_PORT_H, 0x28); // SRAM data
    // ScalerSetByte(P3A_F1_FRAME_CTRL_F_OSD_MAP_ADR_PORT_L, 0x28); // SRAM data
    // ScalerSetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, 0x28); // SRAM data
    ScalerSetByte(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, 0x01);
    // ScalerSetByte(P3A_F4_FRAME_CTRL_F_OSD_WIN_ADR_H, 0x00); // win data
    // ScalerSetByte(P3A_F5_FRAME_CTRL_F_OSD_WIN_ADR_L, 0x00); // win data
    // ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00); // win data
    ScalerSetByte(P3A_F7_FRAME_CTRL_F_OVERLAY_LUT_ADDR, 0x00);
    ScalerSetByte(P3A_F8_FRAME_CTRL_F_COLOR_LUT_PORT, 0x00);
#if(_HW_OSD_PALETTE_BIT == _8_BIT)
    ScalerSetByte(P3A_F9_FRAME_CTRL_F_OVERLAY_LUT_EN, 0x00);
#endif

    // 2. Page3A - Windpw Port
    // ************ By Window  setting *************************************************
    // ============ basic ============
    // win0 ~ win17, win24 ~ win31
    // register 0x00 ~ 0x0F
    for(enumWin = _OSD_WINDOW_0; enumWin <= _OSD_WINDOW_17; enumWin++)
    {
        ucTemp = enumWin / 10 * 16 + (enumWin % 10);
        for(usRegIdx = 0; usRegIdx <= 0x0F; usRegIdx++)
        {
            ScalerSetByte(P3A_F4_FRAME_CTRL_F_OSD_WIN_ADR_H, ucTemp);
            ScalerSetByte(P3A_F5_FRAME_CTRL_F_OSD_WIN_ADR_L, usRegIdx);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
        }
    }
    for(enumWin = _OSD_WINDOW_24; enumWin <= _OSD_WINDOW_31; enumWin++)
    {
        ucTemp = enumWin / 10 * 16 + (enumWin % 10);
        for(usRegIdx = 0; usRegIdx <= 0x0F; usRegIdx++)
        {
            ScalerSetByte(P3A_F4_FRAME_CTRL_F_OSD_WIN_ADR_H, ucTemp);
            ScalerSetByte(P3A_F5_FRAME_CTRL_F_OSD_WIN_ADR_L, usRegIdx);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
        }
    }

    // ============ grid ============
    // win2 ~ win4
    // register 0x20 ~ 0x26
    for(enumWin = _OSD_WINDOW_2; enumWin <= _OSD_WINDOW_4; enumWin++)
    {
        ucTemp = enumWin / 10 * 16 + (enumWin % 10);
        for(usRegIdx = 0x20; usRegIdx <= 0x26; usRegIdx++)
        {
            ScalerSetByte(P3A_F4_FRAME_CTRL_F_OSD_WIN_ADR_H, ucTemp);
            ScalerSetByte(P3A_F5_FRAME_CTRL_F_OSD_WIN_ADR_L, usRegIdx);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
        }
    }

    // ============ high light ============
    // win24 ~ win31
    // register 0x30 ~ 0x31
    for(enumWin = _OSD_WINDOW_24; enumWin <= _OSD_WINDOW_31; enumWin++)
    {
        ucTemp = enumWin / 10 * 16 + (enumWin % 10);
        for(usRegIdx = 0x30; usRegIdx <= 0x31; usRegIdx++)
        {
            ScalerSetByte(P3A_F4_FRAME_CTRL_F_OSD_WIN_ADR_H, ucTemp);
            ScalerSetByte(P3A_F5_FRAME_CTRL_F_OSD_WIN_ADR_L, usRegIdx);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
        }
    }

    // ************ Gradient function *************************************************
    // ucGradeintIdx 0 ~ 5
    // register 0x3200 ~ 0x320A, 0x3210 ~  0x3217
    for(ucTemp = 0; ucTemp <= 5; ucTemp++)
    {
        ScalerOsdSetAddrWindow(_P3A_F6_PT_3200_WIN_F_WIN_GRADIENT0_0 + ucTemp * 0x20);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
        ScalerOsdSetAddrWindow(_P3A_F6_PT_3201_WIN_F_WIN_GRADIENT0_1 + ucTemp * 0x20);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x3F);

        for(usRegIdx = 0x02; usRegIdx <= 0x0A; usRegIdx++)
        {
            ScalerOsdSetAddrWindow(_P3A_F6_PT_3200_WIN_F_WIN_GRADIENT0_0 + ucTemp * 0x20 + usRegIdx);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
        }
        for(usRegIdx = 0x10; usRegIdx <= 0x17; usRegIdx++)
        {
            ScalerOsdSetAddrWindow(_P3A_F6_PT_3200_WIN_F_WIN_GRADIENT0_0 + ucTemp * 0x20 + usRegIdx);
            ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
        }
    }

    // register 0x32C1 ~ 0x32CC
    for(usRegIdx = 0x00; usRegIdx < 0x0C; usRegIdx++)
    {
        ScalerOsdSetAddrWindow(_P3A_F6_PT_32C1_WIN_F_WIN_ROUND_8_PAT_0 + usRegIdx);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
    }

#if(_HW_OSD_ROUND_WIN_0_PIXEL_SUPPORT == _ON)
    ScalerOsdSetAddrWindow(_P3A_F6_PT_32CD_WIN_F_WIN_ROUND_16_PAT_CTRL1);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
    ScalerOsdSetAddrWindow(_P3A_F6_PT_32CE_WIN_F_WIN_ROUND_16_PAT_CTRL2);
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
#endif

    // ************ Panel Pitch setting *************************************************
    // register 0x32D0 ~ 0x32D2
    for(usRegIdx = 0x00; usRegIdx <= 0x02; usRegIdx++)
    {
        ScalerOsdSetAddrWindow(_P3A_F6_PT_32D0_WIN_F_WIN_GRID_PITCH_PANEL_MSB + usRegIdx);
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, 0x00);
    }

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    ScalerSetByte(P3A_EC_OSD_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ucFBSepatateBackup);
#endif

    ScalerSetByte(P3A_E0_OSD_TIMING_DUMMY, 0x00);
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Fosd FB mode Sepatate enable/disable
// Input Value  : ucEn
// Output Value : None
//--------------------------------------------------
void ScalerOsdSetFosdFBSeparateEn(BYTE ucEn)
{
    ScalerSetBit(P3A_EC_OSD_FRONT_BACK_REG_SEP_CTRL_GLOBAL, ~_BIT7, (ucEn & _BIT0) << 7);
}
#endif
