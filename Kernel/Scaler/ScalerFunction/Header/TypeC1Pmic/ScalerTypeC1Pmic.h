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
// ID Code      : ScalerTypeC1Pmic.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_TYPEC1_PMIC_H__
#define __SCALER_TYPEC1_PMIC_H__


#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of TYPEC Hardware IIC
//--------------------------------------------------
#define _TYPE_C_1_HW_IIC_BUFFER_SIZE                24
#define _TYPE_C_1_HW_IIC_READ_SIZE                  _TYPE_C_1_HW_IIC_BUFFER_SIZE
#define _TYPE_C_1_HW_IIC_WRITE_SIZE                 (_TYPE_C_1_HW_IIC_BUFFER_SIZE - 1) // Slave_Addr + 23-Data = 24-Buffer

// _TYPE_C_PMIC_HW_IIC_SPEED == 100K
#define _TYPE_C_1_HW_IIC_SLPC_14318K                0x26 // 38
#define _TYPE_C_1_HW_IIC_SHPC_14318K                0x22 // 34
#define _TYPE_C_1_HW_IIC_SLPC_27000K                0x2E // 46
#define _TYPE_C_1_HW_IIC_SHPC_27000K                0x2B // 43
#define _TYPE_C_1_HW_IIC_SLPC_28000K                0x2F // 47
#define _TYPE_C_1_HW_IIC_SHPC_28000K                0x2F // 47
#define _TYPE_C_1_HW_IIC_STA_SUGPIO_C               0x36 // 54
#define _TYPE_C_1_HW_IIC_TOR                        0x47 // 71

#define _TYPE_C_1_HW_IIC_FTPC                       0x03 // 3
#define _TYPE_C_1_HW_IIC_FD10_14318K                0x01 // 1
#define _TYPE_C_1_HW_IIC_FD10_27000K                0x02 // 2
#define _TYPE_C_1_HW_IIC_FD10_28000K                0x02 // 2

//--------------------------------------------------
// Definitions of PMIC Voltage Adjust Option
//--------------------------------------------------
#define _TYPE_C_1_PMIC_FW_UVP_PPS_THRESHOLD         295 // unit: 10mV
#define _TYPE_C_1_PMIC_SHORT_VOLTAGE                300 // unit: 10mV

//--------------------------------------------------
// Definitions of PMIC Minimum Current
//--------------------------------------------------
#define _TYPE_C_1_PMIC_MIN_CURRENT                  85 // unit: 10mA
#define _TYPE_C_1_PMIC_MIN_PPS_CURRENT              60 // unit: 10mA

//--------------------------------------------------
// Definitions of PMIC Voltage Compesation
//--------------------------------------------------
#define _TYPE_C_1_VOLTAGE_COMPESATION_CURRENT_UNIT  50 // unit: 10mA, R_comp = 0.1V / _VOLTAGE_COMPESATION_CURRENT_UNIT

//--------------------------------------------------
// Definitions of PMIC FW OCP Polling Function
//--------------------------------------------------
#define _TYPE_C_1_PMIC_HW_OCP_MAX                   (_EMB_TYPE_C_1_PMIC_FW_OCP_CURRENT_VALUE + 66) // unit: %, should multiply with PMIC setting current to get the real OCP value

//--------------------------------------------------
// Definitions of PMIC Test FUNCTION
//--------------------------------------------------
#define _TYPE_C_1_PMIC_FORCE_OUTPUT                 _OFF
#define _TYPE_C_1_PMIC_FORCE_VOLTAGE                1200 // unit: 10mV
#define _TYPE_C_1_PMIC_FORCE_CURRENT                100 // unit: 10mA

//--------------------------------------------------
// Definitions of FW WD Timer Event Time (Max: 250ms)
//--------------------------------------------------
#define _TYPE_C_1_WD_EVENT_TIME                     250 // unit: ms

//--------------------------------------------------
// Macros of PMIC IIC Set Srart
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_IIC_SET_START()           (g_stTypeC1PmicIICStatus.b1PmicIICSetStart)
#define SET_TYPE_C_1_PMIC_IIC_SET_START()           (g_stTypeC1PmicIICStatus.b1PmicIICSetStart = _TRUE)
#define CLR_TYPE_C_1_PMIC_IIC_SET_START()           (g_stTypeC1PmicIICStatus.b1PmicIICSetStart = _FALSE)

