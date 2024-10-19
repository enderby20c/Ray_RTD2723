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
// ID Code      : ScalerOsdCommand.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "Osd/ScalerOsd.h"


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
// Description  : OSD Sram Addr
// Input Value  : usAddr
// Output Value :
//--------------------------------------------------
void ScalerOsdSetSramAddr(WORD usAddr)
{
    // Set Address
    ScalerSetByte(P3A_F0_FRAME_CTRL_F_OSD_MAP_ADR_PORT_H, HIBYTE(usAddr));
    // Delay time between P3A_F0_FRAME_CTRL_F_OSD_MAP_ADR_PORT_H and P3A_F1_FRAME_CTRL_F_OSD_MAP_ADR_PORT_L
    // Avoid cpu write faster than osd transfer circuit (eclk to dclk)
    DELAY_XUS(1);
    ScalerSetByte(P3A_F1_FRAME_CTRL_F_OSD_MAP_ADR_PORT_L, LOBYTE(usAddr));
}

//--------------------------------------------------
// Description  : OSD Sram Addr - Font
// Input Value  : usValue
// Output Value :
//--------------------------------------------------
void ScalerOsdSetAddrSramFont(WORD usValue)
{
    // Set Write All Byte
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4), 0x00);
#else
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5), 0x00);
#endif

    // Set Write Font data
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~_BIT0, _BIT0);

    // Set Address
    ScalerOsdSetSramAddr(usValue);
}

//--------------------------------------------------
// Description  : OSD Font Addr
// Input Value  : usValue
// Output Value :
//--------------------------------------------------
void ScalerOsdSetAddrSramCommand(WORD usValue)
{
    // Set Write Command data
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~_BIT0, 0x00);

    // Set Address
    ScalerOsdSetSramAddr(usValue);
}

//--------------------------------------------------
// Description  : OSD Window Addr
// Input Value  : ucValue
// Output Value :
//--------------------------------------------------
void ScalerOsdSetAddrWindow(WORD usValue)
{
    ScalerSetByte(P3A_F4_FRAME_CTRL_F_OSD_WIN_ADR_H, HIBYTE(usValue));
    ScalerSetByte(P3A_F5_FRAME_CTRL_F_OSD_WIN_ADR_L, LOBYTE(usValue));
}

//--------------------------------------------------
// Description  : OSD Font Data Port
// Input Value  : ucValue
// Output Value :
//--------------------------------------------------
void ScalerOsdSetDataPortSram(BYTE ucValue)
{
    ScalerSetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, ucValue);
}

//--------------------------------------------------
// Description  : OSD Window Port
// Input Value  : ucValue
// Output Value :
//--------------------------------------------------
void ScalerOsdSetDataPortWindow(BYTE ucValue)
{
    ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucValue);
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
void ScalerOsdAddrSet(EnumOsdAddrIndicateType enumAddrIndicator, EnumOsdWriteType enumByteSel, WORD usAddress, EnumOsdDBufType enumDbufEnable)
{
    enumDbufEnable = enumDbufEnable;

    // Select Which Byte to Write: 001: Byte0, 010: Byte1, 100: Byte2, 011: Byte0 & Byte1, 101: Byte0 & Byte2, 110: Byte1 & Byte2,000: All
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4),
                 (enumByteSel == _OSD_BYTEALL) ? (0x00) : (enumByteSel << 4));
#else
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5), (enumByteSel == _OSD_BYTEALL) ? (0) : (enumByteSel << 5));
#endif

    switch(enumAddrIndicator)
    {
        case _OSD_WIN_CONTROL:
            ScalerOsdSetAddrWindow(usAddress);
            break;

        case _OSD_SRAM_FONT:
            ScalerOsdSetAddrSramFont(usAddress);
            break;

        default:
        case _OSD_SRAM_COMMAND:
            ScalerOsdSetAddrSramCommand(usAddress);
            break;
    }
}

//--------------------------------------------------
// Description  : Osd Burst Write to Window (P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT)
// Input Value  : Burst Write Pointer, Length, Bank, Table Type, Location
// Output Value : None
//--------------------------------------------------
void ScalerOsdBurstWriteDataPortWindow(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation)
{
    ScalerBurstWrite(pucAddress, usWriteLength, ucBankNum, P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucTableType, bTableLocation);
}

