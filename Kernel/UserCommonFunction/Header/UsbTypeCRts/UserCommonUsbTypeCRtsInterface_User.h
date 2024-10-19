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
// ID Code      : UserCommonUsbTypeCRtsInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_RTS_SMBUS_MODE == _PORT_CTRL_RTS_INT_MODE)
//--------------------------------------------------
// Enumerations of RTS Port Controller Notification Enable Byte 0
//--------------------------------------------------
typedef enum
{
    _TYPE_C_RTS_NOTIFY_EN_B0_NONE = 0x00,
    _TYPE_C_RTS_NOTIFY_EN_B0_RSV_BIT0 = _BIT0,
    _TYPE_C_RTS_NOTIFY_EN_B0_EXTAL_SUPPLY_CHG = _BIT1,
    _TYPE_C_RTS_NOTIFY_EN_B0_PWR_OP_MODE_CHG = _BIT2,
    _TYPE_C_RTS_NOTIFY_EN_B0_RSV_BIT3 = _BIT3,
    _TYPE_C_RTS_NOTIFY_EN_B0_RSV_BIT4 = _BIT4,
    _TYPE_C_RTS_NOTIFY_EN_B0_PROVIDER_CAP_CHG = _BIT5,
    _TYPE_C_RTS_NOTIFY_EN_B0_NEGOTIATE_PWR_LV_CHG = _BIT6,
    _TYPE_C_RTS_NOTIFY_EN_B0_PD_RST_COMPLETE = _BIT7,
    _TYPE_C_RTS_NOTIFY_EN_B0_ALL = 0xFF,
}EnumUsbTypeCRtsNotifyEnByte0;

//--------------------------------------------------
// Enumerations of RTS Port Controller Notification Enable Byte 1
//--------------------------------------------------
typedef enum
{
    _TYPE_C_RTS_NOTIFY_EN_B1_NONE = 0x00,
    _TYPE_C_RTS_NOTIFY_EN_B1_SUPPORT_CAM_CHG = _BIT0,
    _TYPE_C_RTS_NOTIFY_EN_B1_BAT_CHARGE_STATUS_CHG = _BIT1,
    _TYPE_C_RTS_NOTIFY_EN_B1_RSV_BIT10 = _BIT2,
    _TYPE_C_RTS_NOTIFY_EN_B1_PORT_PARTNER_CHG = _BIT3,
    _TYPE_C_RTS_NOTIFY_EN_B1_PWR_DIRECTION_CHG = _BIT4,
    _TYPE_C_RTS_NOTIFY_EN_B1_RSV_BIT13 = _BIT5,
    _TYPE_C_RTS_NOTIFY_EN_B1_CONNECT_CHG = _BIT6,
    _TYPE_C_RTS_NOTIFY_EN_B1_RSV_BIT15 = _BIT7,
    _TYPE_C_RTS_NOTIFY_EN_B1_ALL = 0xFF,
}EnumUsbTypeCRtsNotifyEnByte1;

//--------------------------------------------------
// Enumerations of RTS Port Controller Notification Enable Byte 2
//--------------------------------------------------
typedef enum
{
    _TYPE_C_RTS_NOTIFY_EN_B2_NONE = 0x00,
    _TYPE_C_RTS_NOTIFY_EN_B2_RSV_BIT16 = _BIT0,
    _TYPE_C_RTS_NOTIFY_EN_B2_RSV_BIT17 = _BIT1,
    _TYPE_C_RTS_NOTIFY_EN_B2_RSV_BIT18 = _BIT2,
    _TYPE_C_RTS_NOTIFY_EN_B2_RSV_BIT19 = _BIT3,
    _TYPE_C_RTS_NOTIFY_EN_B2_ALT_FLOW_CHG = _BIT4,
    _TYPE_C_RTS_NOTIFY_EN_B2_DP_STATUS_CHG = _BIT5,
    _TYPE_C_RTS_NOTIFY_EN_B2_DFP_OCP_STATUS = _BIT6,
    _TYPE_C_RTS_NOTIFY_EN_B2_PORT_OP_MODE_CHG = _BIT7,
    _TYPE_C_RTS_NOTIFY_EN_B2_ALL = 0xFF,
}EnumUsbTypeCRtsNotifyEnByte2;

//--------------------------------------------------
// Enumerations of RTS Port Controller Notification Enable Byte 3
//--------------------------------------------------
typedef enum
{
    _TYPE_C_RTS_NOTIFY_EN_B3_NONE = 0x00,
    _TYPE_C_RTS_NOTIFY_EN_B3_PWR_CTRL_REQ = _BIT0,
    _TYPE_C_RTS_NOTIFY_EN_B3_VDM_RECEIVED = _BIT1,
    _TYPE_C_RTS_NOTIFY_EN_B3_PDFW_START = _BIT2,
    _TYPE_C_RTS_NOTIFY_EN_B3_DATA_MSG_RECEIVED = _BIT3,
    _TYPE_C_RTS_NOTIFY_EN_B3_RSV_BIT28 = _BIT4,
    _TYPE_C_RTS_NOTIFY_EN_B3_RSV_BIT29 = _BIT5,
    _TYPE_C_RTS_NOTIFY_EN_B3_RSV_BIT30 = _BIT6,
    _TYPE_C_RTS_NOTIFY_EN_B3_PD_AMS_CHG = _BIT7,
    _TYPE_C_RTS_NOTIFY_EN_B3_ALL = 0xFF,
}EnumUsbTypeCRtsNotifyEnByte3;

//--------------------------------------------------
// Struct for Type-C Rts Notification Enable
//--------------------------------------------------
typedef struct
{
    EnumUsbTypeCRtsNotifyEnByte0 enumNotifyEnByte0;
    EnumUsbTypeCRtsNotifyEnByte1 enumNotifyEnByte1;
    EnumUsbTypeCRtsNotifyEnByte2 enumNotifyEnByte2;
    EnumUsbTypeCRtsNotifyEnByte3 enumNotifyEnByte3;
}StructTypeCRtsNotifyEn;
#endif


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern bit UserCommonUsbTypeCRtsGetI2CEnabledFlag(EnumTypeCPcbPort enumTypeCPcbPort);
extern BYTE UserCommonUsbTypeCRtsGetSlaveAddr(EnumTypeCPcbPort enumTypeCPcbPort);
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_RTS_SUPPORT == _ON))