//--------------------------------------------------
// Macros of PMIC IIC Status
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP()        (g_stTypeC1PmicIICStatus.b1PmicIICMainLoop)
#define SET_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP()        (g_stTypeC1PmicIICStatus.b1PmicIICMainLoop = _TRUE)
#define CLR_TYPE_C_1_PMIC_IIC_IN_MAIN_LOOP()        (g_stTypeC1PmicIICStatus.b1PmicIICMainLoop = _FALSE)
#define GET_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP()      (g_stTypeC1PmicIICStatus.b1PmicIICExint0Loop)
#define SET_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP()      (g_stTypeC1PmicIICStatus.b1PmicIICExint0Loop = _TRUE)
#define CLR_TYPE_C_1_PMIC_IIC_IN_EXINT0_LOOP()      (g_stTypeC1PmicIICStatus.b1PmicIICExint0Loop = _FALSE)
#define GET_TYPE_C_1_PMIC_IIC_IN_WDINT_LOOP()       (g_stTypeC1PmicIICStatus.b1PmicIICWdintLoop)
#define SET_TYPE_C_1_PMIC_IIC_IN_WDINT_LOOP()       (g_stTypeC1PmicIICStatus.b1PmicIICWdintLoop = _TRUE)
#define CLR_TYPE_C_1_PMIC_IIC_IN_WDINT_LOOP()       (g_stTypeC1PmicIICStatus.b1PmicIICWdintLoop = _FALSE)
#define GET_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP() (g_stTypeC1PmicIICStatus.b1PmicIICExint0EverLoop)
#define SET_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP() (g_stTypeC1PmicIICStatus.b1PmicIICExint0EverLoop = _TRUE)
#define CLR_TYPE_C_1_PMIC_IIC_EVER_IN_EXINT0_LOOP() (g_stTypeC1PmicIICStatus.b1PmicIICExint0EverLoop = _FALSE)
#define GET_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP()  (g_stTypeC1PmicIICStatus.b1PmicIICWdintEverLoop)
#define SET_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP()  (g_stTypeC1PmicIICStatus.b1PmicIICWdintEverLoop = _TRUE)
#define CLR_TYPE_C_1_PMIC_IIC_EVER_IN_WDINT_LOOP()  (g_stTypeC1PmicIICStatus.b1PmicIICWdintEverLoop = _FALSE)

//--------------------------------------------------
// Macros of PMIC Vbus Protect Judge Debounce
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_OVP_JUDGE_DEBOUNCE()      (g_stTypeC1PmicControl.ucOvpProtectDebounce)
#define SET_TYPE_C_1_PMIC_OVP_JUDGE_DEBOUNCE(x)     (g_stTypeC1PmicControl.ucOvpProtectDebounce = (x))

#define GET_TYPE_C_1_PMIC_UVP_JUDGE_DEBOUNCE()      (g_stTypeC1PmicControl.ucUvpProtectDebounce)
#define SET_TYPE_C_1_PMIC_UVP_JUDGE_DEBOUNCE(x)     (g_stTypeC1PmicControl.ucUvpProtectDebounce = (x))

#define GET_TYPE_C_1_PMIC_OCP_JUDGE_DEBOUNCE()      (g_stTypeC1PmicControl.ucOcpProtectDebounce)
#define SET_TYPE_C_1_PMIC_OCP_JUDGE_DEBOUNCE(x)     (g_stTypeC1PmicControl.ucOcpProtectDebounce = (x))

//--------------------------------------------------
// Macros of PMIC Output Enable Flag
//--------------------------------------------------
#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
#define GET_TYPE_C_1_PMIC_OUTPUT_ENABLE()           (g_stTypeC1PmicControl.b1OutputEnable)
#define SET_TYPE_C_1_PMIC_OUTPUT_ENABLE()           (g_stTypeC1PmicControl.b1OutputEnable = _ON)
#define CLR_TYPE_C_1_PMIC_OUTPUT_ENABLE()           (g_stTypeC1PmicControl.b1OutputEnable = _OFF)

//--------------------------------------------------
// Macros of PMIC Bi-direction Flag
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_BIDIR_MODE()              (g_stTypeC1PmicControl.b1BiDirMode)
#define SET_TYPE_C_1_PMIC_BIDIR_MODE(x)             (g_stTypeC1PmicControl.b1BiDirMode = (x))

//--------------------------------------------------
// Macros of PMIC Protection Valid Flag
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_PROTECT_VALID()           (g_stTypeC1PmicControl.b1ProtectValid)
#define SET_TYPE_C_1_PMIC_PROTECT_VALID()           (g_stTypeC1PmicControl.b1ProtectValid = _TRUE)
#define CLR_TYPE_C_1_PMIC_PROTECT_VALID()           (g_stTypeC1PmicControl.b1ProtectValid = _FALSE)

