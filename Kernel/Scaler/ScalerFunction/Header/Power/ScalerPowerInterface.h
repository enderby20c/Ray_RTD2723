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
// ID Code      : ScalerPowerInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// HDCP Key Definition
//--------------------------------------------------
#define GET_POWER_LOAD_DPTX_HDCP_KEY_FLG()      ((bit)(g_stPowerPowerLoadData.b1LoadDptxHdcpKey))
#define SET_POWER_LOAD_DPTX_HDCP_KEY_FLG()      (g_stPowerPowerLoadData.b1LoadDptxHdcpKey = 1)
#define CLR_POWER_LOAD_DPTX_HDCP_KEY_FLG()      (g_stPowerPowerLoadData.b1LoadDptxHdcpKey = 0)


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enum of Power Cut Control
//--------------------------------------------------
typedef enum
{
    _POWER_CUT_ON = 0x00,
    _POWER_CUT_OFF,
} EnumPowerCut;

//--------------------------------------------------
// Enum of Clock Gating Control
//--------------------------------------------------
typedef enum
{
    _CLOCK_GATING_ON = 0x00,
    _CLOCK_GATING_OFF,
} EnumPowerClockGating;

//--------------------------------------------------
// Enum of Power Domain Reset Control
//--------------------------------------------------
typedef enum
{
    _POWER_RESET_ENABLE = 0x00,
    _POWER_RESET_DISABLE,
} EnumPowerReset;

//--------------------------------------------------
// Enum of Delay Control when Power ON
//--------------------------------------------------
typedef enum
{
    _POWER_ON_DELAY_NONE = 0x00,
    _POWER_ON_DELAY_1_MS,
    _POWER_ON_DELAY_2_MS,
    _POWER_ON_DELAY_3_MS,
    _POWER_ON_DELAY_4_MS,
    _POWER_ON_DELAY_5_MS,
} EnumPowerOnDelay;

//--------------------------------------------------
// Data Recover from Power Cut State
//--------------------------------------------------
typedef struct
{
    BYTE b1LoadDptxHdcpKey : 1;
} StructPowerLoadData;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructPowerLoadData g_stPowerPowerLoadData;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerPowerXtalPower(BYTE ucOn);
extern void ScalerPowerSetFakeSavingClockControl(bit bEnable);
extern bit ScalerPowerCheckFakeSavingClockControl(void);
extern void ScalerPowerIsolation(EnumPowerAction enumPowerAction);
extern void ScalerPowerRecoverIsolationAreaData(void);
extern BYTE ScalerPowerDomainEnableControl(EnumPowerGroup enumPowerGroup, EnumPowerCut enumPowerCut, EnumPowerOnDelay enumPowerOnDelay);

#if(_HW_TOP_ON_POWER_DOMAIN_GEN != _TOP_ON_POWER_DOMAIN_GEN_0)
extern void ScalerPowerTopOnPowerControl(EnumPowerCut enumPowerCut);
#endif // End of #if(_HW_TOP_ON_POWER_DOMAIN_GEN != _TOP_ON_POWER_DOMAIN_GEN_0)

#if(_HW_IMD_POWER_CUT_INDEPENDENT_SUPPORT == _ON)
extern void ScalerPowerEOtoFBPowerControl(EnumInputDataPath enumInputDataPath, bit bPowerOn);
extern void ScalerPowerFBtoEOPowerControl(EnumMDomainDisplayDataPath enumMDispPath, bit bPowerOn);
#endif

extern EnumPowerCut ScalerPowerGetIDomainS1PowerCutStatus(void);
extern void ScalerPowerLvrThresholdVoltage(void);
extern void ScalerPowerClockGatingControl(EnumPowerAction enumPowerAction);
