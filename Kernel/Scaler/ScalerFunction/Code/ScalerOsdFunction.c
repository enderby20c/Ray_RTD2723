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
// ID Code      : ScalerOsdFunction.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Osd/ScalerOsd.h"

#if(_OSD_H_DELAY_LIMIT_BYPASS == _ON)
#warning "NOTE : Must check osd delay > 4091 (EO mode) or osd delay > 8191 (FB mode) in frame sync and free sync."
#endif

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
// Description  : Set Map Enable
// Input Value  : enumMapSel -> _OSD_A or _OSD_B
// Input Value  : bEnable -> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerOsdMapABFunctionEnable(EnumOsdMapType enumMapSel, bit bEnable)
{
    switch(enumMapSel)
    {
        case _OSD_A:
            ScalerSetBit(P3A_01_FRAME_CTRL_F_MAP_EN, ~_BIT0, (bEnable == _ENABLE) ? (_BIT0) : (0x00));
            break;
        case _OSD_B:
            ScalerSetBit(P3A_01_FRAME_CTRL_F_MAP_EN, ~_BIT1, (bEnable == _ENABLE) ? (_BIT1) : (0x00));
            break;
        default:
            break;
    }
}

#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set Map Enable
// Input Value  : enumMapSel -> _OSD_A or _OSD_B or _OSD_C or _OSD_D
// Input Value  : bEnable -> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerOsdMapFunctionEnable(EnumOsdMapType enumMapSel, bit bEnable)
{
    // Map priority : map D > C > A or B
    switch(enumMapSel)
    {
        case _OSD_A:
            ScalerSetBit(P3A_01_FRAME_CTRL_F_MAP_EN, ~_BIT0, (bEnable == _ENABLE) ? (_BIT0) : (0x00));
            break;
        case _OSD_B:
            ScalerSetBit(P3A_01_FRAME_CTRL_F_MAP_EN, ~_BIT1, (bEnable == _ENABLE) ? (_BIT1) : (0x00));
            break;
        case _OSD_C:
            ScalerSetBit(P3A_01_FRAME_CTRL_F_MAP_EN, ~_BIT2, (bEnable == _ENABLE) ? (_BIT2) : (0x00));
            break;
        case _OSD_D:
            ScalerSetBit(P3A_01_FRAME_CTRL_F_MAP_EN, ~_BIT3, (bEnable == _ENABLE) ? (_BIT3) : (0x00));
            break;
        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Activate OSD circuit enable disable
// Input Value  : bEnable      -> _ENABLE or _DISABLE
// Output Value :
//--------------------------------------------------
void ScalerOsdCircuitActivated(bit bEnable)
{
    bit bBackup = _DISABLE;

    if(ScalerGetBit(P3A_00_FRAME_CTRL_F_OSD_EN, _BIT0) == _BIT0)
    {
        if(bEnable == _ENABLE)
        {
            return;
        }
        bBackup = _ENABLE;
    }

    if(bEnable == _DISABLE)
    {
        // set write all byte
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
        ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#else
        ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
#endif
    }

    ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~(_BIT0), bEnable);

    if((bBackup == _DISABLE) && (bEnable == _ENABLE))
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
    }
}

//--------------------------------------------------
// Description  : Enable Display OSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdEnableOsd(void)
{
    ScalerOsdCircuitActivated(_ENABLE);

    // OSD Overlay Port Enable
    ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT0, _BIT0);
}

//--------------------------------------------------
// Description  : Disable Display OSD
// Input Value  :
// Output Value :
//--------------------------------------------------
void ScalerOsdDisableOsd(void)
{
    // OSD Overlay Port Enable
    ScalerSetBit(P80_A0_OVERLAY_CTRL, ~_BIT0, 0x00);
}

//--------------------------------------------------
// Description  : Get OSD H Double Enable Or Disable
// Input Value  :
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerOsdGetDoubleFunctionH(EnumOsdPositionType enumDelaySel)
{
    switch(enumDelaySel)
    {
        case _OSD_POSITION_GLOBAL_1:
            if(ScalerGetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, _BIT1) == _BIT1)
            {
                return _ENABLE;
            }
            break;
        case _OSD_POSITION_GLOBAL_2:
            if(ScalerGetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, _BIT3) == _BIT3)
            {
                return _ENABLE;
            }
            break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_POSITION_GLOBAL_3:
            if(ScalerGetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, _BIT5) == _BIT5)
            {
                return _ENABLE;
            }
            break;
        case _OSD_POSITION_GLOBAL_4:
            if(ScalerGetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, _BIT7) == _BIT7)
            {
                return _ENABLE;
            }
            break;
#endif
        default:
            break;
    }

    return _DISABLE;
}

//--------------------------------------------------
// Description  : Get OSD V Double Enable Or Disable
// Input Value  :
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerOsdGetDoubleFunctionV(EnumOsdPositionType enumDelaySel)
{
    switch(enumDelaySel)
    {
        case _OSD_POSITION_GLOBAL_1:
            if(ScalerGetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, _BIT0) == _BIT0)
            {
                return _ENABLE;
            }
            break;
        case _OSD_POSITION_GLOBAL_2:
            if(ScalerGetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, _BIT2) == _BIT2)
            {
                return _ENABLE;
            }
            break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_POSITION_GLOBAL_3:
            if(ScalerGetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, _BIT4) == _BIT4)
            {
                return _ENABLE;
            }
            break;
        case _OSD_POSITION_GLOBAL_4:
            if(ScalerGetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, _BIT6) == _BIT6)
            {
                return _ENABLE;
            }
            break;