//--------------------------------------------------
// Macros of PMIC Protection Timer Check Flag
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK()     (g_stTypeC1PmicControl.b1ProtectTimerCheck)
#define SET_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK()     (g_stTypeC1PmicControl.b1ProtectTimerCheck = _TRUE)
#define CLR_TYPE_C_1_PMIC_PROTECT_TIMER_CHECK()     (g_stTypeC1PmicControl.b1ProtectTimerCheck = _FALSE)

//--------------------------------------------------
// Macros of PMIC Protection Timer Start Flag
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_PROTECT_TIMER_START()     (g_stTypeC1PmicControl.b1ProtectTimerStart)
#define SET_TYPE_C_1_PMIC_PROTECT_TIMER_START()     (g_stTypeC1PmicControl.b1ProtectTimerStart = _TRUE)
#define CLR_TYPE_C_1_PMIC_PROTECT_TIMER_START()     (g_stTypeC1PmicControl.b1ProtectTimerStart = _FALSE)
#endif

//--------------------------------------------------
// Macros of PMIC OVP/UVP Check Flag
//--------------------------------------------------
#if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)
#define GET_TYPE_C_1_PMIC_FW_OVP_VOLTAGE()          (g_stTypeC1PmicControl.usOvpVoltage)
#define SET_TYPE_C_1_PMIC_FW_OVP_VOLTAGE(x)         (g_stTypeC1PmicControl.usOvpVoltage = (x))

#define GET_TYPE_C_1_PMIC_FW_UVP_VOLTAGE()          (g_stTypeC1PmicControl.usUvpVoltage)
#define SET_TYPE_C_1_PMIC_FW_UVP_VOLTAGE(x)         (g_stTypeC1PmicControl.usUvpVoltage = (x))

#define GET_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK()        (g_stTypeC1PmicControl.b1OvpUvpCheck)
#define SET_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK()        (g_stTypeC1PmicControl.b1OvpUvpCheck = _TRUE)
#define CLR_TYPE_C_1_PMIC_FW_OVP_UVP_CHECK()        (g_stTypeC1PmicControl.b1OvpUvpCheck = _FALSE)
#endif // End of #if(_EMB_TYPE_C_1_PMIC_FW_OVP_UVP_SUPPORT == _ON)

//--------------------------------------------------
// Macros of PMIC Eizo SIC437A Vbus Check Flag
//--------------------------------------------------
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#define GET_TYPE_C_1_PMIC_EIZO_VBUS_5V_CHECK()      (g_stTypeC1PmicControl.b1EizoVbus5VCheck)
#define SET_TYPE_C_1_PMIC_EIZO_VBUS_5V_CHECK()      (g_stTypeC1PmicControl.b1EizoVbus5VCheck = _TRUE)
#define CLR_TYPE_C_1_PMIC_EIZO_VBUS_5V_CHECK()      (g_stTypeC1PmicControl.b1EizoVbus5VCheck = _FALSE)

#define GET_TYPE_C_1_PMIC_EIZO_VBUS_0V_CHECK()      (g_stTypeC1PmicControl.b1EizoVbus0VCheck)
#define SET_TYPE_C_1_PMIC_EIZO_VBUS_0V_CHECK()      (g_stTypeC1PmicControl.b1EizoVbus0VCheck = _TRUE)
#define CLR_TYPE_C_1_PMIC_EIZO_VBUS_0V_CHECK()      (g_stTypeC1PmicControl.b1EizoVbus0VCheck = _FALSE)
#endif

//--------------------------------------------------
// Macros of PMIC OCP Check Flag
//--------------------------------------------------
#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
#define GET_TYPE_C_1_PMIC_FW_OCP_PROTECT_LEVEL()    (g_stTypeC1PmicControl.ucOcpLevel)
#define SET_TYPE_C_1_PMIC_FW_OCP_PROTECT_LEVEL(x)   (g_stTypeC1PmicControl.ucOcpLevel = (x))

#define GET_TYPE_C_1_PMIC_FW_OCP_CURRENT(x)         (g_stTypeC1PmicControl.pusOcpCurrent[x])
#define SET_TYPE_C_1_PMIC_FW_OCP_CURRENT(x, y)      (g_stTypeC1PmicControl.pusOcpCurrent[x] = (y))

#define GET_TYPE_C_1_PMIC_FW_OCP_DELAY(x)           (g_stTypeC1PmicControl.pusOcpDelay[x])
#define SET_TYPE_C_1_PMIC_FW_OCP_DELAY(x, y)        (g_stTypeC1PmicControl.pusOcpDelay[x] = (y))

