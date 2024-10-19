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
// ID Code      : Scaler3DDI.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "3DDI/Scaler3DDI.h"

#if(_COLOR_IP_3DDI == _ON)

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
Struct3DDIStatus g_pst3DDIstatus[2];

//****************************************************************************
// CODE TABLES
//****************************************************************************
DWORD code tIntraTable[][6] =
{
    // SD
    {0x6148e7ff, 0x00223c1e, 0x00080608, 0x000f3241, 0x04280c0a, 0x0006080c},
    // HD
    {0x6148f7ff, 0x1e223c1e, 0x00080408, 0x000f3241, 0x0a280c0a, 0x00040810}
};

DWORD code tMaTable[][6] =
{
    {0x00019614, 0x14140a0a, 0x05040101, 0x140a060c, 0x32141018, 0x00020200}
};

DWORD code tFilmTable[][6] =
{
    // SD 60HZ
    {0x523c1612, 0x28141514, 0x88781388, 0x28140f14, 0x883207d0, 0x54021428},
    // HD 60HZ
    {0x523c2634, 0x28141514, 0x88781388, 0x28140f14, 0x883207d0, 0x54021428},
    // SD 50HZ
    {0x523c1610, 0x28141514, 0x88781388, 0x28140f14, 0x883207d0, 0x54021428},
    // HD 50HZ
    {0x523c1a10, 0x28141514, 0x88781388, 0x28140f14, 0x883207d0, 0x54021428},
    // DTV 576i
    {0x523c0d10, 0x28141514, 0x88781388, 0x28140f14, 0x883207d0, 0x54021428}
};

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Get path number of 3DDI by input data path
// Input Value  : enum3DDIInputPath
// Output Value : path number of 3DDI
//--------------------------------------------------
BYTE Scaler3DDIGetPath(EnumInputDataPath enum3DDIInputPath)
{
    BYTE uc3DDIPath = _HW_3DDI_PATH_NONE;
    switch(enum3DDIInputPath)
    {
        case _INPUT_PATH_M1:
        case _INPUT_PATH_M1_M2:
        case _INPUT_PATH_M1_M2_S1_S2:
#if(_HW_3DDI_1ST_PATH == _HW_3DDI_PATH_0)
            uc3DDIPath = _HW_3DDI_1ST_PATH;
#elif(_HW_3DDI_2ND_PATH == _HW_3DDI_PATH_0)
            uc3DDIPath = _HW_3DDI_2ND_PATH;
#else
            uc3DDIPath = _HW_3DDI_PATH_NONE;
#endif
            break;

        case _INPUT_PATH_S1_S2:
        case _INPUT_PATH_S2:
        case _INPUT_PATH_S3_S4:
#if(_HW_3DDI_1ST_PATH == _HW_3DDI_PATH_3)
            uc3DDIPath = _HW_3DDI_1ST_PATH;
#elif(_HW_3DDI_2ND_PATH == _HW_3DDI_PATH_3)
            uc3DDIPath = _HW_3DDI_2ND_PATH;
#else
            uc3DDIPath = _HW_3DDI_PATH_NONE;
#endif
            break;

        default:
            uc3DDIPath = _HW_3DDI_PATH_NONE;
            break;
    }

    return uc3DDIPath;
}


//--------------------------------------------------
// Description  : Get register page of current path
// Input Value  : enum3DDIInputPath
// Output Value : register page offset
//--------------------------------------------------
DWORD Scaler3DDIGetRegisterPageOfffset(EnumInputDataPath enum3DDIInputPath)
{
    BYTE uc3DDIPath = Scaler3DDIGetPath(enum3DDIInputPath);
    if(uc3DDIPath == _HW_3DDI_PATH_3)
    {
        return 0x03000000;
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : Get 3DDI index
// Input Value  : enum3DDIInputPath
// Output Value : 3DDI index
//--------------------------------------------------
BYTE Scaler3DDIGetIndex(EnumInputDataPath enum3DDIInputPath)
{
    BYTE uc3DDIPath = Scaler3DDIGetPath(enum3DDIInputPath);
    if(uc3DDIPath == _HW_3DDI_2ND_PATH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------
// Description  : calculate MAX Memory size which 3DDI cost
// Input Value  : none
// Output Value : MAX Memory size
//--------------------------------------------------
DWORD Scaler3DDICalMaxMemorySize(void)
{
    BYTE ucPathNum = 0;
    DWORD ulMemSize = 0;

#if(_3DDI_MAX_HWIDTH <= _3DDI_5A_MAX_HWIDTH)
    ulMemSize = (GET_DEFAULT_FRAME_USE_MEMORY_ROW(((DWORD)_3DDI_MAX_HWIDTH) * _3DDI_MAX_VHEIGHT * _3DDI_DATA_BIT_NUM) + _3DDI_MEM_ROW_MARGIN) * 4 + (GET_DEFAULT_FRAME_USE_MEMORY_ROW(((DWORD)_3DDI_MAX_HWIDTH) * _3DDI_MAX_VHEIGHT * _3DDI_INFO_BIT_NUM) + _3DDI_MEM_ROW_MARGIN) * 2;
#else
    ulMemSize = (GET_DEFAULT_FRAME_USE_MEMORY_ROW(((DWORD)_3DDI_MAX_HWIDTH) * _3DDI_MAX_VHEIGHT * _3DDI_DATA_BIT_NUM) + _3DDI_MEM_ROW_MARGIN) * 2 + (GET_DEFAULT_FRAME_USE_MEMORY_ROW(((DWORD)_3DDI_MAX_HWIDTH) * _3DDI_MAX_VHEIGHT * _3DDI_INFO_BIT_NUM) + _3DDI_MEM_ROW_MARGIN) * 2;
#endif

#if(_HW_3DDI_1ST_PATH != _HW_3DDI_PATH_NONE)
    ucPathNum += 1;
#endif
#if(_HW_3DDI_2ND_PATH != _HW_3DDI_PATH_NONE)
    ucPathNum += 1;
#endif
    ulMemSize = ulMemSize * ucPathNum;
    return ulMemSize;
}

//--------------------------------------------------
// Description  : calculate MAX Memory bankwidth which 3DDI cost
// Input Value  : none
// Output Value : MAX Memory bandwidth
//--------------------------------------------------
DWORD Scaler3DDICalMaxMemoryBW(void)
{
    BYTE ucPathNum = 0;
    DWORD ulMemBW = 0;

#if(_3DDI_MAX_HWIDTH <= _3DDI_5A_MAX_HWIDTH)
    ulMemBW = GET_DWORD_MUL_DIV(((DWORD)_3DDI_MAX_HWIDTH * _3DDI_MAX_VTOTAL), ((DWORD)_3DDI_MAX_FRAME_RATE * _3DDI_DATA_BIT_NUM * 5), 1000000) +
              GET_DWORD_MUL_DIV(((DWORD)_3DDI_MAX_HWIDTH * _3DDI_MAX_VTOTAL), ((DWORD)_3DDI_MAX_FRAME_RATE * _3DDI_INFO_BIT_NUM * 3), 1000000);
#else
    ulMemBW = GET_DWORD_MUL_DIV(((DWORD)_3DDI_MAX_HWIDTH * _3DDI_MAX_VTOTAL), ((DWORD)_3DDI_MAX_FRAME_RATE * _3DDI_DATA_BIT_NUM * 3), 1000000) +
              GET_DWORD_MUL_DIV(((DWORD)_3DDI_MAX_HWIDTH * _3DDI_MAX_VTOTAL), ((DWORD)_3DDI_MAX_FRAME_RATE * _3DDI_INFO_BIT_NUM * 3), 1000000);
#endif

#if(_HW_3DDI_1ST_PATH != _HW_3DDI_PATH_NONE)
    ucPathNum += 1;
#endif
#if(_HW_3DDI_2ND_PATH != _HW_3DDI_PATH_NONE)
    ucPathNum += 1;
#endif
    ulMemBW = ulMemBW * ucPathNum;
    return ulMemBW / _MEMORY_BUS_WIDTH;
}

//--------------------------------------------------
// Description  : Enable/Disable 3DDI Local DB
// Input Value  : unPageOffset, bEnable
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetDB(DWORD ulPageOffset, bit bEnable)
{
    if(bEnable == _ON)
    {
        Scaler32SetBit(PB00744_90_DB_REG_CTL + ulPageOffset, ~_BIT1, _BIT1);
    }
    else
    {
        Scaler32SetBit(PB00744_90_DB_REG_CTL + ulPageOffset, ~_BIT1, 0);
    }
}

//--------------------------------------------------
// Description  : Enable/Disable 3DDI
// Input Value  : unPageOffset, bEnable
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetEnable(DWORD ulPageOffset, bit bEnable)
{
    if(bEnable == _ON)
    {
        Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~(_BIT22 | _BIT21), _BIT22 | _BIT21);
    }
    else
    {
        Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~(_BIT22 | _BIT21), _BIT22);
    }
}

//--------------------------------------------------
// Description  : Set 3DDI Control
// Input Value  : unPageOffset, bEnable
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetCtrl(DWORD ulPageOffset)
{
    // turn off auto field run
    Scaler32SetBit(PB0074C_04_IM_DI_TIMING_ADD_CONTROL0 + ulPageOffset, ~_BIT25, 0);

    // set di output from di
    Scaler32SetBit(PB0074C_04_IM_DI_TIMING_ADD_CONTROL0 + ulPageOffset, ~_BIT20, _BIT20);

    // turn on auto mode
    Scaler32SetBit(PB0074C_04_IM_DI_TIMING_ADD_CONTROL0 + ulPageOffset, ~(_BIT21), _BIT21);
}

//--------------------------------------------------
// Description  : Set 3DDI 3A or5A
// Input Value  : unPageOffset
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetIf3Aor5A(DWORD ulPageOffset)
{
    WORD usHwidth = GET_INPUT_TIMING_HWIDTH();

    if(usHwidth <= _3DDI_5A_MAX_HWIDTH)
    {
        Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~(_BIT4 | _BIT3), _BIT4);
    }
    else
    {
        Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~(_BIT4 | _BIT3), _BIT4 | _BIT3);
    }
}

