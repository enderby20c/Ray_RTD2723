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
// ID Code      : ScalerFwUpdate.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_FW_UPDATE__

#include "ScalerFunctionInclude.h"
#include "FwUpdate/ScalerFwUpdate.h"

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile BYTE g_pucFwUpdateRxBuf[_FW_UPDATE_BUF_LEN];
volatile WORD g_usFwUpdateDdcciCountEXINT;

volatile StructFwUpdateScalerInfo g_stFwUpdateScalerInfo =
{
    _FALSE, _FALSE, _DEBUG_MODE, _INVALID_MODE
};
EnumDDCCIPort g_enumFwUpdateDdcciPort = _DDCCI0;

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : enumIp, enumStatus, ultimeout
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcciSwitchState(void)
{
    switch(g_enumFwUpdateDdcciPort)
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
        case _DDCCI0:
            ScalerFwUpdateDdcci0SwitchState();
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
        case _DDCCI1:
            ScalerFwUpdateDdcci1SwitchState();
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
        case _DDCCI2:
            ScalerFwUpdateDdcci2SwitchState();
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
        case _DDCCI3:
            ScalerFwUpdateDdcci3SwitchState();
            break;
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
        case _DDCCI4:
            ScalerFwUpdateDdcci4SwitchState();
            break;
#endif
        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Get Fw Update DDCCI Port
// Input Value  : enumDdcciChannel
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateGetDdcciPort(EnumDDCCIPort enumDdcciChannel)
{
    switch(GET_DISPLAY_MODE())
    {
        case _DISPLAY_MODE_1P:
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1)
            g_enumFwUpdateDdcciPort = _DDCCI1;
#elif(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2)
            g_enumFwUpdateDdcciPort = _DDCCI2;
#elif(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3)
            g_enumFwUpdateDdcciPort = _DDCCI3;
#elif(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
            g_enumFwUpdateDdcciPort = _DDCCI4;
#else
            g_enumFwUpdateDdcciPort = enumDdcciChannel;
#endif
            break;
        case _DISPLAY_MODE_2P_PIP:
        case _DISPLAY_MODE_2P_PIP_EAGLE_SIGHT:
        case _DISPLAY_MODE_2P_PBP_LR_EQUAL:
        case _DISPLAY_MODE_2P_PBP_LR_L_LARGE:
        case _DISPLAY_MODE_2P_PBP_LR_R_LARGE:
        case _DISPLAY_MODE_2P_PBP_TB:
            if(enumDdcciChannel == _DDCCI0)
            {
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2)
                g_enumFwUpdateDdcciPort = _DDCCI2;
#elif(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3)
                g_enumFwUpdateDdcciPort = _DDCCI3;
#elif(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
                g_enumFwUpdateDdcciPort = _DDCCI4;
#else
                g_enumFwUpdateDdcciPort = enumDdcciChannel;
#endif
            }
            else
            {
                g_enumFwUpdateDdcciPort = enumDdcciChannel;
            }
            break;

        case _DISPLAY_MODE_3P_FLAG:
        case _DISPLAY_MODE_3P_SKEW_L:
        case _DISPLAY_MODE_3P_SKEW_R:
        case _DISPLAY_MODE_3P_SKEW_T:
        case _DISPLAY_MODE_3P_SKEW_B:
            if(enumDdcciChannel == _DDCCI0)
            {
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3)
                g_enumFwUpdateDdcciPort = _DDCCI3;
#elif(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
                g_enumFwUpdateDdcciPort = _DDCCI4;
#else
                g_enumFwUpdateDdcciPort = enumDdcciChannel;
#endif
            }
            else
            {
                g_enumFwUpdateDdcciPort = enumDdcciChannel;
            }
            break;

        case _DISPLAY_MODE_4P:
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
            g_enumFwUpdateDdcciPort = _DDCCI4;
#else
            g_enumFwUpdateDdcciPort = enumDdcciChannel;
#endif
            break;
        default:
            g_enumFwUpdateDdcciPort = enumDdcciChannel;
            break;
    }
}
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : enumIp, enumStatus, ultimeout
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateSwitchState(EnumDDCCIDebugMode enumDdcciMode, BYTE ucOpCode, EnumDDCCIPort enumDdcciChannel)
{
    SET_FW_UPDATE_STATE_BACKUPDDCCIMODE(enumDdcciMode);
    ScalerFwUpdateGetDdcciPort(enumDdcciChannel);
    ScalerFwUpdateDdcciSwitchState();

    SET_FW_UPDATE_STATUS();
    if(ucOpCode == _FW_UPDATE_BACKGROUND_SUB_OP_CODE)
    {
        SET_FW_UPDATE_MODE(_BACKGROUND_MODE);
    }
    else if(ucOpCode == _FW_UPDATE_FOREGROUND_SUB_OP_CODE)
    {
        SET_FW_UPDATE_MODE(_FOREGROUND_MODE);
    }
    ScalerFwUpdateSendReply(_FW_UPDATE_RESULT_IDLE_AND_SUCCESS);

#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    if(ucOpCode == _FW_UPDATE_FOREGROUND_SUB_OP_CODE)
    {
        ScalerTimerReactiveTimerEvent(_FW_UPDATE_FOREGROUND_EXIT_TIMER_COUNT, _SYSTEM_TIMER_EVENT_FW_UPDATE_FOREGROUND_EXIT);
    }
#endif
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateSendReply(BYTE ucResult)
{
    switch(g_enumFwUpdateDdcciPort)
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
        case _DDCCI0:
            ScalerFwUpdateDdcci0SendReply(ucResult);
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
        case _DDCCI1:
            ScalerFwUpdateDdcci1SendReply(ucResult);
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
        case _DDCCI2:
            ScalerFwUpdateDdcci2SendReply(ucResult);
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
        case _DDCCI3:
            ScalerFwUpdateDdcci3SendReply(ucResult);
            break;
#endif
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
        case _DDCCI4:
            ScalerFwUpdateDdcci4SendReply(ucResult);
            break;
#endif
        default:
            break;
    }
    ScalerFwUpdateInitRxBuf();
    CLR_FW_UPDATE_RUN_COMMAND();
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateSendData(BYTE ucLen, BYTE *pucData)
{
    switch(g_enumFwUpdateDdcciPort)
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
        case _DDCCI0:
            ScalerFwUpdateDdcci0SendData(ucLen, pucData);
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
        case _DDCCI1:
            ScalerFwUpdateDdcci1SendData(ucLen, pucData);
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
        case _DDCCI2:
            ScalerFwUpdateDdcci2SendData(ucLen, pucData);
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
        case _DDCCI3:
            ScalerFwUpdateDdcci3SendData(ucLen, pucData);
            break;
#endif
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
        case _DDCCI4:
            ScalerFwUpdateDdcci4SendData(ucLen, pucData);
            break;
#endif
        default:
            break;
    }

    ScalerFwUpdateInitRxBuf();
    CLR_FW_UPDATE_RUN_COMMAND();
}

