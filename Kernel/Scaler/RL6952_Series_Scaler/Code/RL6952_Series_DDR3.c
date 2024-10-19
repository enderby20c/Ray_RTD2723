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
// ID Code      : RL6952_Series_DDR3.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __RL6952_SERIES_DDR3__

#include "ScalerFunctionInclude.h"
#include "DDR3/ScalerDDR3.h"


//****************************************************************************
// CODE TABLES
//****************************************************************************
#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
StructBwCtrlRegInfo code tBwCtrlReg[] =
{
    // Systen Bridge client         BW Ctrl enable ctrl bit                     BW Ctrl mode ctrl bit                       Request threshold register(BYTE)    Time threshold register(WORD)
    {_DBUS_TV_SB2_C00_EARC_TX_R,    {PA4_EB_TV_SB2_DCU1_BW_LIMIT_EN_EB, _BIT0}, {PA4_E8_TV_SB2_DCU1_BW_LIMIT_EN_E8, _BIT7}, PA4_31_TV_SB2_DCU1_BW_LIMIT_0_31,   PA4_32_TV_SB2_DCU1_BW_LIMIT_0_32 },
    {_DBUS_TV_SB2_C01_FRC_CAP_M1,   {PA4_EB_TV_SB2_DCU1_BW_LIMIT_EN_EB, _BIT2}, {PA4_E8_TV_SB2_DCU1_BW_LIMIT_EN_E8, _BIT6}, PA4_35_TV_SB2_DCU1_BW_LIMIT_1_35,   PA4_36_TV_SB2_DCU1_BW_LIMIT_1_36 },
    {_DBUS_TV_SB2_C02_FRC_CAP_M2,   {PA4_EB_TV_SB2_DCU1_BW_LIMIT_EN_EB, _BIT4}, {PA4_E8_TV_SB2_DCU1_BW_LIMIT_EN_E8, _BIT5}, PA4_39_TV_SB2_DCU1_BW_LIMIT_2_39,   PA4_3A_TV_SB2_DCU1_BW_LIMIT_2_3A },
    {_DBUS_TV_SB2_C03_EARC_TX_W,    {PA4_EB_TV_SB2_DCU1_BW_LIMIT_EN_EB, _BIT6}, {PA4_E8_TV_SB2_DCU1_BW_LIMIT_EN_E8, _BIT4}, PA4_3D_TV_SB2_DCU1_BW_LIMIT_3_3D,   PA4_3E_TV_SB2_DCU1_BW_LIMIT_3_3E },
    {_DBUS_TV_SB2_C04_FRC_DISP_M1,  {PA4_EA_TV_SB2_DCU1_BW_LIMIT_EN_EA, _BIT0}, {PA4_E8_TV_SB2_DCU1_BW_LIMIT_EN_E8, _BIT3}, PA4_41_TV_SB2_DCU1_BW_LIMIT_4_41,   PA4_42_TV_SB2_DCU1_BW_LIMIT_4_42 },
    {_DBUS_TV_SB2_C05_FRC_DISP_M2,  {PA4_EA_TV_SB2_DCU1_BW_LIMIT_EN_EA, _BIT2}, {PA4_E8_TV_SB2_DCU1_BW_LIMIT_EN_E8, _BIT2}, PA4_45_TV_SB2_DCU1_BW_LIMIT_5_45,   PA4_46_TV_SB2_DCU1_BW_LIMIT_5_46 },
    {_DBUS_TV_SB2_C07_FRC_DISP_S1,  {PA4_EA_TV_SB2_DCU1_BW_LIMIT_EN_EA, _BIT6}, {PA4_E8_TV_SB2_DCU1_BW_LIMIT_EN_E8, _BIT0}, PA4_4D_TV_SB2_DCU1_BW_LIMIT_7_4D,   PA4_4E_TV_SB2_DCU1_BW_LIMIT_7_4E },
    {_DBUS_TV_SB2_C09_FRC_CAP_S1,   {PA4_E7_TV_SB2_DCU1_BW_LIMIT_EN_E7, _BIT2}, {PA4_E9_TV_SB2_DCU1_BW_LIMIT_EN_E9, _BIT6}, PA4_85_TV_SB2_DCU1_BW_LIMIT_9_85,   PA4_86_TV_SB2_DCU1_BW_LIMIT_9_86 },
    {_DBUS_TV_SB2_C11_OD_M1_W,      {PA4_E7_TV_SB2_DCU1_BW_LIMIT_EN_E7, _BIT6}, {PA4_E9_TV_SB2_DCU1_BW_LIMIT_EN_E9, _BIT4}, PA4_8D_TV_SB2_DCU1_BW_LIMIT_11_8D,  PA4_8E_TV_SB2_DCU1_BW_LIMIT_11_8E},
    {_DBUS_TV_SB2_C13_OD_M1_R,      {PA4_E6_TV_SB2_DCU1_BW_LIMIT_EN_E6, _BIT2}, {PA4_E9_TV_SB2_DCU1_BW_LIMIT_EN_E9, _BIT2}, PA4_95_TV_SB2_DCU1_BW_LIMIT_13_95,  PA4_96_TV_SB2_DCU1_BW_LIMIT_13_96},
    {_DBUS_TV_SB2_C14_OD_M2_R,      {PA4_E6_TV_SB2_DCU1_BW_LIMIT_EN_E6, _BIT4}, {PA4_E9_TV_SB2_DCU1_BW_LIMIT_EN_E9, _BIT1}, PA4_99_TV_SB2_DCU1_BW_LIMIT_14_99,  PA4_9A_TV_SB2_DCU1_BW_LIMIT_14_9A},
    {_DBUS_TV_SB2_C15_OD_M2_W,      {PA4_E6_TV_SB2_DCU1_BW_LIMIT_EN_E6, _BIT6}, {PA4_E9_TV_SB2_DCU1_BW_LIMIT_EN_E9, _BIT0}, PA4_A1_TV_SB2_DCU1_BW_LIMIT_15_A1,  PA4_A2_TV_SB2_DCU1_BW_LIMIT_15_A2},
};
#endif

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************


