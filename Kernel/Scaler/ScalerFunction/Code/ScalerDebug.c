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
// ID Code      : ScalerDebug.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_DEBUG__

#include "ScalerFunctionInclude.h"
#include "Debug/ScalerDebug.h"

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
#warning "NOTE: DEBUG MESSAGE SUPPORT ON!!"
#endif

#if(_PROMOTE_DDC_INT_TO_HW4_INT_LVL == _ON)
#warning "NOTE: _PROMOTE_DDC_INT_TO_HW4_INT_LVL ON!!"
#warning "NOTE: DDC INT related application(EX:FwUpdate, DDC/DDCCI, HDMI RX DDC, AutoTest) will be affected!!"
#endif

#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
#warning "NOTE: _DEBUG_IIC_BY_USERINTERFACE ON!!"
#endif

#if((_DEBUG_MESSAGE_SUPPORT == _ON) && (_HDMI_FREESYNC_SUPPORT == _ON))
#if(_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD != _EDID_SWITCH_MODE)
#warning "_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD Should Be _EDID_SWITCH_MODE When Both _DEBUG_MESSAGE_SUPPORT and _HDMI_FREESYNC_SUPPORT are _ON!!! MCCS CODE in EDID Should be 0!!!"
#endif
#endif

//****************************************************************************
// CODE TABLES
//****************************************************************************


//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
volatile bit g_bDebugRunCommand = _FALSE;
volatile BYTE g_pucDebugDdcciData[_SCALER_DEBUG_BUF_LEN];
volatile BYTE g_ucDebugDdcciCommandNumber;
volatile bit g_bDebugHalt = _FALSE;

EnumDDCCIDebugMode g_enumDebugDdcciMode = _DEBUG_MODE;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
volatile bit g_bDebugMessageEven = _FALSE;
volatile WORD g_usDebugFilterPro;
volatile bit g_bDebugFwHalt = _FALSE;
bit g_bDebugMessageStart = _FALSE;
BYTE idata g_pucDebugMessageBUF[4];
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

#if(_TIME_CURSOR_SUPPORT == _ON)
StructTimerSampleMS g_pstDebugTimerCursorMS[_DEBUG_TIME_CURSOR_END];
BYTE g_ucDebugTimerCursorUsedMS;
StructTimerSampleUS g_pstDebugTimerCursorUS[_DEBUG_TIME_CURSOR_END];
BYTE g_ucDebugTimerCursorUsedUS;
#endif

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
StructDualBankBootDebug g_stDebugDualBank;
bit g_bDebugDdcciSwitchState = _FALSE;
#endif

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
bit g_bDebugCustomerCmdRev = _FALSE;
BYTE g_pucDebugCustomerRevData[_SCALER_DEBUG_BUF_LEN];
#endif

#if(_SYSTEM_BUS_ERROR_DEBUG_SUPPORT == _ON)
// g_pulDebugSysBusErrorInfo[0]: enumDebugSysBusErrorType
// g_pulDebugSysBusErrorInfo[1~7]:
// RX3081: ={CP0_STATUS, CP0_CAUSE, CP0_EPC, CP0_BADVADDR, CP0_CCTL, CP0_CK0, CP0_CK1}
// TR9   : ={MSTATUS, MEPC, MEPC, MTVAL, MIE, MIP, MTVEC}
// g_pulDebugSysBusErrorInfo[8~13]:Detail Information
// g_pulDebugSysBusErrorInfo[14]:Buffer Address of CPU Context
DWORD g_pulDebugSysBusErrorInfo[15];
// CPU Context
// RX3081: ={SP,a0~a3,s0,s1,t8,ra,LO,HI,v0,v1,C0_EPC,C0_STS}
// TR9   : ={SP,a0~a7,t0~t6,ra,mstatus,mepc,mie,s0~s11}
DWORD g_pulDebugCpuContext[32];
#endif

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : DDC-CI or Debug mode Select
// Input Value  : enumMode --> _DEBUG_MODE / _DDCCI_MODE
// Output Value : None
//--------------------------------------------------
void ScalerDebugSelectDDCCIDebugMode(EnumDDCCIDebugMode enumMode)
{
    g_enumDebugDdcciMode = enumMode;
}

//--------------------------------------------------
// Description  : Get DDC-CI or Debug Mode
// Input Value  : None
// Output Value : _DEBUG_MODE / _DDCCI_MODE
//--------------------------------------------------
EnumDDCCIDebugMode ScalerDebugGetDDCCIDebugMode(void)
{
    return g_enumDebugDdcciMode;
}

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Debug Message process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugMessage(SBYTE *pchMessage, DWORD ulValue)
{
    if(SKIP_DBG_IN_INTERRUPT() == _TRUE)
    {
        // Skip Execute ScalerDebug when in Interrupt
        return;
    }

#if(_SCPU_SUPPORT == _ON)
    if((g_pucDebugDdcciData[0] != 0x55) && (g_bDebugMessageEven == _FALSE))
    {
        return;
    }

    if(*pchMessage == 0)
    {
        return;
    }

    BYTE ucMsg0 = pchMessage[0];

    if((g_usDebugFilterPro & 0xF800) == 0xC800)
    {
        if((ucMsg0 >= '0') && (ucMsg0 <= '9'))
        {
            if((g_usDebugFilterPro & (1 << (ucMsg0 - '0'))) == 0)
            {
                return;
            }
        }
        else
        {
            if((g_usDebugFilterPro & (_BIT2 << 8)) == 0)
            {
                return;
            }
        }
    }

    // Acquire BW32 resource lock
    if(RESOURCE_ACQUIRE(_RESOURCE_ID_DBG_MSG, (_WAIT_DBG_MSG_TIMEOUT)) == _FALSE)
    {
        return;
    }
#endif
    ScalerDebugMessageProcess(pchMessage, ulValue);

#if(_SCPU_SUPPORT == _ON)
    RESOURCE_RELEASE(_RESOURCE_ID_DBG_MSG);
#endif
}

//--------------------------------------------------
// Description  : Debug Message process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugMessageProcess(SBYTE *pchMessage, DWORD ulValue)
{
    BYTE ucCnt = 0;
    BYTE ucLength = 0;
    BYTE ucCheckSum = 0;
    BYTE ucIndex = 0;
    SBYTE pchMsg[257];

    pchMsg[256] = 0;
    {
        WORD usIdx = 0;
        while(usIdx < 256)
        {
            SBYTE chCHAR = pchMessage[usIdx];
            pchMsg[usIdx] = chCHAR;
            if(chCHAR == 0)
            {
                break;
            }
            usIdx++;
        }
    }

    if(g_pucDebugDdcciData[0] == 0x55)
    {
        g_bDebugMessageEven = _TRUE;
    }

    if(g_bDebugMessageEven == _FALSE)
    {
        return;
    }

    if(*pchMessage == 0)
    {
        return;
    }

    if((g_usDebugFilterPro & 0xF800) == 0xC800)
    {
        if((pchMsg[0] >= '0') && (pchMsg[0] <= '9'))
        {
            if((g_usDebugFilterPro & (1 << (pchMsg[0] - '0'))) == 0)
            {
                return;
            }
        }
        else
        {
            if((g_usDebugFilterPro & (_BIT2 << 8)) == 0)
            {
                return;
            }
        }
    }

    g_bDebugMessageStart = _FALSE;
    g_bDebugFwHalt = _TRUE;

    for(ucCheckSum = 0; ucCheckSum < 4; ucCheckSum++)
    {
        g_pucDebugMessageBUF[ucCheckSum] = 0;
    }

    do
    {
        if(g_bDebugRunCommand == _TRUE)
        {
            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;
            ucCnt = 0;

            switch(g_pucDebugDdcciData[0])
            {
                case 0x20: // Handshake Setting
                case 0x55:

                    if(g_pucDebugDdcciData[1] == 0x5A)
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = 0xE7;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }
                    else if(g_pucDebugDdcciData[1] == 0xA5)
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = 0xEC;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }
                    else
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = 0xF1;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }

                    break;

                case 0x25: // Debug Message Start

                    if(g_pucDebugDdcciData[1] == 0)
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            ucLength = 0; // Total Length
                            ucIndex = 0;
                            ucCheckSum = 0x00; // Initial checksum

                            do
                            {
                                ucCheckSum += pchMsg[ucLength];
                            }
                            while((pchMsg[ucLength++] != 0) && (ucLength < 240)); // To count the length of pArray1 and checksum

                            g_pucDebugMessageBUF[0] = (BYTE)(ulValue >> 24);
                            g_pucDebugMessageBUF[1] = (BYTE)(ulValue >> 16);
                            g_pucDebugMessageBUF[2] = (BYTE)(ulValue >> 8);
                            g_pucDebugMessageBUF[3] = (BYTE)(ulValue);
                            ucLength = ucLength - 1;

                            MCU_FF26_IIC_DATA_OUT = 0xFA;
                            MCU_FF26_IIC_DATA_OUT = 0xF5;
                            MCU_FF26_IIC_DATA_OUT = ucLength;
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[0];
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[1];
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[2];
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[3];

                            ucIndex = ucCheckSum;
                            ucCheckSum = 0x0F;
                            ucCheckSum = ucCheckSum + ucLength + g_pucDebugMessageBUF[0] + g_pucDebugMessageBUF[1] + g_pucDebugMessageBUF[2] + g_pucDebugMessageBUF[3];

                            g_pucDebugMessageBUF[0] = ucCheckSum + ucIndex; // Save checksum for all string and data
                            MCU_FF26_IIC_DATA_OUT = g_pucDebugMessageBUF[0]; // Checksum for all string and data
                            MCU_FF26_IIC_DATA_OUT = ucCheckSum + g_pucDebugMessageBUF[0];
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x09) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }
                    else
                    {
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            ucIndex = (g_pucDebugDdcciData[1] - 1) * 15;
                            ucCheckSum = g_pucDebugDdcciData[1] + 0x0F;
                            g_pucDebugMessageBUF[0] = 1;

                            do
                            {
                                MCU_FF26_IIC_DATA_OUT = pchMsg[ucIndex];
                                ucCheckSum += pchMsg[ucIndex];
                                ucIndex++;
                                g_pucDebugMessageBUF[0] = g_pucDebugMessageBUF[0] + 1;
                            }
                            while((ucIndex < (g_pucDebugDdcciData[1] * 15)) && (pchMsg[ucIndex] != 0));

                            MCU_FF26_IIC_DATA_OUT = ucCheckSum;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != g_pucDebugMessageBUF[0]) && ((ucCnt++) < _DATA_OUT_COUNT));
                        g_bDebugMessageStart = _TRUE;
                    }

                    break;

                case 0x2A: // Debug Message End

                    if(g_bDebugMessageStart == _TRUE)
                    {
                        g_bDebugMessageStart = _FALSE; // Debug Message End
                        g_bDebugFwHalt = _FALSE;
                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = 0xF7;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));
                    }

                    break;

                case 0x2F: // Debug Message Event finsih

                    do
                    {
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                        MCU_FF26_IIC_DATA_OUT = 0xF5;
                    }
                    while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                    g_bDebugMessageEven = _FALSE;
                    g_bDebugFwHalt = _FALSE;
                    MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xBF;
                    break;

                default:
                    break;
            }

            g_bDebugRunCommand = _FALSE;
            g_ucDebugDdcciCommandNumber = 0;

            MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xDF;

            // Delay Time us [30,x] Avoid MCU Clock too fast lead to Tool Communication Fail.
            DELAY_30US();

            // Release SCL Pin
