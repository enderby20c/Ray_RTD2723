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
// ID Code      : ScalerVgaSyncProcInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Sync Processor Clock Frequency
//--------------------------------------------------
#define _SYNC_PRO_CLK_DIV                           (ScalerGetBit(P40_06_SYNCPROC_CLK_DIVIDER, (_BIT3 | _BIT2 | _BIT1 | _BIT0))) // Sync Pro Clock Divider
#define _SYNC_PRO_USE_M2PLL_CLK                     ((bit)ScalerGetBit(P40_06_SYNCPROC_CLK_DIVIDER, _BIT4) ? _TRUE : _FALSE)
#define _SYNC_PRO_XTAL_CLK                          ((bit)ScalerGetBit(P0_09_GA_POWER_CTRL, _BIT3) ? _HW_INTERNAL_OSC_XTAL : _EXT_XTAL)
#define _SYNC_PROC_CLK                              (DWORD)((GET_M2PLL_POWER_STATUS() == _FALSE) ? _SYNC_PRO_XTAL_CLK : (_SYNC_PRO_USE_M2PLL_CLK ? (((DWORD)_M2PLL_CLK_KHZ) / _SYNC_PRO_CLK_DIV) : _SYNC_PRO_XTAL_CLK))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern WORD ScalerVgaSyncProcGetDeVsyncWidth(void);
extern WORD ScalerVgaSyncProcGetClampEndPosition(void);
extern WORD ScalerVgaSyncProcMeasureIHFreqByStableMeasure(void);
extern void ScalerVgaSyncProcPulseDetectEnable(BYTE ucEnable);

#endif // End of #if(_VGA_SUPPORT == _ON)

