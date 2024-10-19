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
// ID Code      : ScalerBusScpuWrap.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "ScalerFunctionInclude.h"
#include "BusScpuWrap/ScalerBusScpuWrap.h"

#if(_SCPU_SUPPORT == _ON)

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
// Description  : ScpuWrapper INT Handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrap_IRQHandler(void)
{
    if(ScalerBusScpuWrapChkTrappedAddrMatchIntFlag() == (_BIT4 | _BIT3))
    {
        // trapped address SCPU IRQ Enabled and trapped address matched

        // DWORD ulTrapAddr = ScalerBusScpuWrapMemTrashDbgGetTrapAddr();
        // DWORD ulIsWriteOp = ScalerBusScpuWrapMemTrashDbgGetTrapRW();

        // Ack Flag
        ScalerBusScpuWrapMemTrashDbgIntAckStatus();
    }

    if(ScalerBusScpuWrapChkTrappedAddrMisMatchIntFlag() == (_BIT2 | _BIT1))
    {
        // exclusive trapped address SCPU IRQ Enabled and trapped address does not match

        // DWORD ulTrapAddr = ScalerBusScpuWrapMemTrashDbgGetTrapAddr();
        // DWORD ulIsWriteOp = ScalerBusScpuWrapMemTrashDbgGetTrapRW();

        // Ack Flag
        ScalerBusScpuWrapMemTrashDbgNegIntAckStatus();
    }
}

//--------------------------------------------------
// Description  : Init SCPU Wrapper related Interrupt
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapInitial(void)
{
    NOP();
}

//--------------------------------------------------
// Description  : Enable Flash Random Write strobe
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapFlashRandomWstrobeEnable(void)
{
    Scaler32SetBit(PA20020_10_WRAPPER_CFG1, ~(_BIT18), _BIT18);
}

//--------------------------------------------------
// Description  : Disable Flash Random Write strobe
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapFlashRandomWstrobeDisable(void)
{
    Scaler32SetBit(PA20020_10_WRAPPER_CFG1, ~(_BIT18), 0);
}

//--------------------------------------------------
// Description  : Set Remote Cmd Num
// Input Value  : num --> target remote cmd num
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapRemoteCmdNumSet(DWORD ulNum)
{
    Scaler32SetBit(PA20020_10_WRAPPER_CFG1, ~(0x0F << 14), ((ulNum & 0x0F) << 14));
}

//--------------------------------------------------
// Description  : Get Remote Cmd Num
// Input Value  : None
// Output Value : current remote cmd num
//--------------------------------------------------
DWORD ScalerBusScpuWrapRemoteCmdNumGet(void)
{
    return ((Scaler32GetDWord(PA20020_10_WRAPPER_CFG1) >> 14) & 0x0F);
}

//--------------------------------------------------
// Description  : Set Remote Data Num
// Input Value  : num:target remote Data num
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapRemoteWDataNumSet(DWORD ulNum)
{
    Scaler32SetBit(PA20020_10_WRAPPER_CFG1, ~(0x0F << 10), ((ulNum & 0x0F) << 10));
}

//--------------------------------------------------
// Description  : Get Remote Data Num
// Input Value  : None
// Output Value : current remote Data num
//--------------------------------------------------
DWORD ScalerBusScpuWrapRemoteWDataNumGet(void)
{
    return ((Scaler32GetDWord(PA20020_10_WRAPPER_CFG1) >> 10) & 0x0F);
}

//--------------------------------------------------
// Description  : Set Wrt Cmd Bufferable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapWrtCmdBufferable(void)
{
    Scaler32SetBit(PA20020_10_WRAPPER_CFG1, ~(_BIT8), 0);
}

//--------------------------------------------------
// Description  : Set Wrt Cmd NonBufferable
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapWrtCmdNonBufferable(void)
{
    Scaler32SetBit(PA20020_10_WRAPPER_CFG1, ~(_BIT8), _BIT8);
}

//--------------------------------------------------
// Description  : Set wrt outstand num
// Input Value  : num --> target wrt outstand num
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapWrtcmdOutstandNumSet(DWORD ulNum)
{
    Scaler32SetBit(PA20020_10_WRAPPER_CFG1, ~(0x0F << 4), ((ulNum & 0x0F) << 4));
}