//--------------------------------------------------
// Description  : Set 3DDI DMA setting
// Input Value  : unPageOffset, enum3DDIInputPath
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetMemory(DWORD ulPageOffset, EnumInputDataPath enum3DDIInputPath)
{
    WORD usHwidth = GET_INPUT_TIMING_HWIDTH();
    WORD usVHeight = GET_INPUT_TIMING_VHEIGHT();

    {
        // set Timing Related regs
        WORD usHSWidth = GET_INPUT_TIMING_HSYNCWIDTH();
        WORD usHBackPorch = GET_ACTIVE_H_START() - usHSWidth;
        WORD usHBlkSize = GET_INPUT_TIMING_HTOTAL() - GET_INPUT_TIMING_HWIDTH();
        WORD usVBackPorch = GET_INPUT_TIMING_VSTART() - GET_INPUT_TIMING_VSYNCWIDTH();

        Scaler32SetBit(PB0074C_04_IM_DI_TIMING_ADD_CONTROL0 + ulPageOffset, ~(_BIT(17, 8)), (((DWORD)usHBackPorch) << 8) & _BIT(17, 8));
        Scaler32SetBit(PB0074C_04_IM_DI_TIMING_ADD_CONTROL0 + ulPageOffset, ~(_BIT(7, 0)), (((DWORD)usVBackPorch) << 0) & _BIT(7, 0));
        Scaler32SetDWord(PB0074C_08_IM_DI_TIMING_ADD_CONTROL1 + ulPageOffset, (((DWORD)usHwidth) << 16) + usVHeight);
        Scaler32SetBit(PB00740_0C_IM_DI_ACTIVE_WINDOW_CONTROL + ulPageOffset, ~(_BIT(30, 20)), (((DWORD)usHwidth) << 20) & _BIT(30, 20));
        Scaler32SetBit(PB00740_0C_IM_DI_ACTIVE_WINDOW_CONTROL + ulPageOffset, ~(_BIT(19, 10)), (((DWORD)usVHeight) << 10) & _BIT(19, 10));
        Scaler32SetBit(PB00740_0C_IM_DI_ACTIVE_WINDOW_CONTROL + ulPageOffset, ~(_BIT(9, 0)), (((DWORD)usHBlkSize) << 0) & _BIT(9, 0));
        Scaler32SetBit(PB00741_A8_TR2TO1 + ulPageOffset, ~(_BIT(10, 0)), (((DWORD)usHBackPorch) << 0) & _BIT(10, 0));
    }

    {
        DWORD ulDatLength = 0;
        DWORD ulInfoLength = 0;
        DWORD uladdr = 0;
        // mstart must be start of a memory row
        ulDatLength = GET_DEFAULT_FRAME_USE_MEMORY_ROW(((DWORD)usHwidth) * usVHeight * _3DDI_DATA_BIT_NUM) + _3DDI_MEM_ROW_MARGIN;
        ulInfoLength = GET_DEFAULT_FRAME_USE_MEMORY_ROW(((DWORD)usHwidth) * usVHeight * _3DDI_INFO_BIT_NUM) + _3DDI_MEM_ROW_MARGIN;

        if(Scaler3DDIGetPath(enum3DDIInputPath) == _HW_3DDI_2ND_PATH)
        {
            uladdr = ((((GET_3DDI_START_ADDRESS() + GET_3DDI_END_ADDRESS()) / 2) >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) + 1) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM;
            uladdr += _3DDI_2ND_BANK_OFFSET;
        }
        else
        {
            uladdr = GET_3DDI_START_ADDRESS();
            uladdr += _3DDI_1ST_BANK_OFFSET;
        }

        // set DATA memory mstart
        Scaler32SetDWord((PB00744_00_DI_DATMEMORYSTARTADD1 + ulPageOffset), (uladdr << 3));
        uladdr = uladdr + (ulDatLength << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
        Scaler32SetDWord((PB00744_04_DI_DATMEMORYSTARTADD2 + ulPageOffset), (uladdr << 3));
        uladdr = uladdr + (ulDatLength << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
        if(usHwidth <= _3DDI_5A_MAX_HWIDTH)
        {
            Scaler32SetDWord((PB00744_08_DI_DATMEMORYSTARTADD3 + ulPageOffset), (uladdr << 3));
            uladdr = uladdr + (ulDatLength << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
            Scaler32SetDWord((PB00744_0C_DI_DATMEMORYSTARTADD4 + ulPageOffset), (uladdr << 3));
            uladdr = uladdr + (ulDatLength << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
        }
        // set INFO memory mstart
        Scaler32SetDWord((PB00744_10_DI_INFMEMORYSTARTADD1 + ulPageOffset), (uladdr << 3));
        uladdr = uladdr + (ulInfoLength << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);
        Scaler32SetDWord((PB00744_14_DI_INFMEMORYSTARTADD2 + ulPageOffset), (uladdr << 3));
        uladdr = uladdr + (ulInfoLength << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM);

#if(_3DDI_MEMORY_BW_CTRL_SUPPORT == _ON)
        //=============================================
        // Update BW Ctrl client info & Set BW Ctrl register
        //=============================================
        Scaler3DDISetBwCtrl(enum3DDIInputPath);
#endif
    }

    {
        DWORD ulNum = 0;
        DWORD ulRemain = 0;

        // set 10 bit mode
        Scaler32SetBit(PB00740_04_COLOR_RECOVERY_OPTION + ulPageOffset, ~_BIT30, _BIT30);
        Scaler32SetBit(PB00740_04_COLOR_RECOVERY_OPTION + ulPageOffset, ~_BIT29, _BIT29);

        // set data len, num, remain, water
        ulNum = ((DWORD)usHwidth * usVHeight) * _3DDI_DATA_BIT_NUM / 128 / _3DDI_MEM_LENGTH;
        ulRemain = ((DWORD)usHwidth * usVHeight) * _3DDI_DATA_BIT_NUM - ulNum * _3DDI_MEM_LENGTH * 128;
        if(ulRemain == 0)
        {
            ulNum = ulNum - 1;
            ulRemain = _3DDI_MEM_LENGTH;
        }
        else
        {
            if(ulRemain % 128 == 0)
            {
                ulRemain = ulRemain / 128;
            }
            else
            {
                ulRemain = ulRemain / 128 + 1;
            }
        }

        if(usHwidth <= _3DDI_5A_MAX_HWIDTH)
        {
            Scaler32SetDWord(PB00744_18_DDR_RDATDMA_WTLENNUM + ulPageOffset, (((DWORD)(128 - _3DDI_MEM_LENGTH)) << 24) + (((DWORD)_3DDI_MEM_LENGTH) << 16) + ulNum);
        }
        else
        {
            Scaler32SetDWord(PB00744_18_DDR_RDATDMA_WTLENNUM + ulPageOffset, (((DWORD)(256 - _3DDI_MEM_LENGTH)) << 24) + (((DWORD)_3DDI_MEM_LENGTH) << 16) + ulNum);
        }

        Scaler32SetDWord(PB00744_1C_DDR_WDATDMA_WTLENNUM + ulPageOffset, (((DWORD)_3DDI_MEM_LENGTH) << 24) + (((DWORD)_3DDI_MEM_LENGTH) << 16) + ulNum);
        Scaler32SetBit(PB00744_20_DDR_DATDMA_RM + ulPageOffset, ~(_BIT(14, 8)), (((DWORD)ulRemain) << 8) & _BIT(14, 8));
        Scaler32SetBit(PB00744_20_DDR_DATDMA_RM + ulPageOffset, ~(_BIT(6, 0)), (((DWORD)ulRemain) << 0) & _BIT(6, 0));

        // set info len, num, remain, water
        ulNum = ((DWORD)usHwidth * usVHeight) * _3DDI_INFO_BIT_NUM / 128 / _3DDI_MEM_LENGTH;
        ulRemain = ((DWORD)usHwidth * usVHeight) * _3DDI_INFO_BIT_NUM - ulNum * _3DDI_MEM_LENGTH * 128;
        if(ulRemain == 0)
        {
            ulNum = ulNum - 1;
            ulRemain = _3DDI_MEM_LENGTH;
        }
        else
        {
            if(ulRemain % 128 == 0)
            {
                ulRemain = ulRemain / 128;
            }
            else
            {
                ulRemain = ulRemain / 128 + 1;
            }
        }

        Scaler32SetDWord(PB00744_24_DDR_RINFDMA_WTLENNUM + ulPageOffset, (((DWORD)_3DDI_MEM_LENGTH) << 24) + (((DWORD)_3DDI_MEM_LENGTH) << 16) + ulNum);
        Scaler32SetDWord(PB00744_28_DDR_WINFDMA_WTLENNUM + ulPageOffset, (((DWORD)_3DDI_MEM_LENGTH) << 24) + (((DWORD)_3DDI_MEM_LENGTH) << 16) + ulNum);
        Scaler32SetBit(PB00744_2C_DDR_INFDMA_RM + ulPageOffset, ~(_BIT(14, 8)), (((DWORD)ulRemain) << 8) & _BIT(14, 8));
        Scaler32SetBit(PB00744_2C_DDR_INFDMA_RM + ulPageOffset, ~(_BIT(6, 0)), (((DWORD)ulRemain) << 0) & _BIT(6, 0));
    }
}

//--------------------------------------------------
// Description  : Set 3DDI Intra setting
// Input Value  : unPageOffset, Intra table
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetIntra(DWORD ulPageOffset, DWORD pulIntraTable[6])
{
    if(pulIntraTable == (DWORD *)_NULL_POINTER)
    {
        return;
    }

    Scaler32SetDWord(PB00748_E0_IM_DI_NINTRA_CONTROL + ulPageOffset, pulIntraTable[0]);
    Scaler32SetDWord(PB00748_E4_IM_DI_NINTRA_LOWPASS_SOURCE + ulPageOffset, pulIntraTable[1]);
    Scaler32SetDWord(PB00748_E8_IM_DI_NINTRA_SEARCH_DIR_LIMIT + ulPageOffset, pulIntraTable[2]);
    Scaler32SetDWord(PB00748_EC_IM_DI_NINTRA_INTERSECTION_TH + ulPageOffset, pulIntraTable[3]);
    Scaler32SetDWord(PB00748_F0_IM_DI_NINTRA_1ST_2ND_YDIFF_TH + ulPageOffset, pulIntraTable[4]);
    Scaler32SetDWord(PB00748_F4_IM_DI_NINTRA_HIGH_FREQ_LIMIT + ulPageOffset, pulIntraTable[5]);
}

//--------------------------------------------------
// Description  : Set 3DDI Ma setting
// Input Value  : unPageOffset, Ma table
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetMaTable(DWORD ulPageOffset, DWORD pulMaTab[6])
{
    if(pulMaTab == (DWORD *)_NULL_POINTER)
    {
        return;
    }

    Scaler32SetDWord(PB00740_90_IM_DI_MA_OTHERS_TH + ulPageOffset, pulMaTab[0]);
    Scaler32SetDWord(PB00740_94_IM_DI_MA_SAWTOOTH_TH + ulPageOffset, pulMaTab[1]);
    Scaler32SetDWord(PB00740_80_IM_DI_MA_FRAME_MOTION_TH_A + ulPageOffset, pulMaTab[2]);
    Scaler32SetDWord(PB00740_84_IM_DI_MA_FRAME_MOTION_TH_B + ulPageOffset, pulMaTab[3]);
    Scaler32SetDWord(PB00740_88_IM_DI_MA_FRAME_MOTION_TH_C + ulPageOffset, pulMaTab[4]);
    Scaler32SetDWord(PB00740_8C_IM_DI_MA_FIELD_TEETH_TH_A + ulPageOffset, pulMaTab[5]);
}

//--------------------------------------------------
// Description  : Set 3DDI Ma sub-function enable
// Input Value  : unPageOffset
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetMaCtrl(DWORD ulPageOffset)
{
    Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~_BIT27, _BIT27);
    Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~_BIT28, _BIT28);
    Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~(_BIT2 | _BIT1 | _BIT0), _BIT2 | _BIT0);
    Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~(_BIT6 | _BIT5), _BIT6 | _BIT5);
}

