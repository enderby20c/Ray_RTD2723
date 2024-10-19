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

#if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)
//----------------------------------------------------------------------------------------------------
// ID Code      : ScalerSDRAMInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE ucCLK;
    BYTE ucCMD;
    BYTE ucDQS0;
    BYTE ucDQS1;
    BYTE ucDQ0;
    BYTE ucDQ1;
} StructSDRAMPLLPI;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructSDRAMPLLPI g_pstSdramPLLPHASE[];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerSdramPowerControl(bit bOn);
extern void ScalerSdramControlReset(void);
#endif // endif #if(_MEMORY_TYPE_CONFIG == _MEMORY_SDRAM)

