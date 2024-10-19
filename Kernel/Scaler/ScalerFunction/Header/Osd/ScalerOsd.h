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
// ID Code      : ScalerOsd.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_OSD_H__
#define __SCALER_OSD_H__

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define _OSD_TIMING_GEN_VS_START                ((_PANEL_DV_START < 6) ? (6) : (_PANEL_DV_START))


//-------------------------------------------
// Map A Character select address
//-------------------------------------------
#define GET_OSD_MAPA_CHAR_SEL_ADDR()            (((WORD)ScalerGetBit(P3A_3D_FRAME_CTRL_F_MAP_A_SELECT_BASE_H, HIBYTE(_HW_OSD_FONT_SEL_BASE_ADDR_BIT)) << 8) | (ScalerGetByte(P3A_3E_FRAME_CTRL_F_MAP_A_SELECT_BASE_L)))
#define SET_OSD_MAPA_CHAR_SEL_ADDR(x)           {\
                                                    ScalerSetBit(P3A_3D_FRAME_CTRL_F_MAP_A_SELECT_BASE_H, ~(HIBYTE(_HW_OSD_FONT_SEL_BASE_ADDR_BIT)), HIBYTE((x) & _HW_OSD_FONT_SEL_BASE_ADDR_BIT));\
                                                    ScalerSetByte(P3A_3E_FRAME_CTRL_F_MAP_A_SELECT_BASE_L, LOBYTE(x));\
                                                }

//-------------------------------------------
// Map B Row base address
//-------------------------------------------
#define GET_OSD_MAPB_ROW_BASE_ADDR()            (((WORD)ScalerGetBit(P3A_37_FRAME_CTRL_F_ROW_COMMAND_BASE_H, HIBYTE(_HW_OSD_ROW_CMD_BASE_ADDR_B_BIT)) << 8) | (ScalerGetByte(P3A_38_FRAME_CTRL_F_ROW_COMMAND_BASE_L)))
#define SET_OSD_MAPB_ROW_BASE_ADDR(x)           {\
                                                    ScalerSetBit(P3A_37_FRAME_CTRL_F_ROW_COMMAND_BASE_H, ~(HIBYTE(_HW_OSD_ROW_CMD_BASE_ADDR_B_BIT)), HIBYTE((x) & _HW_OSD_ROW_CMD_BASE_ADDR_B_BIT));\
                                                    ScalerSetByte(P3A_38_FRAME_CTRL_F_ROW_COMMAND_BASE_L, LOBYTE(x));\
                                                }

//-------------------------------------------
// Map B Character select address
//-------------------------------------------
#define GET_OSD_MAPB_CHAR_SEL_ADDR()            (((WORD)ScalerGetBit(P3A_3F_FRAME_CTRL_F_MAP_B_SELECT_BASE_H, HIBYTE(_HW_OSD_FONT_SEL_BASE_ADDR_BIT)) << 8) | (ScalerGetByte(P3A_40_FRAME_CTRL_F_MAP_B_SELECT_BASE_L)))
#define SET_OSD_MAPB_CHAR_SEL_ADDR(x)           {\
                                                    ScalerSetBit(P3A_3F_FRAME_CTRL_F_MAP_B_SELECT_BASE_H, ~(HIBYTE(_HW_OSD_FONT_SEL_BASE_ADDR_BIT)), HIBYTE((x) & _HW_OSD_FONT_SEL_BASE_ADDR_BIT));\
                                                    ScalerSetByte(P3A_40_FRAME_CTRL_F_MAP_B_SELECT_BASE_L, LOBYTE(x));\
                                                }

#if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)
//-------------------------------------------
// Map C Row base address
//-------------------------------------------
#define GET_OSD_MAPC_ROW_BASE_ADDR()            (((WORD)ScalerGetBit(P3A_39_FRAME_CTRL_F_ROW_COMMAND_BASE_H_MAP_C, HIBYTE(_HW_OSD_ROW_CMD_BASE_ADDR_B_BIT)) << 8) | (ScalerGetByte(P3A_3A_FRAME_CTRL_F_ROW_COMMAND_BASE_L_MAP_C)))
#define SET_OSD_MAPC_ROW_BASE_ADDR(x)           {\
                                                    ScalerSetBit(P3A_39_FRAME_CTRL_F_ROW_COMMAND_BASE_H_MAP_C, ~(HIBYTE(_HW_OSD_ROW_CMD_BASE_ADDR_B_BIT)), HIBYTE((x) & _HW_OSD_ROW_CMD_BASE_ADDR_B_BIT));\
                                                    ScalerSetByte(P3A_3A_FRAME_CTRL_F_ROW_COMMAND_BASE_L_MAP_C, LOBYTE(x));\
                                                }

