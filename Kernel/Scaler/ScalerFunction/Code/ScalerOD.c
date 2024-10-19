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
// ID Code      : ScalerOD.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_OD__

#include "ScalerFunctionInclude.h"
#include "OD/ScalerOD.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_OD_FUNCTION == _ON)

StructOdPathInfo code tOdPathInfo[_HW_OD_PATH_COUNT] =
{
    {_OD_PATH_M1, _HW_OD_M1_PAGE},
#if(_HW_OD_PATH_COUNT > 1)
    {_OD_PATH_M2, _HW_OD_M2_PAGE},
#endif
#if(_HW_OD_PATH_COUNT > 2)
    {_OD_PATH_M3, _HW_OD_M3_PAGE},
    {_OD_PATH_M4, _HW_OD_M4_PAGE},
#endif
};

StructOdParam code tOdCmpParam[] =
{
#if(_HW_OD_COMP_GEN < _OD_COMP_GEN_1)
    // OD_BIT_10X   CMP_METHOD              PRE_SOURCE_RES              CUR_SOURCE_RES              CMP_MODE                DECMP_MODE      NR_TH  EST_VALUE
    // |                |                       |                               |                       |                       |               |  |
    { 0U,   _OD_CMP_METHOD_DEFAULT,     _OD_PRE_SRC_RES_DEFAULT,    _OD_CUR_SRC_RES_DEFAULT,    _OD_CMP_MODE_DEFAULT,   _OD_DECMP_MODE_DEFAULT, 0, 0}, // _OD_PARAM_OFF
#if(_OD_6_0_AND_4_5_BIT_MODE_IMPROVE_OPTION == _OFF)
    {45U,   _OD_CMP_METHOD_SP_1X4,      _OD_PRE_SRC_RES_6_BIT,      _OD_CUR_SRC_RES_6_BIT,      _OD_CMP_MODE_AVG,       _OD_DECMP_MODE_DUP,     4, 4}, // _OD_PARAM_4_5_BPP
    {60U,   _OD_CMP_METHOD_SP_1X4,      _OD_PRE_SRC_RES_8_BIT,      _OD_CUR_SRC_RES_8_BIT,      _OD_CMP_MODE_AVG,       _OD_DECMP_MODE_DUP,     2, 2}, // _OD_PARAM_6_0_BPP
#else
    {45U,   _OD_CMP_METHOD_SP_1X4,      _OD_PRE_SRC_RES_6_BIT,      _OD_CUR_SRC_RES_6_BIT,      _OD_CMP_MODE_AVG,       _OD_DECMP_MODE_INTERP,  4, 4}, // _OD_PARAM_4_5_BPP
    {60U,   _OD_CMP_METHOD_SP_1X2,      _OD_PRE_SRC_RES_4_BIT,      _OD_CUR_SRC_RES_5_BIT,      _OD_CMP_MODE_AVG,       _OD_DECMP_MODE_INTERP,  5, 5}, // _OD_PARAM_6_0_BPP
#endif
    {75U,   _OD_CMP_METHOD_SP_1X2,      _OD_PRE_SRC_RES_5_BIT,      _OD_CUR_SRC_RES_5_BIT,      _OD_CMP_MODE_AVG,       _OD_DECMP_MODE_DUP,     4, 4}, // _OD_PARAM_7_5_BPP
#else // _HW_OD_COMP_GEN >= _OD_COMP_GEN_1
    // OD_BIT_10X   CMP_METHOD              PRE_SOURCE_RES              CUR_SOURCE_RES              CMP_MODE                DECMP_MODE      NR_TH  EST_VALUE
    // |                |                       |                               |                       |                       |               |  |
    { 0U,   _OD_CMP_METHOD_DEFAULT,     _OD_PRE_SRC_RES_DEFAULT,    _OD_CUR_SRC_RES_DEFAULT,    _OD_CMP_MODE_DEFAULT,   _OD_DECMP_MODE_DEFAULT, 0, 0}, // _OD_PARAM_OFF
    {45U,   _OD_CMP_METHOD_PF_1X4,      _OD_PRE_SRC_RES_6_BIT,      _OD_CUR_SRC_RES_6_BIT,      _OD_CMP_MODE_DEFAULT,   _OD_DECMP_MODE_DEFAULT, 4, 4}, // _OD_PARAM_4_5_BPP
    {60U,   _OD_CMP_METHOD_PF_1X4,      _OD_PRE_SRC_RES_8_BIT,      _OD_CUR_SRC_RES_8_BIT,      _OD_CMP_MODE_DEFAULT,   _OD_DECMP_MODE_DEFAULT, 2, 2}, // _OD_PARAM_6_0_BPP
    {75U,   _OD_CMP_METHOD_SP_1X2,      _OD_PRE_SRC_RES_5_BIT,      _OD_CUR_SRC_RES_5_BIT,      _OD_CMP_MODE_AVG,       _OD_DECMP_MODE_DUP,     4, 4}, // _OD_PARAM_7_5_BPP
#endif
};

EnumODParamIndex code tODParamChkList[] =
{
    _OD_PARAM_7_5_BPP,
    _OD_PARAM_6_0_BPP,
    _OD_PARAM_4_5_BPP,
};

#if(_HW_OD_COMP_GEN >= _OD_COMP_GEN_1)
BYTE code tPF_1x4_Filter[] =
{
    1, 2, 5, 11, 18, 27, 27, 18, 11, 5, 2, 1
};
#endif

#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
#if(_OD_FUNCTION == _ON)