#endif
        default:
            break;
    }

    return _DISABLE;
}

//--------------------------------------------------
// Description  : Get OSD Enable Or Disable
// Input Value  :
// Output Value : _ENABLE or _DISABLE
//--------------------------------------------------
bit ScalerOsdGetOsdEnable(void)
{
    return ((bit)ScalerGetBit(P80_A0_OVERLAY_CTRL, _BIT0));
}

//--------------------------------------------------
// Description  : Osd double buufer mode
// Input Value  : enumDB
// Output Value :
//--------------------------------------------------
void ScalerOsdGlobalDoubleBufferSel(EnumOsdDoubleBufferType enumDB)
{
    switch(enumDB)
    {
        case _OSD_DB_DISABLE:
            ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~(_BIT7 | _BIT6), 0x00);
            break;

        case _OSD_DB_NORMAL:
            ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~(_BIT7 | _BIT6), _BIT6);
            break;

        case _OSD_DB_WAIT_READY_AND_DVS:
            ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~(_BIT5), 0x00); // set db_ready = 0 to prevent abnormal osd local db signal
            ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~(_BIT7 | _BIT6), _BIT7);
            break;

        default:
            break;
    }
}

#if(_HW_FOSD_TIMING_GEN_DB_GEN_TYPE == _OSD_TIMING_GEN_DB_GEN_1)
//--------------------------------------------------
// Description  : Double Buffer enable/disable in OSD timing gen
// Input Value  : bEnable -> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerOsdSetOsdTimingGenDBEnable(bit bEnable)
{
    // DB priority : osd_tg_db_en (Page3AE0[1]) -> Global IMD -> Global D -> Local
    ScalerSetBit(P3A_E0_OSD_TIMING_DUMMY, ~_BIT1, ((BYTE)bEnable << 1));
}

//--------------------------------------------------
// Description  : Get Double Buffer status in OSD timing gen
// Input Value  : None
// Output Value : DB status
//--------------------------------------------------
bit ScalerOsdGetOsdTimingGenDBEnable(void)
{
    return ((ScalerGetBit(P3A_E0_OSD_TIMING_DUMMY, _BIT1) == _BIT1) ? (_ENABLE) : (_DISABLE));
}

//--------------------------------------------------
// Description  : Osd Timing gen Global Double Buffer apply
// Input Value  : DB apply polling/ no polling/ none
// Output Value : None
//--------------------------------------------------
void ScalerOsdTimingGenGlobalDBApply(EnumDBApply enumDBApply)
{
    if((enumDBApply == _DB_APPLY_NONE) || (g_bOsdTgDBApply == _FALSE))
    {
        return;
    }
    // Set apply bit
    // Function effective in Global IMD and Global D Double Buffer
    ScalerSetBit(P3A_E0_OSD_TIMING_DUMMY, ~_BIT2, _BIT2);
    g_bOsdTgDBApply = _FALSE;

    if(enumDBApply == _DB_APPLY_POLLING)
    {
        // Wait D double buffer
        if(ScalerTimerPollingFlagProc(_DOUBLE_BUFFER_WAIT_TIME, P3A_E0_OSD_TIMING_DUMMY, _BIT2, 0) == _FALSE)
        {
            DebugMessageOsd("[Error] Osd timin gen DB apply time out", 0);
        }
    }
}

