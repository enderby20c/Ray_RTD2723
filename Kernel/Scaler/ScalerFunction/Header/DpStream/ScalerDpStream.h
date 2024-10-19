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
// ID Code      : ScalerDpStream.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_DP_STREAM_H__
#define __SCALER_DP_STREAM_H__

#if(_DP_SUPPORT == _ON)
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
extern bit ScalerDpStreamJudgePreCheck(EnumDpStreamType enumDpStreamType, EnumDpStreamInfoType enumDpStreamInfoType, EnumDpStreamDataPath enumDpStreamDataPath);
extern bit ScalerDpStreamStableCheck(EnumDpStreamType enumDpStreamType, EnumDpStreamInfoType enumDpStreamInfoType, EnumDpStreamDataPath enumDpStreamDataPath);
extern EnumDpMacStreamSourceType ScalerDpStreamTypeSourceTypeMapping(EnumDpStreamType enumDpStreamType);
extern EnumDpStreamType ScalerDpStreamSourceTypeStreamTypeMapping(EnumDpMacStreamSourceType enumDpStreamSourceType);
extern void ScalerDpStreamSetDataPathProc(EnumDpStreamType enumDpStreamType, EnumDpStreamInfoType enumDpStreamInfoType);
extern EnumDpStreamInfoType ScalerDpStreamGetInfoType(EnumDpStreamType enumDpStreamType);
extern void ScalerDpStreamSetDataPath(EnumDpStreamType enumDpStreamType, EnumDpStreamDataPath enumDataPath);
#if(_DP_TX_SUPPORT == _ON)
extern EnumDpStreamDataPath ScalerDpStreamVideoDataPathJudge(EnumDpStreamType enumDpStreamType);
extern EnumDpStreamDataPath ScalerDpStreamDscDataPathJudge(EnumDpStreamType enumDpStreamType);
extern bit ScalerDpStreamDscPassThroughJudge(EnumDpStreamType enumDpStreamType);
extern bit ScalerDpStreamDscPassThroughEnableCheck(EnumDpStreamType enumDpStreamType);
extern EnumDpStreamDataPath ScalerDpStreamDscPassThroughDataPathJudge(EnumDpStreamType enumDpStreamType);
extern EnumDpStreamDataPath ScalerDpStreamVesaPassThroughDataPathJudge(EnumDpStreamType enumDpStreamType);
extern EnumDpStreamDataPath ScalerDpStreamVesaCodingTypeDataPathJudge(EnumDpStreamType enumDpStreamType);
extern bit ScalerDpStreamVideoReorderSupportCheck(EnumDpStreamType enumDpStreamType);
extern bit ScalerDpStreamBandWidthCheck(EnumDpStreamType enumDpStreamType, EnumDpStreamDataPath enumDataPath);
#endif
extern WORD ScalerDpStreamGetRxInputPixelClk(EnumDpStreamType enumDpStreamType);

#if(_DP_RX_DSC_DECODER_SUPPORT == _ON)
extern bit ScalerDpStreamDscDecodeCheck(EnumDpStreamType enumDpStreamType);
extern WORD ScalerDpStreamGetRxDscElement(EnumDpStreamType enumDpStreamType, EnumDpStreamPpsElement enumElement);
#endif
extern bit ScalerDpStreamDataPathMaxPixelClkCheck(EnumDpStreamType enumDpStreamType);
#endif

#endif // End of #ifndef __SCALER_DP_STREAM_H__