//-------------------------------------------
// Map C Character select address
//-------------------------------------------
#define GET_OSD_MAPC_CHAR_SEL_ADDR()            (((WORD)ScalerGetBit(P3A_71_FRAME_CTRL_F_MAP_C_SELECT_BASE_H, HIBYTE(_HW_OSD_FONT_SEL_BASE_ADDR_BIT)) << 8) | (ScalerGetByte(P3A_72_FRAME_CTRL_F_MAP_C_SELECT_BASE_L)))
#define SET_OSD_MAPC_CHAR_SEL_ADDR(x)           {\
                                                    ScalerSetBit(P3A_71_FRAME_CTRL_F_MAP_C_SELECT_BASE_H, ~(HIBYTE(_HW_OSD_FONT_SEL_BASE_ADDR_BIT)), HIBYTE((x) & _HW_OSD_FONT_SEL_BASE_ADDR_BIT));\
                                                    ScalerSetByte(P3A_72_FRAME_CTRL_F_MAP_C_SELECT_BASE_L, LOBYTE(x));\
                                                }

//-------------------------------------------
// Map D Row base address
//-------------------------------------------
#define GET_OSD_MAPD_ROW_BASE_ADDR()            (((WORD)ScalerGetBit(P3A_3B_FRAME_CTRL_F_ROW_COMMAND_BASE_H_MAP_D, HIBYTE(_HW_OSD_ROW_CMD_BASE_ADDR_B_BIT)) << 8) | (ScalerGetByte(P3A_3C_FRAME_CTRL_F_ROW_COMMAND_BASE_L_MAP_D)))
#define SET_OSD_MAPD_ROW_BASE_ADDR(x)           {\
                                                    ScalerSetBit(P3A_3B_FRAME_CTRL_F_ROW_COMMAND_BASE_H_MAP_D, ~(HIBYTE(_HW_OSD_ROW_CMD_BASE_ADDR_B_BIT)), HIBYTE((x) & _HW_OSD_ROW_CMD_BASE_ADDR_B_BIT));\
                                                    ScalerSetByte(P3A_3C_FRAME_CTRL_F_ROW_COMMAND_BASE_L_MAP_D, LOBYTE(x));\
                                                }

//-------------------------------------------
// Map C Character select address
//-------------------------------------------
#define GET_OSD_MAPD_CHAR_SEL_ADDR()            (((WORD)ScalerGetBit(P3A_73_FRAME_CTRL_F_MAP_D_SELECT_BASE_H, HIBYTE(_HW_OSD_FONT_SEL_BASE_ADDR_BIT)) << 8) | (ScalerGetByte(P3A_74_FRAME_CTRL_F_MAP_D_SELECT_BASE_L)))
#define SET_OSD_MAPD_CHAR_SEL_ADDR(x)           {\
                                                    ScalerSetBit(P3A_73_FRAME_CTRL_F_MAP_D_SELECT_BASE_H, ~(HIBYTE(_HW_OSD_FONT_SEL_BASE_ADDR_BIT)), HIBYTE((x) & _HW_OSD_FONT_SEL_BASE_ADDR_BIT));\
                                                    ScalerSetByte(P3A_74_FRAME_CTRL_F_MAP_D_SELECT_BASE_L, LOBYTE(x));\
                                                }
#endif // end of #if(_HW_FOSD_MAP_C_D_SUPPORT == _ON)


// 4 byte command status
#if(_HW_OSD_REG_MAPPING_GEN == _USER_OSD_GEN_4)
#define GET_OSD_COMMAND_4_BYTE_ENABLE()         ((ScalerGetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, _BIT1) == _BIT1) ? (_ENABLE) : (_DISABLE))
#define SET_OSD_COMMAND_4_BYTE_ENABLE(x)        {\
                                                    ScalerSetBit(P3A_F3_FRAME_CTRL_F_OSD_WRITE_OPTION, ~_BIT1, (((x) == _ENABLE) ? (_BIT1) : (0x00)));\
                                                }
#endif


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerOsdDrawGridLinePanelPitch(WORD usPitchHorizontal, WORD usPitchVertical);

#endif // End of #ifndef __SCALER_OSD_H__