// Timer Control Macro
#define GET_TYPE_C_1_PMIC_WD_TIMER_VALUE()          (g_stTypeC1PmicControl.usWDTimer)
#define SET_TYPE_C_1_PMIC_WD_TIMER_VALUE(x)         (g_stTypeC1PmicControl.usWDTimer = (x))
#define CLR_TYPE_C_1_PMIC_WD_TIMER_VALUE()          (g_stTypeC1PmicControl.usWDTimer = 0)

#define GET_TYPE_C_1_PMIC_PEAK_CURRENT_TYPE()       (g_stTypeC1PmicControl.enumTypeCPDPeakCurType)
#define SET_TYPE_C_1_PMIC_PEAK_CURRENT_TYPE(x)      (g_stTypeC1PmicControl.enumTypeCPDPeakCurType = (x))

#define GET_TYPE_C_1_PMIC_PEAK_CURRENT_PROTECT()    (g_stTypeC1PmicControl.enumTypeCPDPeakCurProtect)
#define SET_TYPE_C_1_PMIC_PEAK_CURRENT_PROTECT(x)   (g_stTypeC1PmicControl.enumTypeCPDPeakCurProtect = (x))

#define GET_TYPE_C_1_PMIC_SHORT_VOLTAGE()           ((WORD)(g_stTypeC1PmicControl.b12ShortVoltage))
#define SET_TYPE_C_1_PMIC_SHORT_VOLTAGE(x)          (g_stTypeC1PmicControl.b12ShortVoltage = (x))

#if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
#define GET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE()    (g_stTypeC1PmicControl.b12SafetyCurrent)
#define SET_TYPE_C_1_PMIC_SAFETY_CURRENT_VALUE(x)   (g_stTypeC1PmicControl.b12SafetyCurrent = (x))

#define GET_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER()  (g_stTypeC1PmicControl.b1SafetyProtectFlag)
#define SET_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER()  (g_stTypeC1PmicControl.b1SafetyProtectFlag = _TRUE)
#define CLR_TYPE_C_1_PMIC_SAFETY_PROTECT_TRIGGER()  (g_stTypeC1PmicControl.b1SafetyProtectFlag = _FALSE)
#endif

#elif(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
#define GET_TYPE_C_1_PMIC_OCP_CURRENT_VALUE()       (g_stTypeC1PmicControl.b12OcpByPollingCurrent)
#define SET_TYPE_C_1_PMIC_OCP_CURRENT_VALUE(x)      (g_stTypeC1PmicControl.b12OcpByPollingCurrent = (x))

#define GET_TYPE_C_1_PMIC_OCP_PROTECT_TRIGGER()     (g_stTypeC1PmicControl.b1PollingOcpProtectFlag)
#define SET_TYPE_C_1_PMIC_OCP_PROTECT_TRIGGER()     (g_stTypeC1PmicControl.b1PollingOcpProtectFlag = _TRUE)
#define CLR_TYPE_C_1_PMIC_OCP_PROTECT_TRIGGER()     (g_stTypeC1PmicControl.b1PollingOcpProtectFlag = _FALSE)
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

//--------------------------------------------------
// Macros of PMIC Check Operating Status
//--------------------------------------------------
#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
#define GET_TYPE_C_1_PMIC_GET_OMF_INFO_START()      (g_stTypeC1PmicControl.b1GetOmfInfoFlag)
#define SET_TYPE_C_1_PMIC_GET_OMF_INFO_START()      (g_stTypeC1PmicControl.b1GetOmfInfoFlag = _TRUE)
#define CLR_TYPE_C_1_PMIC_GET_OMF_INFO_START()      (g_stTypeC1PmicControl.b1GetOmfInfoFlag = _FALSE)

#define GET_TYPE_C_1_PMIC_OMF_INFO()                (g_stTypeC1PmicControl.enumOmfInfo)
#define SET_TYPE_C_1_PMIC_OMF_INFO(x)               (g_stTypeC1PmicControl.enumOmfInfo = (x))
#endif

//--------------------------------------------------
// Macros of PMIC Output Mode Flag
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_OUTPUT_MODE_STATUS()      (g_stTypeC1PmicControl.enumOutputPdoType)
#define SET_TYPE_C_1_PMIC_OUTPUT_MODE_STATUS(x)     (g_stTypeC1PmicControl.enumOutputPdoType = (x))

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
//--------------------------------------------------
// Macros of PMIC Force Off Control Type
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_FORCE_OFF_TYPE()          (g_stTypeC1PmicControl.enumForceOffType)
#define SET_TYPE_C_1_PMIC_FORCE_OFF_TYPE(x)         (g_stTypeC1PmicControl.enumForceOffType = (x))

