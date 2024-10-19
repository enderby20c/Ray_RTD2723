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
// ID Code      : ScalerODInterface.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_OD_FUNCTION == _ON)
#define GET_OD_TABLE_VALID_STATUS()                 (g_ucODTableValidBit)
#define SET_OD_TABLE_VALID_STATUS()                 (g_ucODTableValidBit = _TRUE)
#define CLR_OD_TABLE_VALID_STATUS()                 (g_ucODTableValidBit = _FALSE)

#define GET_OD_TABLE_LAST_ADDRESS()                 (g_pucODLUTBackup)
#define SET_OD_TABLE_LAST_ADDRESS(x)                (g_pucODLUTBackup = (x))
#define CLR_OD_TABLE_LAST_ADDRESS()                 (g_pucODLUTBackup = 0x0000)

#define GET_OD_TABLE_LAST_BANK_NUM()                (g_ucODLUTBankNumBackup)
#define SET_OD_TABLE_LAST_BANK_NUM(x)               (g_ucODLUTBankNumBackup = (x))
#define CLR_OD_TABLE_LAST_BANK_NUM()                (g_ucODLUTBankNumBackup = 0x0000)

#if(_OD_BY_POSITION_SUPPORT == _ON)
#define GET_OD_BYPOS_TABLE_LAST_ADDRESS()           (g_pucODByPosTableBackup)
#define SET_OD_BYPOS_TABLE_LAST_ADDRESS(x)          (g_pucODByPosTableBackup = (x))
#define CLR_OD_BYPOS_TABLE_LAST_ADDRESS()           (g_pucODByPosTableBackup = 0x0000)

#define GET_OD_BYPOS_TABLE_LAST_BANK_NUM()          (g_ucODLUTBankNumBackup)
#define SET_OD_BYPOS_TABLE_LAST_BANK_NUM(x)         (g_ucODLUTBankNumBackup = (x))
#define CLR_OD_BYPOS_TABLE_LAST_BANK_NUM()          (g_ucODLUTBankNumBackup = 0x0000)
#endif
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _OD_ADJUST_GAIN,
    _OD_ADJUST_GAIN_ODLUT,
#if(_OD_BY_POSITION_SUPPORT == _ON)
    _OD_ADJUST_BYPOS,
    _OD_ADJUST_GAIN_ODLUT_BYPOS,
#endif
} EnumODAdjustMode;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_OD_FUNCTION == _ON)
extern BYTE g_ucODTableValidBit;
extern BYTE g_ucODLUTBankNumBackup;
extern BYTE *g_pucODLUTBackup;
#if(_OD_BY_POSITION_SUPPORT == _ON)
extern BYTE g_ucODByPosTableBankNumBackup;
extern BYTE *g_pucODByPosTableBackup;
#endif
#endif


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_OD_FUNCTION == _ON)

extern void ScalerODEnable(EnumFunctionOnOFF enumOn);
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _OFF)
extern void ScalerODAdjust(EnumODAdjustMode enumODAdjustMode, StructODSetting *pstODSetting);
#endif

extern void ScalerODInitial(void);
extern void ScalerODAdjustDeltaGain(BYTE ucValue);
extern BYTE ScalerODGetDeltaGain(void);
extern EnumODParamIndex ScalerODGetUseParam(void);

extern bit ScalerODGetSupportStatus(void);
extern bit ScalerODGetRealtimeEnableStatus(void);
#endif