//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
//--------------------------------------------------
// Description  : System Bridge initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SystemBridgeInitial(void)
{
    //============================
    // Set IP arbitration enable
    //============================

    //---------- SB2 clients ----------
    // _BIT15: Client15 (OD_M2_W)
    // _BIT14: Client14 (OD_M2_R)
    // _BIT13: Client13 (OD_M1_R)
    // _BIT12: Client12 (DUMMY_C12) - _OFF
    // _BIT11: Client11 (OD_M1_W)
    // _BIT10: Client10 (DUMMY_C10) - _OFF
    // _BIT9:  Client09 (FRC_CAP_S1)
    // _BIT8:  Client08 (DUMMY_C08) - _OFF
    // _BIT7:  Client07 (FRC_DISP_S1)
    // _BIT6:  Client06 (DUMMY_C06) - _OFF
    // _BIT5:  Client05 (FRC_DISP_M2)
    // _BIT4:  Client04 (FRC_DISP_M1)
    // _BIT3:  Client03 (EARC_TX_W)
    // _BIT2:  Client02 (FRC_CAP_M2)
    // _BIT1:  Client01 (FRC_CAP_M1)
    // _BIT0:  Client00 (EARC_TX_R)
    ScalerSetWord(PA4_06_TV_SB2_DCU1_ARB_CR1_06, 0xEABF);
}

//--------------------------------------------------
// Description  : Check if can use DC-PHY Scramble
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerDDR3DcPhyScrambleAvaiable(void)
{
    return _TRUE;
}

//--------------------------------------------------
// Description  : Get DDR old RDL status
// Input Value  : None
// Output Value : True(old RDL), False(new RDL)
//--------------------------------------------------
bit ScalerDDR3GetDDROldRDLStatus(void)
{
    return _FALSE;
}

