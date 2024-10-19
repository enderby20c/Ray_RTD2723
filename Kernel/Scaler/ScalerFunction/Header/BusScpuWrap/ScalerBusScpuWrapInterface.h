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
// ID Code      : ScalerBusScpuWrapInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DEBUGAXI_RDATA_FIFO_FULL                       _BIT10
#define _DEBUGAXI_WID_FULL                              _BIT9
#define _DEBUGAXI_WDATA_FIFO_FULL                       _BIT8
#define _DEBUGAXI_RCMD_FIFO_FULL                        _BIT7
#define _DEBUGAXI_WCMD_FIFO_FULL                        _BIT6
#define _DEBUGAXI_BREADY                                _BIT5
#define _DEBUGAXI_RDATA_FIFO_EMPTY                      _BIT4
#define _DEBUGAXI_WID_EMPTY                             _BIT3
#define _DEBUGAXI_WDATA_FIFO_EMPTY                      _BIT2
#define _DEBUGAXI_RCMD_FIFO_EMPTY                       _BIT1
#define _DEBUGAXI_WCMD_FIFO_EMPTY                       _BIT0

#define _DBGWRAP_DIS_RDATA_SYNC_FIFO_FULL               _BIT7
#define _DBGWRAP_DIS_RDATA_SYNC_FIFO_EMPTY              _BIT6
#define _DBGWRAP_RDATA_ASYNC_FIFO_EMPTY                 _BIT5
#define _DBGWRAP_RDATA_ASYNC_FIFO_FULL                  _BIT4
#define _DBGWRAP_WDATA_ASYNC_FIFO_EMPTY                 _BIT3
#define _DBGWRAP_WDATA_ASYNC_FIFO_FULL                  _BIT2
#define _DBGWRAP_CMD_ASYNC_FIFO_EMPTY                   _BIT1
#define _DBGWRAP_CMD_ASYNC_FIFO_FULL                    _BIT0

#define _DBGWRAP_DC_RD_OUTSTANDING_BUF_FIFO_CNT         (_BIT14 | _BIT13 | _BIT12 | _BIT11 | _BIT10 | _BIT9 | _BIT8)
#define _DBGWRAP_DC_RD_OUTSTANDING_BUF_FULL             _BIT7
#define _DBGWRAP_DC_RD_OUTSTANDING_BUF_EMPTY            _BIT6
// #define _DBGWRAP_RDATA_ASYNC_FIFO_EMPTY              _BIT5
// #define _DBGWRAP_RDATA_ASYNC_FIFO_FULL               _BIT4
// #define _DBGWRAP_WDATA_ASYNC_FIFO_EMPTY              _BIT3
// #define _DBGWRAP_WDATA_ASYNC_FIFO_FULL               _BIT2
// #define _DBGWRAP_CMD_ASYNC_FIFO_EMPTY                _BIT1
// #define _DBGWRAP_CMD_ASYNC_FIFO_FULL                 _BIT0


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// SCPU Wrapper Related Enum
//--------------------------------------------------
typedef enum
{
    _DEBUG_MODE_DC = 0x00,  /*!< DebugMode DC            */
    _DEBUG_MODE_DIS = 0x01, /*!< DebugMode Disram        */
    _DEBUG_MODE_FR = 0x02,  /*!< DebugMode Flash_RBus    */
}EnumCpuBusScpuWrapDebugMode;

typedef enum
{
    _DBG_MNT_RW = 0x00, /*!< Debug Monitor R/W both   */
    _DBG_MNT_R = 0x01,  /*!< Debug Monitor R          */
    _DBG_MNT_W = 0x02,  /*!< Debug Monitor W          */
}EnumCpuBusScpuWrapDebugMntType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_SCPU_SUPPORT == _ON)
extern void ScalerBusScpuWrap_IRQHandler(void);

extern void ScalerBusScpuWrapInitial(void);
extern void ScalerBusScpuWrapRemoteCmdNumSet(DWORD ulNum);
extern DWORD ScalerBusScpuWrapRemoteCmdNumGet(void);
extern void ScalerBusScpuWrapRemoteWDataNumSet(DWORD ulNum);
extern DWORD ScalerBusScpuWrapRemoteWDataNumGet(void);
extern void ScalerBusScpuWrapWrtCmdBufferable(void);
extern void ScalerBusScpuWrapWrtCmdNonBufferable(void);
extern void ScalerBusScpuWrapWrtcmdOutstandNumSet(DWORD ulNum);
extern DWORD ScalerBusScpuWrapWrtcmdOutstandNumGet(void);
extern void ScalerBusScpuWrapRdcmdOutstandNumSet(DWORD ulNum);
extern DWORD ScalerBusScpuWrapRdcmdOutstandNumGet(void);

extern void ScalerBusScpuWrapScpuDebugSelSet(DWORD ulSel);
extern DWORD ScalerBusScpuWrapScpuDebugSelGet(void);

