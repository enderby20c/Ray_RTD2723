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
// ID Code      : ScalerDMInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#if(_DM_FUNCTION == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _DM_FUNCTION_BYPASS_HW_APPLY                             _OFF

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile Struct3rdPartyDMDRM g_stDMDRMFormat;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
// ScalerDM.c
extern EnumDDomainRegion ScalerDMGetDDomainRegionMuteStatus(void);

#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern bit ScalerDMGetMetadataSupport(EnumInputPort enumInputPort);
extern void ScalerDMB05DoubleBufferApply(EnumInputDataPath enumSelectedDataPath);
#endif

// ScalerDM_EXINT0.c
#if(_IS_MAIN_PROCESS_CPU == _TRUE)
extern void ScalerDMIDenStartHandler_EXINT0(EnumInputDataPath enumInputPath);
extern void ScalerDMGetDRAMData_EXINT0(EnumInputPort enumInputPort, EnumRegionIndex enumRegionIndex);
extern void ScalerDMMetadataSourceMapping_EXINT0(BYTE *pucDMMetaData, EnumDMReceivedType enumDMReceivedType, EnumInputPort enumInputPort);
extern void ScalerDMMetadataHandler_EXINT0(BYTE *pucDMMetaData, EnumDMReceivedType enumDMReceivedType, EnumRegionIndex enumRegionIndex, EnumInputPort enumInputPort);
extern void ScalerDMDRAMHandler_EXINT0(EnumInputPort enumInputPort, EnumRegionIndex enumRegionIndex);
extern void ScalerDMCheckMetadata_EXINT0(EnumRegionIndex enumRegionIndex);
extern EnumRegionIndex ScalerDMGetIndexFromInputDataPath_EXINT0(EnumInputDataPath enumInputDataPath);
extern bit ScalerDMJudgeDRAMMetadata(BYTE *pucSdpInfoData);
extern EnumDMReceivedType ScalerDMConvertInfoData(EnumInputPort enumInputPort, BYTE *pucSdpInfoData, BYTE *pucDMInfoData);
extern void ScalerDMPacketReCheck_EXINT0(EnumInputPort enumInputPort);
#endif
#endif
