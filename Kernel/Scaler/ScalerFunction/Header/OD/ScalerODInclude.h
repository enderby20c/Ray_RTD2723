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
// ID Code      : ScalerODInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _OD_PIXEL_PER_COMP                                          (4) // Number of pixels processed per compression

#define GET_OD_BIT_RATE(x)                                          (((x) == _OD_PARAM_7_5_BPP) ? 75U :\
                                                                     (((x) == _OD_PARAM_6_0_BPP) ? 60U :\
                                                                     (((x) == _OD_PARAM_4_5_BPP) ? 45U : _OFF)))

#define GET_OD_USE_BIT()                                            (GET_OD_BIT_RATE(g_enumODParamIndex))
#define GET_OD_USE_PARAM()                                          (g_enumODParamIndex)
#define SET_OD_USE_PARAM(x)                                         (g_enumODParamIndex = (x))
#define CLR_OD_USE_PARAM()                                          (g_enumODParamIndex = _OD_PARAM_OFF)

#if(_OD_FUNCTION == _ON)

#define _OD_PATH_WIDTH_DIVISOR                                      ((GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH) ? (2) :\
                                                                     (GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH) ? (1) :\
                                                                     (1))

#define _OD_PATH_HEIGHT_DIVISOR                                     ((GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH) ? (2) :\
                                                                     (GET_D_DOMAIN_PATH() == _D_DOMAIN_2_PATH) ? (2) :\
                                                                     (1))

#if(_FRC_SUPPORT == _ON)
#define GET_DYNAMIC_OD_STATUS(disp_mode, memory_dvf_select)         (\
                                                                        ((disp_mode) == _DISPLAY_MODE_1P) &&\
                                                                        (\
                                                                            ((memory_dvf_select) == _2_IVF) ||\
                                                                            ((memory_dvf_select) == _2_5_IVF) ||\
                                                                            ((memory_dvf_select) == _3_IVF)\
                                                                        )\
                                                                    )
#endif

#if(_FW_OD_PATH_START_ADDR_DESCENDING == _TRUE)
#define _OD_PATH_INIT_ROW                                           (GET_OD_END_ADDRESS() >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM)
#else // Start address ascending
#define _OD_PATH_INIT_ROW                                           (GET_OD_START_ADDRESS() >> _FW_MEM_ROW_ADDR_SHIFT_BIT_NUM)
#endif

#define _OD_PATH_MEMORY_SPACE_ROW_MARGIN                            (2)

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _OD_PATH_M1 = 0x01,
    _OD_PATH_M2 = 0x02,
    _OD_PATH_M3 = 0x04,
    _OD_PATH_M4 = 0x08,
} EnumOdPath;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if(_OD_FUNCTION == _ON)
extern EnumODParamIndex g_enumODParamIndex;

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
extern DWORD g_pulOD3BlkStartAddr[3];
#endif

#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_OD_FUNCTION == _ON)
extern EnumODParamIndex ScalerODGetParamSet(DWORD ulMemoryRemainSpace, WORD usMemoryRemainBW);
extern DWORD ScalerODGetMemoryUsagePerPath(BYTE ucODBit10x);
extern void ScalerODHLWinSetting(EnumHLWType enumHLWType, EnumDBApply enumDBApply);

#if(_HW_FRC_HW_AUTO_3BLOCK_TOGGLE_SUPPORT == _ON)
extern void ScalerODSetThreeBlockAddress(void);
#endif

#if(_FRC_SUPPORT == _ON)
extern void ScalerODIntHandler_EXINT0(void);
#endif
#endif