//--------------------------------------------------
// Description  : Set 3DDI Ma HFD enable
// Input Value  : unPageOffset
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetMaHFD(DWORD ulPageOffset, bit bEnable)
{
    if(bEnable == _ON)
    {
        Scaler32SetBit(PB00741_EC_IM_DI_HFD_CONTROL + ulPageOffset, ~_BIT24, _BIT24);
    }
    else
    {
        Scaler32SetBit(PB00741_EC_IM_DI_HFD_CONTROL + ulPageOffset, ~_BIT24, 0);
    }
}

//--------------------------------------------------
// Description  : Set 3DDI Ma BTR enable
// Input Value  : unPageOffset
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetMaBTR(DWORD ulPageOffset, bit bEnable)
{
    if(bEnable == _ON)
    {
        if(GET_INPUT_TIMING_HWIDTH() <= _3DDI_5A_MAX_HWIDTH)
        {
            Scaler32SetBit(PB00742_08_IM_DI_BTR_CONTROL + ulPageOffset, ~(_BIT8 | _BIT1 | _BIT0), _BIT8 | _BIT0);
            Scaler32SetBit(PB00742_20_IM_DI_BER_TEMPORAL_CONTROL + ulPageOffset, ~_BIT0, _BIT0);
        }
        else
        {
            Scaler32SetBit(PB00742_08_IM_DI_BTR_CONTROL + ulPageOffset, ~(_BIT8 | _BIT1 | _BIT0), _BIT8 | _BIT1 | _BIT0);
            Scaler32SetBit(PB00742_20_IM_DI_BER_TEMPORAL_CONTROL + ulPageOffset, ~_BIT0, 0);
        }
    }
    else
    {
        Scaler32SetBit(PB00742_08_IM_DI_BTR_CONTROL + ulPageOffset, ~_BIT0, 0);
        Scaler32SetBit(PB00742_20_IM_DI_BER_TEMPORAL_CONTROL + ulPageOffset, ~_BIT0, 0);
    }
}