//---------------------------------------------------------
// Description  : Background Fw Update Init Rx Buffer
// Input Value  : ucFwBank, *pucArry
// Output Value : None
//---------------------------------------------------------
void ScalerFwUpdateInitRxBuf(void)
{
    // Clear buffer for new message
    memset(g_pucFwUpdateRxBuf, 0, _FW_UPDATE_BUF_LEN);
}
//--------------------------------------------------
// Description  : Scaler Fw Update Config DDCCI
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDisableDdcciConfig(void)
{
    switch(g_enumFwUpdateDdcciPort)
    {
#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
        case _DDCCI1:
            MCU_FE87_IIC_1_SET_SLAVE = 0x3C;
            MCU_FE8C_IIC_1_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
            ScalerSetBit(PFE_86_IIC_1_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
        case _DDCCI2:
            MCU_FE95_IIC_2_SET_SLAVE = 0x3C;
            MCU_FE9A_IIC_2_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
            ScalerSetBit(PFE_94_IIC_2_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
        case _DDCCI3:
            MCU_FEA4_IIC_3_SET_SLAVE = 0x3C;
            MCU_FEA9_IIC_3_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
            ScalerSetBit(PFE_A3_IIC_3_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            break;
#endif
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
        case _DDCCI4:
            MCU_FD01_IIC_4_SET_SLAVE = 0x3C;
            MCU_FD06_IIC_4_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0);
            ScalerSetBit(PFD_00_IIC_4_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
            break;
#endif
        default:
            break;
    }
}
//--------------------------------------------------
// Description  : Exit Fw Update
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateExit(void)
{
    ScalerFwUpdateDisableDdcciConfig();
    ScalerMcuDdcciSwitchPort(GET_FW_UPDATE_STATE_BACKUPDDCCIMODE());
    ScalerFwUpdateInitRxBuf();
    CLR_FW_UPDATE_STATUS();
    SET_FW_UPDATE_MODE(_INVALID_MODE);
}

//------------------------------------------------------------
// Description  : Get Current Background Fw Update State
// Input Value  : None
// Output Value : Bit State
//------------------------------------------------------------
bit ScalerFwUpdateGetState(void)
{
    return GET_FW_UPDATE_STATUS();
}

#if(((_FW_UPDATE_FOREGROUND_SUPPORT == _ON) && (_FW_UPDATE_FOREGROUND_EXIT_TYPE == _FW_UPDATE_FOREGROUND_RESET)) || (_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON))
//--------------------------------------------------
// Description  : Reset  MCU
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateReset(void)
{
    // Reset MCU
    MCU_FFEE_MCU_CLOCK_CONTROL |= _BIT1;
}
#endif

#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci0SwitchState(void)
{
    // Change Slave Address and Interrupt setting
    MCU_FF28_IIC_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1);

    MCU_FF23_IIC_SET_SLAVE = 0x3A;

    // Clear IRQ FLag
    MCU_FF27_IIC_STATUS = 0x00;
    // Read IIC Data In(0xFF25) to Clear Data In Flag
    pData[0] = MCU_FF25_IIC_DATA_IN;
    // Write IIC Data Out(0xFF26) to Clear Data Out Flag
    MCU_FF26_IIC_DATA_OUT = 0x00;
    // Clear IIC Buffer Overflow or Underflow Flag
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);
    // Reset IIC Buffer
    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FF28_IIC_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci0SendReply(BYTE ucResult)
{
    BYTE ucIndex = 0;

    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex++)
    {
        MCU_FF26_IIC_DATA_OUT = ucResult;
    }
    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateDdcci0SendData(BYTE ucLen, BYTE *pucData)
{
    BYTE ucIndex = 0;
    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        MCU_FF26_IIC_DATA_OUT = pucData[ucIndex];
    }
    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}
#endif

#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci1SwitchState(void)
{
    if((GET_DISPLAY_MODE() == _DISPLAY_MODE_1P) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
    {
        ScalerSetByte(PFE_86_IIC_1_CH_SEL, ScalerGetByte(PFF_22_IIC_CH_SEL));
        CLR_DDCCI_AUTO_SWITCH();
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        SET_DDCCI_AUTO_SWITCH();
    }
    MCU_FE87_IIC_1_SET_SLAVE = 0x3A;

    // Change Slave Address and Interrupt setting
    MCU_FE8C_IIC_1_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1);

    // Clear IRQ FLag
    MCU_FE8B_IIC_1_STATUS = 0x00;
    // Read IIC Data In(0xFF25) to Clear Data In Flag
    pData[0] = MCU_FE89_IIC_1_DATA_IN;
    // Write IIC Data Out(0xFF26) to Clear Data Out Flag
    MCU_FE8A_IIC_1_DATA_OUT = 0x00;
    // Clear IIC Buffer Overflow or Underflow Flag
    MCU_FE8D_IIC_1_STATUS2 &= ~(_BIT5 | _BIT4);
    // Reset IIC Buffer
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FE8C_IIC_1_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci1SendReply(BYTE ucResult)
{
    BYTE ucIndex = 0;

    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex++)
    {
        MCU_FE8A_IIC_1_DATA_OUT = ucResult;
    }
    MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateDdcci1SendData(BYTE ucLen, BYTE *pucData)
{
    BYTE ucIndex = 0;
    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        MCU_FE8A_IIC_1_DATA_OUT = pucData[ucIndex];
    }
    MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
}
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci2SwitchState(void)
{
    if((GET_DISPLAY_MODE() < _DISPLAY_MODE_3P_FLAG) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
    {
        ScalerSetByte(PFE_94_IIC_2_CH_SEL, ScalerGetByte(PFF_22_IIC_CH_SEL));
        CLR_DDCCI_AUTO_SWITCH();
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        SET_DDCCI_AUTO_SWITCH();
    }
    MCU_FE95_IIC_2_SET_SLAVE = 0x3A;

    // Change Slave Address and Interrupt setting
    MCU_FE9A_IIC_2_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1);

    // Clear IRQ FLag
    MCU_FE99_IIC_2_STATUS = 0x00;
    // Read IIC Data In(0xFF25) to Clear Data In Flag
    pData[0] = MCU_FE97_IIC_2_DATA_IN;
    // Write IIC Data Out(0xFF26) to Clear Data Out Flag
    MCU_FE98_IIC_2_DATA_OUT = 0x00;
    // Clear IIC Buffer Overflow or Underflow Flag
    MCU_FE9B_IIC_2_STATUS2 &= ~(_BIT5 | _BIT4);
    // Reset IIC Buffer
    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FE9A_IIC_2_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci2SendReply(BYTE ucResult)
{
    BYTE ucIndex = 0;

    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex++)
    {
        MCU_FE98_IIC_2_DATA_OUT = ucResult;
    }
    MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateDdcci2SendData(BYTE ucLen, BYTE *pucData)
{
    BYTE ucIndex = 0;
    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        MCU_FE98_IIC_2_DATA_OUT = pucData[ucIndex];
    }
    MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;
}
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci3SwitchState(void)
{
    if((GET_DISPLAY_MODE() < _DISPLAY_MODE_4P) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
    {
        ScalerSetByte(PFE_A3_IIC_3_CH_SEL, ScalerGetByte(PFF_22_IIC_CH_SEL));
        CLR_DDCCI_AUTO_SWITCH();
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        SET_DDCCI_AUTO_SWITCH();
    }
    MCU_FEA4_IIC_3_SET_SLAVE = 0x3A;

    // Change Slave Address and Interrupt setting
    MCU_FEA9_IIC_3_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1);

    // Clear IRQ FLag
    MCU_FEA8_IIC_3_STATUS = 0x00;
    // Read IIC Data In(0xFF25) to Clear Data In Flag
    pData[0] = MCU_FEA6_IIC_3_DATA_IN;
    // Write IIC Data Out(0xFF26) to Clear Data Out Flag
    MCU_FEA7_IIC_3_DATA_OUT = 0x00;
    // Clear IIC Buffer Overflow or Underflow Flag
    MCU_FEAA_IIC_3_STATUS2 &= ~(_BIT5 | _BIT4);
    // Reset IIC Buffer
    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FEA9_IIC_3_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci3SendReply(BYTE ucResult)
{
    BYTE ucIndex = 0;

    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex++)
    {
        MCU_FEA7_IIC_3_DATA_OUT = ucResult;
    }
    MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateDdcci3SendData(BYTE ucLen, BYTE *pucData)
{
    BYTE ucIndex = 0;
    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        MCU_FEA7_IIC_3_DATA_OUT = pucData[ucIndex];
    }
    MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;
}
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
//--------------------------------------------------
// Description  : Switch to Fw Update State
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci4SwitchState(void)
{
    if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
    {
        ScalerSetByte(PFD_00_IIC_4_CH_SEL, ScalerGetByte(PFF_22_IIC_CH_SEL));
        CLR_DDCCI_AUTO_SWITCH();
        ScalerSetBit(PFF_22_IIC_CH_SEL, ~(_BIT2 | _BIT1 | _BIT0), (_BIT2 | _BIT1 | _BIT0));
        SET_DDCCI_AUTO_SWITCH();
    }
    MCU_FD01_IIC_4_SET_SLAVE = 0x3A;

    // Change Slave Address and Interrupt setting
    MCU_FD06_IIC_4_IRQ_CONTROL &= ~(_BIT4 | _BIT3 | _BIT2 | _BIT1);

    // Clear IRQ FLag
    MCU_FD05_IIC_4_STATUS = 0x00;
    // Read IIC Data In(0xFF25) to Clear Data In Flag
    pData[0] = MCU_FD03_IIC_4_DATA_IN;
    // Write IIC Data Out(0xFF26) to Clear Data Out Flag
    MCU_FD04_IIC_4_DATA_OUT = 0x00;
    // Clear IIC Buffer Overflow or Underflow Flag
    MCU_FD07_IIC_4_STATUS2 &= ~(_BIT5 | _BIT4);
    // Auto  Reset IIC Buffer
    MCU_FD08_IIC_4_IRQ_CONTROL2 |= _BIT7;
    // Reset IIC Buffer
    MCU_FD08_IIC_4_IRQ_CONTROL2 |= _BIT6;

    // Enable STOP_I, D_IN_I, SUB_I interrupts
    MCU_FD06_IIC_4_IRQ_CONTROL |= _BIT4 | _BIT2 | _BIT1;
}

//--------------------------------------------------
// Description  : Fw Update Send out Reply
// Input Value  : none
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateDdcci4SendReply(BYTE ucResult)
{
    BYTE ucIndex = 0;

    MCU_FD08_IIC_4_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex++)
    {
        MCU_FD04_IIC_4_DATA_OUT = ucResult;
    }
    MCU_FD08_IIC_4_IRQ_CONTROL2 &= ~_BIT5;
}