BYTE g_ucODTableValidBit;
BYTE g_ucODLUTBankNumBackup;
BYTE *g_pucODLUTBackup;
EnumODParamIndex g_enumODParamIndex;
#if(_FRC_SUPPORT == _ON)
BYTE g_ucODCurrDynamicStatus;
#endif

#if(_OD_BY_POSITION_SUPPORT == _ON)
BYTE g_ucODByPosTableBankNumBackup;
BYTE *g_pucODByPosTableBackup;
#endif

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
DWORD g_pulOD3BlkStartAddr[3];
#endif

#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_OD_FUNCTION == _ON)
//--------------------------------------------------
// Description  : OD on/off
// Input Value  : enumOn --> _FUNCTION_ON/_FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerODEnable(EnumFunctionOnOFF enumOn)
{
    //=================
    // Enable OD
    //=================
    if((enumOn == _FUNCTION_ON) && (GET_OD_USE_PARAM() != _OD_PARAM_OFF))
    {
#if(_FRC_SUPPORT == _ON)
        DebugMessageFRC("OD_ON", 0);

        if(GET_DYNAMIC_OD_STATUS(GET_DISPLAY_MODE(), GET_FS_ACTIVE_INFO_DVF_SELECT()) == _ENABLE)
        {
            DebugMessageFRC("Dynamic OD", GET_FS_ACTIVE_INFO_DVF_SELECT());
            // Enable DEN_START IRQ
            SET_OD_CURR_DYNAMIC_STATUS(_ENABLE);
            ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_DYNAMIC_OD, _ENABLE);
        }
        else
        {
            DebugMessageFRC("Static OD", 0);

            // Enable OD function, disable DEN_START IRQ
            SET_OD_CURR_DYNAMIC_STATUS(_DISABLE);
            ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_DYNAMIC_OD, _DISABLE);
            ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
        }
#else
        // Enable OD function
        ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
#endif
    }
    //=================
    // Disable OD
    //=================
    else
    {
        bit bWaitTillRWFinish = (ScalerODGetRealtimeEnableStatus() == _ON) ? _TRUE : _FALSE;

#if(_FRC_SUPPORT == _ON)
        DebugMessageFRC("OD_OFF", 0);

        SET_OD_CURR_DYNAMIC_STATUS(_DISABLE);
        ScalerGlobalInterruptProcForDDomain(_GLOBAL_INT_DDOMAIN_DYNAMIC_OD, _DISABLE);
#endif
        // Disable OD function
        ScalerSetBit(P3_A1_LS_CTRL0, ~(_BIT7 | _BIT6), 0x00);

        if(bWaitTillRWFinish == _TRUE)
        {
            // Wait 2 DVS to ensure that OD last write/read operations are finished
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
            ScalerTimerWaitForDDomainEvent(_EVENT_DVS);
        }
    }
}

//--------------------------------------------------
// Description  : Get OD parameter set
//                according to available memory space & BW.
// Input Value  : Remaining space & BW
// Output Value : Serial num of OD parameter set
//--------------------------------------------------
EnumODParamIndex ScalerODGetParamSet(DWORD ulMemoryRemainSpace, WORD usMemoryRemainBW)
{
    BYTE ucParamI = 0;
    WORD usODUseSpace = 0;
    WORD usODUseBW = 0;
    StructMemoryBWUsageParam stMemBWParam;

    DebugMessageMemory("4. Remaining BW for OD", usMemoryRemainBW);
    DebugMessageMemory("4. Remaining Space for OD", ulMemoryRemainSpace);

    if((_PANEL_PIXEL_TYPE == _PANEL_PIXEL_OLED) || (_PANEL_PIXEL_TYPE == _PANEL_PIXEL_MICRO_LED))
    {
        // Disable OD for emissive panel
        return _OD_PARAM_OFF;
    }

    //=============================================
    // Get memory BW parameters
    //=============================================
    ScalerMDomainGetMemBWParam(&stMemBWParam);

    //=============================================
    // Check if OD 7.5/6.0/4.5 bit mode is avaliable
    //=============================================
    for(ucParamI = 0; ucParamI < (sizeof(tODParamChkList) / sizeof(tODParamChkList[0])); ucParamI++)
    {
        BYTE ucODBit10x = GET_OD_BIT_RATE(tODParamChkList[ucParamI]);

        if(tODParamChkList[ucParamI] > _MTP_OD_ACCEPT_MAX_PARAM)
        {
            continue;
        }

        if(CHECK_OD_PARAM_AVAILABLE(tODParamChkList[ucParamI]) == _FALSE)
        {
            continue;
        }
        usODUseSpace = ScalerMDomainODCalculateMemoryUseSpace(ucODBit10x);
        usODUseBW = ScalerMDomainODCalculateMemoryUseBW(ucODBit10x, &stMemBWParam);

#if(_DEBUG_MESSAGE_MEMORY == _ON)
        if(_TRUE)
        {
            SBYTE pchODBWStr[] = "4. 7_5_bit OD BW";
            SBYTE pchODSizeStr[] = "4. 7_5_bit OD Size";
            pchODBWStr[3] = '0' + (ucODBit10x / 10);
            pchODBWStr[5] = '0' + (ucODBit10x % 10);
            pchODSizeStr[3] = '0' + (ucODBit10x / 10);
            pchODSizeStr[5] = '0' + (ucODBit10x % 10);

            DebugMessageMemory(pchODBWStr, usODUseBW);
            DebugMessageMemory(pchODSizeStr, usODUseSpace);
        }
#endif
        if((usODUseSpace <= ulMemoryRemainSpace) &&
           (usODUseBW <= usMemoryRemainBW))
        {
            return tODParamChkList[ucParamI];
        }
    }

    //=============================================
    // Otherwise, OD off
    //=============================================
    return _OD_PARAM_OFF;
}

