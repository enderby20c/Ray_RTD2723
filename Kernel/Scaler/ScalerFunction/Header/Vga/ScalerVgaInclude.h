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
// ID Code      : ScalerVgaInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_VGA_SUPPORT == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of HS Phase Delay Calibration
//--------------------------------------------------
#define _HS_DELAY_DVTOTAL                           (100UL) // line
#define _HS_DELAY_TARGET_DHFREQ                     (3600UL) // 0.1KHz
#define _HS_DELAY_DHTOTAL                           ((WORD)(GET_D_CLK_FREQ() * 10 / _HS_DELAY_TARGET_DHFREQ)) // pixel
#define _HS_DELAY_REAL_DHFREQ                       ((WORD)(GET_D_CLK_FREQ() * 10 / _HS_DELAY_DHTOTAL)) // 0.1kHz
#define _HS_DELAY_ICLK_RATE                         (200UL) // MHz
#define _HS_DELAY_IHTOTAL                           ((DWORD)_HS_DELAY_DHTOTAL * 1000 * _HS_DELAY_ICLK_RATE / GET_D_CLK_FREQ())

#define SET_HS_DELAY_LATCH_EDGE()                   {\
                                                        ScalerSetBit(P30_A2_VGATOP_VGIP_DELAY_CTRL, ~_BIT3, 0x00);\
                                                    }

//--------------------------------------------------
// VGA Mode Table Start
//--------------------------------------------------
#define GET_VGA_MODE_HSTART()                       (g_usVgaTopModeHstart)
#define SET_VGA_MODE_HSTART(x)                      (g_usVgaTopModeHstart = (x))

#define GET_VGA_MODE_VSTART()                       (g_usVgaTopModeVstart)
#define SET_VGA_MODE_VSTART(x)                      (g_usVgaTopModeVstart = (x))

//--------------------------------------------------
// HS delay Time
//--------------------------------------------------
#define _PHASE_DELAY_HALF_PERIOD_SHIFT              ((ScalerGetBit(P0_BC_ADC_CK_OUT_CTRL, _BIT5) == _BIT5) ? 32 : 0)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of VGATOP Waiting Events (P30_E4)
//--------------------------------------------------
typedef enum
{
    _EVENT_VGA_IVS = _BIT4,
    _EVENT_VGA_IEN_START = _BIT5,
    _EVENT_VGA_IEN_STOP = _BIT6,
} EnumVgaTopWaitEventType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern WORD g_usVgaTopPhaseDelayTime;

extern WORD g_usVgaTopModeHstart;
extern WORD g_usVgaTopModeVstart;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerVgaTopSetVsBypassEnable(bit bEnable);
extern void ScalerVgaTopModifyPolarity(void);
extern void ScalerVgaTopSetAuto(EnumMeasureFieldSelect enumFieldSelect, EnumMeasureBoundType enumBoundType, WORD usHTotal);
extern bit ScalerVgaTopGetAutoResult(StructAutoActiveData *pstActiveRegion, bit bWait);
extern bit ScalerVgaTopAutoFuncWaitFinish(void);
extern bit ScalerVgaTopWaitForEvent(EnumVgaTopWaitEventType enumEvent);

#endif // End of #if(_VGA_SUPPORT == _ON)
