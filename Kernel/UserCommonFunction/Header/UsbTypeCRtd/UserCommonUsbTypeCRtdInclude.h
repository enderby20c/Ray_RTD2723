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
// ID Code      : UserCommonUsbTypeCRtdInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTD_SUPPORT == _ON))

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

typedef struct
{
    BYTE b1DetectStatusFlag : 1;
    EnumTypeCAttachStatus enumCcAttach;
    EnumTypeCOrientation enumOrientation;
    EnumTypeCPowerRole enumPowerRole;
    EnumTypeCDataRole enumDataRole;
    EnumTypeCAltModeStatus enumAltModeReady;
    EnumTypeCPinCfgType enumPinAssignment;
    WORD usPdoStatusVoltage;
    WORD usPdoStatusCurrent;

}StructTypeCRtdInfo;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_PORT_CTRL_RTD_DET_CC_ATTACH_BY_SMBUS == _ON)
extern EnumTypeCAttachStatus UserCommonUsbTypeCRtdGetCcAttachByI2C(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
#if(_PORT_CTRL_RTD_DET_ALT_MODE_READY_BY_SMBUS == _ON)
extern EnumTypeCAltModeStatus UserCommonUsbTypeCRtdGetAltModeReadyByI2C(EnumTypeCPcbPort enumTypeCPcbPort);
#endif
extern bit UserCommonUsbTypeCRtdSetPinAssignment(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCMultiFuncStatus enumMultiFunc, EnumTypeCPinCfgCapType enumPinAssignment);
#endif  // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))
