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
// ID Code      : ScalerUsbBillboardInterface.h
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_TYPE_C_PORT_CTRL_SUPPORT == _ON)
#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#define GET_USB_HUB_MUX_SEL_STATUS()                    (g_ucUsbBillboardMuxSelPort)
#define SET_USB_HUB_MUX_SEL_STATUS(x)                   (g_ucUsbBillboardMuxSelPort = (x))
#endif
#endif

#if(_BILLBOARD_SCALER_SUPPORT == _ON)
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)

#define _USB_VENDOR_DUAL_BANK_PROCESS                   0x45
#define _USB_VENDOR_SET_CUSTOM_COMMAND                  0x4C

#define GET_USB_BB_ISP_READY_FLAG()                     (g_bUsbBillboardIspInfoReadyFlag)
#define SET_USB_BB_ISP_READY_FLAG(x)                    (g_bUsbBillboardIspInfoReadyFlag = (x))
#define CLR_USB_BB_ISP_READY_FLAG()                     (g_bUsbBillboardIspInfoReadyFlag = _FALSE)

#define GET_USB_BB_ISP_SUB_OPCODE()                     (g_stUsbBillboardIspCommandInfo.ucSubOpCode)
#define SET_USB_BB_ISP_SUB_OPCODE(x)                    (g_stUsbBillboardIspCommandInfo.ucSubOpCode = (x))
#define CLR_USB_BB_ISP_SUB_OPCODE()                     (g_stUsbBillboardIspCommandInfo.ucSubOpCode = _FALSE)

#define GET_USB_BB_ISP_OPCODE()                         (g_stUsbBillboardIspCommandInfo.ucOpCode)
#define SET_USB_BB_ISP_OPCODE(x)                        (g_stUsbBillboardIspCommandInfo.ucOpCode = (x))
#define CLR_USB_BB_ISP_OPCODE()                         (g_stUsbBillboardIspCommandInfo.ucOpCode = _FALSE)


#define GET_USB_BB_ISP_REV_CMD_STATUS()                 (g_stUsbBillboardIspCommandInfo.ucRevCmd)
#define SET_USB_BB_ISP_REV_CMD_STATUS()                 (g_stUsbBillboardIspCommandInfo.ucRevCmd = _TRUE)
#define CLR_USB_BB_ISP_REV_CMD_STATUS()                 (g_stUsbBillboardIspCommandInfo.ucRevCmd = _FALSE)

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern StructUsbBillboardIspCommandInfo g_stUsbBillboardIspCommandInfo;
extern StructUsbBillboardCustomCommandInfo g_stUsbBillboardCustomCommandInfo;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DUAL_BANK_DEBUG_SUPPORT == _ON)
extern void ScalerUsbBillboardCopyISPInfo(BYTE *pucSrcAddr, BYTE ucLength, BYTE ucReadyFlag);
#endif

extern void ScalerUsbBillboardSetBBProgramEnable(void);
extern void ScalerUsbBillboardClrBBProgramEnable(void);
extern void ScalerUsbBillboardIspFlagInitial(void);
#endif
extern void ScalerUsbBillboardHandler(void);
extern void ScalerUsbBillboardPllPower(EnumBillboardCtrl enumAtion);
extern BYTE g_ucUsbBillboardMuxSelPort;
extern bit g_bUsbBillboardIspEn;
#if(_USB_TYPE_C_BB_PROGRAM_SUPPORT == _ON)
extern bit g_bUsbBillboardIspProcessing;
extern bit g_bUsbBillboardIspProcessingUpdate;
extern bit g_bUsbBillboardIspProcessingDone;
extern void ScalerUsbBillboardProgramCheckDone(void);
#endif
#endif