//-------------------------------------------------------------
// Description  : Fw Update Send out data
// Input Value  : none
// Output Value : None
//---------------------------------------------------------------
void ScalerFwUpdateDdcci4SendData(BYTE ucLen, BYTE *pucData)
{
    BYTE ucIndex = 0;
    MCU_FD08_IIC_4_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        MCU_FD04_IIC_4_DATA_OUT = pucData[ucIndex];
    }
    MCU_FD08_IIC_4_IRQ_CONTROL2 &= ~_BIT5;
}
#endif

#if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))
//--------------------------------------------------
// Description  : For Signature, DeRsa Calc
// Input Value  : None
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFwUpdateDeRsaCalculateforSign(StructSignKeyInfoType *pstHdcp2SignKeyInfoType, WORD usRsaMode, WORD usSigSize, WORD usRRModNSize, WORD usNKeySize, WORD usEKeySize, WORD usNPivSize)
{
    WORD usIndex = 0;

    // Enable HDCP 2.2 RSA Module
    SET_HDCP22_RSA_WRITE_KEY_MODE();

    // RSA Clock Select
    SET_HDCP22_RSA_CLK();

    if(usRsaMode == _DIGITAL_SIGNATURE_RSA_3072)
    {
        // Select RSA Key Download Data Length
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), 0x00);
    }
    else if(usRsaMode == _DIGITAL_SIGNATURE_RSA_2048)
    {
        // Select RSA Key Download Data Length
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT6);
    }
    else if(usRsaMode == _DIGITAL_SIGNATURE_RSA_1024)
    {
        // Select RSA Key Download Data Length
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), _BIT7);
    }
    else if(usRsaMode == _DIGITAL_SIGNATURE_RSA_512)
    {
        // Select RSA Key Download Data Length
        ScalerSetBit(P63_11_HDCP_RSA_CTRL1, ~(_BIT7 | _BIT6), (_BIT7 | _BIT6));
    }
    // Load Signature to RSA Module as cipher text
    for(usIndex = 0; usIndex < (usSigSize / 8); usIndex++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Enable write cipher text to RSA Module
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, ((usSigSize / 8 - 1) - usIndex));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pstHdcp2SignKeyInfoType->pucSignFile[usIndex << 3], 8);
    }
    for(usIndex = 0; usIndex < (usRRModNSize / 8); usIndex++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load RRmodN
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x30 + ((usRRModNSize / 8 - 1) - usIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pstHdcp2SignKeyInfoType->pucSignRrmodn[usIndex << 3], 8);
    }

    for(usIndex = 0; usIndex < (usNKeySize / 8); usIndex++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load N Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0x90 + ((usNKeySize / 8 - 1) - usIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pstHdcp2SignKeyInfoType->pucSignNKey[(usIndex << 3)], 8);
    }

    for(usIndex = 0; usIndex < (usEKeySize / 8); usIndex++)
    {
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~_BIT0, _BIT0);

        // Load E Key
        ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (BYTE)(0xC0 + ((usEKeySize / 8 - 1) - usIndex)));

        memcpy((volatile BYTE xdata *)P63_17_HDCP_RSA_DATA_IN_DATA7, &pstHdcp2SignKeyInfoType->pucSignEKey[usIndex << 3], 8);
    }

    // Load Npinv to RSA Module
    memcpy((volatile BYTE xdata *)P63_12_HDCP_RSA_NP_INV_3, &pstHdcp2SignKeyInfoType->pucSignNpinv, usNPivSize);

    // Set RSA Write key done
    SET_HDCP22_RSA_WRITE_KEY_DONE();

    // Enable RSA Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT4 | _BIT0), (_BIT6 | _BIT5 | _BIT4));

    // Reset RSA Calcualte Enable to Start Calculate
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT4 | _BIT0), 0x00);

    // Polling 100ms for RSA Module Done
    if(ScalerTimerPollingFlagProc(100, P63_10_HDCP_RSA_CTRL0, _BIT2, _SUCCESS) == _TRUE)
    {
        // Disable RSA Module
        ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT7 | _BIT0), 0x00);
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------
// Description  : For Signature, Readout RSA result
// Input Value  : None
// Output Value : *pucArray
//--------------------------------------------------
void ScalerFwUpdateReadoutRsaforSign(BYTE *pucArray, WORD usRsaSize)
{
    WORD usIndex = 0;

    // Read Out RSA Message
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT6 | _BIT5 | _BIT0), _BIT6);

    // Read Message From One of 2 Address
    if(ScalerGetBit(P63_10_HDCP_RSA_CTRL0, _BIT1) == 0x00)
    {
        for(usIndex = 0; usIndex < (usRsaSize / 8); usIndex++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, usIndex);
            SET_HDCP22_RSA_READ_POP_OUT_ENABLE();
            memcpy(&pucArray[((usRsaSize / 8 - 1) - usIndex) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
    else
    {
        for(usIndex = 0; usIndex < (usRsaSize / 8); usIndex++)
        {
            ScalerSetByte(P63_16_HDCP_RSA_DATA_ADDR, (0x30 | usIndex));
            SET_HDCP22_RSA_READ_POP_OUT_ENABLE();
            memcpy(&pucArray[((usRsaSize / 8 - 1) - usIndex) * 8], (volatile BYTE xdata *)P63_20_HDCP_RSA_DATA_OUT_DATA7, 8);
        }
    }
}

//--------------------------------------------------
// Description  : For Signature, Sha256 Calc
// Input Value  : *pucInputArray, ucCalCount
// Output Value : _TRUE or _FALSE
//--------------------------------------------------
bit ScalerFwUpdateSha256CalculateforSign(BYTE *pucInputArray, BYTE ucCalCount)
{
    BYTE ucIndex = 0;

    // Set 1, Then Set 0 for Reset SHA256 Module
    SET_HDCP22_SHA_MODULE_RESET();
    CLR_HDCP22_SHA_MODULE_RESET();

    // Write SHA256 Input Data, Total 512 bits
    for(ucIndex = 0; ucIndex < 16; ucIndex++)
    {
        ScalerSetByte(P63_31_HDCP_SHA_DATA1, pucInputArray[ucIndex * 4]);
        ScalerSetByte(P63_32_HDCP_SHA_DATA2, pucInputArray[1 + ucIndex * 4]);
        ScalerSetByte(P63_33_HDCP_SHA_DATA3, pucInputArray[2 + ucIndex * 4]);
        ScalerSetByte(P63_34_HDCP_SHA_DATA4, pucInputArray[3 + ucIndex * 4]);
#if(_HW_HDCP_SHA_SRAM_WRITE_DONE_FUNCTION_SUPPORT == _ON)
        // Inform HW SHA data Has been set first 32 bit
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT0), _BIT0);

        // Polling 1ms for HDCP Sha Data Write Done
        if(ScalerTimerPollingFlagProc(1, P63_30_HDCP_SHA_CONTRL, _BIT6, _TRUE) == _TRUE)
        {
            ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~(_BIT6 | _BIT0), _BIT6);
        }
#else
        // Inform HW SHA data Has been set first 32 bit
        ScalerSetBit(P63_30_HDCP_SHA_CONTRL, ~_BIT0, _BIT0);

        ScalerMcuDelayXus(1);
#endif
    }
    if(ucCalCount == 0)
    {
        // Set First Calculate
        SET_HDCP22_SHA_FIRST_CALCULATE();

        // Enable SHA256 Calculate
        SET_HDCP22_SHA_CALCULATE_ENABLE();
    }
    else
    {
        // Disable First Calculate
        CLR_HDCP22_SHA_FIRST_CALCULATE();

        // Enable SHA256 Calculate
        SET_HDCP22_SHA_CALCULATE_ENABLE();
    }

    // Polling 10ms for HDCP Sha Done
    if(ScalerTimerPollingFlagProc(10, P63_30_HDCP_SHA_CONTRL, _BIT4, _TRUE) == _TRUE)
    {
        return _TRUE;
    }
    return _FALSE;
}

