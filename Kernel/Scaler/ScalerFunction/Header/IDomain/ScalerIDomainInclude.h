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
// ID Code      : ScalerIDomainInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GET_VGIP_INITIAL_VDELAY()                   (g_usIDomainVgipVDelayInitial)
#define SET_VGIP_INITIAL_VDELAY(x)                  (g_usIDomainVgipVDelayInitial = (x))

#define GET_IDOMAIN_DATA_PATH(x)                    (g_pstIDomainPathInfo[x].enumInputPath)
#define GET_IDOMAIN_REG_PAGE(x)                     (g_pstIDomainPathInfo[x].ucInputPage)
#define GET_ONLINE_MEASURE_REG_PAGE(x)              (g_pstIDomainPathInfo[x].ucMeasurePage)
#define GET_IDOMAIN_IRQ_REG_OFFSET(x)               (g_pstIDomainPathInfo[x].ucIRQPage)
#define GET_OVF_UDF_OFFSET(x)                       (g_pstIDomainPathInfo[x].ucOvfUdfOffset)
#define GET_BG_CTRL_BIT(x)                          (g_pstIDomainPathInfo[x].ucBGCtrlBit)

#define GET_VGIP_DB_STATUS(x)                       (g_pstIDomainPathInfo[x].enumVGIPDBStatus)
#define GET_I_DB_STATUS(x)                          (g_pstIDomainPathInfo[x].enumIDomainDBStatus)
#define GET_I_DB_ENABLE_BIT(x)                      (g_pstIDomainPathInfo[x].ucIDomainDBEnableBit)
#define GET_I_DB_APPLY_BIT(x)                       (g_pstIDomainPathInfo[x].ucIDomainDBApplyeBit)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumInputDataPath enumInputPath;
    BYTE ucInputPage;
    BYTE ucMeasurePage;
    BYTE ucIRQPage;
    EnumVGIPDBEnableStatus enumVGIPDBStatus;
    EnumIDomainDBEnableStatus enumIDomainDBStatus;
    BYTE ucIDomainDBEnableBit;
    BYTE ucIDomainDBApplyeBit;
    BYTE ucOvfUdfOffset;
    BYTE ucBGCtrlBit;
} StructIDomainPathInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern WORD g_usIDomainVgipVDelayInitial;
extern StructIDomainPathInfo g_pstIDomainPathInfo[_HW_I_DOMAIN_PATH_COUNT];

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerIDomainVgipAdjustIHVDelay(void);
extern void ScalerIDomainFineTuneHCaptureStart(WORD usDeltaIHCapture);
extern BYTE ScalerIDomainGetInputPathCount(EnumInputDataPath enumInputDataPath);
extern BYTE ScalerIDomainGetInputPathPage(EnumInputDataPath enumInputDataPath);
extern BYTE ScalerIDomainGetInputPathPage_EXINT0(EnumInputDataPath enumInputDataPath);
extern BYTE ScalerIDomainGetInputPathPage_EXINT5(EnumInputDataPath enumInputDataPath);
extern BYTE ScalerIDomainGetIRQPageOffset(EnumInputDataPath enumInputDataPath);
extern void ScalerIDomainSettingAfterIDB(void);

