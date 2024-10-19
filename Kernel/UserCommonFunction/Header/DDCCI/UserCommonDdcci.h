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
// ID Code      : UserCommonDdcci.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __USER_COMMON_DDCCI_H__
#define __USER_COMMON_DDCCI_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of DDCCI Capabilities Request
//--------------------------------------------------
#if(_VGA_SUPPORT == _ON)
#define _CREQLEN_DSUB                                   (sizeof(tCP_STRING_DSUB) - 1)
#endif

#if(_HDMI_SUPPORT == _ON)
#define _CREQLEN_HDMI                                   (sizeof(tCP_STRING_HDMI) - 1)
#endif

#if(_DP_SUPPORT == _ON)
#define _CREQLEN_DP                                     (sizeof(tCP_STRING_DP) - 1)
#endif

#if(_DDCCI_AUTO_SWITCH_SUPPORT == _ON)
// I2C Speed = 20k, DDCCI Buffer = _DDCCI_RXBUF_LENGTH
// (1/20K)*_DDCCI_RXBUF_LENGTH*8
#define _CLR_DDCCI0_CMD_RECEIVE_NOT_FINISH_TIMEOUT      (((_DDCCI_RXBUF_LENGTH * 9) / 20) + 1)
#endif

#define _DDCCI_SRC_RTK_ADDRESS                          0x71
#define _DDCCI_RTK_CMD_TYPE                             0x77
#define _DDCCI_CMD_SWITCH_DEBUG_SALVE_REQUEST           0xAA
#define _DDCCI_CMD_GET_FW_INFO_REQUEST                  0xC9

#define _DDCCI_OPCODE_GET_CURRENT_FW_VER_REQUEST        0x01
#define _DDCCI_OPCODE_GET_FW_VER_LOCATE_REQUEST         0x02
#define _DDCCI_OPCODE_GET_DUAL_BANK_INFO_REQUEST        0x09
#define _DDCCI_OPCODE_SWTICH_DEBUG_SALVE_REQUEST        0x05
//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DDCCI_CODE_REDUCTION == _OFF)
extern void UserCommonDdcciGetCpStringData(BYTE *pucDest, EnumPortType enumPortType, WORD usStartIndex, WORD usLength);
extern WORD UserCommonDdcciGetCpStringSize(EnumPortType enumPortType);
extern bit UserCommonDdcciKernelHandler(void);
extern void UserCommonDdcciGetFwInfoRequest(void);

#if(_CUSTOMER_DEBUG_COMMAND_SUPPORT == _ON)
extern void UserCommonDdcciKernelCustomerDebugCommandHandler(void);
#endif

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
extern void UserCommonDdcci0IntGetData(void);

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern void UserCommonDdcci1IntGetData(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x03)
extern void UserCommonDdcci2IntGetData(void);
#endif

#if(_MULTI_DISPLAY_MAX >= 0x04)
extern void UserCommonDdcci3IntGetData(void);
#endif

#if((_HDMI_FREESYNC_SUPPORT == _ON) && (_HDMI_FREESYNC_CAPABILITY_SWITCH_METHOD == _MCCS_SWITCH_MODE))
extern BYTE UserCommonDdcciHDMIFreesyncHandle(EnumDDCCIPort enumDdcciPort);
#endif

#endif // End of #if(_DEBUG_MESSAGE_SUPPORT == _OFF)

#endif

#if(_ISP_FW_CHECK_PROJECT_ID_SUPPORT == _ON)
extern void UserCommonDdcciFwCheck(void);
#endif

#endif // End of #ifndef __USER_COMMON_DDCCI_H__