//--------------------------------------------------------------------------------------------------------------------------
// Description  : For Signature, Down Load RSA Key and Sign File
// Input Value  : pstHdcp2SignKeyInfoType, usLength, *pucReadArray, ucRSAType
// Output Value : None
//--------------------------------------------------------------------------------------------------------------------------
void ScalerFwUpdateDownLoadCalculateKeyforSign(StructSignKeyInfoType *pstHdcp2SignKeyInfoType, WORD usLength, BYTE *pucReadArray, EnumSignKeyInfo enumRSAType)
{
    switch(enumRSAType)
    {
        case _SIGN_FILE:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignFile, pucReadArray, usLength);
            break;

        case _SIGN_NKEY:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignNKey, pucReadArray, usLength);
            break;

        case _SIGN_RRMODN:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignRrmodn, pucReadArray, usLength);
            break;

        case _SIGN_NPINV:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignNpinv, pucReadArray, usLength);
            break;

        case _SIGN_EKEY:
            memcpy(&pstHdcp2SignKeyInfoType->pucSignEKey, pucReadArray, usLength);
            break;

        default:
            break;
    }
}


//--------------------------------------------------
// Description  : For Signature, Readout HASH result
// Input Value  : None
// Output Value : *pucArray
//--------------------------------------------------
void ScalerFwUpdateReadoutHashforSign(BYTE *pucArray)
{
    memcpy(pucArray, (volatile BYTE xdata *)P63_35_HDCP_SHA_0, 32);
}

