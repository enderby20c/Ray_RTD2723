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
// ID Code      : ScalerWdtInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _WDT_INT_EN_MASK    _BIT16

#define _WDT_EN_MASK        (0x000000FF)

#define ENABLE_CPU32_WDT()  {\
                                ScalerWdtEnableWdtINT(_WDT_INT_ENABLE);\
                                ScalerWdtEnableWdt(_WDT_ENABLE);\
                            }

#define DISABLE_CPU32_WDT() {\
                                ScalerWdtEnableWdt(_WDT_DISABLE);\
                                ScalerWdtEnableWdtINT(_WDT_INT_DISABLE);\
                            }


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// WDT Related Enum
//--------------------------------------------------
typedef enum
{
    _WDT_INT_DISABLE = 0,        /*!< WDT Disable Interrupt    */
    _WDT_INT_ENABLE = ((1UL) << 16),   /*!< WDT Enable Interrupt        */
}EnumCpuWdtIntEN;

typedef enum
{
    _WDT_DISABLE = 0xA5,     /*!< WDT Disable    */
    _WDT_ENABLE = 0x33,     /*!< WDT Enable    */
}EnumCpuWdtEN;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerWdtInitial(void);
extern DWORD ScalerWdtGetWdtNmiFlag(void);
extern void ScalerWdtAckWdtNmiFlag(void);
extern void ScalerWdtTriggerWdtReset(void);
extern void ScalerWdtEnableWdtINT(EnumCpuWdtIntEN enumWdtIntEn);
extern DWORD ScalerWdtGetWdtNmiOccurCnt(void);
extern void ScalerWdtResetWdtNmiOccurCnt(void);
extern DWORD ScalerWdtGetWdtOccurCnt(void);
extern void ScalerWdtResetWdtOccurCnt(void);
extern void ScalerWdtEnableWdt(EnumCpuWdtEN enumWdtEn);

__attribute__((section(".itcm_section.ScalerWdtClearWDT")))
extern void ScalerWdtClearWDT(void);

extern void ScalerWdtSetNmiOV(DWORD ulNmiOvMs);
extern void ScalerWdtSetWdtOV(DWORD ulWdtOvMs, EnumClkSel enumSel);