#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get memory client enum
// Input Value  : client type, client index
// Output Value : memory client enum
//--------------------------------------------------
EnumMemoryClient ScalerDDR3GetMemoryClient(EnumMemoryClientType enumClientType, BYTE ucClientIndex)
{
#if(_FRC_MEMORY_BW_CTRL_SUPPORT == _ON)
    EnumMemoryClient code tFrcCapClient[] =
    {
        _DBUS_TV_SB2_C01_FRC_CAP_M1,
        _DBUS_TV_SB2_C02_FRC_CAP_M2,
        _DBUS_TV_SB2_C09_FRC_CAP_S1,
    };
    EnumMemoryClient code tFrcDispClient[] =
    {
        _DBUS_TV_SB2_C04_FRC_DISP_M1,
        _DBUS_TV_SB2_C05_FRC_DISP_M2,
        _DBUS_TV_SB2_C07_FRC_DISP_S1,
    };
#endif
#if(_OD_MEMORY_BW_CTRL_SUPPORT == _ON)
    EnumMemoryClient code tOdWriteClient[] =
    {
        _DBUS_TV_SB2_C11_OD_M1_W,
        _DBUS_TV_SB2_C15_OD_M2_W,
    };
    EnumMemoryClient code tOdReadClient[] =
    {
        _DBUS_TV_SB2_C13_OD_M1_R,
        _DBUS_TV_SB2_C14_OD_M2_R,
    };
#endif
    StructMemoryClientTypeInfo code tClientInfo[] =
    {
#if(_FRC_MEMORY_BW_CTRL_SUPPORT == _ON)
        {_MEM_CLIENT_FRC_CAP,   TABLE_INFO(tFrcCapClient)   },
        {_MEM_CLIENT_FRC_DISP,  TABLE_INFO(tFrcDispClient)  },
#endif
#if(_OD_MEMORY_BW_CTRL_SUPPORT == _ON)
        {_MEM_CLIENT_OD_W,      TABLE_INFO(tOdWriteClient)  },
        {_MEM_CLIENT_OD_R,      TABLE_INFO(tOdReadClient)   },
#endif
    };

    for(BYTE ucIndex = 0; ucIndex < (sizeof(tClientInfo) / sizeof(tClientInfo[0])); ++ucIndex)
    {
        if(tClientInfo[ucIndex].enumType == enumClientType)
        {
            if(ucClientIndex < tClientInfo[ucIndex].stClients.ucTableSize)
            {
                return tClientInfo[ucIndex].stClients.penumTable[ucClientIndex];
            }
            break;
        }
    }

    return _DBUS_SB_CLIENT_END;
}

//--------------------------------------------------
// Description  : Set BW Ctrl Enable/Disable
// Input Value  : client type, client index, bEnable
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SetBwCtrlEnable(EnumMemoryClientType enumClientType, BYTE ucClientIndex, bit bEnable)
{
    EnumMemoryClient enumClient = _DBUS_SB_CLIENT_END;

    enumClient = ScalerDDR3GetMemoryClient(enumClientType, ucClientIndex);
    if(enumClient >= _DBUS_SB_CLIENT_END)
    {
        return; // Unavailable clients.
    }

    {
        StructBwCtrlRegInfo stBwLimiter = tBwCtrlReg[enumClient];

        //----------------------------------
        // SB client, 8-bit register
        //----------------------------------
        // Enable/Disable function
        if(bEnable == _ENABLE)
        {
            ScalerSetBit((WORD)stBwLimiter.stEnCtrl.ulAddr, ~((BYTE)stBwLimiter.stEnCtrl.ulBit), (BYTE)stBwLimiter.stEnCtrl.ulBit);
        }
        else
        {
            ScalerSetBit((WORD)stBwLimiter.stEnCtrl.ulAddr, ~((BYTE)stBwLimiter.stEnCtrl.ulBit), 0x00);
        }
    }
}