//--------------------------------------------------
// Description  : Calcuate osd timing gen DB parameter
// Input Value  :
// Output Value : None
//--------------------------------------------------
bit ScalerOsdCalOsdTimingGenGlobalDBParam(StructOsdTimingGenDB *pstCurOsdTgDbStatus, StructOsdTimingGenDB *pstNextOsdTgDbStatus)
{
    if(pstNextOsdTgDbStatus->b1RefDmTg == _TRUE)
    {
        // DebugMessageOsd("-osd-db-nothing", stCurOsdTgDbStatus.b1RefDmTg);
        return _FALSE;
    }

    WORD usVSta = 0;
    WORD usBvLast = 0;

    // Check osd apply bit status
    if(ScalerGetBit(P3A_E0_OSD_TIMING_DUMMY, _BIT2) == _BIT2)
    {
        ScalerSetBit(P3A_E0_OSD_TIMING_DUMMY, ~_BIT2, 0x00);
        DebugMessageOsd("[Error] Osd timin gen DB apply not clear", 0);
    }
    if(pstCurOsdTgDbStatus->b1RefDmTg == _TRUE)
    {
        if(pstCurOsdTgDbStatus->usDdmVsta > pstNextOsdTgDbStatus->usDdmVsta)
        {
            // Set temp_vs_sta = dden_end + _OSD_NEW_DB_DDEN_END_DELAY
            usVSta = g_usOsdTgDBCurDdmVEnd + _OSD_NEW_DB_DDEN_END_DELAY;
            // Set temp_bv_last = temp_vs_sta + (bv_sta' - dvstart' - 1)
            usBvLast = usVSta + pstNextOsdTgDbStatus->usOsdBvSta - pstNextOsdTgDbStatus->usDdmVsta - 1;
            DebugMessageOsd("-OSD-DB: reg_tg 1 to 0", 1);
        }
        else
        {
            // Set temp_vs_sta = vs_sta'
            usVSta = pstNextOsdTgDbStatus->usOsdVsSta;
            // Set temp_bv_last = oosd_bv_last'
            usBvLast = pstNextOsdTgDbStatus->usOsdBvLast;
            DebugMessageOsd("-OSD-DB: reg_tg 1 to 0", 2);
        }
    }
    else
    {
        if(pstNextOsdTgDbStatus->usDdmVsta >= 6)
        {
            // Set temp_vs_sta = vs_sta'
            usVSta = pstNextOsdTgDbStatus->usOsdVsSta;
            // Set temp_bv_last = bv_last'
            usBvLast = pstNextOsdTgDbStatus->usOsdBvLast;
            DebugMessageOsd("-OSD-DB: reg_tg 0 to 0", 1);
        }
        else if(pstCurOsdTgDbStatus->usDdmVsta >= 6)
        {
            // Set temp_vs_sta = dden_end + _OSD_NEW_DB_DDEN_END_DELAY
            usVSta = g_usOsdTgDBCurDdmVEnd + _OSD_NEW_DB_DDEN_END_DELAY;
            // Set temp_bv_last = temp_vs_sta + (bv_sta' - dvstart' - 1)
            usBvLast = usVSta + pstNextOsdTgDbStatus->usOsdBvSta - pstNextOsdTgDbStatus->usDdmVsta - 1;
            DebugMessageOsd("-OSD-DB: reg_tg 0 to 0", 2);
        }
        else
        {
            // Set temp_vs_sta = vs_sta
            usVSta = pstCurOsdTgDbStatus->usOsdVsSta;
            // Set temp_bv_last
            // check bv_last' < bv_last
            if(pstNextOsdTgDbStatus->usOsdBvLast < pstCurOsdTgDbStatus->usOsdBvLast)
            {
                // temp_bv_last = bv_last + (bv_sta' - dvstart' - 1)
                usBvLast = pstCurOsdTgDbStatus->usOsdBvLast + pstNextOsdTgDbStatus->usOsdBvSta - pstNextOsdTgDbStatus->usDdmVsta - 1;
            }
            else
            {
                // temp_bv_last = temp_vs_sta + (bv_sta' - dvstart' - 1)
                usBvLast = pstCurOsdTgDbStatus->usOsdVsSta + pstNextOsdTgDbStatus->usOsdBvSta - pstNextOsdTgDbStatus->usDdmVsta - 1;
            }
            DebugMessageOsd("-OSD-DB: reg_tg 0 to 0", 3);
        }
    }
    ScalerSetBit(P3A_90_OSD_TIMING_GEN_TEMP_V_STA_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usVSta) & 0x03F));
    ScalerSetByte(P3A_91_OSD_TIMING_GEN_TEMP_V_STA_L, LOBYTE(usVSta));
    ScalerSetBit(P3A_92_OSD_TIMING_GEN_TEMP_V_LAST_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (HIBYTE(usBvLast) & 0x03F));
    ScalerSetByte(P3A_93_OSD_TIMING_GEN_TEMP_V_LAST_L, LOBYTE(usBvLast));

    return _TRUE;
}
#endif

#if(_HW_FOSD_REFER_CAP_WIN_BACKGROUND_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Refer Capture background win enable/disable
// Input Value  : bEn
// Output Value : None
//--------------------------------------------------
void ScalerOsdSetReferCapWinBackground(bit bEn)
{
    ScalerSetBit(P3A_E0_OSD_TIMING_DUMMY, ~_BIT3, ((BYTE)bEn << 3));
}
#endif

//--------------------------------------------------
// Description  : Set MapA high than mapB
// Input Value  : bEnable -> _ENABLE or _DISABLE
// Output Value : None
//--------------------------------------------------
void ScalerOsdMapAHighThanMapB(bit bEnable)
{
    ScalerSetBit(P3A_00_FRAME_CTRL_F_OSD_EN, ~_BIT1, ((BYTE)bEnable << 1));
}

//--------------------------------------------------
// Description  : Get osd max H position
// Input Value  : enumOsdPositionType
// Output Value :
//--------------------------------------------------
WORD ScalerOsdGetMaxHPos(EnumOsdPositionType enumOsdPositionType)
{
    WORD usHDelayLimit = _HW_FOSD_H_DELAY_BIT;

    // Osd H Delay Limit only cw0 or cw270
    if((ScalerGetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, (_BIT3 | _BIT2)) == 0x00) ||
       (ScalerGetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, (_BIT3 | _BIT2)) == (_BIT3 | _BIT2)))
    {
        switch(enumOsdPositionType)
        {
            case _OSD_POSITION_GLOBAL_1:
            case _OSD_POSITION_GLOBAL_2:
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
            case _OSD_POSITION_GLOBAL_3:
            case _OSD_POSITION_GLOBAL_4:
#endif
                usHDelayLimit = _HW_FOSD_H_DELAY_MAX;

#if(_OSD_H_DELAY_LIMIT_BYPASS == _ON)
                if(ScalerDDomainGetDisplayBackground_R1(_DISPLAY_BACKGROUND_V_START) >= 6)
                {
                    usHDelayLimit = _HW_FOSD_H_DELAY_BIT;
                }
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
                if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
                {
                    usHDelayLimit = _HW_FOSD_H_DELAY_MAX * 2 - _DDOMAIN_MAX_EXTENSION - 1;
                }
#endif
                break;
            default:
                break;
        }
    }

    return usHDelayLimit;
}

