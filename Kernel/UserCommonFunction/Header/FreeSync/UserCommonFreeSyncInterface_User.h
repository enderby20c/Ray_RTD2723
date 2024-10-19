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
// ID Code      : UserCommonFreeSyncInterface_User.h No.0000
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
#if(_FREESYNC_SUPPORT == _ON)
extern void UserCommonFreeSyncSupportSwitch(void);
extern void UserCommonFreeSyncSetInputPortSupport(EnumInputPort enumInputPort, EnumFreeSyncSupport enumSupport);
extern DWORD UserCommonFreeSyncGetInfo(EnumInputPort enumInputPort, EnumAmdSpdInfoContent enumContent);
#endif

#if(_FREESYNC_OD_MEASURE == _ON)
extern void UserCommonFreeSyncODSetBackgroundGrayLevel(void);
extern void UserCommonFreeSyncODSetDisplayFormat(WORD usDHtotal, DWORD ulDclk, WORD usTarFreq);
#endif