//--------------------------------------------------
// Description  : For Signature, Release RSA Function
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerFwUpdateReleaseRsaforSign(void)
{
    // release HDCP RSA
    ScalerSetBit(P63_10_HDCP_RSA_CTRL0, ~(_BIT3 | _BIT0), _BIT3);
}
#endif // #if((_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA2048) || (_FW_UPDATE_CHECK_TYPE == _FW_UPDATE_CHECK_RTK_RSA3072))

//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateIntProc(void)
{
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
    ScalerFwUpdateDdcci0IntProc();
#endif

#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
    ScalerFwUpdateDdcci1IntProc();
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
    ScalerFwUpdateDdcci2IntProc();
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
    ScalerFwUpdateDdcci3IntProc();
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
    ScalerFwUpdateDdcci4IntProc();
#endif
}

#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateDdcci0IntProc(void)
{
    BYTE ucTempBuf = 0;
    BYTE ucIndex = 0;
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    BYTE xdata *pucIspXram = GET_ISP_XRAM_BUFFER(0);
#endif
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);
    // Clear status
    if(GET_FW_UPDATE_RUN_COMMAND() == _TRUE)
    {
        // Clear sub,data_in, stop    Flag
        MCU_FF27_IIC_STATUS &= ~(_BIT4 | _BIT1 | _BIT0);
        if((MCU_FF27_IIC_STATUS & _BIT2) == _BIT2)
        {
            ucTempBuf = MCU_FF25_IIC_DATA_IN;
        }

        return;
    }

    ucTempBuf = MCU_FF27_IIC_STATUS;

    if((ucTempBuf & _BIT1) == _BIT1)
    {
        // Clear SUB_I Flag
        MCU_FF27_IIC_STATUS &= ~_BIT1;
        g_usFwUpdateDdcciCountEXINT = 0;
        g_pucFwUpdateRxBuf[0] = MCU_FF24_IIC_SUB_IN;
        // Host write Enable
        MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
    }

    if((ucTempBuf & _BIT2) == _BIT2)
    {
        while((MCU_FF29_IIC_STATUS2 & _BIT1) == 0)
        {
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
            if(g_pucFwUpdateRxBuf[0] == _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS)
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT) < (_FW_UPDATE_FOREGROUND_MAX_ISP_LEN))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                pucIspXram[g_usFwUpdateDdcciCountEXINT - 1] = MCU_FF25_IIC_DATA_IN;
            }
            else