//--------------------------------------------------
// Description  : Osd Burst Write to Sram (P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT)
// Input Value  : Burst Write Pointer, Length, Bank, Table Type, Location
// Output Value : None
//--------------------------------------------------
void ScalerOsdBurstWriteDataPortSram(BYTE *pucAddress, WORD usWriteLength, BYTE ucBankNum, BYTE ucTableType, bit bTableLocation)
{
    ScalerBurstWrite(pucAddress, usWriteLength, ucBankNum, P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, ucTableType, bTableLocation);
}

//--------------------------------------------------
// Description  : Set OSD Frame Control Byte
// Input Value  : usAddr           -> WindowControl address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
//                ucData           -> ucByteSelect's Data
// Output Value :
//--------------------------------------------------
void ScalerOsdFrameControlByte(WORD usAddr, EnumOsdWriteType enumOsdWriteType, BYTE ucData)
{
    ScalerOsdWriteByte((((BYTE)enumOsdWriteType << 4) | _OSD_WIN_CONTROL), _OSD_WITHOUT_DB, usAddr, ucData);
}

//--------------------------------------------------
// Description  : Get OSD Frame Control Byte (Window)
// Input Value  : usAddr           -> WindowControl address
//                enumOsdWriteType -> _OSD_BYTE0 or _OSD_BYTE1 or _OSD_BYTE2
// Output Value : FrameControl Value
//--------------------------------------------------
BYTE ScalerOsdFrameControlByteGet(WORD usAddr, EnumOsdWriteType enumOsdWriteType)
{
    enumOsdWriteType = enumOsdWriteType;

    ScalerOsdSetAddrWindow(usAddr);
    return ScalerGetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT);
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
void ScalerOsdWriteAllByte(BYTE ucIndicate, WORD usAddr, BYTE ucByte0, BYTE ucByte1, BYTE ucByte2)
{
    ScalerOsdWriteByte((((BYTE)_OSD_BYTEALL << 4) | ucIndicate), _OSD_WITHOUT_DB, usAddr, ucByte0);

    if(ucIndicate != _OSD_WIN_CONTROL)
    {
        ScalerSetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, ucByte1);
        ScalerSetByte(P3A_F2_FRAME_CTRL_F_OSD_MAP_DATA_PORT, ucByte2);
    }
}

//--------------------------------------------------
// Description  : Set OSD Write Byte
// Input Value  : ucIndicateAndWriteByte -> [7:4] : EnumOsdWriteType
//                                          [3:0] : EnumOsdAddrIndicateType
//                usAddr                 -> SRAM address
//                ucData                 -> ucIndicate's Data
// Output Value :
//--------------------------------------------------
void ScalerOsdWriteByte(BYTE ucWriteByteAndIndicate, EnumOsdDBufType enumDBuf, WORD usAddr, BYTE ucData)
{
    enumDBuf = enumDBuf;

    // Select Which Byte to Write: 001: Byte0, 010: Byte1, 100: Byte2, 011: Byte0 & Byte1, 101: Byte0 & Byte2, 110: Byte1 & Byte2,000: All
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4),
                 ((ucWriteByteAndIndicate & 0xF0) == ((BYTE)_OSD_BYTEALL << 4)) ? (0x00) : (ucWriteByteAndIndicate & 0xF0));
#else
    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~(_BIT7 | _BIT6 | _BIT5), ((ucWriteByteAndIndicate & 0xF0) == ((BYTE)_OSD_BYTEALL << 4)) ? (0) : ((ucWriteByteAndIndicate & 0xF0) << 1));
#endif

    if((ucWriteByteAndIndicate & 0x0F) == _OSD_WIN_CONTROL)
    {
        // Set Address
        ScalerOsdSetAddrWindow(usAddr);

        // Set Data
        ScalerSetByte(P3A_F6_FRAME_CTRL_F_OSD_WIN_DATA_PORT, ucData);
    }
    else
    {
        // Set Address
        switch(ucWriteByteAndIndicate & 0x0F)
        {
            case _OSD_WIN_CONTROL:
                ScalerOsdSetAddrWindow(usAddr);
                break;

            case _OSD_SRAM_FONT:
                ScalerOsdSetAddrSramFont(usAddr);
                break;

            default:
            case _OSD_SRAM_COMMAND:
                ScalerOsdSetAddrSramCommand(usAddr);
                break;
        }

        // Set Data
        ScalerOsdSetDataPortSram(ucData);
    }
}
