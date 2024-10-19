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
// ID Code      : ScalerDisplayVboTxInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PANEL_STYLE == _PANEL_VBO)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _VBO_FW_CONTROL = 0x00,
    _VBO_HW_CONTROL,
} EnumDisplayVboTxControlMode;

typedef enum
{
    _VBO_TX_PORT_0 = 0x00,
    _VBO_TX_PORT_1,
} EnumDisplayVboTxPort;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayVboTxPhyControl(bit bEnable);
extern void ScalerDisplayVboTxHtpdnControl(EnumDisplayVboTxControlMode enumDisplayVboTxControlMode, bit bValue);
extern void ScalerDisplayVboTxForceVideoOutput(bit bEnable);

#if(_PANEL_VBO_CHANGE_CLK_RESET_TYPE == _VBO_CHANGE_CLK_RESET_BY_RE_LINK_TRAIN)
extern void ScalerDisplayVboTxForceLinkTraining(bit bEnable);
#endif

extern void ScalerDisplayVboTxHtpdnHandler(void);
extern void ScalerDisplayVboTxLocknHandler(void);
extern void ScalerDisplayVboTxPanelSetFastOff(bit bEnable);
extern bit ScalerDisplayVboTxPanelFastOffCheck(void);
extern void ScalerDisplayVboTxPanelBacklightReTurnOn(void);
extern void ScalerDisplayVboTxPollingHotPlug(WORD usNum);

extern void ScalerDisplayVboTxIntHandler_EXINT0(void);
#endif