//--------------------------------------------------
// Description  : Set osd position
// Input Value  : enumOsdPositionType -> _OSD_POSITION_GLOBAL_1 or _OSD_POSITION_GLOBAL_2 or _OSD_POSITION_FONT_A or _OSD_POSITION_FONT_B
//                usX                 -> Horizontal delay value
//                usY                 -> Vertical  delay value
// Output Value :
//--------------------------------------------------
void ScalerOsdPosition(EnumOsdPositionType enumOsdPositionType, WORD usX, WORD usY)
{
    WORD usHDelayLimit = ScalerOsdGetMaxHPos(enumOsdPositionType);

    // Check Osd Double Buffer
    if(((ScalerGetBit(P3A_00_FRAME_CTRL_F_OSD_EN, (_BIT7 | _BIT6)) >> 6) & 0x03) == _OSD_DB_DISABLE)
    {
        ScalerTimerWaitForDDomainEvent(_EVENT_DEN_STOP);
    }

    switch(enumOsdPositionType)
    {
        case _OSD_POSITION_GLOBAL_1:
        case _OSD_POSITION_GLOBAL_2:
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_POSITION_GLOBAL_3:
        case _OSD_POSITION_GLOBAL_4:
#endif
#if(_PANEL_ASYMMETRIC == _ON)
            usX = usX + _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT;
            usY = usY + _PANEL_ASYMMETRIC_DUMMY_NUM_TOP;
#endif
            switch(ScalerGetBit(P3A_23_FRAME_CTRL_F_ROT_DIR, (_BIT3 | _BIT2)))
            {
                case 0x00: // cw0
                    usX = MINOF(usX, usHDelayLimit);
                    break;
                case (_BIT3 | _BIT2): // cw270
                    usY = MINOF(usY, usHDelayLimit);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    switch(enumOsdPositionType)
    {
        case _OSD_POSITION_GLOBAL_1:
            // First Horizontal Delay
            ScalerSetBit(P3A_05_FRAME_CTRL_F_H_DELAY1_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usX >> 8) & 0x3F));
            ScalerSetByte(P3A_06_FRAME_CTRL_F_H_DELAY1_L, (usX & 0xFF));
            // First Vertical Delay
            ScalerSetBit(P3A_03_FRAME_CTRL_F_V_DELAY1_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usY >> 8) & 0x3F));
            ScalerSetByte(P3A_04_FRAME_CTRL_F_V_DELAY1_L, (usY & 0xFF));
            break;

        case _OSD_POSITION_GLOBAL_2:
            // Second Horizontal Delay
            ScalerSetBit(P3A_09_FRAME_CTRL_F_H_DELAY2_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usX >> 8) & 0x3F));
            ScalerSetByte(P3A_0A_FRAME_CTRL_F_H_DELAY2_L, (usX & 0xFF));
            // Second Vertical Delay
            ScalerSetBit(P3A_07_FRAME_CTRL_F_V_DELAY2_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usY >> 8) & 0x3F));
            ScalerSetByte(P3A_08_FRAME_CTRL_F_V_DELAY2_L, (usY & 0xFF));
            break;

        case _OSD_POSITION_FONT_A:
            // FONT A Horizontal Delay
            ScalerSetBit(P3A_15_FRAME_CTRL_F_MAP_A_H_DELAY_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usX >> 8) & 0x3F));
            ScalerSetByte(P3A_16_FRAME_CTRL_F_MAP_A_H_DELAY_L, (usX & 0xFF));
            // FONT A Vertical Delay [7:0]
            ScalerSetBit(P3A_13_FRAME_CTRL_F_MAP_A_V_DELAY_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usY >> 8) & 0x3F));
            ScalerSetByte(P3A_14_FRAME_CTRL_F_MAP_A_V_DELAY_L, (usY & 0xFF));
            break;

        case _OSD_POSITION_FONT_B:
            // FONT B Horizontal Delay
            ScalerSetBit(P3A_19_FRAME_CTRL_F_MAP_B_H_DELAY_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usX >> 8) & 0x3F));
            ScalerSetByte(P3A_1A_FRAME_CTRL_F_MAP_B_H_DELAY_L, (usX & 0x0FF));
            // FONT B Vertical Delay
            ScalerSetBit(P3A_17_FRAME_CTRL_F_MAP_B_V_DELAY_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usY >> 8) & 0x3F));
            ScalerSetByte(P3A_18_FRAME_CTRL_F_MAP_B_V_DELAY_L, (usY & 0x0FF));
            break;

