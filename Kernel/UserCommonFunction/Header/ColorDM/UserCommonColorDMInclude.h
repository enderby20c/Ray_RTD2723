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
// ID Code      : UserCommonColorDMInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DM_FUNCTION == _ON)
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
extern void UserCommonColorDMMuteProc(EnumDisplayRegion enumDisplayRegion, bit bEn);
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern void UserCommonColorDMActiveProc(EnumDisplayRegion enumDisplayRegion, EnumDMCheckPoint enumDMCheckPoint);
extern void UserCommonColorDMClearMetadata(EnumRegionIndex enumRegionIndex);
extern void UserCommonColorDMInitialSetting(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorDMResetProc(void);
extern bit UserCommonColorDMGetBypassHDRProcStatus(EnumDisplayRegion enumDisplayRegion);
extern void UserCommonColorDMRestoreSetting(EnumDisplayRegion enumDisplayRegion, EnumSelRegion enumSelRegion, EnumInputPort enumInputPort, bit bColorFormatConvert);
#endif
#endif