#if((_DEBUG_DDC_CHANNEL_SEL == _DDC5) && (_HW_DDC5_EXIST == _ON))
            ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC4) && (_HW_DDC4_EXIST == _ON))
            ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC3) && (_HW_DDC3_EXIST == _ON))
            ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC2) && (_HW_DDC2_EXIST == _ON))
            ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC1) && (_HW_DDC1_EXIST == _ON))
            ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC0) && (_HW_DDC0_EXIST == _ON))
            ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) && (_HW_ISP_DDC_EXIST == _ON))
            ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif
        }
    }
    while(g_bDebugFwHalt != _FALSE);

    g_bDebugMessageStart = _FALSE;
    g_bDebugFwHalt = _FALSE;
}

//--------------------------------------------------
// Description  : Check Ddc For Debug
// Input Value  : Input Port
// Output Value : None
//--------------------------------------------------
bit ScalerDebugCheckDebugPort(EnumInputPort enumInputPort)
{
    switch(enumInputPort)
    {
#if((_D0_INPUT_PORT_TYPE != _D0_NO_PORT) && (_DEBUG_DDC_CHANNEL_SEL == _DDC0))
        case _D0_INPUT_PORT:
            return _TRUE;
#endif

#if((_D1_INPUT_PORT_TYPE != _D1_NO_PORT) && (_DEBUG_DDC_CHANNEL_SEL == _DDC1))
        case _D1_INPUT_PORT:
            return _TRUE;
#endif

#if((_D2_INPUT_PORT_TYPE != _D2_NO_PORT) && (_DEBUG_DDC_CHANNEL_SEL == _DDC2))
        case _D2_INPUT_PORT:
            return _TRUE;
#endif

#if((_D3_INPUT_PORT_TYPE != _D3_NO_PORT) && (_DEBUG_DDC_CHANNEL_SEL == _DDC3))
        case _D3_INPUT_PORT:
            return _TRUE;
#endif

#if((_D4_INPUT_PORT_TYPE != _D4_NO_PORT) && (_DEBUG_DDC_CHANNEL_SEL == _DDC4))
        case _D4_INPUT_PORT:
            return _TRUE;
#endif

#if((_D5_INPUT_PORT_TYPE != _D5_NO_PORT) && (_DEBUG_DDC_CHANNEL_SEL == _DDC5))
        case _D5_INPUT_PORT:
            return _TRUE;
#endif
        default:
            return _FALSE;
    }
}
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

#if(_TIME_CURSOR_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Time Cursor Difference for MS
// Input Value  : Debug Time Cursor
// Output Value : Time Difference for Ms
//--------------------------------------------------
WORD ScalerDebugGetTimerCursorMSDifference(EnumDebugTimeCursor enumIndex)
{
    // Check if cursor is used
    if(((g_ucDebugTimerCursorUsedMS >> enumIndex) & _BIT0) == _DISABLE)
    {
        return 0xFFFF;
    }
    else
    {
        // Calculate counter difference
        if(g_pstDebugTimerCursorMS[enumIndex].usCounter_StartMS <= g_pstDebugTimerCursorMS[enumIndex].usCounter_EndMS)
        {
            return g_pstDebugTimerCursorMS[enumIndex].usCounter_EndMS - g_pstDebugTimerCursorMS[enumIndex].usCounter_StartMS;
        }
        else
        {
            return 0xFFFF - g_pstDebugTimerCursorMS[enumIndex].usCounter_StartMS + g_pstDebugTimerCursorMS[enumIndex].usCounter_EndMS;
        }
    }
}

//--------------------------------------------------
// Description  : Get Time Cursor Difference for US
// Input Value  : Debug Time Cursor
// Output Value : Time Difference for US
//--------------------------------------------------
DWORD ScalerDebugGetTimerCursorUSDifference(EnumDebugTimeCursor enumIndex)
{
    WORD usMsRecord = 0;
    WORD usUsRecord = 0;

    WORD usMsStart = g_pstDebugTimerCursorMS[enumIndex].usCounter_StartMS;
    WORD usMsEnd = g_pstDebugTimerCursorMS[enumIndex].usCounter_EndMS;

    DWORD ulUsStart = g_pstDebugTimerCursorUS[enumIndex].ulCounter_StartUS;
    DWORD ulUsEnd = g_pstDebugTimerCursorUS[enumIndex].ulCounter_EndUS;
    DWORD ulUsTarget = ScalerTimerGetTargetValue(_CPU_TIMER_3);

    // Check if cursor is used
    if((((g_ucDebugTimerCursorUsedMS >> enumIndex) & _BIT0) == 0) || (((g_ucDebugTimerCursorUsedUS >> enumIndex) & _BIT0) == 0))
    {
        return 0xFFFF;
    }

    // Calculate Ms
    if(usMsStart <= usMsEnd)
    {
        usMsRecord = (usMsEnd - usMsStart);
    }
    else
    {
        usMsRecord = (0xFFFF - usMsStart + usMsEnd);
    }

    // Calculate Us
    if(ulUsStart <= ulUsEnd)
    {
        usUsRecord = (WORD)((ulUsEnd - ulUsStart) * 1000 / ulUsTarget);
    }
    else
    {
        if(usMsRecord != 0)
        {
            usMsRecord -= 1;
        }

        usUsRecord = (WORD)((ulUsTarget + ulUsEnd - ulUsStart) * 1000 / ulUsTarget);
    }

    return ((DWORD)usMsRecord * 1000 + usUsRecord);
}
#endif // End of #if(_TIME_CURSOR_SUPPORT == _ON)

