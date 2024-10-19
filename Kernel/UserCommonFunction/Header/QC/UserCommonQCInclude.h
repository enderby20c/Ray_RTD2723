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
// ID Code      : UserCommonQCInclude.h No.0000
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
#if(_FACTORY_RTD_QC_SUPPORT == _ON)
extern BYTE UserCommonQCGetEnableStatus(void);
extern BYTE UserCommonQCNVRamGetData(EnumSystemDataItemDataType enumDataType, BYTE ucRawValue);
extern EnumDisplayRegion UserCommonQCSourceGetAutoSearchTarget(void);
extern EnumInputPort UserCommonQCSourceGetInputPort0(void);
extern EnumDpVersionType UserCommonQCDpGetVersion(EnumInputPort enumInputPort);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern EnumInputPort UserCommonQCSourceGetInputPort1(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
extern EnumInputPort UserCommonQCSourceGetInputPort2(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
extern EnumInputPort UserCommonQCSourceGetInputPort3(void);
#endif
#endif

