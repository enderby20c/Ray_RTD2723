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
// ID Code      : ScalerDDR2Include.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//--------------------------------------------------
// DDR2 Data Rate
//--------------------------------------------------
#define _DDR2_DATA_RATE_1333M                               1333
#define _DDR2_DATA_RATE_1200M                               1200
#define _DDR2_DATA_RATE_1066M                               1066
#define _DDR2_DATA_RATE_800M                                800
#define _DDR2_DATA_RATE_667M                                667
#define _DDR2_DATA_RATE_533M                                533

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
extern void ScalerDDR2DCPHYInitial(void);
extern void ScalerDDR2DCSysInitial(void);
extern void ScalerDDR2DCSysSystemBridgeReset(void);
extern void ScalerDDR2PowerControl(bit bOn);

#if(_MEMORY_BW_CTRL_SUPPORT == _ON)
extern void ScalerDDR2SetBwCtrlEnable(EnumMemoryClientType enumClientType, BYTE ucClientIndex, bit bEnable);
extern void ScalerDDR2SetBwCtrl(EnumMemoryClientType enumClientType, BYTE ucClientIndex, StructBwCtrlClientInfo *pstClientInfo);
#endif
#endif // End of #if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)