//--------------------------------------------------
// Description  : IC Debug Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebug(void)
{
    BYTE ucCnt = 0;
    BYTE ucDebugHalt = 0;
    BYTE ucResult = 0;
    WORD usAddress = 0;
    WORD usTargetAddr = 0;

    if(SKIP_DBG_IN_INTERRUPT() == _TRUE)
    {
        // Skip Execute ScalerDebug when in Interrupt
        return;
    }

    if(g_enumDebugDdcciMode == _DEBUG_MODE)
    {
        do
        {
            if(g_bDebugRunCommand == _TRUE)
            {
                ucCnt = 0;

                switch(g_pucDebugDdcciData[0])
                {
                    case 0x80:
                        ucDebugHalt = g_pucDebugDdcciData[1];
                        g_bDebugHalt = ((ucDebugHalt == 0) ? _FALSE : _TRUE);
                        break;

                    case 0x41:
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;

                        // CScalerRead
                        MCU_FFF3_SCA_INF_CONTROL |= 0x20;
                        MCU_FFF4_SCA_INF_ADDR = g_pucDebugDdcciData[1];
                        ucResult = MCU_FFF5_SCA_INF_DATA;

                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = ucResult;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                        break;

                    case 0x44:
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;

#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
                        if(UserInterfaceDebugIIC(_READ, g_pucDebugDdcciData, &ucResult) == _DBG_OFF)
#endif
                        {
#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

                            SET_SW_IIC_STATUS(_IIC_SYS_EEPROM);

#if(_EEPROM_TYPE == _EEPROM_24LC16)
                            ScalerMcuIICRead(g_pucDebugDdcciData[2], 1, g_pucDebugDdcciData[1], 1, &ucResult);
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
                            ScalerMcuIICRead(g_pucDebugDdcciData[2], 2, ((g_pucDebugDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDebugDdcciData[1]) & 0x00FF), 1, &ucResult);
#endif

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_HW_IIC_SUPPORT == _ON)
#if(_EEPROM_TYPE == _EEPROM_24LC16)
                            ScalerMcuHwIICRead(g_pucDebugDdcciData[2], 1, g_pucDebugDdcciData[1], 1, &ucResult, _PCB_SYS_EEPROM_IIC);
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
                            ScalerMcuHwIICRead(g_pucDebugDdcciData[2], 2, ((g_pucDebugDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDebugDdcciData[1]) & 0x00FF), 1, &ucResult, _PCB_SYS_EEPROM_IIC);
#endif
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)
                        }

                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = ucResult;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                        break;

                    case 0x45:
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;

#if((_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO))

#if(_HW_IIC_SUPPORT == _ON)
#if(_EEPROM_TYPE == _EEPROM_24LC16)
                        ScalerMcuHwIICRead(g_pucDebugDdcciData[2], 1, g_pucDebugDdcciData[1], 1, &ucResult, _NO_IIC_PIN);
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
                        ScalerMcuHwIICRead(g_pucDebugDdcciData[2], 2, ((g_pucDebugDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDebugDdcciData[1]) & 0x00FF), 1, &ucResult, _NO_IIC_PIN);
#endif
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

#endif // End of #if(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO)

                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF26_IIC_DATA_OUT = ucResult;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                        break;

#if(_DEBUG_MESSAGE_SUPPORT == _ON)
                    case 0x2F: // Debug Message Event finsih
                        MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x20;

                        do
                        {
                            MCU_FF2A_IIC_IRQ_CONTROL2 |= 0x40;
                            MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xBF; // Reset IIC Data Buffer
                            MCU_FF26_IIC_DATA_OUT = 0xF5;
                        }
                        while(((MCU_FF35_DDCCI_REMAIN_DATA & 0x1F) != 0x01) && ((ucCnt++) < _DATA_OUT_COUNT));

                        MCU_FF2A_IIC_IRQ_CONTROL2 &= 0xDF;
                        g_bDebugMessageStart = _FALSE;
                        g_bDebugFwHalt = _FALSE;
                        g_bDebugMessageEven = _FALSE;
                        break;
#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _ON)

                    case 0x3A:
                        // Read flash(if the address is max than 0xFF00, read mcu register)
                        usTargetAddr = (g_pucDebugDdcciData[2] << 8) + g_pucDebugDdcciData[1];
                        if(CHK_ADDRESS_ACCESSIBLE(GET_XDATA_REG_32BIT_ADDR(usTargetAddr)) == _TRUE)
                        {
                            MCU_FF26_IIC_DATA_OUT = ScalerGetByte(usTargetAddr);
                        }
                        else
                        {
                            // The range of target addr belongs to 8to32 IP, being readed via ISP Mode
                            MCU_FF26_IIC_DATA_OUT = 0;
                        }
                        break;

                    case 0x3B:
                        // Write flash(if the address is max than 0xFF00, write mcu register)
                        usTargetAddr = (g_pucDebugDdcciData[2] << 8) + g_pucDebugDdcciData[1];
                        if(CHK_ADDRESS_ACCESSIBLE(GET_XDATA_REG_32BIT_ADDR(usTargetAddr)) == _TRUE)
                        {
                            ScalerSetByte(usTargetAddr, g_pucDebugDdcciData[3]);
                        }
                        break;

                    case _SCALER_READ_REGISTERS_CMD:
                        ScalerDebugGetRegisters();
                        break;

                    case _SCALER_WRITE_REGISTERS_CMD:
                        ScalerDebugSetRegisters();
                        break;

                    case _SCALER_WRITE_32BITSREGISTERS_CMD:
                        ScalerDebugSet32BitRegisters(_SCALER_WRITE_32BITSREGISTERS_CMD);
                        break;

                    case _SCALER_READ_32BITSREGISTERS_CMD:
                        ScalerDebugGet32BitRegisters(_SCALER_READ_32BITSREGISTERS_CMD);
                        break;

#if(_SPI_SUPPORT == _ON)
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
                    case _SCALER_WRITE_PWMTOSPI_REG_CMD:
                        ScalerDebugSetPwmToSpiRegisters();
                        break;

                    case _SCALER_READ_PWMTOSPI_REG_CMD:
                        ScalerDebugGetPwmToSpiRegisters();
                        break;

                    case _SCALER_WRITE_PWMTOSPI_DEV_CMD:
                        ScalerDebugSetPwmToSpiDevice();
                        break;

                    case _SCALER_READ_PWMTOSPI_DEV_CMD:
                        ScalerDebugGetPwmToSpiDevice();
                        break;

                    case _SCALER_WRITE_PWMTOSPI_WORD_CMD:
                        ScalerDebugSetPwmToSpiRegistersGen2();
                        break;

                    case _SCALER_READ_PWMTOSPI_WORD_CMD:
                        ScalerDebugGetPwmToSpiRegistersGen2();
                        break;

                    case _SCALER_WRITE_PWMTOSPI_WORD_DEV_CMD:
                        ScalerDebugSetPwmToSpiDeviceGen2();
                        break;
                    case _SCALER_READ_PWMTOSPI_WORD_DEV_CMD:
                        ScalerDebugGetPwmToSpiDeviceGen2();
                        break;
#endif
#endif

                    case _SCALER_WRITE_DDRSPACE_CMD:
                        ScalerDebugSet32BitRegisters(_SCALER_WRITE_DDRSPACE_CMD);
                        break;

                    case _SCALER_READ_DDRSPACE_CMD:
                        ScalerDebugGet32BitRegisters(_SCALER_READ_DDRSPACE_CMD);
                        break;

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
                    case _SCALER_DUAL_BANK_SWITCH_DDCCI_MODE_CMD:
                        // Switch DDCCI to DDCCI Mode, No Matter Which Port as Auto-Switch
                        ScalerMcuDdcciSwitchPort(_DDCCI_MODE);
                        break;
#endif

                    case _SCALER_DUAL_BANK_BOOT_PROC_CMD:
                        ScalerDebugDualBankHandler(g_pucDebugDdcciData[1]);
                        break;

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
                    case _SCALER_GET_CURRENT_FW_VER_CMD:
                        ScalerDebugGetCurrentFwInfo();
                        break;
#endif

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
                    case _SCALER_CUSTOMER_DEBUG_PROC_CMD:
                        ScalerDebugCustomerDebugProc();
                        SET_CUSTOMER_CMD_REV_STATE();
                        break;
#endif

#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
                    case _SCALER_FW_CHECK_CMD:
                        ScalerDebugFwCheck();
                        break;
#endif

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
                    case _SCALER_FW_UPDATE_CMD:
                        if(((_FW_UPDATE_BACKGROUND_SUPPORT == _ON) && (g_pucDebugDdcciData[1] == _FW_UPDATE_BACKGROUND_SUB_OP_CODE)) ||
                           ((_FW_UPDATE_FOREGROUND_SUPPORT == _ON) && (g_pucDebugDdcciData[1] == _FW_UPDATE_FOREGROUND_SUB_OP_CODE)))
                        {
                            ScalerFwUpdateSwitchState(_DEBUG_MODE, g_pucDebugDdcciData[1], _DDCCI0);
                        }
                        break;
#endif

                    default:
                        switch(g_pucDebugDdcciData[0] & 0x0F) // Write command
                        {
                            case 0x00:

                                // ScalerSetByte(g_pucDdcciData[2], g_pucDdcciData[1]);
                                // MCU_FFF3_SCA_INF_CONTROL |= 0x20;
                                // MCU_FFF4_SCA_INF_ADDR = g_pucDdcciData[2];
                                // MCU_FFF5_SCA_INF_DATA = g_pucDdcciData[1];

                                MCU_FFF3_SCA_INF_CONTROL |= 0x20;
                                MCU_FFF4_SCA_INF_ADDR = 0x9F;
                                usAddress = MCU_FFF5_SCA_INF_DATA;
                                usAddress = (usAddress << 8) + g_pucDebugDdcciData[2];
                                ScalerSetByte(usAddress, g_pucDebugDdcciData[1]);
                                break;

                            case 0x01:
                            case 0x02: // For RTD & I2c Device
                                g_pucDebugDdcciData[2] = g_pucDebugDdcciData[1];
                                break;

                            case 0x06:
                            case 0x03: // For I2c Device
                                g_pucDebugDdcciData[3] = g_pucDebugDdcciData[1];
                                break;

                            case 0x05:
                                g_pucDebugDdcciData[4] = g_pucDebugDdcciData[1];
                                break;

                            case 0x04: // For I2c Device

#if(_DEBUG_IIC_BY_USERINTERFACE == _ON)
                                if(UserInterfaceDebugIIC(_WRITE, g_pucDebugDdcciData, &ucResult) == _DBG_OFF)
#endif
                                {
                                    // Disable EEPROM Write Protect
                                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);

#if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

                                    SET_SW_IIC_STATUS(_IIC_SYS_EEPROM);

#if(_EEPROM_TYPE == _EEPROM_24LC16)
                                    ScalerMcuIICWrite(g_pucDebugDdcciData[2], 1, g_pucDebugDdcciData[1], 1, g_pucDebugDdcciData + 3);
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
                                    ScalerMcuIICWrite(g_pucDebugDdcciData[2], 2, ((g_pucDebugDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDebugDdcciData[1]) & 0x00FF), 1, g_pucDebugDdcciData + 3);
#endif

#elif(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN)  // Else of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

#if(_HW_IIC_SUPPORT == _ON)
#if(_EEPROM_TYPE == _EEPROM_24LC16)
                                    ScalerMcuHwIICWrite(g_pucDebugDdcciData[2], 1, g_pucDebugDdcciData[1], 1, g_pucDebugDdcciData + 3, _PCB_SYS_EEPROM_IIC);
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
                                    ScalerMcuHwIICWrite(g_pucDebugDdcciData[2], 2, ((g_pucDebugDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDebugDdcciData[1]) & 0x00FF), 1, g_pucDebugDdcciData + 3, _PCB_SYS_EEPROM_IIC);
#endif
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

#endif  // End of #if(_PCB_SYS_EEPROM_IIC == _SW_IIC_PIN_GPIO)

                                    // Enable EEPROM Write Protect
                                    PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);
                                }

                                break;

                            case 0x0F: // For I2c Device

                                // Disable EEPROM Write Protect
                                PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_DISABLE);

#if((_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO))

#if(_HW_IIC_SUPPORT == _ON)
#if(_EEPROM_TYPE == _EEPROM_24LC16)
                                ScalerMcuHwIICWrite(g_pucDebugDdcciData[2], 1, g_pucDebugDdcciData[1], 1, g_pucDebugDdcciData + 3, _NO_IIC_PIN);
#elif((_EEPROM_TYPE == _EEPROM_24WC64) || (_EEPROM_TYPE == _EEPROM_CAT24M01) || (_EEPROM_TYPE == _EEPROM_24256))
                                ScalerMcuHwIICWrite(g_pucDebugDdcciData[2], 2, ((g_pucDebugDdcciData[4] << 8) & 0xFF00) + (((WORD)g_pucDebugDdcciData[1]) & 0x00FF), 1, g_pucDebugDdcciData + 3, _NO_IIC_PIN);
#endif
#endif // End of #if(_HW_IIC_SUPPORT == _ON)

#endif // End of #if(_PCB_SYS_EEPROM_IIC != _NO_IIC_PIN) && (_PCB_SYS_EEPROM_IIC != _SW_IIC_PIN_GPIO)

                                // Enable EEPROM Write Protect
                                PCB_EEPROM_WRITE_PROTECT(_EEPROM_WP_ENABLE);

                                break;

                            default:
                                break;
                        }
                        break;
                }

                g_bDebugRunCommand = _FALSE;
                g_ucDebugDdcciCommandNumber = 0;

                // Host write Enable
                MCU_FF2A_IIC_IRQ_CONTROL2 &= (~_BIT5);

                // Delay Time us [30,x] Avoid MCU Clock too fast lead to Tool Communication Fail.
                DELAY_30US();

                // Release Scl Pin
