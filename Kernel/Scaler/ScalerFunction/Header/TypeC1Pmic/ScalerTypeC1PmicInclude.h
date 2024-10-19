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
// ID Code      : ScalerTypeC1PmicInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE ucOvpProtectDebounce;
    BYTE ucUvpProtectDebounce;
    BYTE ucOcpProtectDebounce;

#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
    WORD usOvpVoltage; // Unit: 10-Bit Code
    WORD usUvpVoltage; // Unit: 10-Bit Code
    WORD b1OvpUvpCheck : 1;
#endif // End of #if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
    WORD b1EizoVbus5VCheck : 1;
    WORD b1EizoVbus0VCheck : 1;
#endif

#if(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD != _TYPE_C_PMIC_FW_OCP_NONE)

#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
    EnumTypeCPDPeakCurType enumTypeCPDPeakCurType;
    EnumTypeCPDPeakCurProtect enumTypeCPDPeakCurProtect;
    BYTE ucOcpLevel;
    WORD pusOcpCurrent[4]; // Unit: 10-Bit Code
    WORD pusOcpDelay[4]; // Unit: ms
    WORD usWDTimer;

    WORD b12ShortVoltage : 12;

#if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
    WORD b12SafetyCurrent : 12;
    WORD b1SafetyProtectFlag : 1;
#endif
#endif

#if(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
    WORD b12OcpByPollingCurrent : 12;
    WORD b1PollingOcpProtectFlag : 1;
#endif
#endif

    // -----------------------------
#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
    WORD b1OutputEnable : 1;
    WORD b1BiDirMode : 1;
    WORD b1ProtectValid : 1;
    WORD b1ProtectTimerCheck : 1;
    WORD b1ProtectTimerStart : 1;
#endif

    // -----------------------------
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
    WORD b1GetOmfInfoFlag : 1;
    EnumTypeCPmicOperationMode enumOmfInfo;
#endif

    // -----------------------------
    EnumTypeCPDPdoType enumOutputPdoType;

    // -----------------------------
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
    EnumTypeCPmicForceOffType enumForceOffType;
    EnumPinConfigType enumPinConfig;
    BYTE b1PinControl : 1;
#endif
}StructTypeC1PmicControl;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructPmicIICStatus g_stTypeC1PmicIICStatus;
extern volatile StructTypeC1PmicControl g_stTypeC1PmicControl;


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)
extern void ScalerTypeC1PmicHwIICSetFreqDiv(EnumClkSel enumClock);
#endif
extern void ScalerTypeC1PmicInitial(void);
extern void ScalerTypeC1PmicReset(void);
extern void ScalerTypeC1PmicReset_EXINT0(void);
extern void ScalerTypeC1PmicHandler(void);
extern void ScalerTypeC1PmicTimerEventProc(EnumScalerTimerEventID enumEventID);
extern bit ScalerTypeC1PmicSetting(bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern BYTE ScalerTypeC1PmicSetting_EXINT0(bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern BYTE ScalerTypeC1PmicSetting_WDINT(bit bAction, bit bPowerDirection, EnumTypeCPDPdoType enumPdoType, WORD usVoltage, WORD usCurrent, EnumTypeCPDPeakCurType enumPeakCurrent);
extern bit ScalerTypeC1PmicVbusDischarge(bit bEn);
extern BYTE ScalerTypeC1PmicVbusDischarge_EXINT0(bit bEn);
extern BYTE ScalerTypeC1PmicVbusDischarge_WDINT(bit bEn);

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
extern EnumTypeCPmicOperationMode  ScalerTypeC1PmicReadPpsOperationModeStatus_EXINT0(void);
#endif

extern void ScalerTypeC1PmicSetVbusProtectInfo(StructTypeCVbusProtectInfo stTypeCVbusProtectInfo);

#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
extern void ScalerTypeC1PmicProtectStart(EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeC1PmicProtectStart_EXINT0(EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeC1PmicProtectStart_WDINT(EnumTypeCPowerRole enumPowerRole);
#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
extern void ScalerTypeC1PmicOcpIntHandler_EXINT0(void);
extern void ScalerTypeC1PmicWDTimerEventProc_WDINT(EnumScalerWDTimerEventID enumEventID, BYTE *pucActiveWDID, BYTE *pucActiveWDTime);
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
extern void ScalerTypeC1PmicOvpUvpIntHandler_EXINT0(void);
extern bit ScalerTypeC1PmicGetFwOvpUvpCheckFlag_EXINT0(void);
#endif
#endif // End of #if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
extern EnumTypeCPmicForceOffType ScalerTypeC1PmicGetForceOffControlType(void);
extern EnumPinConfigType ScalerTypeC1PmicGetForceOffGpioPinConfig(void);
extern BYTE ScalerTypeC1PmicGetForceOffGpioPinControl(void);
#endif

/////////////////////////////////////
// EIZO PMIC SIC437A CUSTOMIZED FW //
/////////////////////////////////////
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
extern BYTE ScalerTypeC1PmicSic437aAttachProc_EXINT0(EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeC1PmicSic437aUnattachProc(EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeC1PmicSic437aUnattachProc_EXINT0(EnumTypeCPowerRole enumPowerRole);
extern BYTE ScalerTypeC1PmicSic437aTransitionStartProc_EXINT0(WORD usVoltage, WORD usCurrent, WORD *pusSrcAdjustPowerTime);
extern BYTE ScalerTypeC1PmicSic437aTransitionReadyProc_WDINT(void);
extern BYTE ScalerTypeC1PmicSic437aPRSwapStartProc_EXINT0(EnumTypeCPowerRole enumPowerRole);
extern BYTE ScalerTypeC1PmicSic437aPRSwapToSrcProc_WDINT(void);
extern void ScalerTypeC1PmicSic437aHardRstStartProc(EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeC1PmicSic437aHardRstStartProc_EXINT0(EnumTypeCPowerRole enumPowerRole);
extern void ScalerTypeC1PmicSic437aHardRstStartProc_WDINT(EnumTypeCPowerRole enumPowerRole);
extern BYTE ScalerTypeC1PmicSic437aHardRstVbusOffProc(void);
extern bit ScalerTypeC1PmicSic437aGetVbus5VCheckFlag_EXINT0(void);
extern void ScalerTypeC1PmicSic437aClrVbus5VCheckFlag_EXINT0(void);
extern bit ScalerTypeC1PmicSic437aGetVbus0VCheckFlag_EXINT0(void);
extern void ScalerTypeC1PmicSic437aClrVbus0VCheckFlag_EXINT0(void);
extern void ScalerTypeC1PmicSic437aVbusCheckProc_EXINT0(EnumTypeCVbusCheckType enumVbusCheckType);
extern EnumTypeCVbusCheckType ScalerTypeC1PmicSic437aVbus5VReadyProc_EXINT0(EnumTypeCPowerRole enumPowerRole);
extern BYTE ScalerTypeC1PmicSic437aVbus0VReadyProc_EXINT0(EnumTypeCPowerRole enumPowerRole);
#endif // End of #if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))