#endif
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT + 1) < (WORD)sizeof(g_pucFwUpdateRxBuf))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                g_pucFwUpdateRxBuf[g_usFwUpdateDdcciCountEXINT] = MCU_FF25_IIC_DATA_IN;
            }
        }
    }

    if((ucTempBuf & _BIT4) == _BIT4)
    {
        MCU_FF27_IIC_STATUS &= ~_BIT4;

        if(g_usFwUpdateDdcciCountEXINT > 0)
        {
            SET_FW_UPDATE_RUN_COMMAND();

            g_usFwUpdateDdcciCountEXINT = 0;
            // Host Write Disable
            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT5;
            // Reset IIC Data Buffer
            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

            for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex = ucIndex + 1)
            {
                MCU_FF26_IIC_DATA_OUT = _FW_UPDATE_RESULT_BUSY;
            }
            // Disable mcu write
            MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;

            // Reset data buffer
            MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;
        }
    }
}
#endif // #Endif(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)

#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateDdcci1IntProc(void)
{
    BYTE ucTempBuf = 0;
    BYTE ucIndex = 0;
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    BYTE xdata *pucIspXram = GET_ISP_XRAM_BUFFER(0);
#endif

    MCU_FE8D_IIC_1_STATUS2 &= ~(_BIT4 | _BIT5);
    // Clear status
    if(GET_FW_UPDATE_RUN_COMMAND() == _TRUE)
    {
        // Clear sub,data_in, stop    Flag
        MCU_FE8B_IIC_1_STATUS &= ~(_BIT4 | _BIT1 | _BIT0);
        if((MCU_FE8B_IIC_1_STATUS & _BIT2) == _BIT2)
        {
            ucTempBuf = MCU_FE89_IIC_1_DATA_IN;
        }

        return;
    }

    ucTempBuf = MCU_FE8B_IIC_1_STATUS;

    if((ucTempBuf & _BIT1) == _BIT1)
    {
        // Clear SUB_I Flag
        MCU_FE8B_IIC_1_STATUS &= ~_BIT1;
        g_usFwUpdateDdcciCountEXINT = 0;
        g_pucFwUpdateRxBuf[0] = MCU_FE88_IIC_1_SUB_IN;
        // Host write Enable
        MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;
    }

    if((ucTempBuf & _BIT2) == _BIT2)
    {
        while((MCU_FE8D_IIC_1_STATUS2 & _BIT1) == 0)
        {
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
            if(g_pucFwUpdateRxBuf[0] == _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS)
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT) < (_FW_UPDATE_FOREGROUND_MAX_ISP_LEN))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                pucIspXram[g_usFwUpdateDdcciCountEXINT - 1] = MCU_FE89_IIC_1_DATA_IN;
            }
            else
#endif
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT + 1) < (WORD)sizeof(g_pucFwUpdateRxBuf))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                g_pucFwUpdateRxBuf[g_usFwUpdateDdcciCountEXINT] = MCU_FE89_IIC_1_DATA_IN;
            }
        }
    }

    if((ucTempBuf & _BIT4) == _BIT4)
    {
        MCU_FE8B_IIC_1_STATUS &= ~_BIT4;
        if(g_usFwUpdateDdcciCountEXINT > 0)
        {
            SET_FW_UPDATE_RUN_COMMAND();

            g_usFwUpdateDdcciCountEXINT = 0;
            // Host Write Disable
            MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT5;
            // Reset IIC Data Buffer
            MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;

            for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex = ucIndex + 1)
            {
                MCU_FE8A_IIC_1_DATA_OUT = _FW_UPDATE_RESULT_BUSY;
            }
            // Disable mcu write
            MCU_FE8E_IIC_1_IRQ_CONTROL2 &= ~_BIT5;

            // Reset data buffer
            MCU_FE8E_IIC_1_IRQ_CONTROL2 |= _BIT6;
        }
    }
}
#endif // #if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateDdcci2IntProc(void)
{
    BYTE ucTempBuf = 0;
    BYTE ucIndex = 0;
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    BYTE xdata *pucIspXram = GET_ISP_XRAM_BUFFER(0);
#endif

    MCU_FE9B_IIC_2_STATUS2 &= ~(_BIT4 | _BIT5);
    // Clear status
    if(GET_FW_UPDATE_RUN_COMMAND() == _TRUE)
    {
        // Clear sub,data_in, stop    Flag
        MCU_FE99_IIC_2_STATUS &= ~(_BIT4 | _BIT1 | _BIT0);
        if((MCU_FE99_IIC_2_STATUS & _BIT2) == _BIT2)
        {
            ucTempBuf = MCU_FE97_IIC_2_DATA_IN;
        }

        return;
    }

    ucTempBuf = MCU_FE99_IIC_2_STATUS;

    if((ucTempBuf & _BIT1) == _BIT1)
    {
        // Clear SUB_I Flag
        MCU_FE99_IIC_2_STATUS &= ~_BIT1;
        g_usFwUpdateDdcciCountEXINT = 0;
        g_pucFwUpdateRxBuf[0] = MCU_FE96_IIC_2_SUB_IN;
        // Host write Enable
        MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;
    }

    if((ucTempBuf & _BIT2) == _BIT2)
    {
        while((MCU_FE9B_IIC_2_STATUS2 & _BIT1) == 0)
        {
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
            if(g_pucFwUpdateRxBuf[0] == _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS)
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT) < (_FW_UPDATE_FOREGROUND_MAX_ISP_LEN))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                pucIspXram[g_usFwUpdateDdcciCountEXINT - 1] = MCU_FE97_IIC_2_DATA_IN;
            }
            else
