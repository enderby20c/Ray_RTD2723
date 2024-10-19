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
// ID Code      : UserCommonFwUpdateInterface.h No.0000
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
#if(_FW_UPDATE_PROCESS_SUPPORT == _ON)

extern void UserCommonFwUpdateHandler(void);
extern void UserCommonFwUpdateIntProc(void);
extern BYTE UserCommonFwUpdateGetStatus(void);
extern bit UserCommonFwUpdateStartProcess(WORD usIspPageLen, bit bBankErase);
extern bit UserCommonFwUpdateCheckProcess(void);
extern bit UserCommonFwUpdateFinishProcess(void);
#if((_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON) || (_FW_UPDATE_FOREGROUND_SUPPORT == _ON))
extern bit UserCommonFwUpdateWriteDataProcess(BYTE *pucBuf, WORD usProgramLength, bit bIspXramBuff);
extern bit UserCommonFwUpdateWriteFwData(WORD usProgramLength);
#if((_DIGITAL_SIGNATURE_SUPPORT == _ON) && (_DIGITAL_SIGNATURE_TYPE == _DIGITAL_SIGNATURE_HW))
extern bit UserCommonFwUpdateWriteKeyAndSignatureData(WORD usProgramLength);
#endif
#endif

#if(_USB2_HOST_EHCI_MASS_STORGE_PROGRAM_SUPPORT == _ON)
extern void UserCommonFwUpdateReset(void);
#endif

#endif