//--------------------------------------------------
// Description  : Get wrt outstand num
// Input Value  : None
// Output Value : current wrt outstand num
//--------------------------------------------------
DWORD ScalerBusScpuWrapWrtcmdOutstandNumGet(void)
{
    return ((Scaler32GetDWord(PA20020_10_WRAPPER_CFG1) >> 4) & 0x0F);
}

//--------------------------------------------------
// Description  : Set wrt outstand num
// Input Value  : num --> target wrt outstand num
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapRdcmdOutstandNumSet(DWORD ulNum)
{
    Scaler32SetBit(PA20020_10_WRAPPER_CFG1, ~(0x0F), (ulNum & 0x0F));
}

//--------------------------------------------------
// Description  : Get wrt outstand num
// Input Value  : None
// Output Value : current wrt outstand num
//--------------------------------------------------
DWORD ScalerBusScpuWrapRdcmdOutstandNumGet(void)
{
    return (Scaler32GetDWord(PA20020_10_WRAPPER_CFG1) & 0x0F);
}

//--------------------------------------------------
// Description  : Set SCPU Debug Select
// Input Value  : sel --> target SCPU Debug Select
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapScpuDebugSelSet(DWORD ulSel)
{
    Scaler32SetBit(PA20020_14_WRAPPER_CFG2, ~(0x0F), (ulSel & 0x0F));
}

//--------------------------------------------------
// Description  : Get SCPU Debug Select
// Input Value  : None
// Output Value : current SCPU Debug Select
//--------------------------------------------------
DWORD ScalerBusScpuWrapScpuDebugSelGet(void)
{
    return Scaler32GetBit(PA20020_14_WRAPPER_CFG2, 0x0F);
}

//--------------------------------------------------
// Description  : Set SCPU DebugMode Select
// Input Value  : sel --> target SCPU DebugMode Select
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapScpuDbgModeSelSet(EnumCpuBusScpuWrapDebugMode enumDbgMode)
{
    Scaler32SetBit(PA20020_18_DBG_SEL_CTRL, ~(0x03 << 12), ((enumDbgMode & 0x03) << 12));
}

//--------------------------------------------------
// Description  : Get SCPU DebugMode Select
// Input Value  : None
// Output Value : current SCPU DebugMode Select
//--------------------------------------------------
EnumCpuBusScpuWrapDebugMode ScalerBusScpuWrapScpuDbgModeSelGet(void)
{
    return (EnumCpuBusScpuWrapDebugMode)((Scaler32GetDWord(PA20020_18_DBG_SEL_CTRL) >> 12) & 0x03);
}

//--------------------------------------------------
// Description  : Set SCPU Debug Select DC
// Input Value  : sel:target SCPU Debug Select DC
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapScpuDbgSelDCSet(DWORD ulDc)
{
    Scaler32SetBit(PA20020_18_DBG_SEL_CTRL, ~(0x0F << 8), ((ulDc & 0x0F) << 8));
}

//--------------------------------------------------
// Description  : Get SCPU Debug Select DC
// Input Value  : None
// Output Value : current SCPU Debug Select DC
//--------------------------------------------------
DWORD ScalerBusScpuWrapScpuDbgSelDCGet(void)
{
    return ((Scaler32GetDWord(PA20020_18_DBG_SEL_CTRL) >> 8) & 0x0F);
}

//--------------------------------------------------
// Description  : Set SCPU Debug Select FR
// Input Value  : sel:target SCPU Debug Select FR
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapScpuDbgSelFRSet(DWORD ulFr)
{
    Scaler32SetBit(PA20020_18_DBG_SEL_CTRL, ~(0x0F << 4), ((ulFr & 0x0F) << 4));
}

//--------------------------------------------------
// Description  : Get SCPU Debug Select FR
// Input Value  : None
// Output Value : current SCPU Debug Select FR
//--------------------------------------------------
DWORD ScalerBusScpuWrapScpuDbgSelFRGet(void)
{
    return ((Scaler32GetDWord(PA20020_18_DBG_SEL_CTRL) >> 4) & 0x0F);
}