//--------------------------------------------------
// Description  : Set 3DDI Film table
// Input Value  : unPageOffset, Film table
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetFilmTable(DWORD ulPageOffset, DWORD pulFilmTab[6])
{
    if(pulFilmTab == (DWORD *)_NULL_POINTER)
    {
        return;
    }

    Scaler32SetDWord(PB00740_A0_IM_DI_FILM_SAWTOOTH_FILMFRAME_TH + ulPageOffset, pulFilmTab[0]);
    Scaler32SetDWord(PB00740_A4_IM_DI_FILM_STATIC_SUM_TH + ulPageOffset, pulFilmTab[1]);
    Scaler32SetDWord(PB00740_A8_IM_DI_FILM_FIELD_JUDGE_TH + ulPageOffset, pulFilmTab[2]);
    Scaler32SetDWord(PB00740_AC_IM_DI_FILM_STATIC_SUM_SUB_TH + ulPageOffset, pulFilmTab[3]);
    Scaler32SetDWord(PB00740_B0_IM_DI_FILM_FIELD_JUDGE_SUB_TH + ulPageOffset, pulFilmTab[4]);
    Scaler32SetDWord(PB00740_B4_IM_DI_FILM_MOTION_SUM_TH + ulPageOffset, pulFilmTab[5]);
}

//--------------------------------------------------
// Description  : Set 3DDI Film setting
// Input Value  : unPageOffset
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetFilm(DWORD ulPageOffset)
{
    Scaler32SetBit(PB00740_00_IM_DI_CONTROL + ulPageOffset, ~(_BIT(16, 11)), _BIT(16, 11));
    Scaler32SetDWord(PB00740_A0_IM_DI_FILM_SAWTOOTH_FILMFRAME_TH + ulPageOffset, 0x523c0c10);
    Scaler32SetDWord(PB00740_A4_IM_DI_FILM_STATIC_SUM_TH + ulPageOffset, 0x28141514);
    Scaler32SetDWord(PB00740_A8_IM_DI_FILM_FIELD_JUDGE_TH + ulPageOffset, 0x88781388);
    Scaler32SetDWord(PB00740_AC_IM_DI_FILM_STATIC_SUM_SUB_TH + ulPageOffset, 0x28140f14);
    Scaler32SetDWord(PB00740_B0_IM_DI_FILM_FIELD_JUDGE_SUB_TH + ulPageOffset, 0x883207d0);

    if((GET_INPUT_TIMING_HWIDTH() == _3DDI_5A_MAX_HWIDTH) && (GET_INPUT_TIMING_VHEIGHT() == 288))
    {
        Scaler3DDISetFilmTable(ulPageOffset, tFilmTable[4]);
    }
    else if(GET_INPUT_TIMING_HWIDTH() < _3DDI_5A_MAX_HWIDTH)
    {
        if((GET_INPUT_TIMING_VFREQ() > 550) && (GET_INPUT_TIMING_VFREQ() < 650))
        {
            Scaler3DDISetFilmTable(ulPageOffset, tFilmTable[0]);
        }
        else if((GET_INPUT_TIMING_VFREQ() > 450) && (GET_INPUT_TIMING_VFREQ() < 550))
        {
            Scaler3DDISetFilmTable(ulPageOffset, tFilmTable[2]);
        }
    }
    else if(GET_INPUT_TIMING_HWIDTH() > _3DDI_5A_MAX_HWIDTH)
    {
        if((GET_INPUT_TIMING_VFREQ() > 550) && (GET_INPUT_TIMING_VFREQ() < 650))
        {
            Scaler3DDISetFilmTable(ulPageOffset, tFilmTable[1]);
        }
        else if((GET_INPUT_TIMING_VFREQ() > 450) && (GET_INPUT_TIMING_VFREQ() < 550))
        {
            Scaler3DDISetFilmTable(ulPageOffset, tFilmTable[3]);
        }
    }
}