//--------------------------------------------------
// Macros of PMIC Force Off Gpio Pin Config
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_FORCE_OFF_PIN_CONFIG()    (g_stTypeC1PmicControl.enumPinConfig)
#define SET_TYPE_C_1_PMIC_FORCE_OFF_PIN_CONFIG(x)   (g_stTypeC1PmicControl.enumPinConfig = (x))

//--------------------------------------------------
// Macros of PMIC Force Off Gpio Pin Control
//--------------------------------------------------
#define GET_TYPE_C_1_PMIC_FORCE_OFF_PIN_CONTROL()   (g_stTypeC1PmicControl.b1PinControl)
#define SET_TYPE_C_1_PMIC_FORCE_OFF_PIN_CONTROL(x)  (g_stTypeC1PmicControl.b1PinControl = (x))
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_EMB_TYPE_C_1_PMIC_IIC != _PMIC_NO_IIC_PIN)
extern void ScalerTypeC1PmicHwIICInitial(void);
extern bit ScalerTypeC1PmicHwIICRead(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
extern BYTE ScalerTypeC1PmicHwIICRead_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucReadArray);
extern bit ScalerTypeC1PmicHwIICWrite(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
extern BYTE ScalerTypeC1PmicHwIICWrite_EXINT0(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
extern BYTE ScalerTypeC1PmicHwIICWrite_WDINT(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
extern bit ScalerTypeC1PmicHwIICSetFrsData(BYTE ucSlaveAddr, BYTE ucSubAddrLength, WORD usSubAddr, BYTE ucDataLength, BYTE *pucWriteArray);
extern bit ScalerTypeC1PmicHwIICSetStartCheck(void);
extern BYTE ScalerTypeC1PmicHwIICSetStartCheck_EXINT0(void);
extern BYTE ScalerTypeC1PmicHwIICSetStartCheck_WDINT(void);
extern void ScalerTypeC1PmicIICReset(void);
extern void ScalerTypeC1PmicIICReset_EXINT0(void);
#endif

extern bit ScalerTypeC1PmicSwitchControl(bit bEn, bit bPowerDirection);
extern BYTE ScalerTypeC1PmicSwitchControl_EXINT0(bit bEn, bit bPowerDirection);
extern BYTE ScalerTypeC1PmicSwitchControl_WDINT(bit bEn, bit bPowerDirection);

#if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)
extern bit ScalerTypeC1PmicProtectTracking(void);
#if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))
#if(_EMB_TYPE_C_1_PMIC_SAFETY_PROTECT_SUPPORT == _ON)
extern BYTE ScalerTypeC1PmicTrackingSafetyProtect(void);
extern void ScalerTypeC1PmicSafetyProtect(void);
#endif

#elif(_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_POLLING_PMIC)
extern BYTE ScalerTypeC1PmicTrackingPollingOcp(EnumTypeCPcbPort enumTypeCPcbPort);
extern void ScalerTypeC1PmicPollingOcpProtect(void);
#endif // End of #if((_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_LOW_SPEED_ADC) || (_EMB_TYPE_C_1_PMIC_FW_OCP_PROTECT_METHOD == _TYPE_C_PMIC_FW_OCP_BY_10_BIT_ADC))

#if(_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON)
extern BYTE ScalerTypeC1PmicTrackingVoltageCompensation(EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if(_EMB_TYPE_C_1_PMIC_VOLTAGE_COMPENSATION == _ON)

#if(_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
extern BYTE ScalerTypeC1PmicTrackingIntPin(EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if(_EMB_TYPE_C_1_PMIC_INT_PIN_CHECK_METHOD == _TYPE_C_PMIC_INT_PIN_CHECK_BY_POLLING)
#endif // End of #if(_EMB_TYPE_C_1_PMIC_CHECK_SUPPORT == _ON)

#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
extern BYTE ScalerTypeC1PmicSic437aPmicOcpProc(void);
extern BYTE ScalerTypeC1PmicSic437aPmicOcpProc_EXINT0(void);
extern BYTE ScalerTypeC1PmicSic437aPmicOcpProc_WDINT(void);
extern BYTE ScalerTypeC1PmicSic437aPmicOvpProc_EXINT0(void);
extern void ScalerTypeC1PmicSic437aVbusCheckProc(EnumTypeCVbusCheckType enumVbusCheckType);
extern void ScalerTypeC1PmicSic437aVbusCheckProc_WDINT(EnumTypeCVbusCheckType enumVbusCheckType);
#endif // End of #if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_EMB_TYPE_C_1_PMIC_TYPE != _PMIC_NONE))


#endif // End of #ifndef __SCALER_TYPEC1_PMIC_H__
