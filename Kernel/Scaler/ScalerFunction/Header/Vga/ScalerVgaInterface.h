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
// ID Code      : ScalerVgaInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Hardware Phase Search SOD Method
//--------------------------------------------------
typedef enum
{
    _PHASE_SEARCH_SOD = 0x00,
    _PHASE_SEARCH_WSOD = 0x01,
} EnumAutoPhaseSearchSODMethod;

//--------------------------------------------------
// Enumerations of Hardware Phase Search Step
//--------------------------------------------------
typedef enum
{
    _PHASE_SEARCH_STEP_1 = 0x00,
    _PHASE_SEARCH_STEP_2 = 0x01,
    _PHASE_SEARCH_STEP_4 = 0x02,
    _PHASE_SEARCH_STEP_8 = 0x03,
    _PHASE_SEARCH_STEP_16 = 0x04,
} EnumAutoPhaseSearchStep;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
extern BYTE g_ucVgaModeNo;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_VGA_SUPPORT == _ON)
extern void ScalerVgaTopInputInitial(void);
extern bit ScalerVgaTopModifyVsLatchEdge(bit bWait);
extern void ScalerVgaTopAutoFuncHBoundInitial(WORD usHBoundStart, WORD usHBoundEnd);
extern void ScalerVgaTopAutoFuncVBoundInitial(WORD usVBoundStart, WORD usVBoundEnd);
extern bit ScalerVgaTopHWAutoPhaseSearch(EnumAutoPhaseSearchStep enumPhaseStep, BYTE *pucPhaseResult, DWORD *pulSODMax, DWORD *pulSODMin, EnumAutoPhaseSearchSODMethod enumSODMethod, BYTE ucSODThreshold);
extern bit ScalerVgaTopAutoPhaseGetSOD(DWORD *pulSODValue);
extern bit ScalerVgaTopMeasureActiveRegion(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);
extern void ScalerVgaTopDoubleBufferApply(void);
extern WORD ScalerVgaTopGetCaptureVStartPosition(void);
extern WORD ScalerVgaTopGetCaptureVHeight(void);
extern WORD ScalerVgaTopGetCaptureVDelay(void);
extern void ScalerVgaTopSetCaptureVDelay(WORD usIVSDelay);
extern WORD ScalerVgaTopGetCaptureHStartPosition(void);
extern WORD ScalerVgaTopGetCaptureHWidth(void);
extern WORD ScalerVgaTopGetCaptureHDelay(void);
extern void ScalerVgaTopSetCaptureHDelay(WORD usIHSDelay);
extern bit ScalerVgaTopSetCapture(void);
extern void ScalerVgaTopModifyHsLatchEdgeDelay(void);
extern void ScalerVgaTopDoubleBufferEnable(bit bEn);
#endif