#if(_COLOR_IP_COLOR_CONVERT == _ON)
//--------------------------------------------------
// Description  : Set 3DDI RGB2YUV setting
// Input Value  : enumDisplayRegion, enumInputPort
// Output Value : none
//--------------------------------------------------
void Scaler3DDISetRGB2YUV(EnumDisplayRegion enumDisplayRegion, EnumInputPort enumInputPort, EnumColorSpace enumColorSpace)
{
    EnumInputDataPath enum3DDIInputPath = ScalerRegionGetInputDataPath(enumDisplayRegion);
    if(GET_3DDI_STATUS(enum3DDIInputPath) == _TRUE)
    {
        BYTE ucIColorConvCtrlValue = 0;
        BYTE pucIColorConvTable[_COLOR_CONV_RGB2YUV_TABLE_SIZE];
        DWORD ulPageOffset = Scaler3DDIGetRegisterPageOfffset(enum3DDIInputPath);

        // Get RGB2YUV setting table
        bit bIColorConvTableExist = ScalerColorSpaceGetRgb2YuvTable(enumDisplayRegion, enumInputPort, enumColorSpace, pucIColorConvTable, &ucIColorConvCtrlValue);

        if(bIColorConvTableExist == _TRUE)
        {
            // Set matrix
            Scaler32SetDWord(PB0074C_84_IM_DI_RGB2YCC_H00 + ulPageOffset, (((DWORD)pucIColorConvTable[3]) << 11) + (((DWORD)pucIColorConvTable[4]) << 3) + ((pucIColorConvTable[21] & 0x70) >> 4));
            Scaler32SetDWord(PB0074C_88_IM_DI_RGB2YCC_H01 + ulPageOffset, (((DWORD)pucIColorConvTable[5]) << 11) + (((DWORD)pucIColorConvTable[6]) << 3) + ((pucIColorConvTable[21] & 0x07) >> 0));
            Scaler32SetDWord(PB0074C_8C_IM_DI_RGB2YCC_H02 + ulPageOffset, (((DWORD)pucIColorConvTable[7]) << 11) + (((DWORD)pucIColorConvTable[8]) << 3) + ((pucIColorConvTable[22] & 0x70) >> 4));
            Scaler32SetDWord(PB0074C_90_IM_DI_RGB2YCC_H10 + ulPageOffset, (((DWORD)pucIColorConvTable[9]) << 11) + (((DWORD)pucIColorConvTable[10]) << 3) + ((pucIColorConvTable[22] & 0x07) >> 0));
            Scaler32SetDWord(PB0074C_94_IM_DI_RGB2YCC_H11 + ulPageOffset, (((DWORD)pucIColorConvTable[11]) << 11) + (((DWORD)pucIColorConvTable[12]) << 3) + ((pucIColorConvTable[23] & 0x70) >> 4));
            Scaler32SetDWord(PB0074C_98_IM_DI_RGB2YCC_H12 + ulPageOffset, (((DWORD)pucIColorConvTable[13]) << 11) + (((DWORD)pucIColorConvTable[14]) << 3) + ((pucIColorConvTable[23] & 0x07) >> 0));
            Scaler32SetDWord(PB0074C_9C_IM_DI_RGB2YCC_H20 + ulPageOffset, (((DWORD)pucIColorConvTable[15]) << 11) + (((DWORD)pucIColorConvTable[16]) << 3) + ((pucIColorConvTable[24] & 0x70) >> 4));
            Scaler32SetDWord(PB0074C_A0_IM_DI_RGB2YCC_H21 + ulPageOffset, (((DWORD)pucIColorConvTable[17]) << 11) + (((DWORD)pucIColorConvTable[18]) << 3) + ((pucIColorConvTable[24] & 0x07) >> 0));
            Scaler32SetDWord(PB0074C_A4_IM_DI_RGB2YCC_H22 + ulPageOffset, (((DWORD)pucIColorConvTable[19]) << 11) + (((DWORD)pucIColorConvTable[20]) << 3) + ((pucIColorConvTable[25] & 0x70) >> 4));
            // Set Ctrl
            Scaler32SetDWord(PB0074C_80_IM_DI_RGB2YCC_CTRL + ulPageOffset, ((DWORD)ucIColorConvCtrlValue) & (_BIT(7, 4) | _BIT(2, 0)));
            // Set Enable
            Scaler32SetBit(PB0074C_80_IM_DI_RGB2YCC_CTRL + ulPageOffset, ~_BIT0, _BIT0);
        }
    }
}
#endif

//--------------------------------------------------
// Description  : 3DDI setting Process
// Input Value  : enum3DDIInputPath
// Output Value : none
//--------------------------------------------------
void Scaler3DDISettingProc(EnumInputDataPath enum3DDIInputPath)
{
    DWORD ulPageOffset = Scaler3DDIGetRegisterPageOfffset(enum3DDIInputPath);

    Scaler3DDISetDB(ulPageOffset, _OFF);
    Scaler3DDISetEnable(ulPageOffset, _OFF);
    Scaler3DDISetCtrl(ulPageOffset);
    Scaler3DDISetIf3Aor5A(ulPageOffset);
    Scaler3DDISetMemory(ulPageOffset, enum3DDIInputPath);

    if(GET_INPUT_TIMING_HWIDTH() <= _3DDI_5A_MAX_HWIDTH)
    {
        Scaler3DDISetIntra(ulPageOffset, tIntraTable[0]);
    }
    else
    {
        Scaler3DDISetIntra(ulPageOffset, tIntraTable[1]);
    }

    Scaler3DDISetFilm(ulPageOffset);

    Scaler3DDISetMaTable(ulPageOffset, tMaTable[0]);
    Scaler3DDISetMaCtrl(ulPageOffset);
    Scaler3DDISetMaHFD(ulPageOffset, _ON);
    Scaler3DDISetMaBTR(ulPageOffset, _ON);
    Scaler3DDISetEnable(ulPageOffset, _ON);
    SET_3DDI_STATUS(enum3DDIInputPath, _ON);
}

//--------------------------------------------------
// Description  : Reset 3DDI
// Input Value  : enum3DDIInputPath
// Output Value : none
//--------------------------------------------------
void Scaler3DDIReset(EnumInputDataPath enum3DDIInputPath)
{
    DWORD ulPageOffset = Scaler3DDIGetRegisterPageOfffset(enum3DDIInputPath);
    Scaler3DDISetEnable(ulPageOffset, _OFF);
    // set di output from CTS
    Scaler32SetBit(PB0074C_04_IM_DI_TIMING_ADD_CONTROL0 + ulPageOffset, ~_BIT20, 0);
    // disable RGB2YUV
    Scaler32SetBit(PB0074C_80_IM_DI_RGB2YCC_CTRL + ulPageOffset, ~_BIT0, 0);
    SET_3DDI_STATUS(enum3DDIInputPath, _OFF);
}