#endif
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT + 1) < (WORD)sizeof(g_pucFwUpdateRxBuf))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                g_pucFwUpdateRxBuf[g_usFwUpdateDdcciCountEXINT] = MCU_FE97_IIC_2_DATA_IN;
            }
        }
    }

    if((ucTempBuf & _BIT4) == _BIT4)
    {
        MCU_FE99_IIC_2_STATUS &= ~_BIT4;
        if(g_usFwUpdateDdcciCountEXINT > 0)
        {
            SET_FW_UPDATE_RUN_COMMAND();

            g_usFwUpdateDdcciCountEXINT = 0;
            // Host Write Disable
            MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT5;
            // Reset IIC Data Buffer
            MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;

            for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex = ucIndex + 1)
            {
                MCU_FE98_IIC_2_DATA_OUT = _FW_UPDATE_RESULT_BUSY;
            }
            // Disable mcu write
            MCU_FE9C_IIC_2_IRQ_CONTROL2 &= ~_BIT5;

            // Reset data buffer
            MCU_FE9C_IIC_2_IRQ_CONTROL2 |= _BIT6;
        }
    }
}
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateDdcci3IntProc(void)
{
    BYTE ucTempBuf = 0;
    BYTE ucIndex = 0;
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    BYTE xdata *pucIspXram = GET_ISP_XRAM_BUFFER(0);
#endif

    MCU_FEAA_IIC_3_STATUS2 &= ~(_BIT5 | _BIT4);
    // Clear status
    if(GET_FW_UPDATE_RUN_COMMAND() == _TRUE)
    {
        // Clear sub,data_in, stop    Flag
        MCU_FEA8_IIC_3_STATUS &= ~(_BIT4 | _BIT1 | _BIT0);
        if((MCU_FEA8_IIC_3_STATUS & _BIT2) == _BIT2)
        {
            ucTempBuf = MCU_FEA6_IIC_3_DATA_IN;
        }

        return;
    }

    ucTempBuf = MCU_FEA8_IIC_3_STATUS;

    if((ucTempBuf & _BIT1) == _BIT1)
    {
        // Clear SUB_I Flag
        MCU_FEA8_IIC_3_STATUS &= ~_BIT1;
        g_usFwUpdateDdcciCountEXINT = 0;
        g_pucFwUpdateRxBuf[0] = MCU_FEA5_IIC_3_SUB_IN;
        // Host write Enable
        MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;
    }

    if((ucTempBuf & _BIT2) == _BIT2)
    {
        while((MCU_FEAA_IIC_3_STATUS2 & _BIT1) == 0)
        {
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
            if(g_pucFwUpdateRxBuf[0] == _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS)
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT) < (_FW_UPDATE_FOREGROUND_MAX_ISP_LEN))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                pucIspXram[g_usFwUpdateDdcciCountEXINT - 1] = MCU_FEA6_IIC_3_DATA_IN;
            }
            else
#endif
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT + 1) < (WORD)sizeof(g_pucFwUpdateRxBuf))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                g_pucFwUpdateRxBuf[g_usFwUpdateDdcciCountEXINT] = MCU_FEA6_IIC_3_DATA_IN;
            }
        }
    }

    if((ucTempBuf & _BIT4) == _BIT4)
    {
        MCU_FEA8_IIC_3_STATUS &= ~_BIT4;

        if(g_usFwUpdateDdcciCountEXINT > 0)
        {
            SET_FW_UPDATE_RUN_COMMAND();

            g_usFwUpdateDdcciCountEXINT = 0;
            // Host Write Disable
            MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT5;
            // Reset IIC Data Buffer
            MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;

            for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex = ucIndex + 1)
            {
                MCU_FEA7_IIC_3_DATA_OUT = _FW_UPDATE_RESULT_BUSY;
            }
            // Disable mcu write
            MCU_FEAB_IIC_3_IRQ_CONTROL2 &= ~_BIT5;

            // Reset data buffer
            MCU_FEAB_IIC_3_IRQ_CONTROL2 |= _BIT6;
        }
    }
}
#endif

#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
//--------------------------------------------------
// Description  : Background Fw Update DDCCI  Int Proc
// Input Value  : none
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateDdcci4IntProc(void)
{
    BYTE ucTempBuf = 0;
    BYTE ucIndex = 0;
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
    BYTE xdata *pucIspXram = GET_ISP_XRAM_BUFFER(0);
#endif

    MCU_FD07_IIC_4_STATUS2 &= ~(_BIT5 | _BIT4);

    // Clear status
    if(GET_FW_UPDATE_RUN_COMMAND() == _TRUE)
    {
        // Clear sub,data_in, stop    Flag
        MCU_FD05_IIC_4_STATUS &= ~(_BIT4 | _BIT1 | _BIT0);
        if((MCU_FD05_IIC_4_STATUS & _BIT2) == _BIT2)
        {
            ucTempBuf = MCU_FD03_IIC_4_DATA_IN;
        }

        return;
    }

    ucTempBuf = MCU_FD05_IIC_4_STATUS;

    if((ucTempBuf & _BIT1) == _BIT1)
    {
        // Clear SUB_I Flag
        MCU_FD05_IIC_4_STATUS &= ~_BIT1;
        g_usFwUpdateDdcciCountEXINT = 0;
        g_pucFwUpdateRxBuf[0] = MCU_FD02_IIC_4_SUB_IN;
        // Host write Enable
        MCU_FD08_IIC_4_IRQ_CONTROL2 &= ~_BIT5;
    }

    if((ucTempBuf & _BIT2) == _BIT2)
    {
        while((MCU_FD07_IIC_4_STATUS2 & _BIT1) == 0)
        {
#if(_FW_UPDATE_FOREGROUND_SUPPORT == _ON)
            if(g_pucFwUpdateRxBuf[0] == _FW_UPDATE_FOREGROUND_ISP_DATA_SUB_ADDRESS)
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT) < (_FW_UPDATE_FOREGROUND_MAX_ISP_LEN))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FD08_IIC_4_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                pucIspXram[g_usFwUpdateDdcciCountEXINT - 1] = MCU_FD03_IIC_4_DATA_IN;
            }
            else
