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
// ID Code      : UserCommonCecInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_HDMI_CEC_SUPPORT == _ON)
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
extern void UserCommonCecReceiveNotify(void);
extern void UserCommonCecTransmitInfoPrepare(void);

#if(_AUDIO_ARC_SUPPORT == _ON)
extern bit UserCommonCecGetOsdCecEnable(void);
#endif // End of #if(_AUDIO_ARC_SUPPORT == _ON)

#if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
extern void UserCommonCecHalAcOnInitial(void);
extern void UserCommonCecHalSetPhysicalAddressRetryTimeout(void);
extern void UserCommonCecHalSetWaitForAudioDescriptorReplyTimeout(void);
#endif // End of #if(_HDMI_CEC_KERNEL_HAL_SUPPORT == _ON)
#endif // End of #if(_HDMI_CEC_SUPPORT == _ON)