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
// ID Code      : UserCommonColorMRCMInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_COLOR_IP_MRCM == _ON)

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_MRCM_READY_SET()           (g_enumColorMRCMDataReadySet)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern bit g_bColorMRCMReadResultDone;
extern EnumMRCMSet g_enumColorMRCMDataReadySet;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void UserCommonColorMRCMAdjust(void);
extern void UserCommonColorMRCMGetData(StructMRCMSetting *pstMRCMSetting);
extern QWORD UserCommonColorMRCMReadResult(EnumMRCMReadResultOption enumMRCMReadResultOption);
extern void UserCommonColorMRCMRegionSelect(BYTE ucMRCMRegion);
#endif // End of #if(_COLOR_IP_MRCM == _ON)
