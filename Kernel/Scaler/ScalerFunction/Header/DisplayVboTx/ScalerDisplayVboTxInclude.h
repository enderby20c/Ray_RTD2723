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
// ID Code      : ScalerDisplayVboTxInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_PANEL_STYLE == _PANEL_VBO)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define SET_DISPLAY_VBO_TX_MAC_PORT_ADDR(x)                             (g_ulDisplayVboTxMacPort = (((x) == _VBO_TX_PORT_0) ? 0x00000000 : 0x00100000))
#define GET_DISPLAY_VBO_TX_MAC_PORT_ADDR()                              (g_ulDisplayVboTxMacPort)
#define GET_DISPLAY_VBO_TX_MAC_PORT()                                   ((g_ulDisplayVboTxMacPort == 0x00000000) ? _VBO_TX_PORT_0 : _VBO_TX_PORT_1)

#if(_HW_DISPLAY_VBO_A_PHY_MAPPING_SWAP == _ENABLE)
#define SET_DISPLAY_VBO_TX_PHY_PORT_ADDR(x)                             (g_ulDisplayVboTxPhyPort = (((x) == _VBO_TX_PORT_0) ? 0x00100000 : 0x00000000))
#define GET_DISPLAY_VBO_TX_PHY_PORT_ADDR()                              (g_ulDisplayVboTxPhyPort)
#define GET_DISPLAY_VBO_TX_PHY_PORT()                                   ((g_ulDisplayVboTxPhyPort == 0x00100000) ? _VBO_TX_PORT_0 : _VBO_TX_PORT_1)
#else
#define SET_DISPLAY_VBO_TX_PHY_PORT_ADDR(x)                             (g_ulDisplayVboTxPhyPort = (((x) == _VBO_TX_PORT_0) ? 0x00000000 : 0x00100000))
#define GET_DISPLAY_VBO_TX_PHY_PORT_ADDR()                              (g_ulDisplayVboTxPhyPort)
#define GET_DISPLAY_VBO_TX_PHY_PORT()                                   ((g_ulDisplayVboTxPhyPort == 0x00000000) ? _VBO_TX_PORT_0 : _VBO_TX_PORT_1)
#endif

#define SCALER32_VBO_GET_OFFSET_DWORD(ulOffset, pulAddr)\
                                                                        (SCALER32_GET_OFFSET_DWORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000)))
#define SCALER32_VBO_SET_OFFSET_DWORD(ulOffset, pulAddr, ulValue)\
                                                                        {SCALER32_SET_OFFSET_DWORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulValue));}
#define SCALER32_VBO_GET_OFFSET_WORD(ulOffset, pulAddr, ucWordIndex)\
                                                                        (SCALER32_GET_OFFSET_WORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucWordIndex)))
#define SCALER32_VBO_SET_OFFSET_WORD(ulOffset, pulAddr, ucWordIndex, ulValue)\
                                                                        {SCALER32_SET_OFFSET_WORD((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucWordIndex), (ulValue));}
#define SCALER32_VBO_GET_OFFSET_BYTE(ulOffset, pulAddr, ucIndex)\
                                                                        (SCALER32_GET_OFFSET_BYTE((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucIndex)))
#define SCALER32_VBO_SET_OFFSET_BYTE(ulOffset, pulAddr, ucIndex, ucValue)\
                                                                        {SCALER32_SET_OFFSET_BYTE((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucIndex), (ucValue));}
#define SCALER32_VBO_GET_OFFSET_BIT(ulOffset, pulAddr, ulAnd)\
                                                                        (SCALER32_GET_OFFSET_BIT((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulAnd)))
#define SCALER32_VBO_SET_OFFSET_BIT(ulOffset, pulAddr, ulAnd, ulOr)\
                                                                        {SCALER32_SET_OFFSET_BIT((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulAnd), (ulOr));}

#define SCALER32_VBO_GET_OFFSET_DWORD_EXINT0(ulOffset, pulAddr)\
                                                                        (SCALER32_GET_OFFSET_DWORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000)))
#define SCALER32_VBO_SET_OFFSET_DWORD_EXINT0(ulOffset, pulAddr, ulValue)\
                                                                        {SCALER32_SET_OFFSET_DWORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulValue));}
#define SCALER32_VBO_GET_OFFSET_WORD_EXINT0(ulOffset, pulAddr, ucWordIndex)\
                                                                        (SCALER32_GET_OFFSET_WORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucWordIndex)))
#define SCALER32_VBO_SET_OFFSET_WORD_EXINT0(ulOffset, pulAddr, ucWordIndex, ulValue)\
                                                                        {SCALER32_SET_OFFSET_WORD_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucWordIndex), (ulValue));}
#define SCALER32_VBO_GET_OFFSET_BYTE_EXINT0(ulOffset, pulAddr, ucIndex)\
                                                                        (SCALER32_GET_OFFSET_BYTE_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucIndex)))
#define SCALER32_VBO_SET_OFFSET_BYTE_EXINT0(ulOffset, pulAddr, ucIndex, ucValue)\
                                                                        {SCALER32_SET_OFFSET_BYTE_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ucIndex), (ucValue));}
#define SCALER32_VBO_GET_OFFSET_BIT_EXINT0(ulOffset, pulAddr, ulAnd)\
                                                                        (SCALER32_GET_OFFSET_BIT_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulAnd)))
#define SCALER32_VBO_SET_OFFSET_BIT_EXINT0(ulOffset, pulAddr, ulAnd, ulOr)\
                                                                        {SCALER32_SET_OFFSET_BIT_EXINT0((ulOffset), (((pulAddr) & ~(0xFFF00000)) | 0xB5800000), (ulAnd), (ulOr));}

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    BYTE b1VboLocknPinDetect    : 1;
    BYTE b1VboLocknRippedOff    : 1;
    BYTE b1PanelFastOffStatus   : 1;
}StructDisplayVboTxInfo;

//--------------------------------------------------
// Enumerations of Source State
//--------------------------------------------------
typedef enum
{
    _DISPLAY_VBO_CMU_N_CODE = 0x00,
    _DISPLAY_VBO_CMU_F_CODE,
    _DISPLAY_VBO_CMU_NF_CODE,
}EnumDisplayVboTxCmuInfo;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
extern volatile StructDisplayVboTxInfo g_stDisplayVboTxInfo;
extern volatile DWORD g_ulDisplayVboTxMacPort;
extern volatile DWORD g_ulDisplayVboTxPhyPort;

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
extern void ScalerDisplayVboTxSetPllSsc(bit bDclkSpreadSpeed, BYTE ucSpreadRange);
extern void ScalerDisplayVboTxInitialTable(void);
extern bit ScalerDisplayVboTxGetPllPowerStatus(void);
extern void ScalerDisplayVboTxSetDspcControl(void);
extern DWORD ScalerDisplayVboTxGetNFCode(EnumDisplayVboTxCmuInfo enumDisplayVboTxCmuInfo);

#if(_PANEL_EXIST_MULTIPANEL == _ON)
extern void ScalerDisplayVboTxPowerSwitch(void);
#endif

#endif