#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_POSITION_GLOBAL_3:
            // 3rd Horizontal Delay
            ScalerSetBit(P3A_0D_FRAME_CTRL_F_H_DELAY3_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usX >> 8) & 0x3F));
            ScalerSetByte(P3A_0E_FRAME_CTRL_F_H_DELAY3_L, (usX & 0xFF));
            // 3rd Vertical Delay
            ScalerSetBit(P3A_0B_FRAME_CTRL_F_V_DELAY3_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usY >> 8) & 0x3F));
            ScalerSetByte(P3A_0C_FRAME_CTRL_F_V_DELAY3_L, (usY & 0xFF));
            break;

        case _OSD_POSITION_GLOBAL_4:
            // 4th Horizontal Delay
            ScalerSetBit(P3A_11_FRAME_CTRL_F_H_DELAY4_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usX >> 8) & 0x3F));
            ScalerSetByte(P3A_12_FRAME_CTRL_F_H_DELAY4_L, (usX & 0xFF));
            // 4th Vertical Delay
            ScalerSetBit(P3A_0F_FRAME_CTRL_F_V_DELAY4_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usY >> 8) & 0x3F));
            ScalerSetByte(P3A_10_FRAME_CTRL_F_V_DELAY4_L, (usY & 0xFF));
            break;

        case _OSD_POSITION_FONT_C:
            // FONT C Horizontal Delay
            ScalerSetBit(P3A_1D_FRAME_CTRL_F_MAP_C_H_DELAY_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usX >> 8) & 0x3F));
            ScalerSetByte(P3A_1E_FRAME_CTRL_F_MAP_C_H_DELAY_L, (usX & 0xFF));
            // FONT C Vertical Delay
            ScalerSetBit(P3A_1B_FRAME_CTRL_F_MAP_C_V_DELAY_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usY >> 8) & 0x3F));
            ScalerSetByte(P3A_1C_FRAME_CTRL_F_MAP_C_V_DELAY_L, (usY & 0xFF));
            break;

        case _OSD_POSITION_FONT_D:
            // FONT D Horizontal Delay
            ScalerSetBit(P3A_21_FRAME_CTRL_F_MAP_D_H_DELAY_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usX >> 8) & 0x3F));
            ScalerSetByte(P3A_22_FRAME_CTRL_F_MAP_D_H_DELAY_L, (usX & 0x0FF));
            // FONT D Vertical Delay
            ScalerSetBit(P3A_1F_FRAME_CTRL_F_MAP_D_V_DELAY_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), ((usY >> 8) & 0x3F));
            ScalerSetByte(P3A_20_FRAME_CTRL_F_MAP_D_V_DELAY_L, (usY & 0x0FF));
            break;
#endif // end of #if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)

        default:
            break;
    }
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdPosition(_OSD_POSITION_GLOBAL_A, XPOS(100), YPOS(100));
*/

//--------------------------------------------------
// Description  : OSD Scale Up Initial Vale
// Input Value  : ucHInitValue
// Input Value  : ucVInitValue
// Output Value :
//--------------------------------------------------
void ScalerOsdScalingUpIptInitialValue(BYTE ucHInitValue, BYTE ucVInitValue)
{
    ScalerSetByte(P3A_C1_FRAME_CTRL_F_IPT_INIT_PHASE, (((ucVInitValue & 0x0F) << 4) | (ucHInitValue & 0x0F)));
}

//--------------------------------------------------
// Description  : Set OSD Color Palette
// Input Value  : ucIndex  -> Which palette
//                ucColorR -> Palette red data   (0 ~ 255)
//                ucColorG -> Palette green data (0 ~ 255)
//                ucColorB -> Palette blue data  (0 ~ 255)
// Output Value :
//--------------------------------------------------
void ScalerOsdSetColorPalette(BYTE ucIndex, BYTE ucColorR, BYTE ucColorG, BYTE ucColorB)
{
#if(_HW_OSD_PALETTE_BIT == _8_BIT)
    // Set color_palette_read_en disble
    ScalerSetBit(P3A_F9_FRAME_CTRL_F_OVERLAY_LUT_EN, ~_BIT7, 0x00);
#endif
    // _HW_OSD_PALETTE_BIT == _6_BIT--> Page3AF7[7] : color_palette_read_en
    ScalerSetByte(P3A_F7_FRAME_CTRL_F_OVERLAY_LUT_ADDR, (ucIndex & _HW_OSD_PALETTE_BIT));
    ScalerSetByte(P3A_F8_FRAME_CTRL_F_COLOR_LUT_PORT, ucColorR);
    ScalerSetByte(P3A_F8_FRAME_CTRL_F_COLOR_LUT_PORT, ucColorG);
    ScalerSetByte(P3A_F8_FRAME_CTRL_F_COLOR_LUT_PORT, ucColorB);
}

//--------------------------------------------------
// Description  : Set Dclk Range
// Input Value  : uldclk
// Output Value :
//--------------------------------------------------
void ScalerOsdSetDCLKSpeedRange(DWORD ulDclk)
{
    if(ulDclk > 150000)
    {
        ScalerSetBit(P3A_6D_FRAME_CTRL_F_TEMP, ~_BIT7, _BIT7);
    }
    else
    {
        ScalerSetBit(P3A_6D_FRAME_CTRL_F_TEMP, ~_BIT7, 0x00);
    }
}

