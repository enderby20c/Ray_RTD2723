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
// ID Code      : ScalerGlobal.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_GLOBAL_H__
#define __SCALER_GLOBAL_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Macro for functions which use Global Interrupts
//--------------------------------------------------
#if(_DM_FUNCTION == _ON)
#define SET_GLOBAL_INT_DM(x, y)                             (g_pstGlobalIntFuncForIDomain[x].b1DM = (y))
#define GET_GLOBAL_INT_DM(x)                                (g_pstGlobalIntFuncForIDomain[x].b1DM)
#endif

#if((_OD_FUNCTION == _ON) && (_FRC_SUPPORT == _ON))
#define SET_GLOBAL_INT_DYNAMIC_OD(x)                        (g_stGlobalIntFuncForDDomain.b1DynamicOD = (x))
#define GET_GLOBAL_INT_DYNAMIC_OD()                         (g_stGlobalIntFuncForDDomain.b1DynamicOD)
#endif

#if((_MOTION_BLUR_REDUCTION_LCD_SUPPORT == _ON) && (_DRR_MOTION_BLUR_REDUCTION_SUPPORT == _ON))
#define SET_GLOBAL_INT_DRR_MBR_DVS(x)                       (g_stGlobalIntFuncForDDomain.b1DrrMbrDVS = (x))
#define GET_GLOBAL_INT_DRR_MBR_DVS()                        (g_stGlobalIntFuncForDDomain.b1DrrMbrDVS)
#endif

#if(_COLOR_IP_LOCAL_CONTRAST_HISTOGRAM == _ON)
#define SET_GLOBAL_INT_LOCAL_CONTRAST(x)                    (g_stGlobalIntFuncForDDomain.b1LocalContrast = (x))
#define GET_GLOBAL_INT_LOCAL_CONTRAST()                     (g_stGlobalIntFuncForDDomain.b1LocalContrast)
#endif

#define _I_DOMAIN_DB_EN_MASK                                (((_HW_I_DOMAIN_M1_PATH_SUPPORT == _ON) ? _BIT0 : 0x00) |\
                                                            ((_HW_I_DOMAIN_M2_PATH_SUPPORT == _ON) ? _BIT1 : 0x00) |\
                                                            ((_HW_I_DOMAIN_S1_PATH_SUPPORT == _ON) ? _BIT2 : 0x00) |\
                                                            ((_HW_I_DOMAIN_S2_PATH_SUPPORT == _ON) ? _BIT3 : 0x00) |\
                                                            ((_HW_I_DOMAIN_S3_PATH_SUPPORT == _ON) ? _BIT4 : 0x00) |\
                                                            ((_HW_I_DOMAIN_S4_PATH_SUPPORT == _ON) ? _BIT5 : 0x00))

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerGlobalAddPortMapping(EnumInputPort enumInputPort, EnumDDomainRegion enumDDomainRegion);
extern void ScalerGlobalResetPortMapping(void);

#if(_HW_GLOBAL_WD_MAPPING_SUPPORT == _ON)
extern void ScalerGlobalSetWatchDogMapping(EnumDisplayMode enumDisplayMode);
#endif

#if(_HW_FORMAT_CONVERSION_FB_SUPPORT == _ON)
extern void ScalerGlobalSetDBSyncMode(void);
#endif

extern DWORD ScalerGlobalComputeDwordPowDiv(DWORD ulA, BYTE ucPow, DWORD ulB);

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_I)
extern void ScalerGlobalDoubleBufferEnable_Gen1(EnumInputDataPath enumSelectedDataPath, bit bEn);
extern void ScalerGlobalIDDomainDBSetTriggerEvent_Gen1(EnumInputDataPath enumSelectedDataPath, EnumDBIDomainTriggerEvent enumTriggerEvent);
extern void ScalerGlobalDDomainDBApply_Gen1(EnumDBApply enumDBApply);
extern void ScalerGlobalIDomainDBApply_Gen1(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply);
extern EnumDBEnableStatus ScalerGlobalGetDBStatus_Gen1(EnumInputDataPath enumInputDataPath);
extern void ScalerGlobalIDDomainDBApply_Gen1(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply);
extern void ScalerGlobalWaitDDomainDBApplyFinish_Gen1(void);
#endif

#if(_HW_GLOBAL_DB_TYPE == _GLOBAL_DB_GEN_IV)
extern void ScalerGlobalDoubleBufferEnable_Gen4(EnumInputDataPath enumSelectedDataPath, bit bEn);
extern void ScalerGlobalDDomainDBApply_Gen4(EnumDDomainDBApplyRegion enumDDomainDBApplyRegion, EnumDBApply enumDBApply);
extern void ScalerGlobalIDomainDBApply_Gen4(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply);
extern EnumDBEnableStatus ScalerGlobalGetDBStatus_Gen4(EnumInputDataPath enumInputDataPath);
extern void ScalerGlobalIDDomainDBApply_Gen4(EnumInputDataPath enumSelectedDataPath, EnumDBApply enumDBApply);
extern void ScalerGlobalWaitDDomainDBApplyFinish_Gen4(void);
extern void ScalerGlobalDoubleBufferSwitchtoIMDDB(void);
extern void ScalerGlobalDoubleBufferConfigReset(void);
extern void ScalerGlobalIMDDBApply(EnumInputDataPath enumInputDataPath, EnumDBApply enumDBApply, bit bCheckPath);
extern bit ScalerGlobalPollingVGIPDBHappen(EnumInputDataPath enumInputDataPath);
extern void ScalerGlobalIMDDBEnable(bit bEnable);
extern bit ScalerGlobalGetIMDDBStatus(void);
#endif

extern void ScalerGlobalALLPathWatchDogDisable(EnumInputDataPath enumInputDataPath);

#if(_DISPLAY_PREVENT_GARBAGE_METHOD == _GARBAGE_PREVENT_BY_WATCH_DOG)
extern bit ScalerGlobalGetDvsTimoutWDStatus(EnumInputDataPath enumVgipPath);
#endif

#if(_GLOBAL_INTERRUPT_FUNCTION_FOR_IDOMAIN == _ON)
extern void ScalerGlobalSetInterruptForIDomainEvent(EnumIRQ enumIRQType, BYTE ucIRQPageOffset, bit bEn);
#if(_DM_FUNCTION == _ON)
extern void ScalerGlobalSetDM(EnumInputDataPath enumInputDataPath, bit bEn);
extern bit ScalerGlobalGetDM(EnumInputDataPath enumInputDataPath);
#endif
#endif


#endif // End of #ifndef __SCALER_GLOBAL_H__