//--------------------------------------------------
// Description  : Duplicate 3DDI setting from one path to an other
// Input Value  : enumInputPath0, enumInputPath1
// Output Value : none
//--------------------------------------------------
void Scaler3DDIDuplicate(EnumInputDataPath enumInputSrc, EnumInputDataPath enumInputDest)
{
    DWORD ulPageOffset0 = Scaler3DDIGetRegisterPageOfffset(enumInputSrc);
    DWORD ulPageOffset1 = Scaler3DDIGetRegisterPageOfffset(enumInputDest);
    DWORD ulStartAddr0 = 0;
    DWORD ulStartAddr1 = 0;
    if(ulPageOffset0 > ulPageOffset1)
    {
        ulStartAddr0 = ((((GET_3DDI_START_ADDRESS() + GET_3DDI_END_ADDRESS()) / 2) >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) + 1) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM;
        ulStartAddr1 = GET_3DDI_START_ADDRESS();
    }
    else if(ulPageOffset0 < ulPageOffset1)
    {
        ulStartAddr1 = ((((GET_3DDI_START_ADDRESS() + GET_3DDI_END_ADDRESS()) / 2) >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM) + 1) << _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM;
        ulStartAddr0 = GET_3DDI_START_ADDRESS();
    }
    else
    {
        return;
    }

    Scaler32SetDWord(PB00744_90_DB_REG_CTL + ulPageOffset1, Scaler32GetDWord(PB00744_90_DB_REG_CTL + ulPageOffset0));
    Scaler32SetDWord(PB0074C_04_IM_DI_TIMING_ADD_CONTROL0 + ulPageOffset1, Scaler32GetDWord(PB0074C_04_IM_DI_TIMING_ADD_CONTROL0 + ulPageOffset0));
    Scaler32SetDWord(PB00740_04_COLOR_RECOVERY_OPTION + ulPageOffset1, Scaler32GetDWord(PB00740_04_COLOR_RECOVERY_OPTION + ulPageOffset0));
    // set mem
    Scaler32SetDWord(PB0074C_08_IM_DI_TIMING_ADD_CONTROL1 + ulPageOffset1, Scaler32GetDWord(PB0074C_08_IM_DI_TIMING_ADD_CONTROL1 + ulPageOffset0));
    Scaler32SetDWord(PB00740_0C_IM_DI_ACTIVE_WINDOW_CONTROL + ulPageOffset1, Scaler32GetDWord(PB00740_0C_IM_DI_ACTIVE_WINDOW_CONTROL + ulPageOffset0));
    Scaler32SetDWord(PB00741_A8_TR2TO1 + ulPageOffset1, Scaler32GetDWord(PB00741_A8_TR2TO1 + ulPageOffset0));
    Scaler32SetDWord(PB00744_00_DI_DATMEMORYSTARTADD1 + ulPageOffset1, (((Scaler32GetDWord(PB00744_00_DI_DATMEMORYSTARTADD1 + ulPageOffset0)) >> 3) - ulStartAddr0 + ulStartAddr1) << 3);
    Scaler32SetDWord(PB00744_04_DI_DATMEMORYSTARTADD2 + ulPageOffset1, (((Scaler32GetDWord(PB00744_04_DI_DATMEMORYSTARTADD2 + ulPageOffset0)) >> 3) - ulStartAddr0 + ulStartAddr1) << 3);
    Scaler32SetDWord(PB00744_08_DI_DATMEMORYSTARTADD3 + ulPageOffset1, (((Scaler32GetDWord(PB00744_08_DI_DATMEMORYSTARTADD3 + ulPageOffset0)) >> 3) - ulStartAddr0 + ulStartAddr1) << 3);
    Scaler32SetDWord(PB00744_0C_DI_DATMEMORYSTARTADD4 + ulPageOffset1, (((Scaler32GetDWord(PB00744_0C_DI_DATMEMORYSTARTADD4 + ulPageOffset0)) >> 3) - ulStartAddr0 + ulStartAddr1) << 3);
    Scaler32SetDWord(PB00744_10_DI_INFMEMORYSTARTADD1 + ulPageOffset1, (((Scaler32GetDWord(PB00744_10_DI_INFMEMORYSTARTADD1 + ulPageOffset0)) >> 3) - ulStartAddr0 + ulStartAddr1) << 3);
    Scaler32SetDWord(PB00744_14_DI_INFMEMORYSTARTADD2 + ulPageOffset1, (((Scaler32GetDWord(PB00744_14_DI_INFMEMORYSTARTADD2 + ulPageOffset0)) >> 3) - ulStartAddr0 + ulStartAddr1) << 3);
    Scaler32SetDWord(PB00744_18_DDR_RDATDMA_WTLENNUM + ulPageOffset1, Scaler32GetDWord(PB00744_18_DDR_RDATDMA_WTLENNUM + ulPageOffset0));
    Scaler32SetDWord(PB00744_1C_DDR_WDATDMA_WTLENNUM + ulPageOffset1, Scaler32GetDWord(PB00744_1C_DDR_WDATDMA_WTLENNUM + ulPageOffset0));
    Scaler32SetDWord(PB00744_20_DDR_DATDMA_RM + ulPageOffset1, Scaler32GetDWord(PB00744_20_DDR_DATDMA_RM + ulPageOffset0));
    Scaler32SetDWord(PB00744_24_DDR_RINFDMA_WTLENNUM + ulPageOffset1, Scaler32GetDWord(PB00744_24_DDR_RINFDMA_WTLENNUM + ulPageOffset0));
    Scaler32SetDWord(PB00744_28_DDR_WINFDMA_WTLENNUM + ulPageOffset1, Scaler32GetDWord(PB00744_28_DDR_WINFDMA_WTLENNUM + ulPageOffset0));
    Scaler32SetDWord(PB00744_2C_DDR_INFDMA_RM + ulPageOffset1, Scaler32GetDWord(PB00744_2C_DDR_INFDMA_RM + ulPageOffset0));
    // set intra
    Scaler32SetDWord(PB00748_E0_IM_DI_NINTRA_CONTROL + ulPageOffset1, Scaler32GetDWord(PB00748_E0_IM_DI_NINTRA_CONTROL + ulPageOffset0));
    Scaler32SetDWord(PB00748_E4_IM_DI_NINTRA_LOWPASS_SOURCE + ulPageOffset1, Scaler32GetDWord(PB00748_E4_IM_DI_NINTRA_LOWPASS_SOURCE + ulPageOffset0));
    Scaler32SetDWord(PB00748_E8_IM_DI_NINTRA_SEARCH_DIR_LIMIT + ulPageOffset1, Scaler32GetDWord(PB00748_E8_IM_DI_NINTRA_SEARCH_DIR_LIMIT + ulPageOffset0));
    Scaler32SetDWord(PB00748_EC_IM_DI_NINTRA_INTERSECTION_TH + ulPageOffset1, Scaler32GetDWord(PB00748_EC_IM_DI_NINTRA_INTERSECTION_TH + ulPageOffset0));
    Scaler32SetDWord(PB00748_F0_IM_DI_NINTRA_1ST_2ND_YDIFF_TH + ulPageOffset1, Scaler32GetDWord(PB00748_F0_IM_DI_NINTRA_1ST_2ND_YDIFF_TH + ulPageOffset0));
    Scaler32SetDWord(PB00748_F4_IM_DI_NINTRA_HIGH_FREQ_LIMIT + ulPageOffset1, Scaler32GetDWord(PB00748_F4_IM_DI_NINTRA_HIGH_FREQ_LIMIT + ulPageOffset0));
    // set Film
    Scaler32SetDWord(PB00740_A0_IM_DI_FILM_SAWTOOTH_FILMFRAME_TH + ulPageOffset1, Scaler32GetDWord(PB00740_A0_IM_DI_FILM_SAWTOOTH_FILMFRAME_TH + ulPageOffset0));
    Scaler32SetDWord(PB00740_A4_IM_DI_FILM_STATIC_SUM_TH + ulPageOffset1, Scaler32GetDWord(PB00740_A4_IM_DI_FILM_STATIC_SUM_TH + ulPageOffset0));
    Scaler32SetDWord(PB00740_A8_IM_DI_FILM_FIELD_JUDGE_TH + ulPageOffset1, Scaler32GetDWord(PB00740_A8_IM_DI_FILM_FIELD_JUDGE_TH + ulPageOffset0));
    Scaler32SetDWord(PB00740_AC_IM_DI_FILM_STATIC_SUM_SUB_TH + ulPageOffset1, Scaler32GetDWord(PB00740_AC_IM_DI_FILM_STATIC_SUM_SUB_TH + ulPageOffset0));
    Scaler32SetDWord(PB00740_B0_IM_DI_FILM_FIELD_JUDGE_SUB_TH + ulPageOffset1, Scaler32GetDWord(PB00740_B0_IM_DI_FILM_FIELD_JUDGE_SUB_TH + ulPageOffset0));
    Scaler32SetDWord(PB00740_B4_IM_DI_FILM_MOTION_SUM_TH + ulPageOffset1, Scaler32GetDWord(PB00740_B4_IM_DI_FILM_MOTION_SUM_TH + ulPageOffset0));
    // set ma
    Scaler32SetDWord(PB00740_90_IM_DI_MA_OTHERS_TH + ulPageOffset1, Scaler32GetDWord(PB00740_90_IM_DI_MA_OTHERS_TH + ulPageOffset0));
    Scaler32SetDWord(PB00740_94_IM_DI_MA_SAWTOOTH_TH + ulPageOffset1, Scaler32GetDWord(PB00740_94_IM_DI_MA_SAWTOOTH_TH + ulPageOffset0));
    Scaler32SetDWord(PB00740_80_IM_DI_MA_FRAME_MOTION_TH_A + ulPageOffset1, Scaler32GetDWord(PB00740_80_IM_DI_MA_FRAME_MOTION_TH_A + ulPageOffset0));
    Scaler32SetDWord(PB00740_84_IM_DI_MA_FRAME_MOTION_TH_B + ulPageOffset1, Scaler32GetDWord(PB00740_84_IM_DI_MA_FRAME_MOTION_TH_B + ulPageOffset0));
    Scaler32SetDWord(PB00740_88_IM_DI_MA_FRAME_MOTION_TH_C + ulPageOffset1, Scaler32GetDWord(PB00740_88_IM_DI_MA_FRAME_MOTION_TH_C + ulPageOffset0));
    Scaler32SetDWord(PB00740_8C_IM_DI_MA_FIELD_TEETH_TH_A + ulPageOffset1, Scaler32GetDWord(PB00740_8C_IM_DI_MA_FIELD_TEETH_TH_A + ulPageOffset0));
    Scaler32SetDWord(PB00741_EC_IM_DI_HFD_CONTROL + ulPageOffset1, Scaler32GetDWord(PB00741_EC_IM_DI_HFD_CONTROL + ulPageOffset0));
    Scaler32SetDWord(PB00742_08_IM_DI_BTR_CONTROL + ulPageOffset1, Scaler32GetDWord(PB00742_08_IM_DI_BTR_CONTROL + ulPageOffset0));
    Scaler32SetDWord(PB00742_20_IM_DI_BER_TEMPORAL_CONTROL + ulPageOffset1, Scaler32GetDWord(PB00742_20_IM_DI_BER_TEMPORAL_CONTROL + ulPageOffset0));

    // di control
    Scaler32SetDWord(PB00740_00_IM_DI_CONTROL + ulPageOffset1, (Scaler32GetDWord(PB00740_00_IM_DI_CONTROL + ulPageOffset0) | _BIT22 | _BIT20 | _BIT16 | _BIT8 | _BIT6 | _BIT4 | _BIT2));
}