#endif
            {
                // Avoid buffer overflow
                if((g_usFwUpdateDdcciCountEXINT + 1) < (WORD)sizeof(g_pucFwUpdateRxBuf))
                {
                    g_usFwUpdateDdcciCountEXINT++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FD08_IIC_4_IRQ_CONTROL2 |= _BIT6;
                    g_usFwUpdateDdcciCountEXINT = 0;
                    break;
                }
                g_pucFwUpdateRxBuf[g_usFwUpdateDdcciCountEXINT] = MCU_FD03_IIC_4_DATA_IN;
            }
        }
    }

    if((ucTempBuf & _BIT4) == _BIT4)
    {
        MCU_FD05_IIC_4_STATUS &= ~_BIT4;

        if(g_usFwUpdateDdcciCountEXINT > 0)
        {
            SET_FW_UPDATE_RUN_COMMAND();

            g_usFwUpdateDdcciCountEXINT = 0;
            // Host Write Disable
            MCU_FD08_IIC_4_IRQ_CONTROL2 |= _BIT5;
            // Reset IIC Data Buffer
            MCU_FD08_IIC_4_IRQ_CONTROL2 |= _BIT6;

            for(ucIndex = 0; ucIndex < _HW_DDCCI_BUF_SIZE; ucIndex = ucIndex + 1)
            {
                MCU_FD04_IIC_4_DATA_OUT = _FW_UPDATE_RESULT_BUSY;
            }
            // Disable mcu write
            MCU_FD08_IIC_4_IRQ_CONTROL2 &= ~_BIT5;

            // Reset data buffer
            MCU_FD08_IIC_4_IRQ_CONTROL2 |= _BIT6;
        }
    }
}
#endif

#if(_FW_ISP_SPEED_UP_PROCESS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : FW Udpate Speed Up Inital
// Input Value  : ulStartAddr: Start Flash Address
//                : usPageLen: Progam Length per time
//                : ucSlave:Slave Address
//                : ucSub: Sub Address
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateSpeedUpInital(DWORD ulStartAddr, WORD usPageLen, BYTE ucSlave, BYTE ucSub)
{
    ScalerFwUpdateDisableNormalDdcci();
    // Disable Bdg ISP
    ScalerFwUpdateEnableSpeedUp(_FALSE);
    // Set DDCCI CHannle
    ScalerSetBit(PFD_90_BACKGROUND_ISP_CTRL, ~(_BIT3 | _BIT2 | _BIT1), (g_enumFwUpdateDdcciPort << 1));
    // Set Bdg ISP flow
    ScalerSetByte(PFD_98_BACKGROUND_ISP_LENGTH, usPageLen - 1);

    // Set Start Address
    ScalerSetByte(PFD_94_BACKGROUND_ISP_ADDR_4TH, ((ulStartAddr & 0xFF000000) >> 24));
    ScalerSetByte(PFD_95_BACKGROUND_ISP_ADDR_H, ((ulStartAddr & 0xFF0000) >> 16));
    ScalerSetByte(PFD_96_BACKGROUND_ISP_ADDR_M, ((ulStartAddr & 0xFF00) >> 8));
    ScalerSetByte(PFD_97_BACKGROUND_ISP_ADDR_L, (ulStartAddr & 0xFF));

    // Set Slave Addres & sub Addres
    ScalerSetByte(PFD_92_BACKGROUND_ISP_SLAVE_ADDRESS, ucSlave);
    ScalerSetByte(PFD_93_BACKGROUND_ISP_SUB_ADDRESS, ucSub);

    // Enable Bdg ISP
    ScalerFwUpdateEnableSpeedUp(_TRUE);
}

//--------------------------------------------------
// Description  : FW Udpate Speed Up Disable
// Input Value  : bEnable: TRUE:enbale, FALSE:Disable
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateEnableSpeedUp(bit bEnable)
{
    if(bEnable == _TRUE)
    {
        ScalerSetBit(PFD_90_BACKGROUND_ISP_CTRL, ~(_BIT0), _BIT0);
    }
    else
    {
        ScalerSetBit(PFD_90_BACKGROUND_ISP_CTRL, ~(_BIT0), 0);
    }
}

//--------------------------------------------------
// Description  : FW Udpate Modify Isp Leng
// Input Value  :usPageLen: Progam Length per time
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateMdofiySpeedUpIspLen(WORD usPageLen)
{
    // Disable Bdg ISP
    ScalerFwUpdateEnableSpeedUp(_FALSE);
    // Set Bdg ISP flow
    ScalerSetByte(PFD_98_BACKGROUND_ISP_LENGTH, usPageLen - 1);
    // Enable Bdg ISP
    ScalerFwUpdateEnableSpeedUp(_TRUE);
}

//--------------------------------------------------
// Description  : FW Udpate Disable Normal ddcci
// Input Value  :usPageLen: Progam Length per time
// Output Value : none
//--------------------------------------------------
void ScalerFwUpdateDisableNormalDdcci(void)
{
    switch(g_enumFwUpdateDdcciPort)
    {
#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
        case _DDCCI0:
            MCU_FF23_IIC_SET_SLAVE = 0x3C;
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
        case _DDCCI1:
            MCU_FE87_IIC_1_SET_SLAVE = 0x3C;
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
        case _DDCCI2:
            MCU_FE95_IIC_2_SET_SLAVE = 0x3C;
            break;
#endif

#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
        case _DDCCI3:
            MCU_FEA4_IIC_3_SET_SLAVE = 0x3C;
            break;
#endif
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3)
        case _DDCCI4:
            MCU_FD01_IIC_4_SET_SLAVE = 0x3C;
            break;
#endif
        default:
            break;
    }
}
#endif

#endif
