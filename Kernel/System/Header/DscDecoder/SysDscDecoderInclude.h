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
// ID Code      : SysDscDecoderInclude.h No.0000
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
#if(_DSC_DECODER_SUPPORT == _ON)
extern void SysDscDecoderMacArbiterInitial(void);
extern void SysDscDecoderMacArbiter(EnumInputPort enumInputPort, EnumPortType enumPortType, EnumDscDecoderMacApplyType enumDscDecoderMacApplyType);
extern void SysDscDecoderMacArbiterDxPort(EnumInputPort enumInputPort, EnumPortType enumPortType);
extern BYTE SysDscDecoderGetUnusedDscDecoderMac(void);

#if(_BACKGROUND_DETECTION_DSC_DECODER_SUPPORT == _ON)
extern void SysDscDecoderDxSupportJudge(EnumInputPort enumInputPort, EnumPortType enumPortType);
#endif
#endif
