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
// ID Code      : UserCommonUsbTypeCInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of Port Controller Reconnect Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_USER_PORT_CTRL_RESP_FAIL = _FAIL,
    _TYPE_C_USER_PORT_CTRL_RESP_SUCCESS = _SUCCESS,
}EnumTypeCUserPortCtrlRespStatus;

//--------------------------------------------------
// Enumerations of External Port Controller Reconnect Support
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PORT_CTRL_RECONNECT_NOT_SUPPORT = _FAIL,
    _TYPE_C_PORT_CTRL_RECONNECT_SUPPORT = _SUCCESS,
}EnumTypeCPortCtrlReconnectSupport;

//--------------------------------------------------
// Enumerations of Type-C Pin Assignment E Support Status
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_ON = 0x00,
    _TYPE_C_PIN_ASSIGNMENT_E_SUPPORT_OFF = 0x01,
}EnumTypeCPinAssignmentESupportStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
extern WORD UserCommonUsbTypeCGetAvailablePower(EnumTypeCPcbPort *penumTypeCAltPowerPort);
extern EnumTypeCSpmOperation UserCommonUsbTypeCSpmOperation(void);
extern void UserCommonUsbTypeCSystemPowerManagement(void);
extern WORD UserCommonUsbTypeCGetAdaptorPower(void);
extern WORD UserCommonUsbTypeCGetPortPower(EnumTypeCPcbPort enumTypeCPcbPort);
extern WORD UserCommonUsbTypeCGetHubPower(void);
extern EnumBillboardCtrl UserCommonUsbTypeCGetBillboardSupport(EnumHubDsp enumHubDsp);
extern WORD UserCommonUsbTypeCGetPortMinPower(EnumTypeCPcbPort enumTypeCPcbPort);
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern EnumBillboardProgramCtrl UserCommonUsbTypeCBBProgramEnable(EnumTypeCPcbPort enumTypeCPcbPort);
extern void UserCommonUsbTypeCBBCustomCommand(StructUsbBillboardCustomCommandInfo *pststUsbBillboardCustomCommandInfo);
extern EnumBillboardCustomEvent UserCommonUsbTypeCBBGetCustomEvent(void);
extern void UserCommonUsbTypeCBBClrCustomEvent(EnumBillboardCustomEvent enumBillboardCustomEvent);
#endif // End of #if(_BILLBOARD_SCALER_SUPPORT == _ON)
#endif // End of #if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
#endif // End of #if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))))
extern bit UserCommonUsbTypeCPmicIICRead(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
extern BYTE UserCommonUsbTypeCPmicIICRead_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
#if((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))
extern BYTE UserCommonUsbTypeCPmicIICRead_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucReadArray);
#endif
extern bit UserCommonUsbTypeCPmicIICWrite(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
extern BYTE UserCommonUsbTypeCPmicIICWrite_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
extern BYTE UserCommonUsbTypeCPmicIICWrite_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON))
extern void UserCommonUsbTypeCPmicSetForceOffControlType(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicForceOffType enumForceOffType);
extern bit UserCommonUsbTypeCPmicSetForceOffIIC(EnumTypeCPcbPort enumTypeCPcbPort, BYTE ucSlaveAddr, WORD usSubAddr, BYTE ucSubAddrLength, WORD usLength, BYTE *pucWriteArray);
extern void UserCommonUsbTypeCPmicSetForceOffGpio(EnumTypeCPcbPort enumTypeCPcbPort, EnumPinConfigType enumPinConfig, BYTE ucPinControl);
#endif
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || ((_PORT_CTRL_TCPM_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))))

