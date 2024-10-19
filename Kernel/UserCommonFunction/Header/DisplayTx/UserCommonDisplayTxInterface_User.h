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
// ID Code      : UserCommonDisplayTxInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_PANEL_STYLE == _PANEL_DPTX)
extern void UserCommonDisplayTxDpSSCSet(bit bSscEn);
extern void UserCommonDisplayTxDpTxPollingHotPlug(WORD usNum);
extern bit UserCommonDisplayTxDpTxLinkSequence(void);

#if(_PANEL_DPTX_FORCE_OUTPUT_SUPPORT == _ON)
extern void UserCommonDisplayTxDpTxLinkSignalForceOutput(void);
#endif

extern void UserCommonDisplayTxDpTxPllReset(void);
extern void UserCommonDisplayTxDpTxInitial(void);
extern void UserCommonDisplayTxDpTxPhyInitial(void);
extern void UserCommonDisplayTxDpTxPowerSequenceProc(bit bLevel);
extern void UserCommonDisplayTxDpTxStreamHanlder(bit bOutput);
extern bit UserCommonDisplayTxDpTxXAuxI2COverWrite(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray);
extern bit UserCommonDisplayTxDpTxXAuxI2COverRead(EnumDisplayDpTxOutputPort enumDisplayDpTxOutputPort, BYTE ucSlaveAddress, BYTE ucLength, BYTE *pucDataArray);
#endif

#if(_PANEL_STYLE == _PANEL_VBO)
extern void UserCommonDisplayTxVboPollingHotPlug(WORD usNum);
extern void UserCommonDisplayTxVboLocknHandler(void);
extern void UserCommonDisplayTxVboPanelSetFastOff(bit bEnable);
#endif

#if(_PANEL_STYLE == _PANEL_LVDS)
extern void UserCommonDisplayTxLvdsPLL(bit bOn);
extern void UserCommonDisplayTxLvdsPower(bit bOn);
#endif

#if(_PANEL_EXIST_MULTIPANEL == _ON)
extern void UserCommonDisplayTxMultiPanelSettingApply(void);
#endif