#if((_DEBUG_DDC_CHANNEL_SEL == _DDC5) && (_HW_DDC5_EXIST == _ON))
                ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC4) && (_HW_DDC4_EXIST == _ON))
                ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC3) && (_HW_DDC3_EXIST == _ON))
                ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC2) && (_HW_DDC2_EXIST == _ON))
                ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC1) && (_HW_DDC1_EXIST == _ON))
                ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC0) && (_HW_DDC0_EXIST == _ON))
                ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) && (_HW_ISP_DDC_EXIST == _ON))
                ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif
            }
        }
        while(ucDebugHalt != 0);
    }
}

//--------------------------------------------------
// Description  : Scaler Debug Send Data
// Input Value  : ucLen: Send Data Len
// Output Value : None
//--------------------------------------------------
void ScalerDebugSendData(BYTE ucLen, BYTE *pucSendArray)
{
    BYTE ucIndex = 0;
    WORD usTimeOutCnt = 0;
    bit bReleaseScl = _FALSE;

    // Enable mcu write and reset buffer
    MCU_FF2A_IIC_IRQ_CONTROL2 |= (_BIT6 | _BIT5);

    while(ucIndex < (ucLen))
    {
        // Load data to DDC-CI buffer until buffer full
        if((MCU_FF29_IIC_STATUS2 & _BIT2) == 0)
        {
            MCU_FF26_IIC_DATA_OUT = pucSendArray[ucIndex];
            ucIndex++;
            usTimeOutCnt = _DDCCI_TIMEOUT_LIMIT;
        }
        else
        {
            // Release Scl for Tool to read
            if(bReleaseScl == _FALSE)
            {
                bReleaseScl = _TRUE;
                // Release Scl Pin
#if((_DEBUG_DDC_CHANNEL_SEL == _DDC5) && (_HW_DDC5_EXIST == _ON))
                ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC4) && (_HW_DDC4_EXIST == _ON))
                ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC3) && (_HW_DDC3_EXIST == _ON))
                ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC2) && (_HW_DDC2_EXIST == _ON))
                ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC1) && (_HW_DDC1_EXIST == _ON))
                ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC0) && (_HW_DDC0_EXIST == _ON))
                ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) && (_HW_ISP_DDC_EXIST == _ON))
                ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT1 | _BIT0), 0x00);
#endif
            }
            ScalerTimerDelayXms(2);
            usTimeOutCnt--;
        }

        if(usTimeOutCnt == 0)
        {
            break;
        }
    }

    MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
}