//--------------------------------------------------
// Description  : Set OSD Fisrt Block in Font Back Mode
// Input Value  : ucOn
// Output Value :
//--------------------------------------------------
void ScalerOsdSetFBFirstBlock(EnumOsdFBSel enumPath, BYTE ucOn)
{
    // Set First Block
    if(enumPath == _OSD_FRONT)
    {
        ScalerSetBit(P3A_69_FRAME_CTRL_F_FB_INIT_CNT_H, ~(_BIT7), ucOn << 7);
    }
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    else
    {
        ScalerSetBit(P84_69_FRAME_CTRL_B_FB_INIT_CNT_H, ~(_BIT7), ucOn << 7);
    }
#endif
}

//--------------------------------------------------
// Description  : Set OSD Start Address in Font Back mode
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void ScalerOsdSetFBFirstStartAddr(EnumOsdFBSel enumPath, WORD usAddr)
{
    // Set Address
    if(enumPath == _OSD_FRONT)
    {
        ScalerSetBit(P3A_69_FRAME_CTRL_F_FB_INIT_CNT_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usAddr & 0x3F00) >> 8);
        ScalerSetByte(P3A_6A_FRAME_CTRL_F_FB_INIT_CNT_L, (BYTE)usAddr);
    }
#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    else
    {
        ScalerSetBit(P84_69_FRAME_CTRL_B_FB_INIT_CNT_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usAddr & 0x3F00) >> 8);
        ScalerSetByte(P84_6A_FRAME_CTRL_B_FB_INIT_CNT_L, (BYTE)usAddr);
    }
#endif
}

//--------------------------------------------------
// Description  : Set OSD Font Library Rotation End Address
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void ScalerOsdSetFontRotEndAddress(WORD usAddr)
{
    // Set Address
    // rotate_flib_end_addr = (font_base + n * 9) / 4 - 1.
    // n: rotate font number and must be multiple of 4.
    ScalerSetBit(P3A_CD_FRAME_CTRL_F_FONT_ROT_END_ADDR_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usAddr & 0x3F00) >> 8);
    ScalerSetByte(P3A_CE_FRAME_CTRL_F_FONT_ROT_END_ADDR_L, (BYTE)usAddr);
}

#if(_HW_FOSD_HW_FONT_LIB_ROTATE_START_ADDR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set OSD Font Library Rotation Start Address
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void ScalerOsdSetFontRotStartAddress(WORD usAddr)
{
    // Set Address
    // rotate_flib_str_addr = (font_base + n * 9) / 4.
    // n: rotate font number and must be multiple of 4.
    ScalerSetBit(P3A_B0_FRAME_CTRL_F_FONT_ROT_STR_ADDR_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (usAddr & 0x3F00) >> 8);
    ScalerSetByte(P3A_B1_FRAME_CTRL_F_FONT_ROT_STR_ADDR_L, (BYTE)usAddr);
}
#endif

//--------------------------------------------------
// Description  : OSD Scale Up - Double
// Input Value  : enumDelaySel
// Input Value  : ucHoriEnable
// Input Value  : ucVerEnable
// Output Value :
//--------------------------------------------------
void ScalerOsdScalingUpDoubleEn(EnumOsdPositionType enumDelaySel, BYTE ucHoriEnable, BYTE ucVerEnable)
{
    if((ucHoriEnable == _ENABLE) && (_FOSD_SU_H_FACTOR_MIN > 32))
    {
        DebugMessageOsd("Error: _FOSD_SU_H_FACTOR_MIN must be less than or equal to 32 when H double enable", 0);
        return;
    }

    switch(enumDelaySel)
    {
        case _OSD_POSITION_GLOBAL_1:
            ScalerSetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, ~(_BIT1), (ucHoriEnable == _ENABLE) ? (_BIT1) : (0x00));
            ScalerSetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, ~(_BIT0), (ucVerEnable == _ENABLE) ? (_BIT0) : (0x00));
            break;
        case _OSD_POSITION_GLOBAL_2:
            ScalerSetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, ~(_BIT3), (ucHoriEnable == _ENABLE) ? (_BIT3) : (0x00));
            ScalerSetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, ~(_BIT2), (ucVerEnable == _ENABLE) ? (_BIT2) : (0x00));
            break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_POSITION_GLOBAL_3:
            ScalerSetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, ~(_BIT5), (ucHoriEnable == _ENABLE) ? (_BIT5) : (0x00));
            ScalerSetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, ~(_BIT4), (ucVerEnable == _ENABLE) ? (_BIT4) : (0x00));
            break;
        case _OSD_POSITION_GLOBAL_4:
            ScalerSetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, ~(_BIT7), (ucHoriEnable == _ENABLE) ? (_BIT7) : (0x00));
            ScalerSetBit(P3A_CC_FRAME_CTRL_F_SU_DB_EN, ~(_BIT6), (ucVerEnable == _ENABLE) ? (_BIT6) : (0x00));
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : OSD Scale Up Boundary Condition
// Input Value  : enumRatio
// Output Value :
//--------------------------------------------------
void ScalerOsdScalingUpIptBoundaryCodition(EnumOsdFontScalingBoundaryType enumBoundary)
{
    ScalerSetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, ~(_BIT5 | _BIT4), ((BYTE)enumBoundary << 4));
}

