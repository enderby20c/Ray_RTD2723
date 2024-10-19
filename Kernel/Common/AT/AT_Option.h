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
// ID Code      : AT_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#define _AUTO_TEST_SUPPORT                                  _OFF

#if(_AUTO_TEST_SUPPORT == _ON)
extern void SysATIntProc(void);
extern void SysATHandler(void);
extern void SysATOsdMenuKeyMsgClrFlg(void);
#endif

