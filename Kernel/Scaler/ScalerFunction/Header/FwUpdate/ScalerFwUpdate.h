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
// ID Code      : ScalerFwUpdate.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_FW_UPDATE_H__
#define __SCALER_FW_UPDATE_H__

#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)
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
extern void ScalerFwUpdateDdcciSwitchState(void);
extern void ScalerFwUpdateGetDdcciPort(EnumDDCCIPort enumDdcciChannel);

#if(((_MULTI_DISPLAY_MAX == 0x01) && (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI0)) || (_MULTI_DISPLAY_MAX > 0x01))
extern void ScalerFwUpdateDdcci0SendReply(BYTE ucResult);
extern void ScalerFwUpdateDdcci0SendData(BYTE ucLen, BYTE *pucData);
extern void ScalerFwUpdateDdcci0SwitchState(void);
#endif
#if((_MULTI_DISPLAY_MAX >= 0x02) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI1))
extern void ScalerFwUpdateDdcci1SendReply(BYTE ucResult);
extern void ScalerFwUpdateDdcci1SendData(BYTE ucLen, BYTE *pucData);
extern void ScalerFwUpdateDdcci1SwitchState(void);
#endif
#if((_MULTI_DISPLAY_MAX >= 0x03) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI2))
extern void ScalerFwUpdateDdcci2SendReply(BYTE ucResult);
extern void ScalerFwUpdateDdcci2SendData(BYTE ucLen, BYTE *pucData);
extern void ScalerFwUpdateDdcci2SwitchState(void);
#endif
#if((_MULTI_DISPLAY_MAX >= 0x04) || (_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI3))
extern void ScalerFwUpdateDdcci3SendReply(BYTE ucResult);
extern void ScalerFwUpdateDdcci3SendData(BYTE ucLen, BYTE *pucData);
extern void ScalerFwUpdateDdcci3SwitchState(void);
#endif
#if(_FW_UPDATE_DDCCI_SEL == _FW_UPDATE_SEL_DDCCI4)
extern void ScalerFwUpdateDdcci4SendReply(BYTE ucResult);
extern void ScalerFwUpdateDdcci4SendData(BYTE ucLen, BYTE *pucData);
extern void ScalerFwUpdateDdcci4SwitchState(void);
#endif
#endif

#endif // End of #ifndef __SCALER_FW_UPDATE_H__