//--------------------------------------------------
// Description  : Decide if to enable 3DDI or not
// Input Value  : enumInputPort
// Output Value : TRUE or FALSE
//--------------------------------------------------
bit Scaler3DDIEnableDecision(EnumInputDataPath enumInputDataPath, EnumInputPort enumInputPort)
{
    BYTE ucRegionIndex = ScalerRegionGetIndexFromInputDataPath(enumInputDataPath);

    // check input port
    if(enumInputPort == _A0_INPUT_PORT)
    {
        return _FALSE;
    }

    // check display mode and path
    if((Scaler3DDIGetPath(enumInputDataPath) == _HW_3DDI_PATH_NONE) ||
       (GET_RGN_MAX_DISPLAY_REGION() > 2))
    {
        return _FALSE;
    }

    // check timing info
    if(((g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.b1Interlace) == _TRUE) &&
       ((g_pstMeasureRegionTimingInfo[ucRegionIndex].stTimingInfo.usHWidth) <= 1920) &&
       (((DWORD)(ScalerSyncGetInputPixelClk(enumInputPort) * 100)) < _3DDI_PCLK_LIMIT))
    {
        return _TRUE;
    }

    return _FALSE;
}

#if(_3DDI_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : 3DDI client BW Ctrl caller example
// Input Value  : enum3DDIInputPath
// Output Value : None
//--------------------------------------------------
void Scaler3DDISetBwCtrl(EnumInputDataPath enum3DDIInputPath)
{
    BYTE uc3DDIPath = Scaler3DDIGetPath(enum3DDIInputPath);
    BYTE uc3DDIPathIndex = (uc3DDIPath == _HW_3DDI_1ST_PATH) ? 0 : 1;
    StructBwCtrlClientInfo stBwCtrlInfo = {0};

    // Enable BW Ctrl before enableing function.
    Scaler3DDIBwCtrlGetWriteClientInfo(&stBwCtrlInfo);
    ScalerMemorySetBwCtrl(_MEM_CLIENT_3DDI_W, uc3DDIPathIndex, &stBwCtrlInfo);

    Scaler3DDIBwCtrlGetReadClientInfo(&stBwCtrlInfo);
    ScalerMemorySetBwCtrl(_MEM_CLIENT_3DDI_R, uc3DDIPathIndex, &stBwCtrlInfo);
}