//--------------------------------------------------
// Description  : Scaler Debug Read Registers
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugGetRegisters(void)
{
    BYTE ucLen = 0;
    BYTE ucChecksum = 0;
    bit bAutoIncrease = _FALSE;
    WORD usAddress = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};

    // read date
    ucLen = g_pucDebugDdcciData[3];
    bAutoIncrease = (bit)g_pucDebugDdcciData[4];
    usAddress = ((WORD)g_pucDebugDdcciData[1] << 8) + g_pucDebugDdcciData[2];

    // Length Error
    if(ucLen > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_READ_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < 5; ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    // Check sum Error
    if(ucChecksum != g_pucDebugDdcciData[5])
    {
        pucDdcciOutData[0] = _SCALER_READ_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    pucDdcciOutData[0] = _SCALER_READ_REGISTERS_CMD;
    pucDdcciOutData[1] = ucLen;
    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        pucDdcciOutData[2 + ucIndex] = ScalerGetByte(usAddress);
        ucChecksum += pucDdcciOutData[2 + ucIndex];
        if(bAutoIncrease == _TRUE)
        {
            usAddress++;
        }
    }
    pucDdcciOutData[ucLen + 2] = ucChecksum;
    ScalerDebugSendData(ucLen + 3, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Write Registers
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugSetRegisters(void)
{
    BYTE ucLen = 0;
    BYTE ucChecksum = 0;
    bit bAutoIncrease = _FALSE;
    WORD usAddress = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};

    // Write date
    ucLen = g_pucDebugDdcciData[3];
    bAutoIncrease = (bit)g_pucDebugDdcciData[4];
    usAddress = ((WORD)g_pucDebugDdcciData[1] << 8) + g_pucDebugDdcciData[2];

    // Length Error
    if(ucLen > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_WRITE_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < (ucLen + 5); ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    // Check sum Error
    if(ucChecksum != g_pucDebugDdcciData[5 + ucLen])
    {
        pucDdcciOutData[0] = _SCALER_WRITE_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    // Checksum OK do write option
    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        ScalerSetByte(usAddress, g_pucDebugDdcciData[5 + ucIndex]);
        if(bAutoIncrease == _TRUE)
        {
            usAddress++;
        }
    }

    pucDdcciOutData[0] = _SCALER_WRITE_REGISTERS_CMD;
    pucDdcciOutData[1] = _SCALER_DEBUG_NO_ERROR;
    ScalerDebugSendData(2, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Read 32Bit Registers
//                or DDR SPace
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugGet32BitRegisters(BYTE ucDebugCmd)
{
    DWORD ulAddress = 0;
    DWORD ulData = 0;
    BYTE ucLen = 0;
    bit bAutoIncrease = _FALSE;
    BYTE ucChecksum = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    ulAddress = (((DWORD)g_pucDebugDdcciData[1] << 24) | ((DWORD)g_pucDebugDdcciData[2] << 16) | ((DWORD)g_pucDebugDdcciData[3] << 8) | g_pucDebugDdcciData[4]);
    ucLen = g_pucDebugDdcciData[5];
    bAutoIncrease = (bit)(g_pucDebugDdcciData[6] & _BIT0);
#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
    bit bKcpu = _TRUE;

    // Cpu Type bKcpu:1, 0: Scpu
    if(ucDebugCmd == _SCALER_READ_DDRSPACE_CMD)
    {
        bKcpu = (((g_pucDebugDdcciData[6] & _BIT1) == _BIT1) ? _TRUE : _FALSE);
    }
#endif

    // Length Error
    if((ucLen * 4) > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = ucDebugCmd;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < 7; ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    // Checksum Error
    if(ucChecksum != g_pucDebugDdcciData[7])
    {
        pucDdcciOutData[0] = _SCALER_READ_REGISTERS_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    pucDdcciOutData[0] = ucDebugCmd;
    pucDdcciOutData[1] = ucLen;

    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        if(CHK_ADDRESS_ACCESSIBLE(ulAddress) == _TRUE)
        {
            if(ucDebugCmd == _SCALER_READ_32BITSREGISTERS_CMD)
            {
                ulData = Scaler32GetDWord(ulAddress);
            }

            if(ucDebugCmd == _SCALER_READ_DDRSPACE_CMD)
            {
#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
                if(bKcpu == _TRUE)
                {
                    ulData = Scaler32GetDWord(ulAddress);
                }
                else
                {
#if(_SCPU_SUPPORT == _ON)
                    ulData = ScalerCpuSyncGetDWord(ulAddress);
#else
                    ulData = Scaler32GetDWord(ulAddress);
#endif
                }
#else
                bKcpu = bKcpu;
                ulData = Scaler32GetDWord(ulAddress);
#endif
#else
                ulData = Scaler32GetDWord(ulAddress);
#endif
            }
        }
        else
        {
            ulData = 0;
        }
        pucDdcciOutData[2 + ucIndex * 4] = (ulData & 0xFF000000) >> 24;
        pucDdcciOutData[3 + ucIndex * 4] = (ulData & 0xFF0000) >> 16;
        pucDdcciOutData[4 + ucIndex * 4] = (ulData & 0xFF00) >> 8;
        pucDdcciOutData[5 + ucIndex * 4] = (ulData & 0xFF);
        ucChecksum += pucDdcciOutData[2 + ucIndex * 4];
        ucChecksum += pucDdcciOutData[3 + ucIndex * 4];
        ucChecksum += pucDdcciOutData[4 + ucIndex * 4];
        ucChecksum += pucDdcciOutData[5 + ucIndex * 4];
        if(bAutoIncrease != 0)
        {
            ulAddress += 4;
        }
    }
    pucDdcciOutData[ucLen * 4 + 2] = ucChecksum;
    ScalerDebugSendData(ucLen * 4 + 3, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Write 32Bit Registers
//                or DDR SPace
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugSet32BitRegisters(BYTE ucDebugCmd)
{
    DWORD ulAddress = 0;
    DWORD ulData = 0;
    BYTE ucLen = 0;
    bit bAutoIncrease = _FALSE;
    BYTE ucChecksum = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN];
    ulAddress = (((DWORD)g_pucDebugDdcciData[1] << 24) | ((DWORD)g_pucDebugDdcciData[2] << 16) | ((DWORD)g_pucDebugDdcciData[3] << 8) | g_pucDebugDdcciData[4]);
    ucLen = g_pucDebugDdcciData[5];

    bAutoIncrease = (bit)(g_pucDebugDdcciData[6] & _BIT0);
#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
    bit bKcpu = _TRUE;

    // Cpu Type bKcpu:1, 0: Scpu
    if(ucDebugCmd == _SCALER_WRITE_DDRSPACE_CMD)
    {
        bKcpu = (((g_pucDebugDdcciData[6] & _BIT1) == _BIT1) ? _TRUE : _FALSE);
    }
#endif
    ucChecksum = 0;

    if((ucLen * 4) > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = ucDebugCmd;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    for(ucIndex = 1; ucIndex < ((ucLen * 4) + 7); ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    if(ucChecksum != g_pucDebugDdcciData[7 + (ucLen *4)])
    {
        pucDdcciOutData[0] = ucDebugCmd;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    // Checksum OK do write option
    for(ucIndex = 0; ucIndex < ucLen; ucIndex++)
    {
        ulData = (((DWORD)g_pucDebugDdcciData[7 + ucIndex * 4] << 24) | ((DWORD)g_pucDebugDdcciData[8 + ucIndex * 4] << 16) | ((DWORD)g_pucDebugDdcciData[9 + ucIndex * 4] << 8) | g_pucDebugDdcciData[10 + ucIndex * 4]);

        if(CHK_ADDRESS_ACCESSIBLE(ulAddress) == _TRUE)
        {
            if(ucDebugCmd == _SCALER_WRITE_32BITSREGISTERS_CMD)
            {
                Scaler32SetDWord(ulAddress, ulData);
            }

            if(ucDebugCmd == _SCALER_WRITE_DDRSPACE_CMD)
            {
#if(_HW_CPU32_NOTIFY_INT_SUPPORT == _ON)
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
                if(bKcpu == _TRUE)
                {
                    Scaler32SetDWord(ulAddress, ulData);
                }
                else
                {
#if(_SCPU_SUPPORT == _ON)
                    ScalerCpuSyncSetDWord(ulAddress, ulData);
#else
                    Scaler32SetDWord(ulAddress, ulData);
#endif
                }
#else
                bKcpu = bKcpu;
                Scaler32SetDWord(ulAddress, ulData);
#endif
#else
                Scaler32SetDWord(ulAddress, ulData);
#endif
            }
        }

        if(bAutoIncrease != 0)
        {
            ulAddress += 4;
        }
    }

    pucDdcciOutData[0] = ucDebugCmd;
    pucDdcciOutData[1] = _SCALER_DEBUG_NO_ERROR;
    ScalerDebugSendData(2, pucDdcciOutData);
}

#if(_SPI_SUPPORT == _ON)
#if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scaler Debug Read PWMtoSPI Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugGetPwmToSpiDevice(void)
{
    BYTE ucChecksum = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    BYTE ucDevIndex = 0;
    BYTE ucPwmStartIndex = 0;
    BYTE ucPwmReadNum = 0;
    WORD pusPwmValue[(_SCALER_DEBUG_DATA_COUNT / 2)] = {0};

    ucDevIndex = g_pucDebugDdcciData[1];
    ucPwmStartIndex = g_pucDebugDdcciData[2];
    ucPwmReadNum = g_pucDebugDdcciData[3];

    // Length Error
    if((ucPwmReadNum * 2) > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < 4; ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    // Checksum Error
    if(ucChecksum != g_pucDebugDdcciData[4])
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_DEV_CMD;
    pucDdcciOutData[1] = ucPwmReadNum;

    if(!ScalerSpiDimmingDebugReadPWM(ucDevIndex, (WORD)ucPwmStartIndex, (WORD)ucPwmReadNum, pusPwmValue))
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_GET_SPI_DEV_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }
    ucIndex = 0;
    while(ucIndex < ucPwmReadNum)
    {
        pucDdcciOutData[(ucIndex * 2) + 2] = LOBYTE(pusPwmValue[ucIndex]);
        pucDdcciOutData[(ucIndex * 2) + 3] = HIBYTE(pusPwmValue[ucIndex]);
        ucIndex++;
    }

    ucChecksum = 0;
    for(ucIndex = 0; ucIndex < ucPwmReadNum * 2; ucIndex++)
    {
        ucChecksum += pucDdcciOutData[2 + ucIndex];
    }
    pucDdcciOutData[ucPwmReadNum * 2 + 2] = ucChecksum;
    ScalerDebugSendData(ucPwmReadNum * 2 + 3, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Write PWMtoSPI Device
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugSetPwmToSpiDevice(void)
{
    BYTE ucChecksum = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    BYTE ucDevIndex = 0;
    BYTE ucPwmStartIndex = 0;
    BYTE ucPwmWriteNum = 0;
    WORD pusPwmValue[(_SCALER_DEBUG_DATA_COUNT / 2)];


    ucDevIndex = g_pucDebugDdcciData[1];
    ucPwmStartIndex = g_pucDebugDdcciData[2];
    ucPwmWriteNum = g_pucDebugDdcciData[3];

    // Length Error
    if((ucPwmWriteNum * 2) > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < ((ucPwmWriteNum * 2) + 4); ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    if(ucChecksum != g_pucDebugDdcciData[(ucPwmWriteNum * 2) + 4])
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    // Checksum OK do write option
    ucIndex = 0;
    while(ucIndex < ucPwmWriteNum)
    {
        pusPwmValue[ucIndex] = (((WORD)g_pucDebugDdcciData[((ucIndex << 1) + 5)]) << 8) + g_pucDebugDdcciData[(ucIndex << 1) + 4];
        ucIndex++;
    }
    if(!ScalerSpiDimmingDebugWritePWM(ucDevIndex, (WORD)ucPwmStartIndex, (WORD)ucPwmWriteNum, pusPwmValue))
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_SET_SPI_DEV_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_DEV_CMD;
    pucDdcciOutData[1] = _SCALER_DEBUG_NO_ERROR;
    ScalerDebugSendData(2, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Read PWMtoSPI Registers
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugGetPwmToSpiRegisters(void)
{
    BYTE ucChecksum = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    WORD pusRegValue[_SCALER_DEBUG_DATA_COUNT];
    BYTE ucDevIndex = 0;
    BYTE ucRegStartAddr = 0;
    BYTE ucReadByteNum = 0;

    ucDevIndex = g_pucDebugDdcciData[1];
    ucRegStartAddr = g_pucDebugDdcciData[2];
    ucReadByteNum = g_pucDebugDdcciData[3];

    // Length Error
    if(ucReadByteNum > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_REG_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < 4; ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    // Checksum Error
    if(ucChecksum != g_pucDebugDdcciData[4])
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_REG_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_REG_CMD;
    pucDdcciOutData[1] = ucReadByteNum;

    if(!ScalerSpiDimmingDebugReadReg(ucDevIndex, (WORD)ucRegStartAddr, (WORD)ucReadByteNum, pusRegValue, _SPI_DEBUG_OTHER_REG))
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_REG_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_GET_SPI_REG_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    for(ucIndex = 0; ucIndex < ucReadByteNum; ucIndex++)
    {
        pucDdcciOutData[(2 + ucIndex)] = LOBYTE(pusRegValue[ucIndex]);
    }

    ucChecksum = 0;
    for(ucIndex = 0; ucIndex < ucReadByteNum; ucIndex++)
    {
        ucChecksum += pucDdcciOutData[2 + ucIndex];
    }
    pucDdcciOutData[ucReadByteNum + 2] = ucChecksum;
    ScalerDebugSendData(ucReadByteNum + 3, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Write PWMtoSPI Registers
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugSetPwmToSpiRegisters(void)
{
    BYTE ucChecksum = 0;
    BYTE ucIndex = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    WORD pusRegValue[_SCALER_DEBUG_DATA_COUNT];
    BYTE ucDevIndex = 0;
    BYTE ucRegStartAddr = 0;
    BYTE ucWriteByteNum = 0;

    ucDevIndex = g_pucDebugDdcciData[1];
    ucRegStartAddr = g_pucDebugDdcciData[2];
    ucWriteByteNum = g_pucDebugDdcciData[3];

    // Length Error
    if(ucWriteByteNum > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_REG_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(ucIndex = 1; ucIndex < (ucWriteByteNum + 4); ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    if(ucChecksum != g_pucDebugDdcciData[ucWriteByteNum + 4])
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_REG_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    for(ucIndex = 0; ucIndex < ucWriteByteNum; ucIndex++)
    {
        pusRegValue[ucIndex] = (((WORD)g_pucDebugDdcciData[((ucIndex << 1) + 5)]) << 8) + g_pucDebugDdcciData[(ucIndex << 1) + 4];
    }

    // Checksum OK do write option
    if(!ScalerSpiDimmingDebugWriteReg(ucDevIndex, (WORD)ucRegStartAddr, (WORD)ucWriteByteNum, pusRegValue, _SPI_DEBUG_OTHER_REG))
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_REG_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_SET_SPI_REG_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }


    pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_REG_CMD;
    pucDdcciOutData[1] = _SCALER_DEBUG_NO_ERROR;
    ScalerDebugSendData(2, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Read PWMtoSPI Device New(_SCALER_READ_PWMTOSPI_WORD_DEV_CMD)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugGetPwmToSpiDeviceGen2(void)
{
    BYTE ucChecksum = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    WORD usDevIndex = 0;
    WORD usPwmStartIndex = 0;
    WORD usPwmReadNum = 0;
    WORD pusPwmValue[(_SCALER_DEBUG_DATA_COUNT / 2)];

    usDevIndex = (((WORD)g_pucDebugDdcciData[2]) << 8) | g_pucDebugDdcciData[1];
    usPwmStartIndex = (((WORD)g_pucDebugDdcciData[4]) << 8) | g_pucDebugDdcciData[3];
    usPwmReadNum = (WORD)g_pucDebugDdcciData[5];

    // Length Error
    if((usPwmReadNum * 2) > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_WORD_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(BYTE ucIndex = 1; ucIndex < 6; ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    // Checksum Error
    if(ucChecksum != g_pucDebugDdcciData[6])
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_WORD_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    if(!ScalerSpiDimmingDebugReadPWM((BYTE)usDevIndex, usPwmStartIndex, usPwmReadNum, pusPwmValue))
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_WORD_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_GET_SPI_DEV_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_WORD_DEV_CMD;
    pucDdcciOutData[1] = (BYTE)usPwmReadNum;

    for(BYTE ucIndex = 0; ucIndex < usPwmReadNum; ucIndex++)
    {
        pucDdcciOutData[(ucIndex * 2) + 2] = LOBYTE(pusPwmValue[ucIndex]);
        pucDdcciOutData[(ucIndex * 2) + 3] = HIBYTE(pusPwmValue[ucIndex]);
    }

    ucChecksum = 0;
    for(BYTE ucIndex = 0; ucIndex < (usPwmReadNum * 2); ucIndex++)
    {
        ucChecksum += pucDdcciOutData[2 + ucIndex];
    }
    pucDdcciOutData[(usPwmReadNum * 2) + 2] = ucChecksum;

    ScalerDebugSendData(((usPwmReadNum * 2) + 3), pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Write PWMtoSPI Device New(_SCALER_WRITE_PWMTOSPI_WORD_DEV_CMD)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugSetPwmToSpiDeviceGen2(void)
{
    BYTE ucChecksum = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    WORD usDevIndex = 0;
    WORD usPwmStartIndex = 0;
    WORD usPwmWriteNum = 0;
    WORD pusPwmValue[(_SCALER_DEBUG_DATA_COUNT / 2)];

    usDevIndex = (((WORD)g_pucDebugDdcciData[2]) << 8) | g_pucDebugDdcciData[1];
    usPwmStartIndex = (((WORD)g_pucDebugDdcciData[4]) << 8) | g_pucDebugDdcciData[3];
    usPwmWriteNum = (WORD)g_pucDebugDdcciData[5];

    // Length Error
    if((usPwmWriteNum * 2) > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_WORD_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(BYTE ucIndex = 1; ucIndex < ((usPwmWriteNum * 2) + 6); ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    if(ucChecksum != g_pucDebugDdcciData[(usPwmWriteNum * 2) + 6])
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_WORD_DEV_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    if((usDevIndex == 0xFFFF) && (usPwmStartIndex == 0xFFFF) && (usPwmWriteNum == 0))
    {
        // this is manual Active Command
        ScalerSpiDimmingToggleUpdateSync();
    }
    else
    {
        // Checksum OK do write option
        for(BYTE ucIndex = 0; ucIndex < usPwmWriteNum; ucIndex++)
        {
            pusPwmValue[ucIndex] = (((WORD)g_pucDebugDdcciData[((ucIndex << 1) + 7)]) << 8) + g_pucDebugDdcciData[(ucIndex << 1) + 6];
        }

        if(!ScalerSpiDimmingDebugWritePWM((BYTE)usDevIndex, usPwmStartIndex, usPwmWriteNum, pusPwmValue))
        {
            pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_WORD_DEV_CMD;
            pucDdcciOutData[1] = _SCALER_DEBUG_SET_SPI_DEV_ERROR;
            ScalerDebugSendData(2, pucDdcciOutData);
            return;
        }
    }

    pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_WORD_DEV_CMD;
    pucDdcciOutData[1] = _SCALER_DEBUG_NO_ERROR;
    ScalerDebugSendData(2, pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Read PWMtoSPI Registers New(_SCALER_READ_PWMTOSPI_WORD_CMD)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugGetPwmToSpiRegistersGen2(void)
{
    BYTE ucChecksum = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    WORD pusRegValue[(_SCALER_DEBUG_DATA_COUNT / 2)];
    WORD usReadRegNum = (WORD)g_pucDebugDdcciData[5];

    // Length Error
    if((usReadRegNum * 2) > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_WORD_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(BYTE ucIndex = 1; ucIndex < 6; ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    // Checksum Error
    if(ucChecksum != g_pucDebugDdcciData[6])
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_WORD_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

#if(_DEVICE_LED_DRIVER_MCU_TYPE == _OFF)
    WORD usDevIndex = (((WORD)g_pucDebugDdcciData[2]) << 8) | g_pucDebugDdcciData[1];
    WORD usRegStartAddr = (((WORD)g_pucDebugDdcciData[4]) << 8) | g_pucDebugDdcciData[3];

    if(!ScalerSpiDimmingDebugReadReg((BYTE)usDevIndex, usRegStartAddr, usReadRegNum, pusRegValue, _SPI_DEBUG_OTHER_REG))
    {
        pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_WORD_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_GET_SPI_REG_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }
#if(_DEVICE_LED_DRIVER_REG_WIDTH_BY_BYTE == 1)
    BYTE *pucRegBuf = (BYTE *)pusRegValue;
    for(WORD usIdx = usReadRegNum; usIdx != 0; usIdx--)
    {
        pusRegValue[(usIdx - 1)] = (WORD)pucRegBuf[(usIdx - 1)];
    }
#endif
#else
    for(BYTE ucIndex = 0; ucIndex < usReadRegNum; ucIndex++)
    {
        pusRegValue[ucIndex] = 0;
    }
#endif

    pucDdcciOutData[0] = _SCALER_READ_PWMTOSPI_WORD_CMD;
    pucDdcciOutData[1] = (BYTE)usReadRegNum;

    for(BYTE ucIndex = 0; ucIndex < usReadRegNum; ucIndex++)
    {
        pucDdcciOutData[(ucIndex * 2) + 2] = LOBYTE(pusRegValue[ucIndex]);
        pucDdcciOutData[(ucIndex * 2) + 3] = HIBYTE(pusRegValue[ucIndex]);
    }

    ucChecksum = 0;
    for(BYTE ucIndex = 0; ucIndex < (usReadRegNum * 2); ucIndex++)
    {
        ucChecksum += pucDdcciOutData[2 + ucIndex];
    }
    pucDdcciOutData[(usReadRegNum * 2) + 2] = ucChecksum;

    ScalerDebugSendData(((usReadRegNum * 2) + 3), pucDdcciOutData);
}

//--------------------------------------------------
// Description  : Scaler Debug Write PWMtoSPI Registers New(_SCALER_WRITE_PWMTOSPI_WORD_CMD)
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugSetPwmToSpiRegistersGen2(void)
{
    BYTE ucChecksum = 0;
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    WORD usWriteRegNum = (WORD)g_pucDebugDdcciData[5];

    // Length Error
    if((usWriteRegNum * 2) > _SCALER_DEBUG_DATA_COUNT)
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_WORD_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_DATA_LEN_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    ucChecksum = 0;
    for(BYTE ucIndex = 1; ucIndex < ((usWriteRegNum * 2) + 6); ucIndex++)
    {
        ucChecksum += g_pucDebugDdcciData[ucIndex];
    }

    if(ucChecksum != g_pucDebugDdcciData[(usWriteRegNum * 2) + 6])
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_WORD_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_CHECKSUM_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }

    // Checksum OK do write option

#if(_DEVICE_LED_DRIVER_MCU_TYPE == _OFF)
    WORD pusRegValue[(_SCALER_DEBUG_DATA_COUNT / 2)];
    WORD usDevIndex = (((WORD)g_pucDebugDdcciData[2]) << 8) | g_pucDebugDdcciData[1];
    WORD usRegStartAddr = (((WORD)g_pucDebugDdcciData[4]) << 8) | g_pucDebugDdcciData[3];

    for(BYTE ucIndex = 0; ucIndex < usWriteRegNum; ucIndex++)
    {
        pusRegValue[ucIndex] = (((WORD)g_pucDebugDdcciData[((ucIndex << 1) + 7)]) << 8) + g_pucDebugDdcciData[(ucIndex << 1) + 6];
    }

    if(!ScalerSpiDimmingDebugWriteReg((BYTE)usDevIndex, usRegStartAddr, usWriteRegNum, pusRegValue, _SPI_DEBUG_OTHER_REG))
    {
        pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_WORD_CMD;
        pucDdcciOutData[1] = _SCALER_DEBUG_SET_SPI_REG_ERROR;
        ScalerDebugSendData(2, pucDdcciOutData);
        return;
    }
#endif

    pucDdcciOutData[0] = _SCALER_WRITE_PWMTOSPI_WORD_CMD;
    pucDdcciOutData[1] = _SCALER_DEBUG_NO_ERROR;
    ScalerDebugSendData(2, pucDdcciOutData);
}
#endif // End of #if(_SPI_BACKLIGHT_DIMMING_SUPPORT == _ON)
#endif // End of #if(_SPI_SUPPORT == _ON)

#if(_ASSERT_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Assertion handler for debug
// Input Value  : pchFileName --> file name
//                usLine --> line number in file
//                ucStall --> _TRUE to print message only
// Output Value : None
//--------------------------------------------------
void ScalerDebugAssert(SBYTE *pchFileName, WORD usLine)
{
    pchFileName = pchFileName;
    usLine = usLine;

    DebugMessageAssert(pchFileName, usLine);

    // stall code
    while(_TRUE)
    {
        ScalerDebug();
    }
}
#endif

#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Get Current DDCCI Switch State
// Input Value  : None
// Output Value : Bit State
//--------------------------------------------------
BYTE ScalerDebugGetDdcciSwitchState(void)
{
    return GET_DDCCI_SWITCH_STATE();
}

//--------------------------------------------------
// Description  : Set Current DDCCI Switch State
// Input Value  : None
// Output Value : Bit State
//--------------------------------------------------
void ScalerDebugSetDdcciSwitchState(void)
{
    SET_DDCCI_SWITCH_STATE();
}

//--------------------------------------------------
// Description  : Set dual bank boot debug op code
// Input Value  : ucOpCode
// Output Value : None
//--------------------------------------------------
void ScalerDebugDualBankSetDebugInfo(BYTE ucRevCmd, BYTE ucOpCode, BYTE ucSubOpCode)
{
    g_stDebugDualBank.ucRevDebugCmd = ucRevCmd;
    g_stDebugDualBank.ucOpCode = ucOpCode;
    g_stDebugDualBank.ucSubOpCode = ucSubOpCode;
}

//--------------------------------------------------
// Description  : Get dual bank boot debug op code
// Input Value  : ucOpCode
// Output Value : None
//--------------------------------------------------
BYTE ScalerDebugDualBankGetDebugInfo(BYTE *pucOpCode, BYTE *pucSubOpCode)
{
    *pucOpCode = g_stDebugDualBank.ucOpCode;
    *pucSubOpCode = g_stDebugDualBank.ucSubOpCode;

    return g_stDebugDualBank.ucRevDebugCmd;
}

#endif // End of #if(_DUAL_BANK_DEBUG_SUPPORT == _ON)

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Receive Data in debug mode
// Input Value  : ucOpCode
// Output Value : None
//--------------------------------------------------
void ScalerDebugCustomerDebugProc(void)
{
    memcpy(g_pucDebugCustomerRevData, &g_pucDebugDdcciData[1], (sizeof(g_pucDebugDdcciData) - 1));
    return;
}

//--------------------------------------------------
// Description  : Receive Data in debug mode
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE *ScalerDebugGetCustomerDebugRevData(void)
{
    return g_pucDebugCustomerRevData;
}
#endif

#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scaler Debug Get Fw Version
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugGetCurrentFwInfo(void)
{
    BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
    // OpCode
    pucDdcciOutData[0] = _SCALER_GET_CURRENT_FW_VER_CMD;

    switch(g_pucDebugDdcciData[1])
    {
        case _SCALER_GET_CURRENT_FW_VERSION_OP_CODE:
            // FW Version Byte Count + 2 Byte FW Version
            ScalerFwInfoGetCurrentVersion(&pucDdcciOutData[1]);
            ScalerDebugSendData(3, pucDdcciOutData);
            break;

        case _SCALER_GET_FW_VERSION_LOCATE_OP_CODE:
            ScalerFwInfoGetFwVersionAddress(&pucDdcciOutData[1]);
            ScalerDebugSendData(6, pucDdcciOutData);
            break;

        default:
            break;
    }
}
#endif


#if(_DUAL_BANK_BUNDLE_VERSION_SUPPORT == _ON)
//--------------------------------------------------
// Description  : isp Duanl bank bundle version Info
// Input Value  : None
// Output Value : success or fail
//--------------------------------------------------
EnumISPBundleVerResult ScalerDebugUpdateBundleVersion(void)
{
    // isp Length != _DUAL_BANK_BUNDLE_VERSION_COUNT return error
    if(g_pucDebugDdcciData[2] != _DUAL_BANK_BUNDLE_VERSION_COUNT)
    {
        return _ISP_FAIL;
    }

    // Erase Combine FW Info. Data block
    ScalerFlashErasePage(_DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK, _DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR, _TRUE, _TRUE);

    // Recovery sign flag
    if(ScalerFlashWrite(_DUAL_BANK_BUNDLE_VERSION_LOCATE_BANK, ((WORD)(_DUAL_BANK_BUNDLE_VERSION_LOCATE_SECTOR << 12)), _DUAL_BANK_BUNDLE_VERSION_COUNT, &g_pucDebugDdcciData[3]) == _FALSE)
    {
        return _ISP_FAIL;
    }

    // Success
    return _ISP_SUCCESS;
}
#endif

//--------------------------------------------------
// Description  : Scaler Debug Get Fw Dual Bank Info
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugDualBankHandler(BYTE ucSubCode)
{
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
    ScalerDebugDualBankSetDebugInfo(_TRUE, _SCALER_DUAL_BANK_BOOT_PROC_CMD, ucSubCode);
#else
    // Get Dual bank Info , if Duanl bank support is off repley.
    if(ucSubCode == _SCALER_GET_DUAL_BANK_INFO_OP_CODE)
    {
        BYTE pucDdcciOutData[_SCALER_DEBUG_BUF_LEN] = {0};
        // OpCode
        pucDdcciOutData[0] = _SCALER_DUAL_BANK_BOOT_PROC_CMD;
        // Byte Count
        pucDdcciOutData[1] = 9;

        // Dual bank Support
        pucDdcciOutData[2] = _DUAL_BANK_SUPPORT;

        // Dual bank Type
        pucDdcciOutData[3] = _DUAL_BANK_TYPE;

        // Active User(1)
        pucDdcciOutData[4] = 0xFF;

        // User1 Version(2) + User2 Version(2) + Reserved(2)
#if(_CUSTOMER_FW_VERSION_SUPPORT == _ON)
        ScalerFwInfoGetCurrentVersion(&pucDdcciOutData[5]);
        memset(&pucDdcciOutData[7], 0xFFU, 4);
#else
        // User1 Version(2) + User2 Version(2) + Reserved(2)
        memset(&pucDdcciOutData[5], 0xFFU, 6);
#endif

        ScalerDebugSendData(13, pucDdcciOutData);
    }
#endif
}


#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Scaler Debug Fw Check
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugFwCheck(void)
{
    BYTE pucOutData[7] = {0};
    pucOutData[0] = 0x6A;
    pucOutData[1] = _SCALER_FW_CHECK_CMD;

    switch(g_pucDebugDdcciData[1])
    {
        case _SCALER_FW_CHECK_SUB_OP_GET_ADDR:
            ScalerFwCheckGetProjectIDAddress(&pucOutData[2]);
            ScalerDebugSendData(7, pucOutData);
            break;

        case _SCALER_FW_CHECK_SUB_OP_VERIFY:
            pucOutData[2] = ScalerFwCheckProjectIDVerify(&g_pucDebugDdcciData[2]);
            ScalerDebugSendData(3, pucOutData);
            break;

        default:
            break;
    }
}
#endif

//--------------------------------------------------
// Description  : Get Debug Data in Interrupt Process
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerDebugIntProc(void)
{
    BYTE ucTempBuf = 0;

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
    if(GET_DDCCI0_SLAVE_ADDRESS() != _DEBUG_DEST_ADDRESS)
    {
        return;
    }
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
    if(GET_DDCCI0_DDC_CHANNEL() == GET_DDCCI4_DDC_CHANNEL())
    {
        ScalerMcuDdcci0ClearWrongIntFlag();
        return;
    }
#endif
#endif
    MCU_FF29_IIC_STATUS2 &= ~(_BIT5 | _BIT4);

    if(g_bDebugRunCommand == _FALSE)
    {
        ucTempBuf = MCU_FF27_IIC_STATUS;

        if((ucTempBuf & _BIT1) == _BIT1)
        {
            // Clear SUB_I Flag
            MCU_FF27_IIC_STATUS &= ~_BIT1;

            g_ucDebugDdcciCommandNumber = 0;
            g_pucDebugDdcciData[0] = MCU_FF24_IIC_SUB_IN;

            // Host write Enable
            MCU_FF2A_IIC_IRQ_CONTROL2 &= ~_BIT5;
        }

        if((ucTempBuf & _BIT2) == _BIT2)
        {
            while((MCU_FF29_IIC_STATUS2 & _BIT1) == 0)
            {
                // Avoid buffer overflow
                if((g_ucDebugDdcciCommandNumber + 1) < (BYTE)sizeof(g_pucDebugDdcciData))
                {
                    g_ucDebugDdcciCommandNumber++;
                }
                else
                {
                    // Reset data buffer
                    MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT6;

                    g_ucDebugDdcciCommandNumber = 0;

                    break;
                }

                g_pucDebugDdcciData[g_ucDebugDdcciCommandNumber] = MCU_FF25_IIC_DATA_IN;
            }
        }

        if((ucTempBuf & _BIT4) == _BIT4)
        {
            MCU_FF27_IIC_STATUS &= ~_BIT4;

            if(g_ucDebugDdcciCommandNumber > 0)
            {
                // Hold Scl Pin
#if((_DEBUG_DDC_CHANNEL_SEL == _DDC5) && (_HW_DDC5_EXIST == _ON))
                ScalerSetBit(PFE_81_DDC5_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC4) && (_HW_DDC4_EXIST == _ON))
                ScalerSetBit(PFE_78_DDC4_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC3) && (_HW_DDC3_EXIST == _ON))
                ScalerSetBit(PFE_6F_DDC3_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC2) && (_HW_DDC2_EXIST == _ON))
                ScalerSetBit(PFE_66_DDC2_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC1) && (_HW_DDC1_EXIST == _ON))
                ScalerSetBit(PFF_2E_DDC1_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
#elif((_DEBUG_DDC_CHANNEL_SEL == _DDC0) && (_HW_DDC0_EXIST == _ON))
                ScalerSetBit(PFF_20_DDC0_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
#elif((_DEBUG_DDC_CHANNEL_SEL == _VGA_DDC) && (_HW_ISP_DDC_EXIST == _ON))
                ScalerSetBit(PFF_1D_ADC_DDC_CONTROL_2, ~(_BIT1 | _BIT0), _BIT0);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _ON)

                if(g_pucDebugDdcciData[0] == 0x55)
                {
                    if(g_pucDebugDdcciData[1] == 0x00)
                    {
                        g_usDebugFilterPro = 0;
                    }
                    else
                    {
                        g_usDebugFilterPro = ((g_pucDebugDdcciData[1] << 8) + g_pucDebugDdcciData[2]);
                    }
                }

                if((g_pucDebugDdcciData[0] == 0x2F) && (g_bDebugMessageEven == _TRUE))
                {
                    g_bDebugMessageEven = _FALSE;
                    g_bDebugFwHalt = _FALSE;
                }
                else if((g_pucDebugDdcciData[0] == 0x55) && (g_bDebugMessageEven != _TRUE))
                {
                    g_bDebugMessageEven = _TRUE;
                }
#endif

                MCU_FF2A_IIC_IRQ_CONTROL2 |= _BIT5;
                g_bDebugRunCommand = _TRUE;
            }
        }
    }
    else
    {
        if((MCU_FF27_IIC_STATUS & _BIT1) == _BIT1)
        {
            // Clear SUB_I Flag
            MCU_FF27_IIC_STATUS &= ~_BIT1;
        }

        if((MCU_FF27_IIC_STATUS & _BIT2) == _BIT2)
        {
            // Clear DATA_I Flag
            ucTempBuf = MCU_FF25_IIC_DATA_IN;
        }

        if((MCU_FF27_IIC_STATUS & _BIT4) == _BIT4)
        {
            // Clear STOP_I Flag
            MCU_FF27_IIC_STATUS &= ~_BIT4;
        }
    }
}
