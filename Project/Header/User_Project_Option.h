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
// ID Code      : User_Project_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// Definitions by Project
//****************************************************************************
//--------------------------------------------------
//  User OSD Architecture Version Option
//--------------------------------------------------
#ifndef _USER_OSD_ARCHITECTURE_VERSION
#define _USER_OSD_ARCHITECTURE_VERSION                          _USER_OSD_GEN_2
#endif


//--------------------------------------------------
// Definitions to Switch EDID/Capability String to Dell Spec (DDM Tool)
//--------------------------------------------------
#define _USER_SWITCH_TO_DELL_EDID_CAP_STRING                    _OFF

#if(_USER_SWITCH_TO_DELL_EDID_CAP_STRING == _ON)
#undef _CAPABILITIES_STRING_VGA
#undef _CAPABILITIES_STRING_HDMI
#undef _CAPABILITIES_STRING_DP

#define _CAPABILITIES_STRING_VGA                                "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 0E 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 1E 1F 20 30 3E 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_HDMI                               "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#define _CAPABILITIES_STRING_DP                                 "(prot(monitor)type(LCD)model(RTK)cmds(01 02 03 07 0C E3 F3)vcp(02 04 05 06 08 0B 0C 10 12 14(01 02 04 05 06 08 0B) 16 18 1A 52 60(01 03 04 0F 10 11 12) 87 AC AE B2 B6 C6 C8 CA CC(01 02 03 04 06 0A 0D) D6(01 04 05) DF F1 FD FF)mswhql(1)asset_eep(40)mccs_ver(2.2))"
#endif


//--------------------------------------------------
//  User GOSD resource setting
//--------------------------------------------------
#define _USER_EMBEDDED_GOSD_RESOURCE_FILE_SUPPORT               (_EMBEDDED_RESOURCE_FILE_SUPPORT == _ON)
