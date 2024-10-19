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
// ID Code      : ScalerPLLInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************



//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_PANEL_STYLE == _PANEL_VBO) || (_PANEL_STYLE == _PANEL_DPTX))
extern void ScalerPLLDPTxPLLReset(void);
#endif

extern void ScalerPLLSetDPLLSSC(BYTE ucDclkSpreadSpeed, BYTE ucSpreadRange);
extern void ScalerPLLSetDPLLFreq(DWORD ulFreq);
extern void ScalerPLLM2PLLPower(BYTE ucOn);

#if(_HW_EPLL_SUPPORT == _ON)
extern void ScalerPLLEMCUPLLPower(BYTE ucOn);
#endif

#if(_VGA_SUPPORT == _ON)
extern bit ScalerAPLLFastLockAdjust(WORD usCurrHTotal);
extern void ScalerPLLSetPhase(BYTE ucPhase, WORD usVfreq);
#endif

extern void ScalerPLLFakePowerSavingControl(void);

