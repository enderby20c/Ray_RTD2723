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
// ID Code      : ScalerOD.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_OD_H__
#define __SCALER_OD_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_OD_FUNCTION == _ON)

#define _OD_8BIT_LUT_LENGTH                         (289)
#define _OD_10BIT_LUT_LENGTH                        (578)

#define _OD_GLUT_LENGTH                             (32)

// OD Write: OD_W_BUF  --64-->  OD_W_FIFO  --128-->  Frame Buffer
// OD Read:  Frame Buffer  --128-->  OD_R_FIFO  --64-->  OD_R_BUF
#define _OD_MEM_RW_BUF_UNIT_BIT                     (64) // Unit: bit
#define _OD_MEM_RW_FIFO_UNIT_BIT                    (_OD_MEM_RW_BUF_UNIT_BIT * 2) // 128 bit
#define _OD_MEM_RW_DEFAULT_LEN                      (_HW_OD_MEM_RW_MAX_LENGTH) // Unit: _OD_MEM_RW_BUF_UNIT_BIT


#define _OD_PATH_MAIN                               ((GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH) ? (_OD_PATH_M1 | _OD_PATH_M2) :\
                                                     (GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH) ? (_OD_PATH_M1 | _OD_PATH_M2) :\
                                                     (_OD_PATH_M1))

#define _OD_PATH_ALL                                ((GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH) ? (_OD_PATH_M1 | _OD_PATH_M2 | _OD_PATH_M3 | _OD_PATH_M4) :\
                                                     (GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH) ? (_OD_PATH_M1 | _OD_PATH_M2) :\
                                                     (_OD_PATH_M1))

#define CHK_OD_MAIN_PATH(x)                         ((_OD_PATH_MAIN & (x)) == (x))
#define CHK_OD_EVERY_PATH(x)                        ((_OD_PATH_ALL & (x)) == (x))

#define GET_OD_DATA_PATH(x)                         (tOdPathInfo[(x)].enumOdPath)
#define GET_OD_REG_PAGE(x)                          (tOdPathInfo[(x)].ucOdPage)

#if(_FRC_SUPPORT == _ON)
#define GET_OD_CURR_DYNAMIC_STATUS()                (g_ucODCurrDynamicStatus)
#define SET_OD_CURR_DYNAMIC_STATUS(x)               (g_ucODCurrDynamicStatus = (x))
#endif

// OD parameter default value
#define _OD_PRE_SRC_RES_DEFAULT                     _OD_PRE_SRC_RES_8_BIT
#define _OD_CUR_SRC_RES_DEFAULT                     _OD_CUR_SRC_RES_8_BIT
#define _OD_CMP_METHOD_DEFAULT                      _OD_CMP_METHOD_444_TO_422
#define _OD_CMP_MODE_DEFAULT                        _OD_CMP_MODE_AVG
#define _OD_DECMP_MODE_DEFAULT                      _OD_DECMP_MODE_INTERP

// Define Path Bank Offset
#define _OD_M1_BANK_OFFSET                          ((WORD)0x05 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M1: bank5
#define _OD_M2_BANK_OFFSET                          ((WORD)0x00 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M2: Bank0
#define _OD_M3_BANK_OFFSET                          ((WORD)0x04 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M3: bank4
#define _OD_M4_BANK_OFFSET                          ((WORD)0x02 << _FW_MEM_BANK_ADDR_SHIFT_BIT_NUM) // M4: Bank2

#if(_HW_OD_COMP_GEN >= _OD_COMP_GEN_1)
// Define of compression method Pixel_Filter_1x4
#define _OD_PF_1X4_MIN_FILTER_WIDTH                 (5)
#define _OD_PF_1X4_MAX_FILTER_WIDTH                 (12)
#endif

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    EnumOdPath enumOdPath;
    BYTE ucOdPage;
}StructOdPathInfo;

#if(_OD_FUNCTION == _ON)
typedef enum
{
    _OD_PRE_SRC_RES_8_BIT = 0x00,
    _OD_PRE_SRC_RES_6_BIT = _BIT0,
    _OD_PRE_SRC_RES_5_BIT = _BIT1,
    _OD_PRE_SRC_RES_4_BIT = (_BIT1 | _BIT0),
} EnumOdPreSrcRes;

typedef enum
{
    _OD_CUR_SRC_RES_8_BIT = 0x00,
    _OD_CUR_SRC_RES_6_BIT = _BIT6,
    _OD_CUR_SRC_RES_5_BIT = _BIT7,
    _OD_CUR_SRC_RES_4_BIT = (_BIT7 | _BIT6),
} EnumOdCurSrcRes;

typedef enum
{
    _OD_CMP_METHOD_444_TO_422 = 0x00,
    _OD_CMP_METHOD_444_TO_411 = _BIT1,
    _OD_CMP_METHOD_SP_1X2 = _BIT2,
    _OD_CMP_METHOD_SP_1X3 = (_BIT2 | _BIT1),
    _OD_CMP_METHOD_SP_1X4 = _BIT3,
#if(_HW_OD_COMP_GEN >= _OD_COMP_GEN_1)
    _OD_CMP_METHOD_PF_1X4 = (_BIT3 | _BIT1), // Pixel_Filter_1X4
#endif
} EnumOdCmpMethod;

typedef enum
{
    _OD_CMP_MODE_AVG = 0x00,
    _OD_CMP_MODE_DROP = _BIT6,
} EnumOdCmpMode;

typedef enum
{
    _OD_DECMP_MODE_INTERP = 0x00,
    _OD_DECMP_MODE_DUP = (_BIT6 | _BIT2),
} EnumOdDecmpMode;

typedef enum
{
    _OD_EST_RANGE_BYPASS = 0x00,
    _OD_EST_RANGE_8 = _BIT4,
    _OD_EST_RANGE_16 = _BIT5,
    _OD_EST_RANGE_32 = (_BIT5 | _BIT4),
} EnumOdEstRange;

typedef struct
{
    BYTE ucOdBit10x;
    EnumOdCmpMethod enumCmpMethod;
    EnumOdPreSrcRes enumPreSrcRes;
    EnumOdCurSrcRes enumCurSrcRes;
    EnumOdCmpMode enumCmpMode;
    EnumOdDecmpMode enumDecmpMode;
    BYTE ucNRThreshold;
    BYTE ucLvlEstValue;
} StructOdParam;
#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_OD_FUNCTION == _ON)
#if(_FRC_SUPPORT == _ON)
extern BYTE g_ucODCurrDynamicStatus;
#endif
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_OD_FUNCTION == _ON)
extern void ScalerODSetFrontBackRegSeparate(bit bEnable);
extern void ScalerODGetPathStartAddr(WORD usPathSizeInRow, WORD *pusRowAddrList);
extern void ScalerODSetMemoryAndFIFO(void);
extern void ScalerODLoadLUT(BYTE *pucODTable, BYTE ucBankNum, bit bLUTMode);

extern void ScalerODCompressionSetting(void);

#if(_OD_BY_POSITION_SUPPORT == _ON)
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _OFF)
extern void ScalerODAdjustODByPos(StructODUserByPosData *pstODUserByPosData);
#endif
#endif

extern WORD ScalerODGetShiftBankOffset(BYTE ucCurrPage);

#if(_OD_MEMORY_BW_CTRL_SUPPORT == _ON)
extern void ScalerODBwCtrlGetClientInfo(StructBwCtrlClientInfo *pstInfo, WORD usOdRwLen_BufUnit);
#endif

#endif


#endif // End of #ifndef __SCALER_OD_H__
