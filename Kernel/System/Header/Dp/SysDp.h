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
// ID Code      : SysDp.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SYS_DP_H__
#define __SYS_DP_H__


//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _NONE = 0x00,
    _CHECK_SUPPORT_STATUS,
    _CHECK_DISPLAY_STATUS,
} EnumDpTxCloneModeStatus;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_DP_SUPPORT == _ON)
extern EnumInputPort SysDpGetInitialDpPort(BYTE ucIndex);
extern void SysDpGetUserDefineDpInfo(EnumInputPort enumInputPort);
extern void SysDpMacArbiterInputPort(EnumInputPort enumInputPort, BYTE ucRegionCount);
extern void SysDpRxMainPortInitial(void);
extern void SysDpRxMainPortJudgeHandler(void);
extern bit SysDpRxMainPortSwitchCheck(EnumInputPort enumInputPort);

#if(_DP_MAC_SWITCH_SUPPORT == _ON)
#if(_HW_DP_MAC_DPHY_SWITCH_SUPPORT == _ON)
extern void SysDpMacDphyArbiterInputPort(EnumInputPort enumInputPort);
#endif
#endif

#if(_MULTI_DISPLAY_MAX >= 0x02)
extern bit SysDpRxFixedTargetPortCheck(EnumInputPort enumInputPort);
#endif

extern bit SysDpCableStatus(EnumInputPort enumInputPort);
extern void SysDpCableDetection(void);
extern bit SysDpPowerTargetCheck(EnumPowerStatus enumPowerStatus);
extern void SysDpPowerHandler(void);
extern void SysDpJudgeHPDToggle(void);
#endif

#if(_DP_TX_SUPPORT == _ON)
extern EnumInputPort SysDpTxCloneGetInputPort(void);
extern bit SysDpTxCloneOutputStatus(EnumDpTxCloneModeStatus enumMode);

extern void SysDpTxHdcp14Handler(void);
#if(_DP_HDCP_2_2_SUPPORT == _ON)
extern void SysDpTxHdcp2Handler(void);
#endif
#endif

#endif // End of #ifndef __SYS_DP_H__