extern void ScalerBusScpuWrapScpuDbgModeSelSet(EnumCpuBusScpuWrapDebugMode enumDbgMode);
extern EnumCpuBusScpuWrapDebugMode ScalerBusScpuWrapScpuDbgModeSelGet(void);
extern void ScalerBusScpuWrapScpuDbgSelDCSet(DWORD ulDc);
extern DWORD ScalerBusScpuWrapScpuDbgSelDCGet(void);
extern void ScalerBusScpuWrapScpuDbgSelFRSet(DWORD ulFr);
extern DWORD ScalerBusScpuWrapScpuDbgSelFRGet(void);

extern void ScalerBusScpuWrapMemTrashDbgSet(DWORD ulIdx, DWORD ulStart, DWORD ulEnd, EnumCpuBusScpuWrapDebugMntType enumMntType, DWORD ulDbgEnable);
extern void ScalerBusScpuWrapMemTrashDbgGet(DWORD ulIdx, DWORD *pulStart, DWORD *pulEnd, DWORD *pulCtrl);
extern void ScalerBusScpuWrapMemTrashDbgCtrlSet(DWORD ulIdx, EnumCpuBusScpuWrapDebugMntType enumMntType, DWORD ulDbgEnable);
extern EnumCpuBusScpuWrapDebugMntType ScalerBusScpuWrapMemTrashDbgCtrlGetMntType(DWORD ulIdx);
extern DWORD ScalerBusScpuWrapMemTrashDbgCtrlGetEnable(DWORD ulIdx);

extern void ScalerBusScpuWrapMemTrashDbgIntEnable(void);
extern void ScalerBusScpuWrapMemTrashDbgIntDisable(void);
extern DWORD ScalerBusScpuWrapMemTrashDbgIntGetCfg(void);
extern DWORD ScalerBusScpuWrapMemTrashDbgIntGetStatus(void);
extern void ScalerBusScpuWrapMemTrashDbgIntAckStatus(void);

extern void ScalerBusScpuWrapMemTrashDbgNegIntEnable(void);
extern void ScalerBusScpuWrapMemTrashDbgNegIntDisable(void);
extern DWORD ScalerBusScpuWrapMemTrashDbgNegIntGetCfg(void);
extern DWORD ScalerBusScpuWrapMemTrashDbgNegIntGetStatus(void);
extern void ScalerBusScpuWrapMemTrashDbgNegIntAckStatus(void);

extern DWORD ScalerBusScpuWrapMemTrashDbgGetTrapAddr(void);
extern DWORD ScalerBusScpuWrapMemTrashDbgGetTrapRW(void);

//Debug status
extern DWORD ScalerBusScpuWrapGetDebugAxi128B(void);
extern DWORD ScalerBusScpuWrapGetDebugAxi32B(void);
extern DWORD ScalerBusScpuWrapGetDbgWrapDis(void);

extern DWORD ScalerBusScpuWrapGetDbgWrapDC(void);

extern void ScalerBusScpuWrapAxiDbgMainWrtEnable(void);
extern void ScalerBusScpuWrapAxiDbgMainWrtDisable(void);
extern void ScalerBusScpuWrapAxiDbgMainRdEnable(void);
extern void ScalerBusScpuWrapAxiDbgMainRdDisable(void);

extern DWORD ScalerBusScpuWrapAxiDbgMainWrtGetCnt(void);
extern DWORD ScalerBusScpuWrapAxiDbgMainRdGetCnt(void);
extern DWORD ScalerBusScpuWrapAxiDbgPeriWrtGetCnt(void);
extern DWORD ScalerBusScpuWrapAxiDbgPeriRdGetCnt(void);

extern DWORD ScalerBusScpuWrapAxiDbgMainWrtGetAddr(void);
extern DWORD ScalerBusScpuWrapAxiDbgMainWrtGetID(void);
extern DWORD ScalerBusScpuWrapAxiDbgMainRdGetAddr(void);
extern DWORD ScalerBusScpuWrapAxiDbgMainRdGetID(void);
extern DWORD ScalerBusScpuWrapAxiDbgPeriWrtGetAddr(void);
extern DWORD ScalerBusScpuWrapAxiDbgPeriWrtGetID(void);
extern DWORD ScalerBusScpuWrapAxiDbgPeriRdGetAddr(void);
extern DWORD ScalerBusScpuWrapAxiDbgPeriRdGetID(void);

//TimeStampGeneration APB register control
extern DWORD ScalerBusScpuWrapTimeStampGenApbRead(DWORD ulAddr, DWORD *pulData);
extern DWORD ScalerBusScpuWrapTimeStampGenApbWrite(DWORD ulAddr, DWORD *pulData);

extern DWORD ScalerBusScpuWrapChkTrappedAddrMatchIntFlag(void);
extern DWORD ScalerBusScpuWrapChkTrappedAddrMisMatchIntFlag(void);
#endif
