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
// ID Code      : ScalerVgaSyncProc.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_VGA_SYNC_PROC_H__
#define __SCALER_VGA_SYNC_PROC_H__


#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of V-Sync width & total limitations
//--------------------------------------------------
#define _MAX_VSYNC_HIGH_PERIOD                      12 // Unit capture window

//--------------------------------------------------
// Definitions of Debounce Width And High Pulse Width Counter
//--------------------------------------------------
#define _MIN_SYNC_HIGHPULSE_WIDTH                   173 // Unit ns, Represent the shortest high pulse width
#define _MIN_SYNC_HIGHPULSE_CNT                     (((WORD)((DWORD)_MIN_SYNC_HIGHPULSE_WIDTH * _SYNC_PROC_CLK / 1000000)) & 0x7FF)
#define _MIN_SYNC_HIGHPULSE_CNT_PS                  (((WORD)((DWORD)_MIN_SYNC_HIGHPULSE_WIDTH * _HW_INTERNAL_OSC_XTAL / (0x01 << _IOSC_DIV) / 1000000)) & 0x7FF)

//--------------------------------------------------
// Definitions Of Capture window initial width tolerance
//--------------------------------------------------
#define _CAP_WINDOW_WIDTH_TOR                       2 // Unit: sync processor clock

//--------------------------------------------------
// Definitions Of Sync Processor Auto Run Polling Time, Target 120ms
// Auto Run Typer Time Out Base Counter(0x200000) Reference 27M Crystal About 80ms:                                                                            //
// 120 = 80 + 40(Tolerance), _XTAL27000K / _MCU_XTAL Is Linear Operator
//--------------------------------------------------
#define _AUTO_RUN_POLLING_TIME                      ((WORD)((DWORD)120 * _XTAL27000K / _SYNC_PROC_CLK))

//--------------------------------------------------
// Definitions Of Clamp Position in Pixel clock unit
//--------------------------------------------------
#define _CLAMP_POSITION_START                       0x04
#define _CLAMP_POSITION_END                         0x10

//--------------------------------------------------
// Definitions Of Min/Max H-Sync Freq, Normal Range (15.625, 112.5) Unit:KHz
//--------------------------------------------------
#define _SUPPORT_HSYNC_MIN_FREQ                     10  // + Torlerance
#define _SUPPORT_HSYNC_MAX_FREQ                     150 // + Torlerance

//--------------------------------------------------
// Definitions Of SOG middle compare level & shift range
//--------------------------------------------------
#define _SOG_MID_COMPARE_LEVEL                      (0x16)
#define _SOG_MID_COMPARE_RANGE                      (0x02)

//--------------------------------------------------
// Definitions Of Sync type autorun result
//--------------------------------------------------
#define GET_SYNCPROC_AUTORUN_RESULT()               (ScalerGetBit(P0_4C_VSYNC_COUNTER_LEVEL_MSB, (_BIT6 | _BIT5 | _BIT4)) >> 4)

//--------------------------------------------------
// Definitions Of Two frame times
//--------------------------------------------------
#define _WAIT_TWO_FRAME_TIME                        90 // Reference 24 Hz, (1/24) * 2 = 83ms, give 7ms tolerance

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Hsync Type Detection Auto Run Result
//--------------------------------------------------
typedef enum
{
    _NO_SIGNAL = 0,
    _NOT_SUPPORT = 1,
    _YPBPR_SYNC = 2,
    _SERRATION_CS = 3,
    _XOR_OR_TYPE_CS_WITH_EQR = 4,
    _XOR_OR_TYPE_CS_WITHOUT_EQR = 5,
    _SEPARATE_HSYNC = 6,
    _HSYNC_WITHOUT_VS = 7,
} EnumAutoRunResult;

#if(_SOG_SUPPORT == _ON)
//--------------------------------------------------
// Enumerations of SyncProc/AutoFunc Measure Mode
//--------------------------------------------------
typedef enum
{
    _SOG_LEVEL_VALID,
    _SOG_LEVEL_INVALID,
    _SOG_LEVEL_FAIL,
} EnumSogLevelSearchResult;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerVgaSyncProcAdcInitial(void);
extern void ScalerVgaSyncProcInitial(void);
extern bit ScalerVgaSyncProcHSSyncStableDetect(void);
extern bit ScalerVgaSyncProcStableCheck(void);
extern bit ScalerVgaSyncProcIsSeparate(void);
extern void ScalerVgaSyncProcClampPosSetting(WORD usClampPosStart, WORD usClampPosEnd);
extern void ScalerVgaSyncProcSetDebounce(BYTE ucDebounce);
extern void ScalerVgaSyncProcDownCounterSetting(void);

#if(_SOG_SUPPORT == _ON)
extern EnumSogLevelSearchResult ScalerVgaSyncProcSogCheckFlag(void);
extern EnumSogLevelSearchResult ScalerVgaSyncProcSogCheckHs(StructMeasureSyncData *pstMeasureSyncHV);
extern EnumSogLevelSearchResult ScalerVgaSyncProcSogCheckVs(StructMeasureSyncData *pstMeasureSyncHV);
extern EnumSogLevelSearchResult ScalerVgaSyncProcSogCheckSyncType(void);
extern void ScalerVgaSyncProcSetSogCompareLevel(BYTE *pucLevels);
extern bit ScalerVgaSyncProcSogSyncCheck(void);
extern bit ScalerVgaSyncProcRecheckSOGSyncStable(void);
#endif

#endif // End of #if(_VGA_SUPPORT == _ON)


#endif // End of #ifndef __SCALER_VGA_SYNC_PROC_H__