//--------------------------------------------------
// Description  : Set Memory Trash Debug info
// Input Value  : idx --> index of Memory Trash Debug info (0~3)
//                start --> start address for Memory Trash Debug
//                end --> end address for Memory Trash Debug
//                ctrl --> control flags for Memory Trash Debug
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgSet(DWORD ulIdx, DWORD ulStart, DWORD ulEnd, EnumCpuBusScpuWrapDebugMntType enumMntType, DWORD ulDbgEnable)
{
    Scaler32SetDWord(PA20020_20_MEM_TRASH_DBG_START + (ulIdx << 2), ulStart);
    Scaler32SetDWord(PA20020_30_MEM_TRASH_DBG_END + (ulIdx << 2), ulEnd);
    Scaler32SetDWord(PA20020_40_MEM_TRASH_DBG_CTRL + (ulIdx << 2), ((enumMntType << 2) | ulDbgEnable | 0x12));
}

//--------------------------------------------------
// Description  : Get Memory Trash Debug info
// Input Value  : idx --> index of Memory Trash Debug info (0~3)
//                start --> pointer of start address for Memory Trash Debug
//                end --> pointer of end address for Memory Trash Debug
//                ctrl --> pointer of control flags for Memory Trash Debug
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgGet(DWORD ulIdx, DWORD *pulStart, DWORD *pulEnd, DWORD *pulCtrl)
{
    *pulStart = Scaler32GetDWord(PA20020_20_MEM_TRASH_DBG_START + (ulIdx << 2));
    *pulEnd = Scaler32GetDWord(PA20020_30_MEM_TRASH_DBG_END + (ulIdx << 2));
    *pulCtrl = Scaler32GetDWord(PA20020_40_MEM_TRASH_DBG_CTRL + (ulIdx << 2));
}

//--------------------------------------------------
// Description  : Set Memory Trash Debug Control
// Input Value  : idx --> index of Memory Trash Debug info (0~3)
//                mnttype --> monitor type of Memory Trash Debug (BOTH/R/W)
//                enable --> enable debug
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgCtrlSet(DWORD ulIdx, EnumCpuBusScpuWrapDebugMntType enumMntType, DWORD ulDbgEnable)
{
    Scaler32SetDWord(PA20020_40_MEM_TRASH_DBG_CTRL + (ulIdx << 2), ((enumMntType << 2) | ulDbgEnable | 0x12));
}

//--------------------------------------------------
// Description  : Set Memory Trash Debug ctrl
// Input Value  : idx --> index of Memory Trash Debug info (0~3)
//                ctrl --> control flags for Memory Trash Debug
// Output Value : None
//--------------------------------------------------
EnumCpuBusScpuWrapDebugMntType ScalerBusScpuWrapMemTrashDbgCtrlGetMntType(DWORD ulIdx)
{
    return (EnumCpuBusScpuWrapDebugMntType)((Scaler32GetDWord(PA20020_40_MEM_TRASH_DBG_CTRL + (ulIdx << 2)) >> 2) & (0x03));
}

//--------------------------------------------------
// Description  : Get Memory Trash Debug ctrl
// Input Value  : idx --> index of Memory Trash Debug info (0~3)
// Output Value : debug enable flag for Memory Trash Debug
//--------------------------------------------------
DWORD ScalerBusScpuWrapMemTrashDbgCtrlGetEnable(DWORD ulIdx)
{
    return Scaler32GetBit(PA20020_40_MEM_TRASH_DBG_CTRL + (ulIdx << 2), _BIT0);
}

