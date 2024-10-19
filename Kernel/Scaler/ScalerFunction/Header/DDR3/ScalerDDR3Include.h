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
// ID Code      : ScalerDDR3Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// DDR3 Data Rate
//--------------------------------------------------
#define _DDR3_DATA_RATE_2133M                               2133
#define _DDR3_DATA_RATE_1866M                               1866
#define _DDR3_DATA_RATE_1600M                               1600
#define _DDR3_DATA_RATE_1333M                               1333
#define _DDR3_DATA_RATE_1066M                               1066
#define _DDR3_DATA_RATE_800M                                800

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
extern void ScalerDDR3PowerControl(bit bOn);
extern void ScalerDDR3DCPHYInitial(void);
extern void ScalerDDR3DCSysInitial(void);
extern void ScalerDDR3DCSysSystemBridgeReset(void);
extern bit ScalerDDR3GetDDROldRDLStatus(void);

#if(_FACTORY_RTD_QC_SUPPORT == _ON)
extern DWORD ScalerDDR3CheckMemoryCount(void);
#endif

#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
extern void ScalerDDR3SetBwCtrlEnable(EnumMemoryClientType enumClientType, BYTE ucClientIndex, bit bEnable);
extern void ScalerDDR3SetBwCtrl(EnumMemoryClientType enumClientType, BYTE ucClientIndex, StructBwCtrlClientInfo *pstClientInfo);
#endif

#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)

