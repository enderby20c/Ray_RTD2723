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
// ID Code      : RTD2020Project.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//-------------------------------------------------
// Define OSD Rotate Type
//-------------------------------------------------
#define _OSD_ROTATE_FUNCTION                        _OSD_ROTATE_HARDWARE

//--------------------------------------------------
// Definitions of IR Protocal
//--------------------------------------------------
#if(_IR_SUPPORT == _IR_HW_SUPPORT)
#define _IR_NEC_DTV328                              0
#define _IR_SONY_B102P                              1
#define _IR_PHILIPS_RC6                             2

#define _IR_PROTOCAL                                _IR_NEC_DTV328
#endif // End of #if(_IR_SUPPORT == _IR_HW_SUPPORT)