//--------------------------------------------------
// Description  : OD Front/Back register separate ctrl
// Input Value  : Enable/Disable
// Output Value : None
//--------------------------------------------------
void ScalerODSetFrontBackRegSeparate(bit bEnable)
{
    bEnable = bEnable;

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
    if(ScalerGlobalGetFrontBackStatus(_FRONT_BACK_IN_D_DOMAIN_ALL_PATH) == _TRUE)
    {
        if(bEnable == _ENABLE)
        {
            // Enable OD Front(M1, M2)/Back(S1, S2) register separation
            ScalerSetBit(P3_90_LS_FRONT_BACK_REG_SEP_CTRL, ~_BIT7, _BIT7);
        }
        else // bEnable == _DISABLE
        {
            // Disable OD Front(M1, M2)/Back(S1, S2) register separation
            ScalerSetBit(P3_90_LS_FRONT_BACK_REG_SEP_CTRL, ~_BIT7, 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : OD memory usage per path
// Input Value  : ODBit10x (unit: 0.1 bit)
// Output Value : memory usage (unit: memory access unit)
//--------------------------------------------------
DWORD ScalerODGetMemoryUsagePerPath(BYTE ucODBit10x)
{
    //=============================================
    // Calculate memory usage of each OD path
    //=============================================
    WORD usBGHwidth = _PANEL_DH_WIDTH;
    WORD usBGVheight = _PANEL_DV_HEIGHT;

#if(_PANEL_ASYMMETRIC == _ON)
    usBGHwidth += _PANEL_ASYMMETRIC_DUMMY_NUM_LEFT + _PANEL_ASYMMETRIC_DUMMY_NUM_RIGHT;
    usBGVheight += _PANEL_ASYMMETRIC_DUMMY_NUM_TOP + _PANEL_ASYMMETRIC_DUMMY_NUM_BOTTOM;
#endif

    // OD H_Width per path
    WORD usODPathHWidth = CEILING_OF_INT_DIVISION(usBGHwidth, _OD_PATH_WIDTH_DIVISOR);
    WORD usODPathVHeight = CEILING_OF_INT_DIVISION(usBGVheight, _OD_PATH_HEIGHT_DIVISOR);

    // OD-use-space per path (in bit)
    PDATA_DWORD(0) = ((DWORD)CEILING(usODPathHWidth, _OD_PIXEL_PER_COMP)) * usODPathVHeight * ucODBit10x / 10;

    // OD-use-space per path (padded to mutiples of memory access unit)
    return CEILING(PDATA_DWORD(0), _OD_MEM_RW_FIFO_UNIT_BIT);
}

//--------------------------------------------------
// Description  : Get start address of each OD path
// Input Value  : MemSizePerODPath(in row), Pointer to StartAddrList(in row)
// Output Value : None
//--------------------------------------------------
void ScalerODGetPathStartAddr(WORD usPathSizeInRow, WORD *pusRowAddrList)
{
    BYTE ucIndex = 0;
    WORD usStartRowAddr = _OD_PATH_INIT_ROW;

    // Additional Buffer: 1 row
    usPathSizeInRow += 1;

#if(_FW_OD_PATH_START_ADDR_DESCENDING == _TRUE)
    if(_FW_MEM_CLIENT_SHARE_ADDR_SPACE == _FALSE)
    {
        usStartRowAddr -= usPathSizeInRow;
    }
#endif

    for(ucIndex = 0; ucIndex < _HW_OD_PATH_COUNT; ucIndex++)
    {
        EnumOdPath enumCurrPath = GET_OD_DATA_PATH(ucIndex);

        if(CHK_OD_EVERY_PATH(enumCurrPath) == _TRUE)
        {
#if(_FW_OD_PATH_START_ADDR_DESCENDING == _TRUE)
            if(_FW_MEM_CLIENT_SHARE_ADDR_SPACE == _TRUE)
            {
                usStartRowAddr -= usPathSizeInRow;
            }
#endif

            pusRowAddrList[ucIndex] = usStartRowAddr;

#if(_FW_OD_PATH_START_ADDR_DESCENDING == _FALSE)
            if(_FW_MEM_CLIENT_SHARE_ADDR_SPACE == _TRUE)
            {
                usStartRowAddr += usPathSizeInRow;
            }
#endif
        }
    }

#if(_FW_OD_PATH_START_ADDR_DESCENDING == _FALSE)
    if(_FW_MEM_CLIENT_SHARE_ADDR_SPACE == _FALSE)
    {
        usStartRowAddr += usPathSizeInRow;
    }
#endif

    pusRowAddrList[_HW_OD_PATH_COUNT] = usStartRowAddr;
}

//--------------------------------------------------
// Description  : OD memory & FIFO setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODSetMemoryAndFIFO(void)
{
    BYTE ucIndex = 0;
    // Memory usage of each OD path
    DWORD ulOdUseSpacePerPath_Bit = ScalerODGetMemoryUsagePerPath(GET_OD_USE_BIT());
    WORD usOdUseSpacePerPath_Row =
        ulOdUseSpacePerPath_Bit /
        _FW_MEM_CLIENT_MEMORY_BIT_NUM /
        (_MEMORY_COL_PER_BANK * _MEMORY_BANK) +
        _OD_PATH_MEMORY_SPACE_ROW_MARGIN;

    WORD pusRowAddrList[_HW_OD_PATH_COUNT + 1] = {0};

    //=============================================
    // Calculate buffer R/W length, number and remain
    //=============================================
    // Buffer R/W length
    WORD usOdRwLen_BufUnit = _OD_MEM_RW_DEFAULT_LEN;
    // (Number x Length + Remain) x _OD_MEM_RW_BUF_UNIT_BIT = Total size
    DWORD ulOdUseSpacePerPath_BufUnit = ulOdUseSpacePerPath_Bit / _OD_MEM_RW_BUF_UNIT_BIT;
    PDATA_DWORD(0) = ScalerMemoryCalculateNumberAndRemain(ulOdUseSpacePerPath_BufUnit, usOdRwLen_BufUnit, 1);
    WORD usOdRwNum = LOWORD(PDATA_DWORD(0));
    WORD usOdRwRemain_BufUnit = HIWORD(PDATA_DWORD(0));

    // If R/W_Remain exceeds HW limitation, reset RW_Length to Max RW_Remain.
    if(usOdRwRemain_BufUnit > _HW_OD_MEM_RW_MAX_REMAIN)
    {
        usOdRwLen_BufUnit = _HW_OD_MEM_RW_MAX_REMAIN;
        PDATA_DWORD(0) = ScalerMemoryCalculateNumberAndRemain(ulOdUseSpacePerPath_BufUnit, usOdRwLen_BufUnit, 1);
        usOdRwNum = LOWORD(PDATA_DWORD(0));
        usOdRwRemain_BufUnit = HIWORD(PDATA_DWORD(0)); // RW_Remain <= RW_Length.
    }

#if(_OD_MEMORY_BW_CTRL_SUPPORT == _ON)
    //=============================================
    // Update BW Ctrl client info
    //=============================================
    StructBwCtrlClientInfo stBwCtrlInfo = {};
    ScalerODBwCtrlGetClientInfo(&stBwCtrlInfo, usOdRwLen_BufUnit);
#endif

    //=============================================
    // Set memory start address
    //=============================================
    ScalerODGetPathStartAddr(usOdUseSpacePerPath_Row, pusRowAddrList);

    ScalerODSetFrontBackRegSeparate(_ENABLE);

    for(ucIndex = 0; ucIndex < _HW_OD_PATH_COUNT; ucIndex++)
    {
        EnumOdPath enumCurrPath = GET_OD_DATA_PATH(ucIndex);
        BYTE ucCurrPage = GET_OD_REG_PAGE(ucIndex);

        if(CHK_OD_EVERY_PATH(enumCurrPath) == _TRUE)
        {
            PDATA_DWORD(0) = (DWORD)pusRowAddrList[ucIndex] << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM;
            PDATA_DWORD(0) += (DWORD)ScalerODGetShiftBankOffset(ucCurrPage);
            SET_PAGED_BIT(ucCurrPage, P3_DA_LS_DDR_START_ADDR_MSB, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), ((PDATA_DWORD(0) >> 24) & 0x0F));
            SET_PAGED_BYTE(ucCurrPage, P3_DB_LS_DDR_START_ADDR_H, ((PDATA_DWORD(0) >> 16) & 0xFF));
            SET_PAGED_BYTE(ucCurrPage, P3_DC_LS_DDR_START_ADDR_M, ((PDATA_DWORD(0) >> 8) & 0xFF));
            SET_PAGED_BYTE(ucCurrPage, P3_DD_LS_DDR_START_ADDR_L, (PDATA_DWORD(0) & 0xFF));

#if(_OD_MEMORY_BW_CTRL_SUPPORT == _ON)
            // Set BW Ctrl register
            ScalerMemorySetBwCtrl(_MEM_CLIENT_OD_W, ucIndex, &stBwCtrlInfo);
            ScalerMemorySetBwCtrl(_MEM_CLIENT_OD_R, ucIndex, &stBwCtrlInfo);
#endif
        }
    }

    ScalerODSetFrontBackRegSeparate(_DISABLE);

    //=============================================
    // Set FIFO water levels & buffer setting
    //=============================================
    // Trigger write requests when there is at least 1-burst-data in FIFO.
    WORD usOdWrWtlvl_FifoUnit = (usOdRwLen_BufUnit / 2);
    // Trigger read requests when there is enough space for 2-burst-data in FIFO.
    WORD usOdRdWtlvl_FifoUnit = (usOdRwLen_BufUnit);

    if(usOdRdWtlvl_FifoUnit >= (_HW_OD_MEM_FIFO_MIN_SIZE / 2))
    {
        // If the size of 2-burst-data exceeds half of Read_FIFO,
        // halve waterlevel to keep the Read_FIFO at least half-full.
        usOdRdWtlvl_FifoUnit /= 2;
    }

    for(ucIndex = 0; ucIndex < _HW_OD_PATH_COUNT; ucIndex++)
    {
        EnumOdPath enumCurrPath = GET_OD_DATA_PATH(ucIndex);
        BYTE ucCurrPage = GET_OD_REG_PAGE(ucIndex);

        if(CHK_OD_MAIN_PATH(enumCurrPath) == _TRUE)
        {
            // Set Write_FIFO Water Level
            SET_PAGED_BYTE(ucCurrPage, P3_D0_LS_DDR_FIFO_WTLVL_W_H, HIBYTE(usOdWrWtlvl_FifoUnit));
            SET_PAGED_BYTE(ucCurrPage, P3_D1_LS_DDR_FIFO_WTLVL_W_L, LOBYTE(usOdWrWtlvl_FifoUnit));

            // Set Read_FIFO Water Level
            SET_PAGED_BYTE(ucCurrPage, P3_D2_LS_DDR_FIFO_WTLVL_R_H, HIBYTE(usOdRdWtlvl_FifoUnit));
            SET_PAGED_BYTE(ucCurrPage, P3_D3_LS_DDR_FIFO_WTLVL_R_L, LOBYTE(usOdRdWtlvl_FifoUnit));

            // Set buffer RW Number
            SET_PAGED_BYTE(ucCurrPage, P3_D4_LS_DDR_FIFO_RW_NUM_H, HIBYTE(usOdRwNum));
            SET_PAGED_BYTE(ucCurrPage, P3_D5_LS_DDR_FIFO_RW_NUM_L, LOBYTE(usOdRwNum));

            // Set buffer RW Length
            SET_PAGED_BYTE(ucCurrPage, P3_D6_LS_DDR_FIFO_RW_LEN_H, HIBYTE(usOdRwLen_BufUnit));
            SET_PAGED_BYTE(ucCurrPage, P3_D7_LS_DDR_FIFO_RW_LEN_L, LOBYTE(usOdRwLen_BufUnit));

            // Set buffer RW Remain
            SET_PAGED_BYTE(ucCurrPage, P3_D8_LS_DDR_FIFO_RW_REMAIN_H, HIBYTE(usOdRwRemain_BufUnit));
            SET_PAGED_BYTE(ucCurrPage, P3_D9_LS_DDR_FIFO_RW_REMAIN_L, LOBYTE(usOdRwRemain_BufUnit));
        }
    }
}

//--------------------------------------------------
// Description  : Load OD LUT
// Input Value  :
//                pODTable -> OD TABLE Pointer
//                ucBankNum -> Bank number
//                bLUTMode -> OD LUT Type (8bit/10bit LUT)
// Output Value : None
//--------------------------------------------------
void ScalerODLoadLUT(BYTE *pucODTable, BYTE ucBankNum, bit bLUTMode)
{
    if((GET_OD_TABLE_VALID_STATUS() == _TRUE) && (GET_OD_TABLE_LAST_ADDRESS() == pucODTable) && (GET_OD_TABLE_LAST_BANK_NUM() == ucBankNum))
    {
        return;
    }

    // Enable LUT access
#if(_HW_OD_BY_POSITION_GEN == _OD_BY_POSITION_GEN_0)
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7 | _BIT6), _BIT7);
#else
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~_BIT7, _BIT7);
#endif

    ScalerBurstWrite(pucODTable, ((bLUTMode == _OD_10BIT_LUT) ? _OD_10BIT_LUT_LENGTH : _OD_8BIT_LUT_LENGTH), ucBankNum, P3_C0_LS_LUT_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);

    // Disable LUT access
#if(_HW_OD_BY_POSITION_GEN == _OD_BY_POSITION_GEN_0)
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7 | _BIT6), 0x00);
#else
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~_BIT7, 0x00);
#endif

    SET_OD_TABLE_LAST_ADDRESS(pucODTable);
    SET_OD_TABLE_LAST_BANK_NUM(ucBankNum);
    SET_OD_TABLE_VALID_STATUS();
}

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Set OD Data
// Input Value  :
// Output Value : None
//--------------------------------------------------
void ScalerODAdjust(EnumODAdjustMode enumODAdjustMode, StructODSetting *pstODSetting)
{
    switch(pstODSetting->enumODMode)
    {
        case _OD_OFF:
            break;

        case _OD_USER:
            switch(enumODAdjustMode)
            {
                case _OD_ADJUST_GAIN:
                    ScalerODAdjustDeltaGain(pstODSetting->unODData.stODUserData.ucDeltaGain);
                    break;

                case _OD_ADJUST_GAIN_ODLUT: // adjust all
                    ScalerODAdjustDeltaGain(pstODSetting->unODData.stODUserData.ucDeltaGain);
                    ScalerODLoadLUT(pstODSetting->unODData.stODUserData.stODTableInfo.pucTable, pstODSetting->unODData.stODUserData.stODTableInfo.ucBank, _HW_OD_LUT_MODE);
                    break;

                default:
                    break;
            }
            break;

#if(_OD_BY_POSITION_SUPPORT == _ON)
        case _OD_USER_BYPOS:
            switch(enumODAdjustMode)
            {
                case _OD_ADJUST_GAIN:
                    ScalerODAdjustDeltaGain(pstODSetting->unODData.stODUserByPosData.ucDeltaGain);
                    break;

                case _OD_ADJUST_BYPOS:
                    ScalerODAdjustODByPos(&(pstODSetting->unODData.stODUserByPosData));
                    break;

                case _OD_ADJUST_GAIN_ODLUT_BYPOS: // adjust all
                    ScalerODAdjustDeltaGain(pstODSetting->unODData.stODUserByPosData.ucDeltaGain);
                    ScalerODLoadLUT(pstODSetting->unODData.stODUserByPosData.stODTableInfo.pucTable, pstODSetting->unODData.stODUserByPosData.stODTableInfo.ucBank, _HW_OD_LUT_MODE);
                    ScalerODAdjustODByPos(&(pstODSetting->unODData.stODUserByPosData));
                    break;

                default:
                    break;
            }
            break;
#endif

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get OD support
// Input Value  :
// Output Value :
//--------------------------------------------------
bit ScalerODGetSupportStatus(void)
{
    return ((GET_OD_USE_BIT() == _OFF) ? (_OFF) : (_ON));
}

//--------------------------------------------------
// Description  : OD initialization setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODInitial(void)
{
    if(GET_OD_USE_PARAM() != _OD_PARAM_OFF)
    {
        ScalerODEnable(_FUNCTION_OFF);

        // Set OD compression settings
        ScalerODCompressionSetting();

        // Set OD memory & FIFO settings
        ScalerODSetMemoryAndFIFO();
    }
}

//--------------------------------------------------
// Description  : Adjust OD delta gain
// Input Value  : Delta gain
// Output Value : None
//--------------------------------------------------
void ScalerODAdjustDeltaGain(BYTE ucValue)
{
    ScalerSetByte(P3_A3_DELTA_GAIN, ucValue);
}

//--------------------------------------------------
// Description  : OD compression, level estimation, noise reduction setting
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODCompressionSetting(void)
{
    StructOdParam stOdParam;
    stOdParam = tOdCmpParam[GET_OD_USE_PARAM()];

    // Enable level estimation, delta gain. Set previous frame source pixel resolution
    ScalerSetByte(P3_A1_LS_CTRL0, (_BIT5 | _BIT3 | stOdParam.enumPreSrcRes));

    // Current path: enable compression, set compression mode/method
    ScalerSetByte(P3_B0_LS_FRAME0, (stOdParam.enumCmpMode | _BIT4 | stOdParam.enumCmpMethod));

    // Enable previous/current frame decompression, set decompression mode
    ScalerSetByte(P3_B1_LS_FRAME1, (_BIT7 | _BIT3 | stOdParam.enumDecmpMode));

    // Set current frame source pixel resolution
    ScalerSetByte(P3_B2_LS_FRAME2, (stOdParam.enumCurSrcRes));

    // Set level estimation range, level estimation gain
    ScalerSetByte(P3_B3_LS_FRAME4, (_OD_EST_RANGE_BYPASS | 0x00));

    // Set level estimation value
    ScalerSetByte(P3_B4_LS_FRAME5, (stOdParam.ucLvlEstValue & 0x3F));

    // Set OD apply on full window
    ScalerODHLWinSetting(_HLW_FULL_WINDOW, _DB_APPLY_NO_POLLING);

    // Set noise reduction threshold
    {
        BYTE ucNrEn = (stOdParam.ucNRThreshold > 1) ? _ENABLE : _DISABLE;
        BYTE ucNrThd_B_3 = 0;
        BYTE ucNrThd_B_2_0 = 0;

        if(ucNrEn == _ENABLE)
        {
            ucNrThd_B_3 = ((stOdParam.ucNRThreshold - 1) & 0x08) >> 3;
            ucNrThd_B_2_0 = (stOdParam.ucNRThreshold - 1) & 0x07;
        }
        ScalerSetByte(P3_A2_LS_CTRL1, ((ucNrThd_B_3 << 5) | (ucNrEn << 4) | _BIT3 | ucNrThd_B_2_0));
    }

    // Clear flag
    ScalerSetByte(P3_A4_LS_STATUS0, _BIT0);

#if(_HW_OD_COMP_GEN >= _OD_COMP_GEN_1)
    //--------------------------------------------------
    // Pixel_Filter_1x4 compression method parameters
    //--------------------------------------------------
    // PF_1x4 Filter width W (5 <= W <= 12)
    static_assert
    (
        (GET_TABLE_ELEMENT_NUM(tPF_1x4_Filter) >= _OD_PF_1X4_MIN_FILTER_WIDTH) &&
        (GET_TABLE_ELEMENT_NUM(tPF_1x4_Filter) <= _OD_PF_1X4_MAX_FILTER_WIDTH),
        "Invalid OD tPF_1x4_Filter Width"
    );

    if(stOdParam.enumCmpMethod == _OD_CMP_METHOD_PF_1X4)
    {
        BYTE ucFilterWidth = GET_TABLE_ELEMENT_NUM(tPF_1x4_Filter);
        // Set filter width even/odd mode
        ScalerSetBit(P3_EF_LS_4PIXEL_NEW_METHOD_CTRL, ~(_BIT0), ((ucFilterWidth % 2 == 0) ? 0x00 : _BIT0));

        // Set Filter entry register
        BYTE ucFilterBegin = CEILING_OF_INT_DIVISION((_OD_PF_1X4_MAX_FILTER_WIDTH - ucFilterWidth), 2);
        BYTE ucFilterEnd = ucFilterBegin + ucFilterWidth;

        if(ucFilterBegin != 0)
        {
            for(BYTE ucIndex = 0; ucIndex < ucFilterBegin; ++ucIndex)
            {
                ScalerSetByte((P3_F0_LS_4PIXEL_NEW_METHOD_PARAM_00 + ucIndex), 0x00);
            }
        }

        for(BYTE ucIndex = ucFilterBegin; ucIndex < ucFilterEnd; ++ucIndex)
        {
            ScalerSetByte((P3_F0_LS_4PIXEL_NEW_METHOD_PARAM_00 + ucIndex), tPF_1x4_Filter[ucIndex - ucFilterBegin]);
        }
        for(BYTE ucIndex = ucFilterEnd; ucIndex < _OD_PF_1X4_MAX_FILTER_WIDTH; ++ucIndex)
        {
            ScalerSetByte((P3_F0_LS_4PIXEL_NEW_METHOD_PARAM_00 + ucIndex), 0x00);
        }
    }
#endif
}

//--------------------------------------------------
// Description  : OD HLW type select
// Input Value  : enumHLWType --> _FULL_WINDOW, _INSIDE_WINDOW or _OUTSIDE_WINDOW
// Output Value : None
//--------------------------------------------------
void ScalerODHLWinSetting(EnumHLWType enumHLWType, EnumDBApply enumDBApply)
{
    // Select OD HLW type
    switch(enumHLWType)
    {
        default:
        case _HLW_FULL_WINDOW:
            ScalerSetBit(P3_A6_LS_CTRL2, ~(_BIT7 | _BIT6), 0x00);
            break;

        case _HLW_INSIDE_WINDOW:
            ScalerSetBit(P3_A6_LS_CTRL2, ~(_BIT7 | _BIT6), (_BIT6));
            break;

        case _HLW_OUTSIDE_WINDOW:
            ScalerSetBit(P3_A6_LS_CTRL2, ~(_BIT7 | _BIT6), (_BIT7));
            break;
    }

    ScalerGlobalDDomainDBApply(_D_DOMAIN_DB_APPLY_REGION_EITHER, enumDBApply);
}

#if(_OD_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get BW Ctrl client info
// Input Value  : Pointer to client info, R/W length
// Output Value : None
//--------------------------------------------------
void ScalerODBwCtrlGetClientInfo(StructBwCtrlClientInfo *pstInfo, WORD usOdRwLen_BufUnit)
{
    BYTE code ucTimeThdPercent = 100; // For fine tune usage
    BYTE code ucReqThdFixedValue = 0x01U;

    pstInfo->bEnable = _TRUE;
    pstInfo->enumMode = _BW_CTRL_REQ_MODE;
    pstInfo->ulReqThd = ucReqThdFixedValue; // "A" value
    {
        WORD usHActive = CEILING_OF_INT_DIVISION(_PANEL_DH_WIDTH, _OD_PATH_WIDTH_DIVISOR);
        WORD usHTotal = CEILING_OF_INT_DIVISION(_PANEL_DH_TOTAL, _OD_PATH_WIDTH_DIVISOR);
        DWORD ulMPll_MHz = _MEMORY_PLL_CLOCK;
        DWORD ulPixClk_KHz = GET_D_CLK_FREQ() / _OD_PATH_WIDTH_DIVISOR / _OD_PATH_HEIGHT_DIVISOR;
        WORD usBitRate10x = GET_OD_USE_BIT();
        DWORD ulTValue = 0; // "T" value
        DWORD ulDenominator = 0;

        usHActive = CEILING(usHActive, _OD_PIXEL_PER_COMP);

        // A (unit: request) & T (unit: mclk_cycle)
        // A = 1,
        //
        // T
        // = (LEN * 64 * MPLL_freq) / ((HActive / HTotal) * pixel_rate * bit)
        // = (LEN * 64 * MPLL_freq) / ((HActive * bit) * pixel_rate / HTotal)
        ulDenominator = ScalerGlobalComputeDwordMulDiv(((DWORD)usHActive * usBitRate10x), ulPixClk_KHz, usHTotal) / 1000 / 10;
        ulTValue = ScalerGlobalComputeDwordMulDiv(((DWORD)usOdRwLen_BufUnit * _OD_MEM_RW_BUF_UNIT_BIT * ulMPll_MHz), ucTimeThdPercent, ulDenominator) / 100;

        pstInfo->ulTimeThd = ulTValue;
    }
}
#endif

//--------------------------------------------------
// Description  : Get OD real-time enable status
// Input Value  : None
// Output Value : _ON/_OFF
//--------------------------------------------------
bit ScalerODGetRealtimeEnableStatus(void)
{
#if(_FRC_SUPPORT == _ON)
    if(GET_OD_CURR_DYNAMIC_STATUS() == _ENABLE)
    {
        return _ON;
    }

#endif
    return (ScalerGetBit(P3_A1_LS_CTRL0, (_BIT7 | _BIT6)) == (_BIT7 | _BIT6)) ? _ON : _OFF;
}


//--------------------------------------------------
// Description  : Get OD delta gain
// Input Value  : None
// Output Value : Delta gain
//--------------------------------------------------
BYTE ScalerODGetDeltaGain(void)
{
    return ScalerGetByte(P3_A3_DELTA_GAIN);
}

//--------------------------------------------------
// Description  : Get OD use param
// Input Value  : None
// Output Value : use param
//--------------------------------------------------
EnumODParamIndex ScalerODGetUseParam(void)
{
    return GET_OD_USE_PARAM();
}

#if(_OD_BY_POSITION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : OD by-position on/off
// Input Value  : enumOn --> _FUNCTION_ON/_FUNCTION_OFF
// Output Value : None
//--------------------------------------------------
void ScalerODByPosEnable(EnumFunctionOnOFF enumOn)
{
#if(_HW_OD_BY_POSITION_GEN == _OD_BY_POSITION_GEN_0)
    if((enumOn == _FUNCTION_ON) && (GET_OD_USE_PARAM() != _OD_PARAM_OFF))
    {
        ScalerSetBit(P3_B5_LS_BYPOS0, ~_BIT7, 0x80);
    }
    else
    {
        ScalerSetBit(P3_B5_LS_BYPOS0, ~_BIT7, 0x00);
    }
#endif
}

#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _OFF)
//--------------------------------------------------
// Description  : Adjust By-position OD parameter
// Input Value  : User OD data
// Output Value : None
//--------------------------------------------------
void ScalerODAdjustODByPos(StructODUserByPosData *pstODUserByPosData)
{
    BYTE ucTemp = 0x00;
    BYTE *pucODByPosTable = pstODUserByPosData->stODByPosTableInfo.pucTable;
    BYTE ucBank = pstODUserByPosData->stODByPosTableInfo.ucBank;

    ucTemp = ucTemp;

    if((GET_OD_BYPOS_TABLE_LAST_ADDRESS() == pucODByPosTable) &&
       (GET_OD_BYPOS_TABLE_LAST_BANK_NUM() == ucBank))
    {
        return;
    }

    // Turn off by-position OD
    ScalerODByPosEnable(_FUNCTION_OFF);

#if(_HW_OD_BY_POSITION_GEN == _OD_BY_POSITION_GEN_0)
    // Set region size & last region mode
    ucTemp = pucODByPosTable[0] & (_BIT2);
    ucTemp = ucTemp | (BYTE)(pstODUserByPosData->b2RegionSize << 5);
    ScalerSetBit(P3_B5_LS_BYPOS0, ~(_BIT6 | _BIT5 | _BIT2), ucTemp);

    // Set GLUT mode & gain round
    ucTemp = pucODByPosTable[1] & (_BIT6 | _BIT5 | _BIT4 | _BIT3);
    ScalerSetBit(P3_B6_LS_BYPOS1, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3), ucTemp);

    // Set GLUT gain base
    ucTemp = pucODByPosTable[2] & (0x7F);
    ScalerSetBit(P3_B7_LS_GAIN_BASE, ~(0x7F), ucTemp);

    // Set GLUT gain slope
    ucTemp = pucODByPosTable[3] & (0x3F);
    ScalerSetBit(P3_B8_LS_GAIN_SLOPE, ~(0x3F), ucTemp);

    // Load GLUT
    // Switch access mode to GLUT and Enable GLUT access
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    ScalerBurstWrite((pucODByPosTable + 4), _OD_GLUT_LENGTH, ucBank, P3_C0_LS_LUT_DATA, _BURSTWRITE_DATA_COMMON, _BURSTWRITE_FROM_FLASH);
    // Disable LUT access
    ScalerSetBit(P3_BF_LS_LUT_CTRL, ~(_BIT7 | _BIT6), 0x00);
#endif

    // Set by-position OD enable status
    if(pstODUserByPosData->b1ODByPosEnable == _TRUE)
    {
        ScalerODByPosEnable(_FUNCTION_ON);
    }
    else
    {
        ScalerODByPosEnable(_FUNCTION_OFF);
    }
    SET_OD_BYPOS_TABLE_LAST_ADDRESS(pucODByPosTable);
    SET_OD_BYPOS_TABLE_LAST_BANK_NUM(ucBank);
}
#endif // end of #if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _OFF)
#endif // end of #if(_OD_BY_POSITION_SUPPORT == _ON)

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Set OD address in 3-block-toggle case
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerODSetThreeBlockAddress(void)
{
    // 24->60Hz / 24->72Hz uses HW auto 3 block toggle
    if(GET_FRC_3BLOCK_TOGGLE_STATUS() == _ENABLE)
    {
        DWORD ulBlockAddr = 0;
        DWORD ulTotalMemSpace = 0;
        DWORD ulODUseSpace = 0;

        ulTotalMemSpace = (DWORD)_MEMORY_ROW << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM;
        ulODUseSpace = (ScalerODGetMemoryUsagePerPath(GET_OD_USE_BIT()) / _FW_MEM_CLIENT_MEMORY_BIT_NUM / (_MEMORY_COL_PER_BANK * _MEMORY_BANK) + _OD_PATH_MEMORY_SPACE_ROW_MARGIN) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM;

        //=========================================
        // Set OD 1st Address
        //=========================================
        // Get 1st Write Address
        ulBlockAddr = _FRC_R_2ND_BLOCK_STA_ADDR;
        g_pulOD3BlkStartAddr[0] = (ulBlockAddr + ulTotalMemSpace - ulODUseSpace) % ulTotalMemSpace;

        //=========================================
        // Set OD 2nd Address
        //=========================================
        // Get 2nd Write Address
        ulBlockAddr = _FRC_R_3RD_BLOCK_STA_ADDR;
        g_pulOD3BlkStartAddr[1] = (ulBlockAddr + ulTotalMemSpace - ulODUseSpace) % ulTotalMemSpace;

        //=========================================
        // Set OD 3rd Address
        //=========================================
        // Get 3rd Write Address
        ulBlockAddr = _FRC_R_1ST_BLOCK_STA_ADDR;
        g_pulOD3BlkStartAddr[2] = (ulBlockAddr + ulTotalMemSpace - ulODUseSpace) % ulTotalMemSpace;

        DebugMessageFRC("OD 3Blk-1st Addr", g_pulOD3BlkStartAddr[0]);
        DebugMessageFRC("OD 3Blk-2nd Addr", g_pulOD3BlkStartAddr[1]);
        DebugMessageFRC("OD 3Blk-3rd Addr", g_pulOD3BlkStartAddr[2]);
    }
    else
    {
        g_pulOD3BlkStartAddr[0] = (DWORD)_OD_PATH_INIT_ROW << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM;
        g_pulOD3BlkStartAddr[1] = g_pulOD3BlkStartAddr[0];
        g_pulOD3BlkStartAddr[2] = g_pulOD3BlkStartAddr[0];
    }
}
#endif
//--------------------------------------------------
// Description  : Get Bank Offset By OD Page
// Input Value  : BYTE ucCurrPage
// Output Value : WORD bankoffset
//--------------------------------------------------
WORD ScalerODGetShiftBankOffset(BYTE ucCurrPage)
{
    switch(ucCurrPage)
    {
        default:
        case _HW_OD_M1_PAGE:
            return _OD_M1_BANK_OFFSET;

#if(_HW_OD_PATH_COUNT > 1)
        case _HW_OD_M2_PAGE:
            return _OD_M2_BANK_OFFSET;
#endif

#if(_HW_OD_PATH_COUNT > 2)
        case _HW_OD_M3_PAGE:
            return _OD_M3_BANK_OFFSET;

        case _HW_OD_M4_PAGE:
            return _OD_M4_BANK_OFFSET;
#endif
    }
}
#endif // End of #if(_OD_SUPPORT == _ON)