//--------------------------------------------------
// Description  : Set BW Ctrl registers
// Input Value  : client type, client index, BW Ctrl parameters
// Output Value : None
//--------------------------------------------------
void ScalerDDR3SetBwCtrl(EnumMemoryClientType enumClientType, BYTE ucClientIndex, StructBwCtrlClientInfo *pstClientInfo)
{
    EnumMemoryClient enumClient = _DBUS_SB_CLIENT_END;

    enumClient = ScalerDDR3GetMemoryClient(enumClientType, ucClientIndex);
    if(enumClient >= _DBUS_SB_CLIENT_END)
    {
        return; // Unavailable clients.
    }

    {
        StructBwCtrlRegInfo stBwLimiter = tBwCtrlReg[enumClient];
        WORD usModeCtrlRegAddr = stBwLimiter.stModeCtrl.ulAddr;
        BYTE ucModeCtrlRegBit = stBwLimiter.stModeCtrl.ulBit;
        WORD usReqThdRegAddr = stBwLimiter.ulReqThdRegAddr;
        WORD usTimeThdRegAddr = stBwLimiter.ulTimeThdRegAddr;

        bit bBWCtrlEn = pstClientInfo->bEnable;
        EnumBwCtrlMode enumMode = pstClientInfo->enumMode;
        DWORD ulReqThd = pstClientInfo->ulReqThd;
        DWORD ulTimeThd = pstClientInfo->ulTimeThd;

        // Disable function before updating registers.
        ScalerDDR3SetBwCtrlEnable(enumClientType, ucClientIndex, _DISABLE);

        if(bBWCtrlEn == _FALSE)
        {
            return;
        }

        //----------------------------------
        // SB client, 8-bit register
        //----------------------------------
        // Set BW Ctrl mode
        if(enumMode == _BW_CTRL_LEN_MODE)
        {
            // Set BW Ctrl mode
            ScalerSetBit(usModeCtrlRegAddr, ~(ucModeCtrlRegBit), ucModeCtrlRegBit);

            // Set request threshold
            {
                BYTE ucReqThdRegValue = ulReqThd / _HW_BW_CTRL_LEN_MODE_SB_CLIENT_REQ_THR_REG_GAIN;
                ScalerSetByte(usReqThdRegAddr, ucReqThdRegValue);

                ulReqThd = ucReqThdRegValue * _HW_BW_CTRL_LEN_MODE_SB_CLIENT_REQ_THR_REG_GAIN;
            }
        }
        else // _BW_CTRL_REQ_MODE
        {
            // Set BW Ctrl mode
            ScalerSetBit(usModeCtrlRegAddr, ~(ucModeCtrlRegBit), 0x00);

            // Set request threshold
            ScalerSetByte(usReqThdRegAddr, (BYTE)ulReqThd);
        }

        // Set time threshold
        {
            WORD usTimeThdRegValue = ulTimeThd / _HW_BW_CTRL_SB_CLIENT_TIME_THR_REG_GAIN;
            ScalerSetWord(usTimeThdRegAddr, usTimeThdRegValue);

            ulTimeThd = usTimeThdRegValue * _HW_BW_CTRL_SB_CLIENT_TIME_THR_REG_GAIN;
        }

        // Enable BW Ctrl
        ScalerDDR3SetBwCtrlEnable(enumClientType, ucClientIndex, _ENABLE);

#if(_DEBUG_MESSAGE_MEMORY == _ON)
        {
            SBYTE pchModeMsg[] = "BW Ctrl C00 Mode";
            SBYTE pchReqThdMsg[] = "BW Ctrl C00 ReqThd";
            SBYTE pchTimeThdMsg[] = "BW Ctrl C00 TimeThd";
            SBYTE chSNDigit10x = ('0' + enumClient / 10);
            SBYTE chSNDigit1x = ('0' + enumClient % 10);

            // Client Enum
            pchModeMsg[9] = chSNDigit10x;
            pchReqThdMsg[9] = chSNDigit10x;
            pchTimeThdMsg[9] = chSNDigit10x;

            pchModeMsg[10] = chSNDigit1x;
            pchReqThdMsg[10] = chSNDigit1x;
            pchTimeThdMsg[10] = chSNDigit1x;

            DebugMessageMemory(pchModeMsg, enumMode);
            DebugMessageMemory(pchReqThdMsg, ulReqThd);
            DebugMessageMemory(pchTimeThdMsg, ulTimeThd);
        }
#endif
    }
}
#endif // End of #if(_MEMORY_BW_CTRL_SUPPORT == _ON)
#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