//--------------------------------------------------
// Description  : OSD Scale Up - Interpolation
// Input Value  : enumDelaySel
// Input Value  : ucEn
// Output Value :
//--------------------------------------------------
void ScalerOsdScalingUpIptEn(EnumOsdPositionType enumDelaySel, BYTE ucEn)
{
    if(ucEn == _ENABLE)
    {
        WORD usTemp = 0;

        // Check Win2,3,4 Grid Function
        for(usTemp = 0; usTemp < 3; usTemp++)
        {
            // check Win enable
            ScalerOsdSetAddrWindow((0x100 * usTemp) + _P3A_F6_PT_0200_WIN_F_WIN2_ADR_00);
            if(ScalerGetBit(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, _BIT0) == _BIT0)
            {
                // check grid enable
                ScalerOsdSetAddrWindow((0x100 * usTemp) + _P3A_F6_PT_0220_WIN_F_WIN2_GRID_EN);
                if(ScalerGetBit(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, _BIT0) == _BIT0)
                {
                    return;
                }
            }
        }
    }

    switch(enumDelaySel)
    {
        case _OSD_POSITION_GLOBAL_1:
            ScalerSetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, ~(_BIT0), (ucEn == _ENABLE) ? (_BIT0) : (0x00));
            break;
        case _OSD_POSITION_GLOBAL_2:
            ScalerSetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, ~(_BIT1), (ucEn == _ENABLE) ? (_BIT1) : (0x00));
            break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_POSITION_GLOBAL_3:
            ScalerSetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, ~(_BIT2), (ucEn == _ENABLE) ? (_BIT2) : (0x00));
            break;
        case _OSD_POSITION_GLOBAL_4:
            ScalerSetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, ~(_BIT3), (ucEn == _ENABLE) ? (_BIT3) : (0x00));
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : OSD Scale Up Factor
// Input Value  : ucHFactor = H input/ H output * 2^6. ucVFactor = V input/ V output * 2^6
// Output Value :
// Note         :
//--------------------------------------------------
void ScalerOsdScalingUpIptFactor(BYTE ucHFactor, BYTE ucVFactor)
{
    // 1.x ~ 4
    if((ucHFactor >= _FOSD_SU_H_FACTOR_MIN) && (ucHFactor <= _HW_FOSD_SU_H_FACTOR_MAX))
    {
        ScalerSetBit(P3A_C3_FRAME_CTRL_F_IPT_H_FACTOR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucHFactor & 0x3F));
    }

    if((ucVFactor >= _HW_FOSD_SU_V_FACTOR_MIN) && (ucVFactor <= _HW_FOSD_SU_V_FACTOR_MAX))
    {
        ScalerSetBit(P3A_C2_FRAME_CTRL_F_IPT_V_FACTOR, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), (ucVFactor & 0x3F));
    }
}