//--------------------------------------------------
// Description  : Enable MemTrashDbg Interrupt when address fall into DBG_START[i]~DBG_END[i],i=0~3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgIntEnable(void)
{
    Scaler32SetDWord(PA20020_50_MEM_TRASH_DBG_INT, (_BIT3 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable MemTrashDbg Interrupt when address fall into DBG_START[i]~DBG_END[i],i=0~3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgIntDisable(void)
{
    Scaler32SetDWord(PA20020_50_MEM_TRASH_DBG_INT, _BIT3);
}

//--------------------------------------------------
// Description  : get MemTrashDbg Interrupt config when address fall into DBG_START[i]~DBG_END[i],i=0~3
// Input Value  : None
// Output Value : 0:disable , others:enable
//--------------------------------------------------
DWORD ScalerBusScpuWrapMemTrashDbgIntGetCfg(void)
{
    return Scaler32GetBit(PA20020_50_MEM_TRASH_DBG_INT, _BIT3);
}

//--------------------------------------------------
// Description  : check MemTrashDbg Interrupt status (will set when address fall into DBG_START[i]~DBG_END[i],i=0~3)
// Input Value  : None
// Output Value : 0:not happened , others:happened
//--------------------------------------------------
DWORD ScalerBusScpuWrapMemTrashDbgIntGetStatus(void)
{
    return Scaler32GetBit(PA20020_50_MEM_TRASH_DBG_INT, _BIT4);
}

//--------------------------------------------------
// Description  : Ack MemTrashDbg Interrupt status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgIntAckStatus(void)
{
    // write 0 to Bit4 for ack MemTrashDbg Neg INT Flag
    Scaler32SetDWord(PA20020_50_MEM_TRASH_DBG_INT, _BIT4);

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}

//--------------------------------------------------
// Description  : Enable MemTrashDbg Negative Interrupt when address NOT fall into DBG_START[i]~DBG_END[i],i=0~3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgNegIntEnable(void)
{
    Scaler32SetDWord(PA20020_50_MEM_TRASH_DBG_INT, (_BIT1 | _BIT0));
}

//--------------------------------------------------
// Description  : Disable MemTrashDbg Negative Interrupt when address NOT fall into DBG_START[i]~DBG_END[i],i=0~3
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgNegIntDisable(void)
{
    Scaler32SetDWord(PA20020_50_MEM_TRASH_DBG_INT, _BIT1);
}

//--------------------------------------------------
// Description  : get MemTrashDbg Negative Interrupt config when address NOT fall into DBG_START[i]~DBG_END[i],i=0~3
// Input Value  : None
// Output Value : 0:disable , others:enable
//--------------------------------------------------
DWORD ScalerBusScpuWrapMemTrashDbgNegIntGetCfg(void)
{
    return Scaler32GetBit(PA20020_50_MEM_TRASH_DBG_INT, _BIT1);
}

//--------------------------------------------------
// Description  : check MemTrashDbg Negative Interrupt status (will set when address NOT fall into DBG_START[i]~DBG_END[i],i=0~3)
// Input Value  : None
// Output Value : 0:not happened , others:happened
//--------------------------------------------------
DWORD ScalerBusScpuWrapMemTrashDbgNegIntGetStatus(void)
{
    return Scaler32GetBit(PA20020_50_MEM_TRASH_DBG_INT, _BIT2);
}

//--------------------------------------------------
// Description  : Ack MemTrashDbg Negative Interrupt status
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapMemTrashDbgNegIntAckStatus(void)
{
    // write 0 to Bit2 for ack MemTrashDbg Neg INT Flag
    Scaler32SetDWord(PA20020_50_MEM_TRASH_DBG_INT, _BIT2);

    // avoiding RBUS delay cause repeat entering INT
    ASM_DSB();
}

//--------------------------------------------------
// Description  : Get MemTrashDbg Trapped Address when Interrupt happened
// Input Value  : None
// Output Value : trapped address
//--------------------------------------------------
DWORD ScalerBusScpuWrapMemTrashDbgGetTrapAddr(void)
{
    return Scaler32GetDWord(PA20020_54_MEM_TRASH_DBG_ADDR);
}

//--------------------------------------------------
// Description  : Get MemTrashDbg Trapped r/w operation when Interrupt happened
// Input Value  : None
// Output Value : 0:read ; 1:write
//--------------------------------------------------
DWORD ScalerBusScpuWrapMemTrashDbgGetTrapRW(void)
{
    return Scaler32GetDWord(PA20020_58_MEM_TRASH_DBG_RW);
}

//--------------------------------------------------
// Description  : Get DEBUGAXI128B info
// Input Value  : None
// Output Value : _DEBUGAXI_RDATA_FIFO_FULL    _BIT10
//                _DEBUGAXI_WID_FULL           _BIT9
//                _DEBUGAXI_WDATA_FIFO_FULL    _BIT8
//                _DEBUGAXI_RCMD_FIFO_FULL     _BIT7
//                _DEBUGAXI_WCMD_FIFO_FULL     _BIT6
//                _DEBUGAXI_BREADY             _BIT5
//                _DEBUGAXI_RDATA_FIFO_EMPTY   _BIT4
//                _DEBUGAXI_WID_EMPTY          _BIT3
//                _DEBUGAXI_WDATA_FIFO_EMPTY   _BIT2
//                _DEBUGAXI_RCMD_FIFO_EMPTY    _BIT1
//                _DEBUGAXI_WCMD_FIFO_EMPTY    _BIT0
//--------------------------------------------------
DWORD ScalerBusScpuWrapGetDebugAxi128B(void)
{
    return ((((Scaler32GetDWord(PA20026_04_DEBUGAXI128B_2) & 0x1F) << 6)) |
            (Scaler32GetDWord(PA20026_00_DEBUGAXI128B_1) & 0x3F));
}

//--------------------------------------------------
// Description  : Get DEBUGAXI32B info
// Input Value  : None
// Output Value : _DEBUGAXI_RDATA_FIFO_FULL    _BIT10
//                _DEBUGAXI_WID_FULL           _BIT9
//                _DEBUGAXI_WDATA_FIFO_FULL    _BIT8
//                _DEBUGAXI_RCMD_FIFO_FULL     _BIT7
//                _DEBUGAXI_WCMD_FIFO_FULL     _BIT6
//                _DEBUGAXI_BREADY             _BIT5
//                _DEBUGAXI_RDATA_FIFO_EMPTY   _BIT4
//                _DEBUGAXI_WID_EMPTY          _BIT3
//                _DEBUGAXI_WDATA_FIFO_EMPTY   _BIT2
//                _DEBUGAXI_RCMD_FIFO_EMPTY    _BIT1
//                _DEBUGAXI_WCMD_FIFO_EMPTY    _BIT0
//--------------------------------------------------
DWORD ScalerBusScpuWrapGetDebugAxi32B(void)
{
    return ((((Scaler32GetDWord(PA20026_0C_DEBUGAXI32B_2) & 0x1F) << 6)) |
            (Scaler32GetDWord(PA20026_08_DEBUGAXI32B_1) & 0x3F));
}

//--------------------------------------------------
// Description  : Get DEBUGWRAPPER DIS info
// Input Value  : None
// Output Value : _DBGWRAP_DIS_RDATA_SYNC_FIFO_FULL    _BIT7
//                _DBGWRAP_DIS_RDATA_SYNC_FIFO_EMPTY   _BIT6
//                _DBGWRAP_RDATA_ASYNC_FIFO_EMPTY      _BIT5
//                _DBGWRAP_RDATA_ASYNC_FIFO_FULL       _BIT4
//                _DBGWRAP_WDATA_ASYNC_FIFO_EMPTY      _BIT3
//                _DBGWRAP_WDATA_ASYNC_FIFO_FULL       _BIT2
//                _DBGWRAP_CMD_ASYNC_FIFO_EMPTY        _BIT1
//                _DBGWRAP_CMD_ASYNC_FIFO_FULL         _BIT0
//--------------------------------------------------
DWORD ScalerBusScpuWrapGetDbgWrapDis(void)
{
    return (((Scaler32GetDWord(PA20026_1C_DEBUGWRAPPER_4) & 0x600) >> 3) |
            ((Scaler32GetDWord(PA20026_18_DEBUGWRAPPER_3) & 0x0C) << 2) |
            ((Scaler32GetDWord(PA20026_14_DEBUGWRAPPER_2) & 0x0C)) |
            ((Scaler32GetDWord(PA20026_10_DEBUGWRAPPER_1) & 0x0C) >> 2));
}


//--------------------------------------------------
// Description  : Get DEBUGWRAPPER DC info
// Input Value  : None
// Output Value : _DBGWRAP_DC_RD_OUTSTANDING_BUF_FIFO_CNT  (_BIT14+_BIT13+_BIT12+_BIT11+_BIT10+_BIT9+_BIT8)
//                _DBGWRAP_DC_RD_OUTSTANDING_BUF_FULL  _BIT7
//                _DBGWRAP_DC_RD_OUTSTANDING_BUF_EMPTY _BIT6
//                _DBGWRAP_RDATA_ASYNC_FIFO_EMPTY      _BIT5
//                _DBGWRAP_RDATA_ASYNC_FIFO_FULL       _BIT4
//                _DBGWRAP_WDATA_ASYNC_FIFO_EMPTY      _BIT3
//                _DBGWRAP_WDATA_ASYNC_FIFO_FULL       _BIT2
//                _DBGWRAP_CMD_ASYNC_FIFO_EMPTY        _BIT1
//                _DBGWRAP_CMD_ASYNC_FIFO_FULL         _BIT0
//--------------------------------------------------
DWORD ScalerBusScpuWrapGetDbgWrapDC(void)
{
    return (((Scaler32GetDWord(PA20026_1C_DEBUGWRAPPER_4) & 0x1FF) << 6) |
            ((Scaler32GetDWord(PA20026_18_DEBUGWRAPPER_3) & 0x03) << 4) |
            ((Scaler32GetDWord(PA20026_14_DEBUGWRAPPER_2) & 0x03) << 2) |
            ((Scaler32GetDWord(PA20026_10_DEBUGWRAPPER_1) & 0x03)));
}

//--------------------------------------------------
// Description  : Enable debug axi main write
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapAxiDbgMainWrtEnable(void)
{
    Scaler32SetBit(PA20026_20_AXIDBG_CTRL, ~(_BIT3), 0);
}

//--------------------------------------------------
// Description  : Disable debug axi main write
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapAxiDbgMainWrtDisable(void)
{
    Scaler32SetBit(PA20026_20_AXIDBG_CTRL, ~(_BIT3), _BIT3);
}

//--------------------------------------------------
// Description  : Enable debug axi main read
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapAxiDbgMainRdEnable(void)
{
    Scaler32SetBit(PA20026_20_AXIDBG_CTRL, ~(_BIT2), 0);
}

//--------------------------------------------------
// Description  : Disable debug axi main read
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapAxiDbgMainRdDisable(void)
{
    Scaler32SetBit(PA20026_20_AXIDBG_CTRL, ~(_BIT2), _BIT2);
}

//--------------------------------------------------
// Description  : Enable debug axi peri write
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapAxiDbgPeriWrtEnable(void)
{
    Scaler32SetBit(PA20026_20_AXIDBG_CTRL, ~(_BIT1), 0);
}

//--------------------------------------------------
// Description  : Disable debug axi peri write
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapAxiDbgPeriWrtDisable(void)
{
    Scaler32SetBit(PA20026_20_AXIDBG_CTRL, ~(_BIT1), _BIT1);
}

//--------------------------------------------------
// Description  : Enable debug axi peri read
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapAxiDbgPeriRdEnable(void)
{
    Scaler32SetBit(PA20026_20_AXIDBG_CTRL, ~(_BIT0), 0);
}

//--------------------------------------------------
// Description  : Disable debug axi peri read
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerBusScpuWrapAxiDbgPeriRdDisable(void)
{
    Scaler32SetBit(PA20026_20_AXIDBG_CTRL, ~(_BIT0), _BIT0);
}

//--------------------------------------------------
// Description  : get valid axi main write cnt
// Input Value  : None
// Output Value : valid axi main write cnt
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgMainWrtGetCnt(void)
{
    return ((Scaler32GetDWord(PA20026_24_AXIDBG_STATUS) >> 24) & 0x1F);
}

//--------------------------------------------------
// Description  : get valid axi main read cnt
// Input Value  : None
// Output Value : valid axi main read cnt
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgMainRdGetCnt(void)
{
    return ((Scaler32GetDWord(PA20026_24_AXIDBG_STATUS) >> 16) & 0x1F);
}

//--------------------------------------------------
// Description  : get valid axi peri write cnt
// Input Value  : None
// Output Value : valid axi peri write cnt
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgPeriWrtGetCnt(void)
{
    return ((Scaler32GetDWord(PA20026_24_AXIDBG_STATUS) >> 8) & 0x03);
}

//--------------------------------------------------
// Description  : get valid axi peri read cnt
// Input Value  : None
// Output Value : valid axi peri read cnt
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgPeriRdGetCnt(void)
{
    return (Scaler32GetDWord(PA20026_24_AXIDBG_STATUS) & 0x03);
}


//--------------------------------------------------
// Description  : get axi main write Address
// Input Value  : None
// Output Value : axi main write Address
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgMainWrtGetAddr(void)
{
    return Scaler32GetDWord(PA20026_28_AXIDBG_MAIN_WADDR);
}

//--------------------------------------------------
// Description  : get axi main write ID
// Input Value  : None
// Output Value : axi main write ID
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgMainWrtGetID(void)
{
    return Scaler32GetDWord(PA20026_2C_AXIDBG_MAIN_WID);
}

//--------------------------------------------------
// Description  : get axi main read Address
// Input Value  : None
// Output Value : axi main read Address
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgMainRdGetAddr(void)
{
    return Scaler32GetDWord(PA20026_30_AXIDBG_MAIN_RADDR);
}

//--------------------------------------------------
// Description  : get axi main read ID
// Input Value  : None
// Output Value : axi main read ID
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgMainRdGetID(void)
{
    return Scaler32GetDWord(PA20026_34_AXIDBG_MAIN_RID);
}

//--------------------------------------------------
// Description  : get axi peri write Address
// Input Value  : None
// Output Value : axi peri write Address
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgPeriWrtGetAddr(void)
{
    return Scaler32GetDWord(PA20026_38_AXIDBG_PERI_WADDR);
}

//--------------------------------------------------
// Description  : get axi peri write ID
// Input Value  : None
// Output Value : axi peri write ID
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgPeriWrtGetID(void)
{
    return Scaler32GetDWord(PA20026_3C_AXIDBG_PERI_WID);
}

//--------------------------------------------------
// Description  : get axi peri read Address
// Input Value  : None
// Output Value : axi peri read Address
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgPeriRdGetAddr(void)
{
    return Scaler32GetDWord(PA20026_40_AXIDBG_PERI_RADDR);
}

//--------------------------------------------------
// Description  : get axi peri read ID
// Input Value  : None
// Output Value : axi peri read ID
//--------------------------------------------------
DWORD ScalerBusScpuWrapAxiDbgPeriRdGetID(void)
{
    return Scaler32GetDWord(PA20026_44_AXIDBG_PERI_RID);
}


//--------------------------------------------------
// Description  : Read TimeStamp Gen APB register
// Input Value  : ulAddr:32bits address of register
//                  pulData:32bits data pointer of register
// Output Value : 0:failed ; 1:success
//--------------------------------------------------
DWORD ScalerBusScpuWrapTimeStampGenApbRead(DWORD ulAddr, DWORD *pulData)
{
    Scaler32SetDWord(PA20028_00_TSGEN_INPUT_CTRL0, ulAddr);
    *pulData = Scaler32GetDWord(PA20028_04_TSGEN_INPUT_CTRL1);

    return (Scaler32GetDWord(PA20028_08_TSGEN_INPUT_CTRL2) ^ _BIT0);
}

//--------------------------------------------------
// Description  : Write TimeStamp Gen APB APB register
// Input Value  : ulAddr:32bits address of register
//                  pulData:32bits data pointer of register
// Output Value : 0:failed ; 1:success
//--------------------------------------------------
DWORD ScalerBusScpuWrapTimeStampGenApbWrite(DWORD ulAddr, DWORD *pulData)
{
    Scaler32SetDWord(PA20028_00_TSGEN_INPUT_CTRL0, ulAddr);
    Scaler32SetDWord(PA20028_04_TSGEN_INPUT_CTRL1, (*pulData));

    return (Scaler32GetDWord(PA20028_08_TSGEN_INPUT_CTRL2) ^ _BIT0);
}


//--------------------------------------------------
// Description  : get Trapped Address Match INT flag
// Input Value  : None
// Output Value : 0: not set ; Other:set
//--------------------------------------------------
DWORD ScalerBusScpuWrapChkTrappedAddrMatchIntFlag(void)
{
    return Scaler32GetBit(PA20020_50_MEM_TRASH_DBG_INT, (_BIT4 | _BIT3));
}

//--------------------------------------------------
// Description  : get Trapped Address Match INT flag
// Input Value  : None
// Output Value : 0: not set ; Other:set
//--------------------------------------------------
DWORD ScalerBusScpuWrapChkTrappedAddrMisMatchIntFlag(void)
{
    return Scaler32GetBit(PA20020_50_MEM_TRASH_DBG_INT, (_BIT2 | _BIT1));
}
#endif