//--------------------------------------------------
// Description  : Get BW Ctrl client info - 3DDI write
// Input Value  : Pointer to client info
// Output Value : None
//--------------------------------------------------
void Scaler3DDIBwCtrlGetWriteClientInfo(StructBwCtrlClientInfo *pstInfo)
{
    // TODO:
    BYTE code ucTimeThdPercent = 100; // For fine tune usage
    BYTE code ucReqThdFixedValue = 0x01U;

    pstInfo->bEnable = _TRUE;
    pstInfo->enumMode = _BW_CTRL_REQ_MODE;

    pstInfo->ulReqThd = ucReqThdFixedValue;

    WORD usRWLen_64bit = _3DDI_MEM_LENGTH * 2;
    WORD usHActive = GET_INPUT_TIMING_HWIDTH();
    WORD usHTotal = GET_INPUT_TIMING_HTOTAL();
    DWORD ulMPll_MHz = _MEMORY_PLL_CLOCK;
    DWORD ulPixClk_KHz = (DWORD)GET_INPUT_TIMING_HFREQ() * GET_INPUT_TIMING_HTOTAL() / 10; // GET_INPUT_TIMING_HFREQ() unit: 0.1 KHz
    WORD usBitRate = _3DDI_DATA_BIT_NUM * 1 + _3DDI_INFO_BIT_NUM * 1;
    DWORD ulTValue = 0;
    DWORD ulDenominator = 0;

    // A (unit: request) & T (unit: mclk_cycle)
    // A = 1,
    //
    // T
    // = (LEN * 64 * MPLL_freq) / ((HActive / HTotal) * pixel_rate * bit)
    // = (LEN * 64 * MPLL_freq) / ((HActive * bit) * pixel_rate / HTotal)
    ulDenominator = ScalerGlobalComputeDwordMulDiv(((DWORD)usHActive * usBitRate), ulPixClk_KHz, usHTotal) / 1000;
    ulTValue = ScalerGlobalComputeDwordMulDiv(((DWORD)usRWLen_64bit * 64 * ulMPll_MHz), ucTimeThdPercent, ulDenominator) / 100;

    pstInfo->ulTimeThd = ulTValue;
}

//--------------------------------------------------
// Description  : Get BW Ctrl client info - 3DDI write
// Input Value  : Pointer to client info
// Output Value : None
//--------------------------------------------------
void Scaler3DDIBwCtrlGetReadClientInfo(StructBwCtrlClientInfo *pstInfo)
{
    // TODO:
    BYTE code ucTimeThdPercent = 96; // For fine tune usage
    BYTE code ucReqThdFixedValue = 0x01U;

    pstInfo->bEnable = _TRUE;
    pstInfo->enumMode = _BW_CTRL_REQ_MODE;

    pstInfo->ulReqThd = ucReqThdFixedValue;

    WORD usRWLen_64bit = _3DDI_MEM_LENGTH * 2;
    WORD usHActive = GET_INPUT_TIMING_HWIDTH();
    WORD usHTotal = GET_INPUT_TIMING_HTOTAL();
    DWORD ulMPll_MHz = _MEMORY_PLL_CLOCK;
    DWORD ulPixClk_KHz = (DWORD)GET_INPUT_TIMING_HFREQ() * GET_INPUT_TIMING_HTOTAL() / 10; // GET_INPUT_TIMING_HFREQ() unit: 0.1 KHz
    WORD usBitRate = ((usHActive <= _3DDI_5A_MAX_HWIDTH) ?
                      (_3DDI_DATA_BIT_NUM * 4 + _3DDI_INFO_BIT_NUM * 2) :
                      (_3DDI_DATA_BIT_NUM * 2 + _3DDI_INFO_BIT_NUM * 2));
    DWORD ulTValue = 0;
    DWORD ulDenominator = 0;

    // A (unit: request) & T (unit: mclk_cycle)
    // A = 1,
    //
    // T
    // = (LEN * 64 * MPLL_freq) / ((HActive / HTotal) * pixel_rate * bit)
    // = (LEN * 64 * MPLL_freq) / ((HActive * bit) * pixel_rate / HTotal)
    ulDenominator = ScalerGlobalComputeDwordMulDiv(((DWORD)usHActive * usBitRate), ulPixClk_KHz, usHTotal) / 1000;
    ulTValue = ScalerGlobalComputeDwordMulDiv(((DWORD)usRWLen_64bit * 64 * ulMPll_MHz), ucTimeThdPercent, ulDenominator) / 100;

    pstInfo->ulTimeThd = ulTValue;
}
#endif

#if(_FW_FRL_MEASURE_FROM_INTERFACE == _ON)
//--------------------------------------------------
// Description  : Modify timing after 3DDI
// Input Value  : enumInputPath
// Output Value : none
//--------------------------------------------------
bit Scaler3DDIModifyTiming(EnumInputDataPath enum3DDIInputPath)
{
    BYTE ucIDomainPage = ScalerMeasureGetIDomainPage(GET_MEASURE_INPUT_PATH());
    DWORD ulPageOffset = Scaler3DDIGetRegisterPageOfffset(enum3DDIInputPath);

    // reset 3DDI HW
    Scaler32SetDWord(PB0074A_D0_CCDINR_TIMING_MONITOR_CTRL_1 + ulPageOffset, 0x00);

    // 3DDI HW measure Vstart
    Scaler32SetBit(PB0074A_D0_CCDINR_TIMING_MONITOR_CTRL_1 + ulPageOffset, ~(_BIT31 | _BIT28 | _BIT27), (_BIT31 | _BIT28 | _BIT27));
    Scaler32SetBit(PB0074A_D0_CCDINR_TIMING_MONITOR_CTRL_1 + ulPageOffset, ~(_BIT(11, 8)), _BIT9);

    if((ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (ScalerTimerWaitForIDomainEvent(_EVENT_IVS, GET_MEASURE_INPUT_PATH()) == _FALSE) ||
       (Scaler32GetDWord(PB0074A_E0_CCDINR_TIMING_MONITOR_RESULT1_1 + ulPageOffset) > 65535))
    {
        return _FALSE;
    }

    // Modify Vstart for VGIP rising/falling latch
    if((Scaler32GetDWord(PB0074A_E0_CCDINR_TIMING_MONITOR_RESULT1_1 + ulPageOffset)) > 0x01)
    {
        if((GET_PAGED_BIT(ucIDomainPage, P0_11_M1_VGIP_SIGINV, _BIT6) == 0x00) &&
           (GET_PAGED_BIT(ucIDomainPage, P0_12_M1_VGIP_DELAY_CTRL, _BIT2) == _BIT2))
        {
            // VGIP VSync rising latch by Hsync: After VIGP, Vsync delay 1 line
            SET_INPUT_TIMING_VSTART(Scaler32GetDWord(PB0074A_E0_CCDINR_TIMING_MONITOR_RESULT1_1 + ulPageOffset) - 1);
            DebugMessageMeasure("---------------------1-3ddi Vstart, VGIP VSync rising latch by Hsync", GET_INPUT_TIMING_VSTART());
        }
        else
        {
            // default: VGIP VSync falling latch by Hsync, VIGP VS by pass enable
            SET_INPUT_TIMING_VSTART(Scaler32GetDWord(PB0074A_E0_CCDINR_TIMING_MONITOR_RESULT1_1 + ulPageOffset));
            DebugMessageMeasure("---------------------2-3ddi Vstart, VGIP VSync falling latch by Hsync", GET_INPUT_TIMING_VSTART());
        }
    }
    else
    {
        SET_INPUT_TIMING_VSTART(0);
    }

    // reset 3DDI HW
    Scaler32SetDWord(PB0074A_D0_CCDINR_TIMING_MONITOR_CTRL_1 + ulPageOffset, 0x00);

    return _TRUE;
}
#endif
#endif