//--------------------------------------------------
// Description  : OSD Scale Up End Position
// Input Value  : enumOsdPositionType
// Input Value  : usHEnd
// Input Value  : usHEnd
// Output Value :
//--------------------------------------------------
void ScalerOsdScalingUpIptSize(EnumOsdPositionType enumOsdPositionType, WORD usHEnd, WORD usVEnd)
{
    switch(enumOsdPositionType)
    {
        case _OSD_POSITION_GLOBAL_1:
            ScalerSetBit(P3A_C4_FRAME_CTRL_F_IPT_DLY1_H_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE((usHEnd + 1) & 0x3F00));
            ScalerSetByte(P3A_C5_FRAME_CTRL_F_IPT_DLY1_H_END_L, LOBYTE(usHEnd + 1));
            ScalerSetBit(P3A_C6_FRAME_CTRL_F_IPT_DLY1_V_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE((usVEnd + 1) & 0x3F00));
            ScalerSetByte(P3A_C7_FRAME_CTRL_F_IPT_DLY1_V_END_L, LOBYTE(usVEnd + 1));
            break;
        case _OSD_POSITION_GLOBAL_2:
            ScalerSetBit(P3A_C8_FRAME_CTRL_F_IPT_DLY2_H_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE((usHEnd + 1) & 0x3F00));
            ScalerSetByte(P3A_C9_FRAME_CTRL_F_IPT_DLY2_H_END_L, LOBYTE(usHEnd + 1));
            ScalerSetBit(P3A_CA_FRAME_CTRL_F_IPT_DLY2_V_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE((usVEnd + 1) & 0x3F00));
            ScalerSetByte(P3A_CB_FRAME_CTRL_F_IPT_DLY2_V_END_L, LOBYTE(usVEnd + 1));
            break;
#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
        case _OSD_POSITION_GLOBAL_3:
            ScalerSetBit(P3A_B8_FRAME_CTRL_F_IPT_DLY3_H_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE((usHEnd + 1) & 0x3F00));
            ScalerSetByte(P3A_B9_FRAME_CTRL_F_IPT_DLY3_H_END_L, LOBYTE(usHEnd + 1));
            ScalerSetBit(P3A_BA_FRAME_CTRL_F_IPT_DLY3_V_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE((usVEnd + 1) & 0x3F00));
            ScalerSetByte(P3A_BB_FRAME_CTRL_F_IPT_DLY3_V_END_L, LOBYTE(usVEnd + 1));
            break;
        case _OSD_POSITION_GLOBAL_4:
            ScalerSetBit(P3A_BC_FRAME_CTRL_F_IPT_DLY4_H_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE((usHEnd + 1) & 0x3F00));
            ScalerSetByte(P3A_BD_FRAME_CTRL_F_IPT_DLY4_H_END_L, LOBYTE(usHEnd + 1));
            ScalerSetBit(P3A_BE_FRAME_CTRL_F_IPT_DLY4_V_END_H, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), HIBYTE((usVEnd + 1) & 0x3F00));
            ScalerSetByte(P3A_BF_FRAME_CTRL_F_IPT_DLY4_V_END_L, LOBYTE(usVEnd + 1));
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Set OSD Transparency
// Input Value  : ucTransparency -> 0 ~ 255
// Output Value :
//--------------------------------------------------
void ScalerOsdSetTransparency(BYTE ucTransparency)
{
    // alpha_blending_level
    ScalerSetByte(P3A_2C_FRAME_CTRL_F_ALPHA_BLENDING_LEV, ucTransparency);
}

//--------------------------------------------------
// Description  : Set Osd transparency type
// Input Value  : enumOsdTransparencyType -> _OSD_TRANSPARENCY_DISABLE or _OSD_TRANSPARENCY_ONLY_WINDOW                      or
//                                           _OSD_TRANSPARENCY_ALL     or _OSD_TRANSPARENCY_WINDOW_AND_CHARACTER_BACKGROUND
// Output Value :
//--------------------------------------------------
void ScalerOsdSetTransparencyType(EnumOsdTransparencyType enumOsdTransparencyType)
{
    ScalerSetBit(P3A_2D_FRAME_CTRL_F_ALPHA_BLENDING_TYP, ~(_BIT7 | _BIT6), enumOsdTransparencyType << 6);
}

//--------------------------------------------------
// Description  : Set OSD Transparency for Timer Interrupt
// Input Value  : ucTransparency -> 0 ~ 255
// Output Value :
//--------------------------------------------------
void ScalerOsdSetTransparency_T0INT(BYTE ucTransparency)
{
    // alpha_blending_level
    ScalerSetByte_EXINT(P3A_2C_FRAME_CTRL_F_ALPHA_BLENDING_LEV, ucTransparency);
}

//--------------------------------------------------
// Description  : Set specific color blending
// Input Value  :     bEnable -> _ENABLE or _DISABLE
//                    ucIndex -> BlendingColor LUT index
// Output Value :
//--------------------------------------------------
void ScalerOsdSpecificColorBlending(bit bEnable, BYTE ucIndex)
{
#if(_HW_OSD_PALETTE_BIT == _8_BIT)
    ScalerSetByte(P3A_70_FRAME_CTRL_F_MATCH_COLOR_BLEND_COLOR, ucIndex);
#endif

#if(_HW_OSD_PALETTE_BIT == _6_BIT)
    // blend_matchcolor_bit = 1. Set Match Color blending color bit[5:0]
    // blend_matchcolor_bit = 0. Set Match Color blending color bit[3:0]
    ScalerSetBit(P3A_2E_FRAME_CTRL_F_MATCH_COLOR_BLEND, ~(_BIT7), (_BIT7));
    // Set Match Blending Color from 64-color LUT [5:0]
    ScalerSetBit(P3A_2E_FRAME_CTRL_F_MATCH_COLOR_BLEND, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (ucIndex & 0x03F) << 1);
#endif

    // Set Specific Match Color Blending Enable/Disable
    ScalerSetBit(P3A_2E_FRAME_CTRL_F_MATCH_COLOR_BLEND, ~_BIT0, bEnable);
}

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set OSD Extension
// Input Value  : ucExtension
// Output Value :
//--------------------------------------------------
void ScalerOsdSetExtension(BYTE ucExtension)
{
    ScalerSetByte(P3A_DD_OSD_TIMING_GEN_EXTENSION_FB_MAIN, 0x00);
    ScalerOsdSetFosdFBSeparateEn(_ENABLE);
    ScalerOsdSetFBFirstStartAddr(_OSD_BACK, _PANEL_DH_WIDTH / 2 - ucExtension);
    ScalerOsdSetFosdFBSeparateEn(_DISABLE);

#if(_GOSD_SUPPORT == _ON)
    ScalerGosdDispOsdSetExtension(ucExtension);
#endif
}
#endif

//--------------------------------------------------
// Description  : Set OSD Mouse Fun
// Input Value  : bEn
// Output Value :
//--------------------------------------------------
void ScalerOsdSetMouseFunEnable(bit bEn)
{
    // Check OSD Scale up
    if((ScalerGetBit(P3A_C0_FRAME_CTRL_F_OSD_SU_CRTL, (_BIT1 | _BIT0)) != 0x00) && (bEn == _ENABLE))
    {
        return;
    }

    ScalerSetBit(P3A_30_FRAME_CTRL_F_FONT_PRIORITY, ~(_BIT7 | _BIT6), ((bEn == _ENABLE) ? (_BIT7 | _BIT6) : (0x00)));
}

/*
//--------------------------------------------------
// example
//--------------------------------------------------
    ScalerOsdSpecificColorBlending(_ENABLE,15);
*/

