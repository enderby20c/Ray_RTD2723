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
// ID Code      : ScalerGosdSe.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#define __SCALER_GOSDSE__

#include "ScalerFunctionInclude.h"
#include "Gosd/ScalerGosdSe.h"
#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// CODE TABLES
//****************************************************************************
//----------------------------------------------------------------------------------------------------
// 4 taps Stretch Coefficient Table
//----------------------------------------------------------------------------------------------------
DWORD code tGosdSe_H_COEF_4_TAPS[] =
{
    0x3fc0, 0x3f80, 0x3f80, 0x3f60, 0x3f20, 0x3ee0, 0x3ea0, 0x3e80,
    0x3e60, 0x3e40, 0x3e40, 0x3e40, 0x3e60, 0x3ec0, 0x3f40, 0x3fc0,
    0x0080, 0x0180, 0x0280, 0x03a0, 0x04e0, 0x0640, 0x07a0, 0x08e0,
    0x0a40, 0x0b80, 0x0ca0, 0x0dc0, 0x0ea0, 0x0f40, 0x0fc0, 0x1000
};
DWORD code tGosdSe_V_COEF_4_TAPS[] =
{
    0x3fc0, 0x3f80, 0x3f80, 0x3f60, 0x3f20, 0x3ee0, 0x3ea0, 0x3e80,
    0x3e60, 0x3e40, 0x3e40, 0x3e40, 0x3e60, 0x3ec0, 0x3f40, 0x3fc0,
    0x0080, 0x0180, 0x0280, 0x03a0, 0x04e0, 0x0640, 0x07a0, 0x08e0,
    0x0a40, 0x0b80, 0x0ca0, 0x0dc0, 0x0ea0, 0x0f40, 0x0fc0, 0x1000
};

//----------------------------------------------------------------------------------------------------
// 2 taps Stretch Coefficient Table
//----------------------------------------------------------------------------------------------------
DWORD code tGosdSe_H_COEF_2_TAPS[] =
{
    0x3fc0, 0x3f80, 0x3f20, 0x3fa0, 0x3e60, 0x3e40, 0x3e60, 0x3e40,
    0x0080, 0x0280, 0x04e0, 0x07a0, 0x0a40, 0x0ca0, 0x0ea0, 0x0fc0
};
DWORD code tGosdSe_V_COEF_2_TAPS[] =
{
    0x3fc0, 0x3f80, 0x3f20, 0x3fa0, 0x3e60, 0x3e40, 0x3e60, 0x3e40,
    0x0080, 0x0280, 0x04e0, 0x07a0, 0x0a40, 0x0ca0, 0x0ea0, 0x0fc0
};

//****************************************************************************
// VARIABLE DECLARATIONS
//****************************************************************************
DWORD g_ulGosdSeCmdBaseAddress;
DWORD g_ulGosdSeCmdLength;
volatile DWORD g_pulGosdSeExecutingSurfaceId[3];

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : get SE execute
// Input Value  : None
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdSeGetExecute(void)
{
    return g_bGosdSeExecuting;
}

//--------------------------------------------------
// Description  : check Surface Status for Executing
// Input Value  : ulSurfaceId
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerGosdSeCheckSurfaceStatus(DWORD ulSurfaceId, EnumGosdSeLayerType enumType)
{
    bit bResult = _FALSE;

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
    if(ScalerGosdCheckSurface(ulSurfaceId) == _FALSE)
    {
        DebugMessageGOSD("Surface is uncreated or outof range", ulSurfaceId);
        return _FALSE;
    }
#endif
    switch(GOSD_GET_SURFACE_STATUS(ulSurfaceId))
    {
        case _GOSD_SURFACE_UNDEFINED:
        case _GOSD_SURFACE_IDLE:
            bResult = _TRUE;
            break;
        case _GOSD_SURFACE_DISPOSD_SHOWING:
            if((enumType == _GOSD_SEINFO_LAYERTYPE_SRC1) ||
               (enumType == _GOSD_SEINFO_LAYERTYPE_SRC2))
            {
                // allow: SE read Displaying surface
                bResult = _TRUE;
            }
            else
            {
                // deny: SE write Displaying surface
                bResult = _FALSE;
            }
            break;
        case _GOSD_SURFACE_UNCREATED:
        case _GOSD_SURFACE_LOADING:
        case _GOSD_SURFACE_SE_WORKING_READ:
        case _GOSD_SURFACE_SE_WORKING_WRITE:
        default:
            bResult = _FALSE;
            break;
    }

    if(bResult == _FALSE)
    {
        DebugMessageGOSD("Surface is not ready for Draw", ulSurfaceId);
        DebugMessageGOSD("  Status", GOSD_GET_SURFACE_STATUS(ulSurfaceId));
    }

    return bResult;
}

#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
//--------------------------------------------------
// Description  : reset SE SW parematers
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdSeInitial(void)
{
    g_ulGosdSeCmdBaseAddress = _GOSD_MEMORY_END_ADDRESS;
    g_ulGosdSeCmdLength = _GOSDSE_CMD_LENGTH_DEFAULT;

    // if SE is idle
    if(g_bGosdSeExecuting == _FALSE)
    {
        // reset executing SurfaceId list
        for(BYTE ucIdx = 0; ucIdx < GET_TABLE_ELEMENT_NUM(g_pulGosdSeExecutingSurfaceId); ucIdx++)
        {
            g_pulGosdSeExecutingSurfaceId[ucIdx] = _GOSD_SURFACE_NUMBER;
        }
        // reset cmd registers
        Scaler32SetDWord(PB00480_1C_CMDBASE_Q1, g_ulGosdSeCmdBaseAddress);
        Scaler32SetDWord(PB00480_20_CMDLMT_Q1, g_ulGosdSeCmdBaseAddress + g_ulGosdSeCmdLength);
        Scaler32SetDWord(PB00480_24_CMDRPTR_Q1, g_ulGosdSeCmdBaseAddress);
        Scaler32SetDWord(PB00480_28_CMDWPTR_Q1, g_ulGosdSeCmdBaseAddress);
    }
    // if SE is executing, SurfaceId list & cmd registers will reset at ScalerGosdSeDone_Handler
}

//--------------------------------------------------
// Description  : Power on initial
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdSePowerOnInitial(void)
{
    g_bGosdSeExecuting = _FALSE;

    ScalerGosdSeInitial();

    // interrupt com_empty enable
    Scaler32SetBit(PB00480_14_INTE_Q1, ~(_BIT3), _BIT3);

    // set Stretch Reg
    StructGosdSeStretchConfig stStretchConfig = {0};

    stStretchConfig.enumHorizontalTypeSel = _GOSD_SEINFO_STRETCH_EVEN;
    stStretchConfig.enumVerticalTypeSel = _GOSD_SEINFO_STRETCH_EVEN;
    stStretchConfig.enumHorizontalTapNumberSel = _GOSD_SEINFO_STRETCH_4TAP;
    stStretchConfig.enumVerticalTapNumberSel = _GOSD_SEINFO_STRETCH_4TAP;
    ScalerGosdSeSetRegStretch(&stStretchConfig);

#if(_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON)
    ScalerGosdSeSetBwCtrl();
#endif
}

//--------------------------------------------------
// Description  : sort format type
// Input Value  : enumFmt : format
// Output Value : EnumGosdSeColorFormatType
//--------------------------------------------------
EnumGosdSeColorFormatType ScalerGosdSeGetFormatType(EnumGosdSeColorFormat enumFmt)
{
    switch (enumFmt)
    {
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        case _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8:
        case _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8U8:
            return _GOSD_SEINFO_AFBC_FORMAT;
#endif
        case _GOSD_SEINFO_COLOR_FORMAT_ARGB8888:
        case _GOSD_SEINFO_COLOR_FORMAT_ARGB1555:
        case _GOSD_SEINFO_COLOR_FORMAT_ARGB4444:
        case _GOSD_SEINFO_COLOR_FORMAT_RGB888:
        case _GOSD_SEINFO_COLOR_FORMAT_RGB565:
        case _GOSD_SEINFO_COLOR_FORMAT_INDEX8:
            return _GOSD_SEINFO_ARGB_FORMAT;

        default:
            return _GOSD_SEINFO_ARGB_FORMAT;
    }
}

//--------------------------------------------------
// Description  : set SE execute
// Input Value  : None
// Output Value : EnumGosdSyncCmdFeedBack
//--------------------------------------------------
EnumGosdSyncCmdFeedBack ScalerGosdSeExecute(void)
{
    if(g_bGosdSeExecuting == _FALSE)
    {
        g_bGosdSeExecuting = _TRUE;
        Scaler32SetBit(PB00480_08_CTRL_Q1, ~_BIT1, _BIT1);

        return _GOSD_SYNC_FEEDBACK_SUCCESS;
    }
    else
    {
        return _GOSD_SYNC_FEEDBACK_BUSY_DRAW;
    }
}

//--------------------------------------------------
// Description  : set write_reg cmd
// Input Value  : *pstCmd : write_reg cmd
//            ulAddress : register address
//            ulValue : register value
// Output Value : void
//--------------------------------------------------
void ScalerGosdSeWriteRegCmd(StructGosdSeCmdWriteRegister *pstCmd, DWORD ulAddress, DWORD ulValue)
{
    pstCmd->stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_WRITE_REGISTER;
    pstCmd->stDWordReg.b12RegisterAddress = GOSDSE_CMD0_REGSHIFT(ulAddress);
    pstCmd->stDWordReg.b1Clut = _GOSD_SEINFO_REGMODE_REGISTER;
    pstCmd->stDWordValue.ulRegisterValue = ulValue;
}

//--------------------------------------------------
// Description  : set baddr & pitch cmd
// Input Value  : *pstSeCmdRegBaddr : write_reg cmd
//           *pstSeCmdRegPitch : write_reg cmd
//            ucIndex : baddr & pitch index
//            ulAddress : baddr value
//            usPitch : pitch value
// Output Value : None
//--------------------------------------------------
void ScalerGosdSeSetBaddrPitchCmd(StructGosdSeCmdWriteRegister *pstSeCmdRegBaddr, StructGosdSeCmdWriteRegister *pstSeCmdRegPitch, BYTE ucIndex, DWORD ulAddress, WORD usPitch)
{
    ScalerGosdSeWriteRegCmd(pstSeCmdRegBaddr, PB00480_34_SE20_BADDR_0_Q1 + ucIndex * 4, ulAddress);
    ScalerGosdSeWriteRegCmd(pstSeCmdRegPitch, PB00480_74_SE20_PITCH_0_Q1 + ucIndex * 4, usPitch);
}

//--------------------------------------------------
// Description  : Set Stretch Registers
// Input Value  : StructGosdSeStretchConfig
// Output Value : None
//--------------------------------------------------
void ScalerGosdSeSetRegStretch(StructGosdSeStretchConfig *pstStretchConfig)
{
    DWORD *pulCoeffTable = _NULL_POINTER;
    BYTE ucTapNum = 0;

    DWORD ulStretchSettings = ((DWORD)pstStretchConfig->enumVerticalTypeSel << 0) |
                              ((DWORD)pstStretchConfig->enumHorizontalTypeSel << 4) |
                              ((DWORD)pstStretchConfig->enumVerticalTapNumberSel << 8) |
                              ((DWORD)pstStretchConfig->enumHorizontalTapNumberSel << 12) |
                              _BIT16; // stretch ref_alpha_en fixed = 1
    // set STRETCH
    Scaler32SetDWord(PB00481_30_SE20_STRETCH_Q1, ulStretchSettings);

    // set HCOEFF
    ucTapNum = (pstStretchConfig->enumHorizontalTapNumberSel == _GOSD_SEINFO_STRETCH_4TAP) ? (4) : (2);
    pulCoeffTable = (pstStretchConfig->enumHorizontalTapNumberSel == _GOSD_SEINFO_STRETCH_4TAP) ? (tGosdSe_H_COEF_4_TAPS) : (tGosdSe_H_COEF_2_TAPS);
    for(BYTE ucLoopCnt = 0; ucLoopCnt < (ucTapNum << 3); ucLoopCnt++)
    {
        Scaler32SetDWord(PB00482_00_SE20_S1_HCOEFF_0_Q1 + ucLoopCnt * 4, *(pulCoeffTable + ucLoopCnt));
    }

    // set VCOEFF
    ucTapNum = (pstStretchConfig->enumVerticalTapNumberSel == _GOSD_SEINFO_STRETCH_4TAP) ? (4) : (2);
    pulCoeffTable = (pstStretchConfig->enumVerticalTapNumberSel == _GOSD_SEINFO_STRETCH_4TAP) ? (tGosdSe_V_COEF_4_TAPS) : (tGosdSe_V_COEF_2_TAPS);
    for(BYTE ucLoopCnt = 0; ucLoopCnt < (ucTapNum << 3); ucLoopCnt++)
    {
        Scaler32SetDWord(PB00482_80_SE20_S1_VCOEFF_0_Q1 + ucLoopCnt * 4, *(pulCoeffTable + ucLoopCnt));
    }
}

//--------------------------------------------------
// Description  : check AFBC format X/ Y/ W/ H limitations
// Input Value  : *pstLayer : layer info
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerGosdSeAfbcGuard(StructGosdSeLayerInfo *pstLayer)
{
    bit bPass = _TRUE;

    if((pstLayer->usDataX % _GOSD_SE_AFBC_X_ALIGN) != 0)
    {
        DebugMessageGOSD("  X=", pstLayer->usDataX);
        bPass = _FALSE;
    }
    if((pstLayer->usDataY % _GOSD_SE_AFBC_Y_ALIGN) != 0)
    {
        DebugMessageGOSD("  Y=", pstLayer->usDataY);
        bPass = _FALSE;
    }
    if((pstLayer->usDataWidth % _GOSD_SE_AFBC_W_ALIGN) != 0)
    {
        DebugMessageGOSD("  W=", pstLayer->usDataWidth);
        bPass = _FALSE;
    }
    if((pstLayer->usDataHeight % _GOSD_SE_AFBC_H_ALIGN) != 0)
    {
        DebugMessageGOSD("  H=", pstLayer->usDataHeight);
        bPass = _FALSE;
    }

    return bPass;
}

//--------------------------------------------------
// Description  : check HW&SW limitations of layer
// Input Value  : *pstLayer : layer info
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerGosdSeLayerGuard(StructGosdSeLayerInfo *pstLayer)
{
    BYTE ucBpp = 0;
    DWORD ulLength = 0;

    if(pstLayer == _NULL_POINTER)
    {
        DebugMessageGOSD("Layer Error : Empty Layer", 0);
        return _FALSE;
    }

    switch(pstLayer->stSurface.enumFormat)
    {
        case _GOSD_SEINFO_COLOR_FORMAT_ARGB8888:
            ucBpp = 4;
            break;
        case _GOSD_SEINFO_COLOR_FORMAT_RGB888:
            ucBpp = 3;
            break;
        case _GOSD_SEINFO_COLOR_FORMAT_ARGB4444:
        case _GOSD_SEINFO_COLOR_FORMAT_ARGB1555:
        case _GOSD_SEINFO_COLOR_FORMAT_RGB565:
            ucBpp = 2;
            break;
        case _GOSD_SEINFO_COLOR_FORMAT_INDEX8:
            ucBpp = 1;
            break;
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        case _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8U8:
        case _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8:
            ucBpp = 1;
            break;
#endif
        default:
            DebugMessageGOSD("Layer Error: Not Support Format", pstLayer->stSurface.enumFormat);
            return _FALSE;
    }

    switch(pstLayer->stSurface.enumFormat)
    {
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
        case _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8U8:
            // Bpp = 4.5
            ulLength = (DWORD)pstLayer->stSurface.usFullWidth * pstLayer->stSurface.usFullHeight * 9 / 2;
            break;
        case _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8:
            // Bpp = 3.5
            ulLength = (DWORD)pstLayer->stSurface.usFullWidth * pstLayer->stSurface.usFullHeight * 7 / 2;
            break;
#endif
        default:
            ulLength = (DWORD)pstLayer->stSurface.usFullWidth * pstLayer->stSurface.usFullHeight * ucBpp;
            break;
    }
    // check DDR memory boundary
    if(pstLayer->stSurface.ulAddress + ulLength >= _GOSD_MEMORY_END_ADDRESS)
    {
        DebugMessageGOSD("Layer Error: Image size overflow", 0);
        DebugMessageGOSD("  _GOSD_MEMORY_END_ADDRESS", _GOSD_MEMORY_END_ADDRESS);
        DebugMessageGOSD("  Address", pstLayer->stSurface.ulAddress);
        DebugMessageGOSD("  Length", ulLength);
        return _FALSE;
    }

    // check index8 format
    if(pstLayer->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        if(pstLayer->enumLayerType == _GOSD_SEINFO_LAYERTYPE_RSLT)
        {
            DebugMessageGOSD("Layer Error: Rslt format can't INDEX8", 0);
            return _FALSE;
        }
        else if(pstLayer->stSurface.ulClutAddress % 16 != 0)
        {
            DebugMessageGOSD("Layer Error: CLUT address not align 16Byte", pstLayer->stSurface.ulClutAddress);
            return _FALSE;
        }
    }

    // Check Image Boundary
    if(pstLayer->usDataWidth > _GOSD_SE_WIDTH_LIMITATION)
    {
        DebugMessageGOSD("Layer Error: Width > 8192", pstLayer->usDataWidth);
        return _FALSE;
    }
    if(pstLayer->usDataWidth == 0)
    {
        DebugMessageGOSD("Layer Error: Width = 0", pstLayer->usDataWidth);
        return _FALSE;
    }
    if(pstLayer->usDataHeight > _GOSD_SE_HEIGHT_LIMITATION)
    {
        DebugMessageGOSD("Layer Error: Height > 8192", pstLayer->usDataHeight);
        return _FALSE;
    }
    if(pstLayer->usDataHeight == 0)
    {
        DebugMessageGOSD("Layer Error: Height = 0", pstLayer->usDataHeight);
        return _FALSE;
    }
    if(pstLayer->usDataX > _GOSD_SE_WIDTH_LIMITATION - 1)
    {
        DebugMessageGOSD("Layer Error: X > 8191", pstLayer->usDataX);
        return _FALSE;
    }
    if(pstLayer->usDataX + pstLayer->usDataWidth > pstLayer->stSurface.usFullWidth)
    {
        DebugMessageGOSD("Layer Error: X+W > FullW", 0);
        DebugMessageGOSD("  X:", pstLayer->usDataX);
        DebugMessageGOSD("  W:", pstLayer->usDataWidth);
        DebugMessageGOSD("  FullW:", pstLayer->stSurface.usFullWidth);
        return _FALSE;
    }
    if(pstLayer->usDataY > _GOSD_SE_HEIGHT_LIMITATION - 1)
    {
        DebugMessageGOSD("Layer Error: Y > 8191", pstLayer->usDataY);
        return _FALSE;
    }
    if(pstLayer->usDataY + pstLayer->usDataHeight > pstLayer->stSurface.usFullHeight)
    {
        DebugMessageGOSD("Layer Error: Y+H > FullH", 0);
        DebugMessageGOSD("  Y:", pstLayer->usDataY);
        DebugMessageGOSD("  H:", pstLayer->usDataHeight);
        DebugMessageGOSD("  FullH:", pstLayer->stSurface.usFullHeight);
        return _FALSE;
    }

    // Check Address & Pitch
    if((pstLayer->stSurface.ulAddress % 16) != 0) // address must 16-bytes alignment
    {
        DebugMessageGOSD("Error: Layer Baddr not align 16bytes", pstLayer->stSurface.ulAddress);
        return _FALSE;
    }
    if(pstLayer->stSurface.usPitch != pstLayer->stSurface.usFullWidth * ucBpp)
    {
        DebugMessageGOSD("Layer Error: Pitch =", pstLayer->stSurface.usPitch);
        return _FALSE;
    }
    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstLayer->stSurface.enumFormat))
    {
        if((pstLayer->stSurface.ulAddressC1 % 16) != 0) // address must 16-bytes alignment
        {
            DebugMessageGOSD("Layer Error: BaddrC1 not align 16bytes", pstLayer->stSurface.ulAddressC1);
            return _FALSE;
        }
        if(pstLayer->stSurface.usPitchC1 != pstLayer->stSurface.usFullWidth * ucBpp)
        {
            DebugMessageGOSD("Layer Error: PitchC1 = ", pstLayer->stSurface.usPitchC1);
            return _FALSE;
        }
        if((pstLayer->stSurface.usFullWidth % _GOSD_SE_AFBC_FULLW_ALIGN) != 0) // AFBC full width must 32pixel alignment
        {
            DebugMessageGOSD("Layer Error: AFBC full width not align 32pixel", pstLayer->stSurface.usFullWidth);
            return _FALSE;
        }
        if((pstLayer->stSurface.usFullHeight % _GOSD_SE_AFBC_FULLH_ALIGN) != 0) // AFBC full height must 8pixel alignment
        {
            DebugMessageGOSD("Layer Error: AFBC full height not align 8pixel", pstLayer->stSurface.usFullHeight);
            return _FALSE;
        }
        if(pstLayer->stSurface.ulAddressC1 != (pstLayer->stSurface.ulAddress + ((DWORD)pstLayer->stSurface.usFullWidth / 32 * pstLayer->stSurface.usFullHeight / 8 * 16))) // AFBC C1 address constraint
        {
            DebugMessageGOSD("Layer Error: AFBC AddressC1", pstLayer->stSurface.ulAddressC1);
            DebugMessageGOSD("  Address", pstLayer->stSurface.ulAddress);
            DebugMessageGOSD("  FullWidth", pstLayer->stSurface.usFullWidth);
            DebugMessageGOSD("  FullHeight", pstLayer->stSurface.usFullHeight);
            return _FALSE;
        }
    }

    // Check support BigEndian format
    if(_FALSE == pstLayer->stSurface.bBigEndian)
    {
        switch(pstLayer->stSurface.enumFormat)
        {
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB8888:
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB4444:
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB1555:
            case _GOSD_SEINFO_COLOR_FORMAT_RGB565:
                break;
            default:
                DebugMessageGOSD("Layer Error: Not support BigEndian format", pstLayer->stSurface.enumFormat);
                return _FALSE;
        }
    }

    // Check input constant color format
    if((pstLayer->bSelectConst) && ((pstLayer->enumLayerType == _GOSD_SEINFO_LAYERTYPE_SRC1) || (pstLayer->enumLayerType == _GOSD_SEINFO_LAYERTYPE_SRC2)))
    {
        switch(pstLayer->stSurface.enumFormat)
        {
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB8888:
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB4444:
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB1555:
            case _GOSD_SEINFO_COLOR_FORMAT_RGB888:
            case _GOSD_SEINFO_COLOR_FORMAT_RGB565:
                break;
            default:
                DebugMessageGOSD("Layer Error: Not support Input constant color format", pstLayer->stSurface.enumFormat);
                return _FALSE;
        }
    }

    // Check support ARGB order format
    if(_GOSD_SEINFO_ARGB_ORDER_ARGB != pstLayer->stSurface.enumArgbOrder)
    {
        // ARGB_order is only supported ARGB8888, ARGB4444, ARGB1555, AFBC_4U8, AFBC_3U8
        switch(pstLayer->stSurface.enumFormat)
        {
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB8888:
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB4444:
            case _GOSD_SEINFO_COLOR_FORMAT_ARGB1555:
            case _GOSD_SEINFO_COLOR_FORMAT_INDEX8:
                break;
#if(_HW_GOSD_AFBC_FORMAT_SUPPORT == _ON)
            case _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8U8:
                break;
            case _GOSD_SEINFO_COLOR_FORMAT_AFBC_U8U8U8:
                // AFBC_3U8 is only supported ARGB, ARBG, ABGR, ABRG, AGRB, AGBR
                switch(pstLayer->stSurface.enumArgbOrder)
                {
                    case _GOSD_SEINFO_ARGB_ORDER_ARGB:
                    case _GOSD_SEINFO_ARGB_ORDER_ARBG:
                    case _GOSD_SEINFO_ARGB_ORDER_ABGR:
                    case _GOSD_SEINFO_ARGB_ORDER_ABRG:
                    case _GOSD_SEINFO_ARGB_ORDER_AGRB:
                    case _GOSD_SEINFO_ARGB_ORDER_AGBR:
                        break;
                    default:
                        DebugMessageGOSD("Layer Error: Not support ARGB_Order", pstLayer->stSurface.enumArgbOrder);
                        DebugMessageGOSD("  Format", pstLayer->stSurface.enumFormat);
                        return _FALSE;
                }
                break;
#endif
            default:
                DebugMessageGOSD("Layer Error: Format only support ARGB Order", pstLayer->stSurface.enumFormat);
                DebugMessageGOSD("  Order", pstLayer->stSurface.enumArgbOrder);
                return _FALSE;
        }
    }

    if(pstLayer->enumRsltMirrorModeSel != _GOSD_SEINFO_MIRROR_NONE)
    {
        // Mirror is only supported when rslt layer
        if(pstLayer->enumLayerType != _GOSD_SEINFO_LAYERTYPE_RSLT)
        {
            DebugMessageGOSD("Layer Error: Not support mirror LayerType", pstLayer->enumLayerType);
            return _FALSE;
        }
        // Rslt_Mirror is only supported when format is ARGB8888
        if(pstLayer->stSurface.enumFormat != _GOSD_SEINFO_COLOR_FORMAT_ARGB8888)
        {
            DebugMessageGOSD("Layer Error: Not support mirror format", pstLayer->stSurface.enumFormat);
            return _FALSE;
        }
    }

    if(pstLayer->enumRsltRotateModeSel != _OSD_ROTATE_DEGREE_0)
    {
        // Rotate is only supported when rslt layer
        if(pstLayer->enumLayerType != _GOSD_SEINFO_LAYERTYPE_RSLT)
        {
            DebugMessageGOSD("Layer Error: Not support rotate LayerType", pstLayer->enumLayerType);
            return _FALSE;
        }
        // Rslt_Rotate is only supported when format is ARGB8888
        if(pstLayer->stSurface.enumFormat != _GOSD_SEINFO_COLOR_FORMAT_ARGB8888)
        {
            DebugMessageGOSD("Layer Error: Not support rotate format", pstLayer->stSurface.enumFormat);
            return _FALSE;
        }
    }
    // Rslt_Rotate & Rslt_Mirror can't both turn-on in one operation
    if((pstLayer->enumRsltMirrorModeSel != _GOSD_SEINFO_MIRROR_NONE) && (pstLayer->enumRsltRotateModeSel != _OSD_ROTATE_DEGREE_0))
    {
        DebugMessageGOSD("Layer Error: Mirror and Rotate cant both turn-on", 0);
        return _FALSE;
    }
    // Rslt_Rotate | Rslt_Mirror turn-on
    if((pstLayer->enumRsltMirrorModeSel != _GOSD_SEINFO_MIRROR_NONE) || (pstLayer->enumRsltRotateModeSel != _OSD_ROTATE_DEGREE_0))
    {
        // output_w and output_h must be 16 Pixels alignment
        if((pstLayer->usDataWidth % _GOSD_SE_ROTATE_MIRROR_OUTW_ALIGN != 0) || (pstLayer->usDataHeight % _GOSD_SE_ROTATE_MIRROR_OUTH_ALIGN != 0))
        {
            DebugMessageGOSD("Layer Error: Mirror/Rotate turn-on", 0);
            DebugMessageGOSD("  rslt_W not 16 Pixels alignment", pstLayer->usDataWidth);
            DebugMessageGOSD("  rslt_H not 16 Pixels alignment", pstLayer->usDataHeight);
            return _FALSE;
        }
        // output_w and output_h must be equal
        if(pstLayer->usDataWidth != pstLayer->usDataHeight)
        {
            DebugMessageGOSD("Layer Error: Mirror/Rotate turn-on, rslt_W = rslt_H", 0);
            DebugMessageGOSD("  rslt_W", pstLayer->usDataWidth);
            DebugMessageGOSD("  rslt_H", pstLayer->usDataHeight);
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : check HW&SW limitations of Format Convert
// Input Value  : *pstSrc1Layer : src1 layer info
//                *pstRsltLayer : rslt layer info
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerGosdSeFormatConversionGuard(StructGosdSeLayerInfo *pstSrc1Layer, StructGosdSeLayerInfo *pstRsltLayer)
{
    // AFBC format must 32x16 pixel alignment
    if(ScalerGosdSeGetFormatType(pstSrc1Layer->stSurface.enumFormat) == _GOSD_SEINFO_AFBC_FORMAT)
    {
        if(ScalerGosdSeAfbcGuard(pstSrc1Layer) == _FALSE)
        {
            DebugMessageGOSD("Fcv Error: src1 AFBC but not align 32x16pixel", 0);
            return _FALSE;
        }
    }
    if(ScalerGosdSeGetFormatType(pstRsltLayer->stSurface.enumFormat) == _GOSD_SEINFO_AFBC_FORMAT)
    {
        if(ScalerGosdSeAfbcGuard(pstRsltLayer) == _FALSE)
        {
            DebugMessageGOSD("Fcv Error: rslt AFBC but not align 32x16pixel", 0);
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : check HW&SW limitations of BitBlit
// Input Value  : *pstSrc1Layer : src1 layer info
//                *pstSrc2Layer : src2 layer info
//                *pstRsltLayer : rslt layer info
//                *pstBitBlitInfo: BitBlit info
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerGosdSeBitBlitGuard(StructGosdSeLayerInfo *pstSrc1Layer, StructGosdSeLayerInfo *pstSrc2Layer, StructGosdSeLayerInfo *pstRsltLayer, StructGosdSeBitBlitInfo *pstBitBlitInfo)
{
    if(pstBitBlitInfo->enumSrc2LinearGradientModeSel != _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_NONE)
    {
        if(pstSrc2Layer->stSurface.enumFormat != _GOSD_SEINFO_COLOR_FORMAT_ARGB8888)
        {
            DebugMessageGOSD("BitBlit Error: Linear_Gradient not support format", pstSrc2Layer->stSurface.enumFormat);
            return _FALSE;
        }
        if(pstSrc2Layer->stSurface.enumArgbOrder != _GOSD_SEINFO_ARGB_ORDER_ARGB)
        {
            DebugMessageGOSD("BitBlit Error: Linear_Gradient not support Order", pstSrc2Layer->stSurface.enumArgbOrder);
            return _FALSE;
        }
    }

    // if src1 & src2 both index8, ClutAddress must be the same
    if((pstSrc1Layer->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8) &&
       (pstSrc2Layer->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8))
    {
        if(pstSrc1Layer->stSurface.ulClutAddress != pstSrc2Layer->stSurface.ulClutAddress)
        {
            DebugMessageGOSD("BitBlit Error: src1, src2 both index8, but ClutAddress different", 0);
            return _FALSE;
        }
    }

    // if layer_control = 0, AFBC format must 32x16 pixel alignment
    if(pstBitBlitInfo->bLayerControl == _FALSE)
    {
        if(ScalerGosdSeGetFormatType(pstSrc1Layer->stSurface.enumFormat) == _GOSD_SEINFO_AFBC_FORMAT)
        {
            if(ScalerGosdSeAfbcGuard(pstSrc1Layer) == _FALSE)
            {
                DebugMessageGOSD("BitBlit Error: src1 AFBC but not align 32x16pixel", 0);
                return _FALSE;
            }
        }
        if(ScalerGosdSeGetFormatType(pstSrc2Layer->stSurface.enumFormat) == _GOSD_SEINFO_AFBC_FORMAT)
        {
            if(ScalerGosdSeAfbcGuard(pstSrc2Layer) == _FALSE)
            {
                DebugMessageGOSD("BitBlit Error: src2 AFBC but not align 32x16pixel", 0);
                return _FALSE;
            }
        }
        if(ScalerGosdSeGetFormatType(pstRsltLayer->stSurface.enumFormat) == _GOSD_SEINFO_AFBC_FORMAT)
        {
            if(ScalerGosdSeAfbcGuard(pstRsltLayer) == _FALSE)
            {
                DebugMessageGOSD("BitBlit Error: rslt AFBC but not align 32x16pixel", 0);
                return _FALSE;
            }
        }
    }

    // if layer_control = 1, rslt_layer = src1_layer
    if(pstBitBlitInfo->bLayerControl == _ENABLE)
    {
        if(pstSrc1Layer->stSurface.enumFormat != pstRsltLayer->stSurface.enumFormat)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 Format", pstSrc1Layer->stSurface.enumFormat);
            DebugMessageGOSD("  Rslt Format", pstRsltLayer->stSurface.enumFormat);
            return _FALSE;
        }
        if(pstSrc1Layer->stSurface.ulAddress != pstRsltLayer->stSurface.ulAddress)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 Address", pstSrc1Layer->stSurface.ulAddress);
            DebugMessageGOSD("  Rslt Address", pstRsltLayer->stSurface.ulAddress);
            return _FALSE;
        }
        if(pstSrc1Layer->stSurface.usPitch != pstRsltLayer->stSurface.usPitch)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 Pitch", pstSrc1Layer->stSurface.usPitch);
            DebugMessageGOSD("  Rslt Pitch", pstRsltLayer->stSurface.usPitch);
            return _FALSE;
        }
        if(ScalerGosdSeGetFormatType(pstSrc1Layer->stSurface.enumFormat) == _GOSD_SEINFO_AFBC_FORMAT)
        {
            if(pstSrc1Layer->stSurface.ulAddressC1 != pstRsltLayer->stSurface.ulAddressC1)
            {
                DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
                DebugMessageGOSD("  Src1 AddressC1", pstSrc1Layer->stSurface.ulAddressC1);
                DebugMessageGOSD("  Rslt AddressC1", pstRsltLayer->stSurface.ulAddressC1);
                return _FALSE;
            }
            if(pstSrc1Layer->stSurface.usPitchC1 != pstRsltLayer->stSurface.usPitchC1)
            {
                DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
                DebugMessageGOSD("  Src1 PitchC1", pstSrc1Layer->stSurface.usPitchC1);
                DebugMessageGOSD("  Rslt PitchC1", pstRsltLayer->stSurface.usPitchC1);
                return _FALSE;
            }
            if(pstSrc1Layer->stSurface.bAfbcYuvTrans != pstRsltLayer->stSurface.bAfbcYuvTrans)
            {
                DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
                DebugMessageGOSD("  Src1 AfbcYuvTrans", pstSrc1Layer->stSurface.bAfbcYuvTrans);
                DebugMessageGOSD("  Rslt AfbcYuvTrans", pstRsltLayer->stSurface.bAfbcYuvTrans);
                return _FALSE;
            }
        }
        if(pstSrc1Layer->stSurface.bBigEndian != pstRsltLayer->stSurface.bBigEndian)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 BigEndian", pstSrc1Layer->stSurface.bBigEndian);
            DebugMessageGOSD("  Rslt BigEndian", pstRsltLayer->stSurface.bBigEndian);
            return _FALSE;
        }
        if(pstSrc1Layer->stSurface.enumArgbOrder != pstRsltLayer->stSurface.enumArgbOrder)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 ArgbOrder", pstSrc1Layer->stSurface.enumArgbOrder);
            DebugMessageGOSD("  Rslt ArgbOrder", pstRsltLayer->stSurface.enumArgbOrder);
            return _FALSE;
        }
        if(pstSrc1Layer->usDataX != pstRsltLayer->usDataX)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 X", pstSrc1Layer->usDataX);
            DebugMessageGOSD("  Rslt X", pstRsltLayer->usDataX);
            return _FALSE;
        }
        if(pstSrc1Layer->usDataY != pstRsltLayer->usDataY)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 Y", pstSrc1Layer->usDataY);
            DebugMessageGOSD("  Rslt Y", pstRsltLayer->usDataY);
            return _FALSE;
        }
        if(pstSrc1Layer->usDataWidth != pstRsltLayer->usDataWidth)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 X", pstSrc1Layer->usDataWidth);
            DebugMessageGOSD("  Rslt X", pstRsltLayer->usDataWidth);
            return _FALSE;
        }
        if(pstSrc1Layer->usDataHeight != pstRsltLayer->usDataHeight)
        {
            DebugMessageGOSD("BitBlit Error: layer_ctrl=1 but src1 != rslt", 0);
            DebugMessageGOSD("  Src1 X", pstSrc1Layer->usDataHeight);
            DebugMessageGOSD("  Rslt X", pstRsltLayer->usDataHeight);
            return _FALSE;
        }
    }

    if(pstBitBlitInfo->enumModeSel == _GOSD_SEINFO_BLENDING_ALPHA)
    {
        if(pstBitBlitInfo->enumSrcAlphaModeSel > _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_SRC)
        {
            DebugMessageGOSD("BitBlit Error: Not support SrcAlphaModeSel", pstBitBlitInfo->enumSrcAlphaModeSel);
            return _FALSE;
        }
        if(pstBitBlitInfo->enumDstAlphaModeSel > _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_SRC)
        {
            DebugMessageGOSD("BitBlit Error: Not support DstAlphaModeSel", pstBitBlitInfo->enumSrcAlphaModeSel);
            return _FALSE;
        }
    }
    else if(pstBitBlitInfo->enumModeSel == _GOSD_SEINFO_BLENDING_FB)
    {
        if(pstBitBlitInfo->enumSrcAlphaModeSel > _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONSTANT_1)
        {
            DebugMessageGOSD("BitBlit Error: Not support SrcAlphaModeSel", pstBitBlitInfo->enumSrcAlphaModeSel);
            return _FALSE;
        }
        if(pstBitBlitInfo->enumDstAlphaModeSel > _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONSTANT_1)
        {
            DebugMessageGOSD("BitBlit Error: Not support DstAlphaModeSel", pstBitBlitInfo->enumSrcAlphaModeSel);
            return _FALSE;
        }
        if(pstBitBlitInfo->enumSrcClrModeSel > _GOSD_SEINFO_BLENDING_DFB_CLR_MIN_SRCALPHA_1_DESTALPHA)
        {
            DebugMessageGOSD("BitBlit Error: Not support SrcClrModeSel", pstBitBlitInfo->enumSrcClrModeSel);
            return _FALSE;
        }
        if(pstBitBlitInfo->enumDstClrModeSel > _GOSD_SEINFO_BLENDING_DFB_CLR_MIN_SRCALPHA_1_DESTALPHA)
        {
            DebugMessageGOSD("BitBlit Error: Not support DstClrModeSel", pstBitBlitInfo->enumDstClrModeSel);
            return _FALSE;
        }
    }


    return _TRUE;
}

//--------------------------------------------------
// Description  : check HW&SW limitations of Stretch
// Input Value  : *pstSrc1Layer : src1 layer info
//                *pstRsltLayer : rslt layer info
// Output Value : _TRUE/_FALSE
//--------------------------------------------------
bit ScalerGosdSeStrecthGuard(StructGosdSeLayerInfo *pstSrcLayer, StructGosdSeLayerInfo *pstRsltLayer, StructGosdSeStretchInfo *pstStretchInfo)
{
    DWORD ulFactor = 0;

    if(pstRsltLayer->usDataWidth < _GOSD_SE_MIN_STRETCH_OUT_WIDTH)
    {
        DebugMessageGOSD("Stretch Error: Rslt OutW < 16", pstRsltLayer->usDataWidth);
        return _FALSE;
    }

    ulFactor = GET_DWORD_MUL_DIV((1UL << 14), pstSrcLayer->usDataWidth, pstRsltLayer->usDataWidth);
    // Factor must between 0x20000 ~ 0x00800 (0.125x ~ 8x)
    if(ulFactor < 0x00800)
    {
        DebugMessageGOSD("Stretch Error: H Stretch Rate > 8x", 0);
        DebugMessageGOSD("  Src Width:", pstSrcLayer->usDataWidth);
        DebugMessageGOSD("  Rslt Width:", pstRsltLayer->usDataWidth);
        return _FALSE;
    }
    if(ulFactor > 0x20000)
    {
        DebugMessageGOSD("Stretch Error: H Stretch Rate < 0.125x", 0);
        DebugMessageGOSD("  Src Width:", pstSrcLayer->usDataWidth);
        DebugMessageGOSD("  Rslt Width:", pstRsltLayer->usDataWidth);
        return _FALSE;
    }

    ulFactor = GET_DWORD_MUL_DIV((1UL << 14), pstSrcLayer->usDataHeight, pstRsltLayer->usDataHeight);
    // Factor must between 0x20000 ~ 0x00800 (0.125x ~ 8x)
    if(ulFactor < 0x00800)
    {
        DebugMessageGOSD("Stretch Error: V Stretch Rate > 8x", 0);
        DebugMessageGOSD("  Src Height:", pstSrcLayer->usDataHeight);
        DebugMessageGOSD("  Rslt Height:", pstRsltLayer->usDataHeight);
        return _FALSE;
    }
    if(ulFactor > 0x20000)
    {
        DebugMessageGOSD("Stretch Error: V Stretch Rate < 0.125x", 0);
        DebugMessageGOSD("  Src Height:", pstSrcLayer->usDataHeight);
        DebugMessageGOSD("  Rslt Height:", pstRsltLayer->usDataHeight);
        return _FALSE;
    }

    if(pstSrcLayer->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        if(pstStretchInfo->enumAlgoSel != _GOSD_SEINFO_STRETCH_REPEATE_DROP)
        {
            DebugMessageGOSD("Stretch Error: Src INDEX8 but stretch algo not repeate/drop", 0);
            return _FALSE;
        }
    }

    return _TRUE;
}

//--------------------------------------------------
// Description  : Calculate Stretch Factor
// Input Value  : Input Size
//                Output Size
// Output Value : Stretch Factor
//--------------------------------------------------
DWORD ScalerGosdSeCalculateStretchFactor(WORD usInputSize, WORD usOutputSize)
{
    return GET_DWORD_MUL_DIV((1UL << 14), usInputSize, usOutputSize); // (In/Out) * 2^14
}

//--------------------------------------------------
// Description  : Calculate Stretch Initial Phase
// Input Value  : Input Size
//                Output Size
// Output Value : Stretch Initial Phase
//--------------------------------------------------
DWORD ScalerGosdSeCalculateStretchPhase(WORD usInputSize, WORD usOutputSize)
{
    if(usInputSize > usOutputSize)
    {
        return GET_DWORD_MUL_DIV((1UL << 3), usInputSize, usOutputSize) - (1UL << (3)); // (In/Out - 1) / 2 * 2^4
    }
    else
    {
        return (1UL << (6)) | ((1UL << (6)) - ((1UL << (3)) - GET_DWORD_MUL_DIV((1UL << 3), usInputSize, usOutputSize))); // _BIT6 | 2^6 - (1 - In/Out) / 2 * 2^4
    }
}

//--------------------------------------------------
// Description  : write cmd to DDR, and update related registers
// Input Value  : *pucSeCmdBuffer : CMD
//                ulSeCmdLength : size of CMD (Byte)
// Output Value : _SUCCESS / _FAIL
//--------------------------------------------------
bit ScalerGosdSeWriteCmd(BYTE *pucSeCmdBuffer, DWORD ulSeCmdLength)
{
    if(ScalerGosdSePollingDone(4) == _FALSE)
    {
        DebugMessageGOSD("Se Busy!", 0);
        return _FAIL;
    }

    if(0 != ulSeCmdLength % (sizeof(DWORD) * 4))
    {
        DebugMessageGOSD("Se cmd length not 16 byte alignment!", 0);
        return _FAIL;
    }

    DWORD ulBYTECounter = 0;
    DWORD ulWritePtr = 0;
    DWORD ulWritePtrReg = 0;
    DWORD ulLimitPtrReg = 0;

    // HW limitation: Write_Ptr must not equal to Limit_Ptr
    // -16: The min length of a CMD is 16Byte
    ulLimitPtrReg = GET_DDR_32BIT_ADDR(Scaler32GetDWord(PB00480_20_CMDLMT_Q1) - 16);
    ulWritePtrReg = GET_DDR_32BIT_ADDR(Scaler32GetDWord(PB00480_28_CMDWPTR_Q1));
    ulWritePtr = ulWritePtrReg;

    if(ulLimitPtrReg < ulWritePtrReg + ulSeCmdLength)
    {
        DebugMessageGOSD("Se Cmd out of range!", 0);
        return _FAIL;
    }

    for(ulBYTECounter = 0; ulBYTECounter < ulSeCmdLength; ulBYTECounter += sizeof(DWORD))
    {
        Scaler32SetDWord(ulWritePtr, GOSDSE_8TO32_BIG(&pucSeCmdBuffer[ulBYTECounter]));
        ulWritePtr += sizeof(DWORD);
    }
    ScalerCpuHalCleanDataCache();

    Scaler32SetDWord(PB00480_28_CMDWPTR_Q1, GET_PHY_32BIT_DDR_ADDR(ulWritePtr));
    return _SUCCESS;
}

//--------------------------------------------------
// Description  : polling SE idle
// Input Value  : ulWaitTimeout --> wait timeout (unit: ms)
// Output Value : _TRUE / _FALSE
//--------------------------------------------------
bit ScalerGosdSePollingDone(DWORD ulWaitTimeout)
{
    DWORD ulTimeElapsed = 0;
    WORD usPreviousTime = g_usTimerCounter;

    do
    {
        if(g_bGosdSeExecuting == _FALSE)
        {
            return _TRUE;
        }

        if(usPreviousTime != g_usTimerCounter)
        {
            ulTimeElapsed++;
            usPreviousTime = g_usTimerCounter;
        }
    }
    while(ulTimeElapsed <= ulWaitTimeout);

    return _FALSE;
}

//--------------------------------------------------
// Description  : Se done interrupt handler
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdSeDone_Handler(void)
{
    DWORD ulIntStatus = Scaler32GetBit(PB00480_10_INTS_Q1, _BIT3);
    DWORD ulIntEnable = Scaler32GetBit(PB00480_14_INTE_Q1, _BIT3);

    // check com_empty = true
    if((ulIntStatus != 0) && (ulIntEnable != 0))
    {
        // Disable Se interrupt
        Scaler32SetDWord(PB00480_14_INTE_Q1, 0);

        g_bGosdSeExecuting = _FALSE;

        // reset surface status & drawing SurfaceId list
        for(BYTE ucIdx = 0; ucIdx < GET_TABLE_ELEMENT_NUM(g_pulGosdSeExecutingSurfaceId); ucIdx++)
        {
            if(g_pulGosdSeExecutingSurfaceId[ucIdx] < _GOSD_SURFACE_NUMBER)
            {
                if(GOSD_GET_SURFACE_STATUS(g_pulGosdSeExecutingSurfaceId[ucIdx]) != _GOSD_SURFACE_DISPOSD_SHOWING)
                {
                    GOSD_SET_SURFACE_STATUS(g_pulGosdSeExecutingSurfaceId[ucIdx], _GOSD_SURFACE_IDLE);
                }

                g_pulGosdSeExecutingSurfaceId[ucIdx] = _GOSD_SURFACE_NUMBER;
            }
        }

        // reset cmd buffer registers
        Scaler32SetDWord(PB00480_1C_CMDBASE_Q1, g_ulGosdSeCmdBaseAddress);
        Scaler32SetDWord(PB00480_20_CMDLMT_Q1, g_ulGosdSeCmdBaseAddress + g_ulGosdSeCmdLength);
        Scaler32SetDWord(PB00480_24_CMDRPTR_Q1, g_ulGosdSeCmdBaseAddress);
        Scaler32SetDWord(PB00480_28_CMDWPTR_Q1, g_ulGosdSeCmdBaseAddress);
        // write 1 clear com_empty INTS
        Scaler32SetBit(PB00480_10_INTS_Q1, ~(_BIT16 | _BIT3 | _BIT2), _BIT3);

        // Enable Se interrupt
        Scaler32SetBit(PB00480_14_INTE_Q1, ~(_BIT3), _BIT3);
    }
}

//--------------------------------------------------
// Description  : set SE Fetch Clut cmd
// Input Value  :ulClutAddress
// Output Value : EnumGosdSeOperationResult : set operation result
//--------------------------------------------------
EnumGosdSyncCmdFeedBack ScalerGosdSeFetchClut(DWORD ulClutAddress)
{
    if(ulClutAddress % 16 != 0)
    {
        DebugMessageGOSD("Error: Clut Addr not align 16bytes", ulClutAddress);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    UnionGosdSeCmdFetchClut unSeCmd = {0};

    unSeCmd.stSeCmdFetchClut.stDWordClut.b1Force = _ENABLE;
    unSeCmd.stSeCmdFetchClut.stDWordClut.b2Entry = 0x2; // fixed 256 color
    unSeCmd.stSeCmdFetchClut.stDWordClut.b4OpCode = 0x02; // fixed

    unSeCmd.stSeCmdFetchClut.stDWordSaddr.ulSaddr = ulClutAddress;

    unSeCmd.stSeCmdFetchClut.stDWordNop1.ulNop = _GOSD_SEINFO_OPCODE_NOP;
    unSeCmd.stSeCmdFetchClut.stDWordNop2.ulNop = _GOSD_SEINFO_OPCODE_NOP;

    if(ScalerGosdSeWriteCmd(unSeCmd.pucSeCmdBuffer, sizeof(StructGosdSeCmdFetchClut)) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    return _GOSD_SYNC_FEEDBACK_SUCCESS;
}

//--------------------------------------------------
// Description  : set SE Format Convert cmd
// Input Value  : *pstSrc1LayerInfo : src1 layer info
//           *pstRsltLayerInfo : rslt layer info
// Output Value : EnumGosdSeOperationResult : set operation result
//--------------------------------------------------
EnumGosdSyncCmdFeedBack ScalerGosdSeFormatConversion(StructGosdSeLayerInfo *pstSrc1LayerInfo, StructGosdSeLayerInfo *pstRsltLayerInfo)
{
    if(_TRUE == g_bGosdSeExecuting)
    {
        DebugMessageGOSD("SE is not idle", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    if(_FALSE == ScalerGosdSeLayerGuard(pstSrc1LayerInfo))
    {
        DebugMessageGOSD("Src1 Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstRsltLayerInfo))
    {
        DebugMessageGOSD("Rslt Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeFormatConversionGuard(pstSrc1LayerInfo, pstRsltLayerInfo))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    // Fetch Clut
    if(pstSrc1LayerInfo->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        EnumGosdSyncCmdFeedBack enumReturn = ScalerGosdSeFetchClut(pstSrc1LayerInfo->stSurface.ulClutAddress);
        if(enumReturn != _GOSD_SYNC_FEEDBACK_SUCCESS)
        {
            return enumReturn;
        }
    }

    UnionGosdSeCmdExtfcvFcv unSeCmd = {0};
    DWORD ulRegValue = 0;

    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdFcv.pstDWordBaddr[0]), &(unSeCmd.stSeCmdFcv.pstDWordPitch[0]), 0, pstSrc1LayerInfo->stSurface.ulAddress, pstSrc1LayerInfo->stSurface.usPitch);
    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdFcv.pstDWordBaddr[1]), &(unSeCmd.stSeCmdFcv.pstDWordPitch[1]), 1, pstRsltLayerInfo->stSurface.ulAddress, pstRsltLayerInfo->stSurface.usPitch);

    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstSrc1LayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdFcv.pstDWordBaddr[2]), &(unSeCmd.stSeCmdFcv.pstDWordPitch[2]), 2, pstSrc1LayerInfo->stSurface.ulAddressC1, pstSrc1LayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdFcv.pstDWordBaddr[2].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdFcv.pstDWordBaddr[2].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdFcv.pstDWordPitch[2].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdFcv.pstDWordPitch[2].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstRsltLayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdFcv.pstDWordBaddr[3]), &(unSeCmd.stSeCmdFcv.pstDWordPitch[3]), 3, pstRsltLayerInfo->stSurface.ulAddressC1, pstRsltLayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdFcv.pstDWordBaddr[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdFcv.pstDWordBaddr[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdFcv.pstDWordPitch[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdFcv.pstDWordPitch[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT12), ((DWORD)pstSrc1LayerInfo->stSurface.bBigEndian << 12)); // 0xB0048100[12]:src1_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT20), ((DWORD)pstRsltLayerInfo->stSurface.bBigEndian << 20)); // 0xB0048100[20]:rslt_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT24), _BIT24); // 0xB0048100[24]:rounding_en = 1
    ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdFcv.pstDWordReg[0]), PB00481_00_CLR_FMT_Q1, ulRegValue);

    if(_TRUE == pstSrc1LayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdFcv.pstDWordReg[1]), PB00481_14_SRC_COLOR_Q1, pstSrc1LayerInfo->ulConstClrValue);
    }
    else
    {
        unSeCmd.stSeCmdFcv.pstDWordReg[1].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdFcv.pstDWordReg[1].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_TRUE == pstRsltLayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdFcv.pstDWordReg[2]), PB00481_24_RSLT_ALPHA_Q1, pstRsltLayerInfo->ucConstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdFcv.pstDWordReg[2].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdFcv.pstDWordReg[2].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    unSeCmd.stSeCmdFcv.pstDWordReg[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
    unSeCmd.stSeCmdFcv.pstDWordReg[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;

    unSeCmd.stSeCmdFcv.stDWord1.b4Opcode = _GOSD_SEINFO_OPCODE_EXT_FMTFCV;
    unSeCmd.stSeCmdFcv.stDWord1.b5RsltFmt = pstRsltLayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdFcv.stDWord1.b1LayCtrl = _FALSE;
    unSeCmd.stSeCmdFcv.stDWord1.b1LayNum = _FALSE;
    unSeCmd.stSeCmdFcv.stDWord1.b2RsltSwapChroma = _FALSE;
    unSeCmd.stSeCmdFcv.stDWord1.b2Src1SwapChroma = _FALSE;
    unSeCmd.stSeCmdFcv.stDWord1.b1YUVItu = _FALSE;
    unSeCmd.stSeCmdFcv.stDWord1.b1RsltMatrix = _FALSE;
    unSeCmd.stSeCmdFcv.stDWord1.b1SelOutAlpha = pstRsltLayerInfo->bSelectConst;
    unSeCmd.stSeCmdFcv.stDWord1.b5RsltArgbOrder = pstRsltLayerInfo->stSurface.enumArgbOrder;
    unSeCmd.stSeCmdFcv.stDWord1.b1RsltAfbcYuvtrans = pstRsltLayerInfo->stSurface.bAfbcYuvTrans;
    unSeCmd.stSeCmdFcv.stDWord1.b5Src2ArgbOrder = _GOSD_SEINFO_ARGB_ORDER_ARGB;

    unSeCmd.stSeCmdFcv.stDWord2.b13RsltOutX = pstRsltLayerInfo->usDataX;
    unSeCmd.stSeCmdFcv.stDWord2.b13RsltOutY = pstRsltLayerInfo->usDataY;

    switch(pstRsltLayerInfo->enumRsltRotateModeSel)
    {
        default:
        case _OSD_ROTATE_DEGREE_0:
            unSeCmd.stSeCmdFcv.stDWord2.b2RsltRotate = 0;
            break;
        case _OSD_ROTATE_DEGREE_90:
            unSeCmd.stSeCmdFcv.stDWord2.b2RsltRotate = 3;
            break;
        case _OSD_ROTATE_DEGREE_180:
            unSeCmd.stSeCmdFcv.stDWord2.b2RsltRotate = 2;
            break;
        case _OSD_ROTATE_DEGREE_270:
            unSeCmd.stSeCmdFcv.stDWord2.b2RsltRotate = 1;
            break;
    }

    unSeCmd.stSeCmdFcv.stDWord2.b2RsltMirror = pstRsltLayerInfo->enumRsltMirrorModeSel;

    unSeCmd.stSeCmdFcv.stDWord3.b7RsltAddrIndexC2 = _FALSE; // no use
    unSeCmd.stSeCmdFcv.stDWord3.b7RsltAddrIndexC1 = 3; // fixed
    unSeCmd.stSeCmdFcv.stDWord3.b7RsltAddrIndex = 1; // fixed

    if(pstSrc1LayerInfo->usDataWidth == _GOSD_SE_WIDTH_LIMITATION)
    {
        // Width=8192, InptW should Set as 0
        unSeCmd.stSeCmdFcv.stDWord4.b13Src1InptW = 0;
    }
    else
    {
        unSeCmd.stSeCmdFcv.stDWord4.b13Src1InptW = pstSrc1LayerInfo->usDataWidth;
    }
    if(pstSrc1LayerInfo->usDataHeight == _GOSD_SE_HEIGHT_LIMITATION)
    {
        // Height=8192, InptH should Set as 0
        unSeCmd.stSeCmdFcv.stDWord4.b13Src1InptH = 0;
    }
    else
    {
        unSeCmd.stSeCmdFcv.stDWord4.b13Src1InptH = pstSrc1LayerInfo->usDataHeight;
    }
    unSeCmd.stSeCmdFcv.stDWord4.b5Src1Fmt = pstSrc1LayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdFcv.stDWord4.b1Src1Matrix = _FALSE;

    unSeCmd.stSeCmdFcv.stDWord5.b13Src1InptX = pstSrc1LayerInfo->usDataX;
    unSeCmd.stSeCmdFcv.stDWord5.b13Src1InptY = pstSrc1LayerInfo->usDataY;
    unSeCmd.stSeCmdFcv.stDWord5.b5Src1ArgbOrder = pstSrc1LayerInfo->stSurface.enumArgbOrder;
    unSeCmd.stSeCmdFcv.stDWord5.b1Src1FcvStch = _FALSE;

    unSeCmd.stSeCmdFcv.stDWord6.b7Src1AddrIndexC2 = _FALSE; // no sue
    unSeCmd.stSeCmdFcv.stDWord6.b7Src1AddrIndexC1 = 2; // fixed
    unSeCmd.stSeCmdFcv.stDWord6.b7Src1AddrIndex = 0; // fixed
    unSeCmd.stSeCmdFcv.stDWord6.b1Src1InputSel = pstSrc1LayerInfo->bSelectConst;
    unSeCmd.stSeCmdFcv.stDWord6.b1Src1AfbcYuvtrans = pstSrc1LayerInfo->stSurface.bAfbcYuvTrans;

    unSeCmd.stSeCmdFcv.stDWordNop7.ulNop = _GOSD_SEINFO_OPCODE_NOP;
    unSeCmd.stSeCmdFcv.stDWordNop8.ulNop = _GOSD_SEINFO_OPCODE_NOP;

    if(ScalerGosdSeWriteCmd(unSeCmd.pucSeCmdBuffer, sizeof(StructGosdSeCmdExtfcvFcv)) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    // set executing surface list
    g_pulGosdSeExecutingSurfaceId[0] = pstSrc1LayerInfo->stSurface.ulSurfaceId;
    g_pulGosdSeExecutingSurfaceId[2] = pstRsltLayerInfo->stSurface.ulSurfaceId;
    // set surface status
    if(GOSD_GET_SURFACE_STATUS(pstSrc1LayerInfo->stSurface.ulSurfaceId) != _GOSD_SURFACE_DISPOSD_SHOWING)
    {
        GOSD_SET_SURFACE_STATUS(pstSrc1LayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_READ);
    }
    GOSD_SET_SURFACE_STATUS(pstRsltLayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_WRITE);

    return ScalerGosdSeExecute();
}

//--------------------------------------------------
// Description  : set SE Format BitBlit cmd
// Input Value  : *pstSrc1LayerInfo : src1 layer info
//           *pstSrc2LayerInfo : src2 layer info
//           *pstRsltLayerInfo : rslt layer info
//           *pstBitBlitInfo : BitBlit setting
// Output Value : EnumGosdSeOperationResult : set operation result
//--------------------------------------------------
EnumGosdSyncCmdFeedBack ScalerGosdSeBitBlit(StructGosdSeLayerInfo *pstSrc1LayerInfo, StructGosdSeLayerInfo *pstSrc2LayerInfo, StructGosdSeLayerInfo *pstRsltLayerInfo, StructGosdSeBitBlitInfo *pstBitBlitInfo)
{
    if(_TRUE == g_bGosdSeExecuting)
    {
        DebugMessageGOSD("SE is not idle", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstSrc1LayerInfo))
    {
        DebugMessageGOSD("Src1 Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstSrc2LayerInfo))
    {
        DebugMessageGOSD("Src2 Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstRsltLayerInfo))
    {
        DebugMessageGOSD("Rslt Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeBitBlitGuard(pstSrc1LayerInfo, pstSrc2LayerInfo, pstRsltLayerInfo, pstBitBlitInfo))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    if(pstSrc1LayerInfo->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        EnumGosdSyncCmdFeedBack enumReturn = ScalerGosdSeFetchClut(pstSrc1LayerInfo->stSurface.ulClutAddress);
        if(enumReturn != _GOSD_SYNC_FEEDBACK_SUCCESS)
        {
            return enumReturn;
        }
    }
    else if(pstSrc2LayerInfo->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        EnumGosdSyncCmdFeedBack enumReturn = ScalerGosdSeFetchClut(pstSrc2LayerInfo->stSurface.ulClutAddress);
        if(enumReturn != _GOSD_SYNC_FEEDBACK_SUCCESS)
        {
            return enumReturn;
        }
    }

    UnionGosdSeCmdExtfcvBitBlit unSeCmd;
    DWORD ulRegValue = 0;

    memset((void *)&unSeCmd.stSeCmdBitBlit, 0, sizeof(StructGosdSeCmdExtfcvBitBlit));

    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordBaddr[0]), &(unSeCmd.stSeCmdBitBlit.pstDWordPitch[0]), 0, pstSrc1LayerInfo->stSurface.ulAddress, pstSrc1LayerInfo->stSurface.usPitch);
    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordBaddr[1]), &(unSeCmd.stSeCmdBitBlit.pstDWordPitch[1]), 1, pstSrc2LayerInfo->stSurface.ulAddress, pstSrc2LayerInfo->stSurface.usPitch);
    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordBaddr[2]), &(unSeCmd.stSeCmdBitBlit.pstDWordPitch[2]), 2, pstRsltLayerInfo->stSurface.ulAddress, pstRsltLayerInfo->stSurface.usPitch);

    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstSrc1LayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordBaddr[3]), &(unSeCmd.stSeCmdBitBlit.pstDWordPitch[3]), 3, pstSrc1LayerInfo->stSurface.ulAddressC1, pstSrc1LayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordBaddr[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordBaddr[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordPitch[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordPitch[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstSrc2LayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordBaddr[4]), &(unSeCmd.stSeCmdBitBlit.pstDWordPitch[4]), 4, pstSrc2LayerInfo->stSurface.ulAddressC1, pstSrc2LayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordBaddr[4].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordBaddr[4].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordPitch[4].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordPitch[4].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstRsltLayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordBaddr[5]), &(unSeCmd.stSeCmdBitBlit.pstDWordPitch[5]), 5, pstRsltLayerInfo->stSurface.ulAddressC1, pstRsltLayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordBaddr[5].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordBaddr[5].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordPitch[5].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordPitch[5].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT12), ((DWORD)pstSrc1LayerInfo->stSurface.bBigEndian << 12)); // 0xB0048100[12]:src1_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT16), ((DWORD)pstSrc1LayerInfo->stSurface.bBigEndian << 16)); // 0xB0048100[16]:src2_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT20), ((DWORD)pstRsltLayerInfo->stSurface.bBigEndian << 20)); // 0xB0048100[20]:rslt_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT24), _BIT24); // 0xB0048100[24]:rounding_en = 1
    ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[0]), PB00481_00_CLR_FMT_Q1, ulRegValue);

    if(_TRUE == pstSrc1LayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[1]), PB00481_14_SRC_COLOR_Q1, pstSrc1LayerInfo->ulConstClrValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[1].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[1].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_TRUE == pstSrc2LayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[2]), PB00481_14_SRC_COLOR_Q1, pstSrc2LayerInfo->ulConstClrValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[2].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[2].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_TRUE == pstRsltLayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[3]), PB00481_24_RSLT_ALPHA_Q1, pstRsltLayerInfo->ucConstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    // ColorKey Value setting
    if((pstBitBlitInfo->enumColorKeyModeSel == _GOSD_SEINFO_BLENDING_COLORKEY_SOURCE) || (pstBitBlitInfo->enumColorKeyModeSel == _GOSD_SEINFO_BLENDING_COLORKEY_BOTH))
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[4]), PB00481_04_COLOR_KEY_Q1, pstBitBlitInfo->ulSrcColorKeyValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[4].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[4].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if((pstBitBlitInfo->enumColorKeyModeSel == _GOSD_SEINFO_BLENDING_COLORKEY_DESTINATION) || (pstBitBlitInfo->enumColorKeyModeSel == _GOSD_SEINFO_BLENDING_COLORKEY_BOTH))
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[5]), PB00481_08_DST_COLOR_KEY_Q1, pstBitBlitInfo->ulDstColorKeyValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[5].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[5].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    // Src2 Alpha mode constant value setting
    if((pstBitBlitInfo->enumSrcAlphaModeSel == _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONST) || (pstBitBlitInfo->enumSrcAlphaModeSel == _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_CONST))
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[6]), PB00481_18_SRC_ALPHA_Q1, pstBitBlitInfo->ucSrcAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[6].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[6].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    // Src1 Alpha mode constant value setting
    if((pstBitBlitInfo->enumDstAlphaModeSel == _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONST) || (pstBitBlitInfo->enumDstAlphaModeSel == _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_CONST))
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[7]), PB00481_1C_DEST_ALPHA_Q1, pstBitBlitInfo->ucDstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[7].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[7].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    // DirectFB/OpenGL constant value setting
    if(pstBitBlitInfo->bEnableColorize == _TRUE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[8]), PB00481_14_SRC_COLOR_Q1, pstBitBlitInfo->ulConstClrValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[8].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[8].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(pstBitBlitInfo->bEnableSrcPremulcolor == _TRUE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[9]), PB00481_18_SRC_ALPHA_Q1, pstBitBlitInfo->ucConstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[9].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[9].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(pstBitBlitInfo->bEnableColorAlpha == _TRUE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[10]), PB00481_28_FB_COLORALPHA_Q1, pstBitBlitInfo->ucConstAlphaValueForBlendColor);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[10].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[10].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(pstBitBlitInfo->bEnableAlphaChannel == _TRUE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[11]), PB00481_18_SRC_ALPHA_Q1, pstBitBlitInfo->ucConstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[11].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[11].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    if(pstBitBlitInfo->enumSrc2LinearGradientModeSel != _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_NONE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[12]), PB00481_14_SRC_COLOR_Q1, pstBitBlitInfo->ulStartClrValue);
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[13]), PB00481_68_SRC_LG_2_Q1, (pstBitBlitInfo->usClrStepXGreen << 16) | (pstBitBlitInfo->usClrStepXRed));
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[14]), PB00481_6C_SRC_LG_3_Q1, (pstBitBlitInfo->usClrStepXBlue << 16) | (pstBitBlitInfo->usClrStepXAlpha));
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[15]), PB00481_70_SRC_LG_4_Q1, (pstBitBlitInfo->usClrStepYGreen << 16) | (pstBitBlitInfo->usClrStepYRed));
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[16]), PB00481_74_SRC_LG_5_Q1, (pstBitBlitInfo->usClrStepYBlue << 16) | (pstBitBlitInfo->usClrStepYAlpha));
        switch (pstBitBlitInfo->enumSrc2LinearGradientModeSel)
        {
            case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_XY:
                ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[17]), PB00481_78_SRC_LG_6_Q1, 0);
                break;
            case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_X:
                ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[17]), PB00481_78_SRC_LG_6_Q1, 2);
                break;
            case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_Y:
                ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdBitBlit.pstDWordReg[17]), PB00481_78_SRC_LG_6_Q1, 3);
                break;

            case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_NONE:
            default:
                break;
        }
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.pstDWordReg[12].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[12].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[13].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[13].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[14].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[14].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[15].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[15].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[16].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[16].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[17].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdBitBlit.pstDWordReg[17].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    unSeCmd.stSeCmdBitBlit.stDWord1.b4Opcode = _GOSD_SEINFO_OPCODE_EXT_FMTFCV;
    unSeCmd.stSeCmdBitBlit.stDWord1.b5RsltFmt = pstRsltLayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdBitBlit.stDWord1.b1LayCtrl = pstBitBlitInfo->bLayerControl;
    unSeCmd.stSeCmdBitBlit.stDWord1.b1LayNum = _TRUE;
    unSeCmd.stSeCmdBitBlit.stDWord1.b2RsltSwapChroma = _FALSE;
    unSeCmd.stSeCmdBitBlit.stDWord1.b2Src1SwapChroma = _FALSE;
    unSeCmd.stSeCmdBitBlit.stDWord1.b1YUVItu = _FALSE;
    unSeCmd.stSeCmdBitBlit.stDWord1.b1RsltMatrix = _FALSE;
    unSeCmd.stSeCmdBitBlit.stDWord1.b1SelOutAlpha = pstRsltLayerInfo->bSelectConst;
    unSeCmd.stSeCmdBitBlit.stDWord1.b5RsltArgbOrder = pstRsltLayerInfo->stSurface.enumArgbOrder;
    unSeCmd.stSeCmdBitBlit.stDWord1.b1RsltAfbcYuvtrans = pstRsltLayerInfo->stSurface.bAfbcYuvTrans;
    unSeCmd.stSeCmdBitBlit.stDWord1.b5Src2ArgbOrder = pstSrc2LayerInfo->stSurface.enumArgbOrder;

    unSeCmd.stSeCmdBitBlit.stDWord2.b13RsltOutX = pstRsltLayerInfo->usDataX;
    unSeCmd.stSeCmdBitBlit.stDWord2.b13RsltOutY = pstRsltLayerInfo->usDataY;
    unSeCmd.stSeCmdBitBlit.stDWord2.b2RsltRotate = pstRsltLayerInfo->enumRsltRotateModeSel;
    unSeCmd.stSeCmdBitBlit.stDWord2.b2RsltMirror = pstRsltLayerInfo->enumRsltMirrorModeSel;

    unSeCmd.stSeCmdBitBlit.stDWord3.b7RsltAddrIndexC2 = _FALSE;    // no use
    unSeCmd.stSeCmdBitBlit.stDWord3.b7RsltAddrIndexC1 = 5;    // fixed
    unSeCmd.stSeCmdBitBlit.stDWord3.b7RsltAddrIndex = 2;  // fixed

    if(pstSrc1LayerInfo->usDataWidth == _GOSD_SE_WIDTH_LIMITATION)
    {
        // Width=8192, InptW should Set as 0
        unSeCmd.stSeCmdBitBlit.stDWord4.b13Src1InptW = 0;
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.stDWord4.b13Src1InptW = pstSrc1LayerInfo->usDataWidth;
    }
    if(pstSrc1LayerInfo->usDataHeight == _GOSD_SE_HEIGHT_LIMITATION)
    {
        // Height=8192, InptH should Set as 0
        unSeCmd.stSeCmdBitBlit.stDWord4.b13Src1InptH = 0;
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.stDWord4.b13Src1InptH = pstSrc1LayerInfo->usDataHeight;
    }
    unSeCmd.stSeCmdBitBlit.stDWord4.b5Src1Fmt = pstSrc1LayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdBitBlit.stDWord4.b1Src1Matrix = _FALSE;

    unSeCmd.stSeCmdBitBlit.stDWord5.b13Src1InptX = pstSrc1LayerInfo->usDataX;
    unSeCmd.stSeCmdBitBlit.stDWord5.b13Src1InptY = pstSrc1LayerInfo->usDataY;
    unSeCmd.stSeCmdBitBlit.stDWord5.b5Src1ArgbOrder = pstSrc1LayerInfo->stSurface.enumArgbOrder;
    unSeCmd.stSeCmdBitBlit.stDWord5.b1Src1FcvStch = _FALSE;

    unSeCmd.stSeCmdBitBlit.stDWord6.b7Src1AddrIndexC2 = _FALSE;    // no sue
    unSeCmd.stSeCmdBitBlit.stDWord6.b7Src1AddrIndexC1 = 3;    // fixed
    unSeCmd.stSeCmdBitBlit.stDWord6.b7Src1AddrIndex = 0;  // fixed
    unSeCmd.stSeCmdBitBlit.stDWord6.b1Src1InputSel = pstSrc1LayerInfo->bSelectConst;
    unSeCmd.stSeCmdBitBlit.stDWord6.b1Src1AfbcYuvtrans = pstSrc1LayerInfo->stSurface.bAfbcYuvTrans;

    unSeCmd.stSeCmdBitBlit.stDWord7.b13Src2InptX = pstSrc2LayerInfo->usDataX;
    unSeCmd.stSeCmdBitBlit.stDWord7.b13Src2InptY = pstSrc2LayerInfo->usDataY;
    unSeCmd.stSeCmdBitBlit.stDWord7.b5Src2Fmt = pstSrc2LayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdBitBlit.stDWord7.b1Src2Matrix = _FALSE;

    unSeCmd.stSeCmdBitBlit.stDWord8.b7Src2AddrIndexC2 = _FALSE;    // no sue
    unSeCmd.stSeCmdBitBlit.stDWord8.b7Src2AddrIndexC1 = 4;    // fixed
    unSeCmd.stSeCmdBitBlit.stDWord8.b7Src2AddrIndex = 1;  // fixed
    unSeCmd.stSeCmdBitBlit.stDWord8.b1Src2InptSel = pstSrc2LayerInfo->bSelectConst;
    unSeCmd.stSeCmdBitBlit.stDWord8.b2Src2SwapChroma = _FALSE;
    unSeCmd.stSeCmdBitBlit.stDWord8.b1Src2AfbcYuvtrans = pstSrc2LayerInfo->stSurface.bAfbcYuvTrans;
    if(pstBitBlitInfo->enumSrc2LinearGradientModeSel == _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_NONE)
    {
        unSeCmd.stSeCmdBitBlit.stDWord8.b1Src2LinearGradient = _FALSE;
    }
    else
    {
        unSeCmd.stSeCmdBitBlit.stDWord8.b1Src2LinearGradient = _TRUE;
    }

    unSeCmd.stSeCmdBitBlit.stDWord9.b3LayerNumExt = _GOSD_SEINFO_OPERATION_MODE_BITBLIT;

    unSeCmd.stSeCmdBitBlit.stDWord10.b4BlendSel = pstBitBlitInfo->enumModeSel;
    switch(pstBitBlitInfo->enumModeSel)
    {
        case _GOSD_SEINFO_BLENDING_ROP:
            unSeCmd.stSeCmdBitBlit.stDWord10.b4RopCode = pstBitBlitInfo->enumRopCode;
            break;
        case _GOSD_SEINFO_BLENDING_ALPHA:
            unSeCmd.stSeCmdBitBlit.stDWord9.b3SourceAlphaSel = pstBitBlitInfo->enumSrcAlphaModeSel;
            unSeCmd.stSeCmdBitBlit.stDWord9.b3DestinationAlphaSel = pstBitBlitInfo->enumDstAlphaModeSel;

            unSeCmd.stSeCmdBitBlit.stDWord10.b2ColorKeySel = pstBitBlitInfo->enumColorKeyModeSel;
            break;
        case _GOSD_SEINFO_BLENDING_FB:
            unSeCmd.stSeCmdBitBlit.stDWord9.b3SourceAlphaSel = pstBitBlitInfo->enumSrcAlphaModeSel;
            unSeCmd.stSeCmdBitBlit.stDWord9.b3DestinationAlphaSel = pstBitBlitInfo->enumDstAlphaModeSel;

            unSeCmd.stSeCmdBitBlit.stDWord10.b2ColorKeySel = pstBitBlitInfo->enumColorKeyModeSel;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbDestinationPremultiply = pstBitBlitInfo->bEnableDstPremultiply;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbSourcePremulcolor = pstBitBlitInfo->bEnableSrcPremulcolor;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbSourcePremultiply = pstBitBlitInfo->bEnableSrcPremultiply;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbXor = pstBitBlitInfo->bEnableXor;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbColorize = pstBitBlitInfo->bEnableColorize;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbBlendColoralpha = pstBitBlitInfo->bEnableColorAlpha;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbBlendAlphachannel = pstBitBlitInfo->bEnableAlphaChannel;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbDemultiply = pstBitBlitInfo->bEnableDemultiply;
            unSeCmd.stSeCmdBitBlit.stDWord10.b4FbSourceColorBlendSel = pstBitBlitInfo->enumSrcClrModeSel;
            unSeCmd.stSeCmdBitBlit.stDWord10.b4FbDestinationColorBlendSel = pstBitBlitInfo->enumDstClrModeSel;
            unSeCmd.stSeCmdBitBlit.stDWord10.b4RopCode = pstBitBlitInfo->enumRopCode;
            break;
        case _GOSD_SEINFO_BLENDING_GL:
            unSeCmd.stSeCmdBitBlit.stDWord10.b2ColorKeySel = pstBitBlitInfo->enumColorKeyModeSel;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbDestinationPremultiply = pstBitBlitInfo->bEnableDstPremultiply;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbSourcePremulcolor = pstBitBlitInfo->bEnableSrcPremulcolor;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbSourcePremultiply = pstBitBlitInfo->bEnableSrcPremultiply;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbXor = pstBitBlitInfo->bEnableXor;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbColorize = pstBitBlitInfo->bEnableColorize;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbBlendColoralpha = pstBitBlitInfo->bEnableColorAlpha;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbBlendAlphachannel = pstBitBlitInfo->bEnableAlphaChannel;
            unSeCmd.stSeCmdBitBlit.stDWord10.b1FbDemultiply = pstBitBlitInfo->bEnableDemultiply;
            unSeCmd.stSeCmdBitBlit.stDWord10.b4RopCode = pstBitBlitInfo->enumRopCode;
#if(_HW_GOSD_SE_BITBLIT_OPENGL_CONSTANT_COEFF_SUPPORT == _ON)
            unSeCmd.stSeCmdBitBlit.stDWord11.b7GlDestinationColorSel = pstBitBlitInfo->ucGLDstClrIndex;
            unSeCmd.stSeCmdBitBlit.stDWord11.b7GlSourceColorSel = pstBitBlitInfo->ucGLSrcClrIndex;
            unSeCmd.stSeCmdBitBlit.stDWord11.b7GlDestinationAlphaSel = pstBitBlitInfo->ucGLDstAlphaIndex;
            unSeCmd.stSeCmdBitBlit.stDWord11.b7GlSourceAlphaSel = pstBitBlitInfo->ucGLSrcAlphaIndex;
#else
            unSeCmd.stSeCmdBitBlit.stDWord11.b6GlDestinationColorSel = pstBitBlitInfo->b6GLDstClrIndex;
            unSeCmd.stSeCmdBitBlit.stDWord11.b6GlSourceColorSel = pstBitBlitInfo->b6GLSrcClrIndex;
            unSeCmd.stSeCmdBitBlit.stDWord11.b6GlDestinationAlphaSel = pstBitBlitInfo->b6GLDstAlphaIndex;
            unSeCmd.stSeCmdBitBlit.stDWord11.b6GlSourceAlphaSel = pstBitBlitInfo->b6GLSrcAlphaIndex;
#endif
            break;
        default:
            break;
    }
    unSeCmd.stSeCmdBitBlit.stDWordNop12.ulNop = _GOSD_SEINFO_OPCODE_NOP;

    if(ScalerGosdSeWriteCmd(unSeCmd.pucSeCmdBuffer, sizeof(StructGosdSeCmdExtfcvBitBlit)) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    // set executing surface list
    g_pulGosdSeExecutingSurfaceId[0] = pstSrc1LayerInfo->stSurface.ulSurfaceId;
    g_pulGosdSeExecutingSurfaceId[1] = pstSrc2LayerInfo->stSurface.ulSurfaceId;
    g_pulGosdSeExecutingSurfaceId[2] = pstRsltLayerInfo->stSurface.ulSurfaceId;
    // set surface status
    if(GOSD_GET_SURFACE_STATUS(pstSrc1LayerInfo->stSurface.ulSurfaceId) != _GOSD_SURFACE_DISPOSD_SHOWING)
    {
        GOSD_SET_SURFACE_STATUS(pstSrc1LayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_READ);
    }
    if(GOSD_GET_SURFACE_STATUS(pstSrc2LayerInfo->stSurface.ulSurfaceId) != _GOSD_SURFACE_DISPOSD_SHOWING)
    {
        GOSD_SET_SURFACE_STATUS(pstSrc2LayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_READ);
    }
    GOSD_SET_SURFACE_STATUS(pstRsltLayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_WRITE);

    return ScalerGosdSeExecute();
}

//--------------------------------------------------
// Description  : set SE Stretch cmd
// Input Value  : *pstSrc1LayerInfo : src1 layer info
//                *pstRsltLayerInfo : rslt layer info
//                *pstStretchInfo : Stretch setting
// Output Value : EnumGosdSeOperationResult : set operation result
//--------------------------------------------------
EnumGosdSyncCmdFeedBack ScalerGosdSeStretch(StructGosdSeLayerInfo *pstSrc1LayerInfo, StructGosdSeLayerInfo *pstRsltLayerInfo, StructGosdSeStretchInfo *pstStretchInfo)
{
    if(_TRUE == g_bGosdSeExecuting)
    {
        DebugMessageGOSD("SE is not idle", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstSrc1LayerInfo))
    {
        DebugMessageGOSD("Src1 Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstRsltLayerInfo))
    {
        DebugMessageGOSD("Rslt Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeStrecthGuard(pstSrc1LayerInfo, pstRsltLayerInfo, pstStretchInfo))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    if(pstSrc1LayerInfo->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        EnumGosdSyncCmdFeedBack enumReturn = ScalerGosdSeFetchClut(pstSrc1LayerInfo->stSurface.ulClutAddress);
        if(enumReturn != _GOSD_SYNC_FEEDBACK_SUCCESS)
        {
            return enumReturn;
        }
    }

    UnionGosdSeCmdExtfcvStretch unSeCmd;
    DWORD ulRegValue = 0;
    DWORD ulStretchFactor = 0;
    DWORD ulStretchInitialPhase = 0;

    memset((void *)&unSeCmd.stSeCmdStretch, 0, sizeof(StructGosdSeCmdExtfcvStretch));

    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretch.pstDWordBaddr[0]), &(unSeCmd.stSeCmdStretch.pstDWordPitch[0]), 0, pstSrc1LayerInfo->stSurface.ulAddress, pstSrc1LayerInfo->stSurface.usPitch);
    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretch.pstDWordBaddr[1]), &(unSeCmd.stSeCmdStretch.pstDWordPitch[1]), 1, pstRsltLayerInfo->stSurface.ulAddress, pstRsltLayerInfo->stSurface.usPitch);

    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstSrc1LayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretch.pstDWordBaddr[2]), &(unSeCmd.stSeCmdStretch.pstDWordPitch[2]), 2, pstSrc1LayerInfo->stSurface.ulAddressC1, pstSrc1LayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdStretch.pstDWordBaddr[2].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretch.pstDWordBaddr[2].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretch.pstDWordPitch[2].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretch.pstDWordPitch[2].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstRsltLayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretch.pstDWordBaddr[3]), &(unSeCmd.stSeCmdStretch.pstDWordPitch[3]), 3, pstRsltLayerInfo->stSurface.ulAddressC1, pstRsltLayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdStretch.pstDWordBaddr[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretch.pstDWordBaddr[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretch.pstDWordPitch[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretch.pstDWordPitch[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT12), ((DWORD)pstSrc1LayerInfo->stSurface.bBigEndian << 12)); // 0xB0048100[12]:src1_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT20), ((DWORD)pstRsltLayerInfo->stSurface.bBigEndian << 20)); // 0xB0048100[20]:rslt_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT24), _BIT24); // 0xB0048100[24]:rounding_en = 1
    ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretch.pstDWordReg[0]), PB00481_00_CLR_FMT_Q1, ulRegValue);

    if(_TRUE == pstSrc1LayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretch.pstDWordReg[1]), PB00481_14_SRC_COLOR_Q1, pstSrc1LayerInfo->ulConstClrValue);
    }
    else
    {
        unSeCmd.stSeCmdStretch.pstDWordReg[1].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretch.pstDWordReg[1].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_TRUE == pstRsltLayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretch.pstDWordReg[2]), PB00481_24_RSLT_ALPHA_Q1, pstRsltLayerInfo->ucConstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdStretch.pstDWordReg[2].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretch.pstDWordReg[2].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    // setting PB00481_34_SE20_HDHS_Q1 cmd
    ulStretchFactor = ScalerGosdSeCalculateStretchFactor(pstSrc1LayerInfo->usDataWidth, pstRsltLayerInfo->usDataWidth);
    ulStretchInitialPhase = ScalerGosdSeCalculateStretchPhase(pstSrc1LayerInfo->usDataWidth, pstRsltLayerInfo->usDataWidth);

    ulRegValue = 0;
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(0x0003FFFF), ulStretchFactor); // 0xB0048134[17:0]: H factor
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(0x01FC0000), (ulStretchInitialPhase << 18)); // 0xB0048134[24:18]: H init-phase
    ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretch.pstDWordReg[3]), PB00481_34_SE20_HDHS_Q1, ulRegValue);

    // setting PB00481_38_SE20_VDHS_Q1 cmd
    ulStretchFactor = ScalerGosdSeCalculateStretchFactor(pstSrc1LayerInfo->usDataHeight, pstRsltLayerInfo->usDataHeight);
    ulStretchInitialPhase = ScalerGosdSeCalculateStretchPhase(pstSrc1LayerInfo->usDataHeight, pstRsltLayerInfo->usDataHeight);

    ulRegValue = 0;
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(0x0003FFFF), ulStretchFactor); // 0xB0048138[17:0]: V factor
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(0x01FC0000), (ulStretchInitialPhase << 18)); // 0xB0048138[24:18]: V init-phase
    ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretch.pstDWordReg[4]), PB00481_38_SE20_VDHS_Q1, ulRegValue);

    unSeCmd.stSeCmdStretch.pstDWordReg[5].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
    unSeCmd.stSeCmdStretch.pstDWordReg[5].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;

    unSeCmd.stSeCmdStretch.stDWord1.b4Opcode = _GOSD_SEINFO_OPCODE_EXT_FMTFCV;
    unSeCmd.stSeCmdStretch.stDWord1.b5RsltFmt = pstRsltLayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdStretch.stDWord1.b1LayCtrl = _FALSE;
    unSeCmd.stSeCmdStretch.stDWord1.b1LayNum = _FALSE;
    unSeCmd.stSeCmdStretch.stDWord1.b2RsltSwapChroma = _FALSE;
    unSeCmd.stSeCmdStretch.stDWord1.b2Src1SwapChroma = _FALSE;
    unSeCmd.stSeCmdStretch.stDWord1.b1YUVItu = _FALSE;
    unSeCmd.stSeCmdStretch.stDWord1.b1RsltMatrix = _FALSE;
    unSeCmd.stSeCmdStretch.stDWord1.b1SelOutAlpha = pstRsltLayerInfo->bSelectConst;
    unSeCmd.stSeCmdStretch.stDWord1.b5RsltArgbOrder = pstRsltLayerInfo->stSurface.enumArgbOrder;
    unSeCmd.stSeCmdStretch.stDWord1.b1RsltAfbcYuvtrans = pstRsltLayerInfo->stSurface.bAfbcYuvTrans;
    unSeCmd.stSeCmdStretch.stDWord1.b5Src2ArgbOrder = _GOSD_SEINFO_ARGB_ORDER_ARGB;

    unSeCmd.stSeCmdStretch.stDWord2.b13RsltOutX = pstRsltLayerInfo->usDataX;
    unSeCmd.stSeCmdStretch.stDWord2.b13RsltOutY = pstRsltLayerInfo->usDataY;
    unSeCmd.stSeCmdStretch.stDWord2.b2RsltRotate = pstRsltLayerInfo->enumRsltRotateModeSel;
    unSeCmd.stSeCmdStretch.stDWord2.b2RsltMirror = pstRsltLayerInfo->enumRsltMirrorModeSel;

    unSeCmd.stSeCmdStretch.stDWord3.b7RsltAddrIndexC2 = _FALSE; // no use
    unSeCmd.stSeCmdStretch.stDWord3.b7RsltAddrIndexC1 = 3; // fixed
    unSeCmd.stSeCmdStretch.stDWord3.b7RsltAddrIndex = 1; // fixed

    if(pstSrc1LayerInfo->usDataWidth == _GOSD_SE_WIDTH_LIMITATION)
    {
        // Width=8192, InptW should Set as 0
        unSeCmd.stSeCmdStretch.stDWord4.b13Src1InptW = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretch.stDWord4.b13Src1InptW = pstSrc1LayerInfo->usDataWidth;
    }
    if(pstSrc1LayerInfo->usDataHeight == _GOSD_SE_HEIGHT_LIMITATION)
    {
        // Height=8192, InptH should Set as 0
        unSeCmd.stSeCmdStretch.stDWord4.b13Src1InptH = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretch.stDWord4.b13Src1InptH = pstSrc1LayerInfo->usDataHeight;
    }
    unSeCmd.stSeCmdStretch.stDWord4.b5Src1Fmt = pstSrc1LayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdStretch.stDWord4.b1Src1Matrix = _FALSE;

    unSeCmd.stSeCmdStretch.stDWord5.b13Src1InptX = pstSrc1LayerInfo->usDataX;
    unSeCmd.stSeCmdStretch.stDWord5.b13Src1InptY = pstSrc1LayerInfo->usDataY;
    unSeCmd.stSeCmdStretch.stDWord5.b5Src1ArgbOrder = pstSrc1LayerInfo->stSurface.enumArgbOrder;
    unSeCmd.stSeCmdStretch.stDWord5.b1Src1FcvStch = _ENABLE;

    unSeCmd.stSeCmdStretch.stDWord6.b7Src1AddrIndexC2 = _FALSE; // no sue
    unSeCmd.stSeCmdStretch.stDWord6.b7Src1AddrIndexC1 = 2; // fixed
    unSeCmd.stSeCmdStretch.stDWord6.b7Src1AddrIndex = 0; // fixed
    unSeCmd.stSeCmdStretch.stDWord6.b1Src1InputSel = pstSrc1LayerInfo->bSelectConst;
    unSeCmd.stSeCmdStretch.stDWord6.b1Src1AfbcYuvtrans = pstSrc1LayerInfo->stSurface.bAfbcYuvTrans;

    // DWORD7~DWORD8 all 0

    unSeCmd.stSeCmdStretch.stDWord9.b3LayerNumExt = _GOSD_SEINFO_OPERATION_MODE_STRETCH;

    // DWORD10~DWORD11 all 0

    if(pstRsltLayerInfo->usDataWidth == _GOSD_SE_WIDTH_LIMITATION)
    {
        // Width=8192, OutW should Set as 0
        unSeCmd.stSeCmdStretch.stDWord12.b13StretchOutW = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretch.stDWord12.b13StretchOutW = pstRsltLayerInfo->usDataWidth;
    }
    if(pstRsltLayerInfo->usDataHeight == _GOSD_SE_HEIGHT_LIMITATION)
    {
        // Height=8192, OutH should Set as 0
        unSeCmd.stSeCmdStretch.stDWord12.b13StretchOutH = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretch.stDWord12.b13StretchOutH = pstRsltLayerInfo->usDataHeight;
    }
    if((pstSrc1LayerInfo->usDataWidth == pstRsltLayerInfo->usDataWidth) &&
       (pstSrc1LayerInfo->usDataHeight == pstRsltLayerInfo->usDataHeight))
    {
        unSeCmd.stSeCmdStretch.stDWord12.b3StretchSrcSel = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretch.stDWord12.b3StretchSrcSel = 1; // fixed src1
    }
    if(pstRsltLayerInfo->usDataWidth != pstSrc1LayerInfo->usDataWidth)
    {
        unSeCmd.stSeCmdStretch.stDWord12.b1StretchHorizontal = _ENABLE;
    }
    if(pstRsltLayerInfo->usDataHeight != pstSrc1LayerInfo->usDataHeight)
    {
        unSeCmd.stSeCmdStretch.stDWord12.b1StretchVertical = _ENABLE;
    }
    unSeCmd.stSeCmdStretch.stDWord12.b1StretchAlgo = pstStretchInfo->enumAlgoSel;

    if(ScalerGosdSeWriteCmd(unSeCmd.pucSeCmdBuffer, sizeof(StructGosdSeCmdExtfcvStretch)) == _FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    // set executing surface list
    g_pulGosdSeExecutingSurfaceId[0] = pstSrc1LayerInfo->stSurface.ulSurfaceId;
    g_pulGosdSeExecutingSurfaceId[2] = pstRsltLayerInfo->stSurface.ulSurfaceId;
    // set surface status
    if(GOSD_GET_SURFACE_STATUS(pstSrc1LayerInfo->stSurface.ulSurfaceId) != _GOSD_SURFACE_DISPOSD_SHOWING)
    {
        GOSD_SET_SURFACE_STATUS(pstSrc1LayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_READ);
    }
    GOSD_SET_SURFACE_STATUS(pstRsltLayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_WRITE);

    return ScalerGosdSeExecute();
}

//--------------------------------------------------
// Description  : set SE Format StretchBitBlit cmd
// Input Value  : *pstSrc1LayerInfo : src1 layer info
//                *pstSrc2LayerInfo : src2 layer info
//                *pstRsltLayerInfo : rslt layer info
//                *pstBitBlitInfo : BitBlit setting
// Output Value : EnumGosdSeOperationResult : set operation result
//--------------------------------------------------
EnumGosdSyncCmdFeedBack ScalerGosdSeStretchBitBlit(StructGosdSeLayerInfo *pstSrc1LayerInfo, StructGosdSeLayerInfo *pstSrc2LayerInfo, StructGosdSeLayerInfo *pstRsltLayerInfo, StructGosdSeStretchInfo *pstStretchInfo, StructGosdSeBitBlitInfo *pstBitBlitInfo)
{
    if(_TRUE == g_bGosdSeExecuting)
    {
        DebugMessageGOSD("SE is not idle", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstSrc1LayerInfo))
    {
        DebugMessageGOSD("Src1 Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstSrc2LayerInfo))
    {
        DebugMessageGOSD("Src2 Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeLayerGuard(pstRsltLayerInfo))
    {
        DebugMessageGOSD("Rslt Error", 0);
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeBitBlitGuard(pstSrc1LayerInfo, pstSrc2LayerInfo, pstRsltLayerInfo, pstBitBlitInfo))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }
    if(_FALSE == ScalerGosdSeStrecthGuard(pstSrc2LayerInfo, pstRsltLayerInfo, pstStretchInfo))
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    if(pstSrc1LayerInfo->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        EnumGosdSyncCmdFeedBack enumReturn = ScalerGosdSeFetchClut(pstSrc1LayerInfo->stSurface.ulClutAddress);
        if(enumReturn != _GOSD_SYNC_FEEDBACK_SUCCESS)
        {
            return enumReturn;
        }
    }
    else if(pstSrc2LayerInfo->stSurface.enumFormat == _GOSD_SEINFO_COLOR_FORMAT_INDEX8)
    {
        EnumGosdSyncCmdFeedBack enumReturn = ScalerGosdSeFetchClut(pstSrc2LayerInfo->stSurface.ulClutAddress);
        if(enumReturn != _GOSD_SYNC_FEEDBACK_SUCCESS)
        {
            return enumReturn;
        }
    }

    UnionGosdSeCmdExtfcvStretchBitBlit unSeCmd;
    DWORD ulRegValue = 0;
    DWORD ulStretchFactor = 0;
    DWORD ulStretchInitialPhase = 0;

    memset((void *)&unSeCmd.stSeCmdStretchBitBlit, 0, sizeof(StructGosdSeCmdExtfcvStretchBitBlit));

    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[0]), &(unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[0]), 0, pstSrc1LayerInfo->stSurface.ulAddress, pstSrc1LayerInfo->stSurface.usPitch);
    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[1]), &(unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[1]), 1, pstSrc2LayerInfo->stSurface.ulAddress, pstSrc2LayerInfo->stSurface.usPitch);
    ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[2]), &(unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[2]), 2, pstRsltLayerInfo->stSurface.ulAddress, pstRsltLayerInfo->stSurface.usPitch);

    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstSrc1LayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[3]), &(unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[3]), 3, pstSrc1LayerInfo->stSurface.ulAddressC1, pstSrc1LayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstSrc2LayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[4]), &(unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[4]), 4, pstSrc2LayerInfo->stSurface.ulAddressC1, pstSrc2LayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[4].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[4].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[4].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[4].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_GOSD_SEINFO_AFBC_FORMAT == ScalerGosdSeGetFormatType(pstRsltLayerInfo->stSurface.enumFormat))
    {
        ScalerGosdSeSetBaddrPitchCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[5]), &(unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[5]), 5, pstRsltLayerInfo->stSurface.ulAddressC1, pstRsltLayerInfo->stSurface.usPitchC1);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[5].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordBaddr[5].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[5].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordPitch[5].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT12), ((DWORD)pstSrc1LayerInfo->stSurface.bBigEndian << 12)); // 0xB0048100[12]:src1_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT16), ((DWORD)pstSrc1LayerInfo->stSurface.bBigEndian << 16)); // 0xB0048100[16]:src2_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT20), ((DWORD)pstRsltLayerInfo->stSurface.bBigEndian << 20)); // 0xB0048100[20]:rslt_bigendian_en
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(_BIT24), _BIT24); // 0xB0048100[24]:rounding_en = 1
    ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[0]), PB00481_00_CLR_FMT_Q1, ulRegValue);

    if(_TRUE == pstSrc1LayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[1]), PB00481_14_SRC_COLOR_Q1, pstSrc1LayerInfo->ulConstClrValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[1].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[1].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_TRUE == pstSrc2LayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[2]), PB00481_14_SRC_COLOR_Q1, pstSrc2LayerInfo->ulConstClrValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[2].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[2].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(_TRUE == pstRsltLayerInfo->bSelectConst)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[3]), PB00481_24_RSLT_ALPHA_Q1, pstRsltLayerInfo->ucConstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[3].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[3].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    // ColorKey Value setting
    if((pstBitBlitInfo->enumColorKeyModeSel == _GOSD_SEINFO_BLENDING_COLORKEY_SOURCE) || (pstBitBlitInfo->enumColorKeyModeSel == _GOSD_SEINFO_BLENDING_COLORKEY_BOTH))
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[4]), PB00481_04_COLOR_KEY_Q1, pstBitBlitInfo->ulSrcColorKeyValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[4].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[4].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if((pstBitBlitInfo->enumColorKeyModeSel == _GOSD_SEINFO_BLENDING_COLORKEY_DESTINATION) || (pstBitBlitInfo->enumColorKeyModeSel == _GOSD_SEINFO_BLENDING_COLORKEY_BOTH))
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[5]), PB00481_08_DST_COLOR_KEY_Q1, pstBitBlitInfo->ulDstColorKeyValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[5].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[5].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    // Src2 Alpha mode constant value setting
    if((pstBitBlitInfo->enumSrcAlphaModeSel == _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONST) || (pstBitBlitInfo->enumSrcAlphaModeSel == _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_CONST))
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[6]), PB00481_18_SRC_ALPHA_Q1, pstBitBlitInfo->ucSrcAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[6].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[6].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    // Src1 Alpha mode constant value setting
    if((pstBitBlitInfo->enumDstAlphaModeSel == _GOSD_SEINFO_BLENDING_DFB_ALPHA_CONST) || (pstBitBlitInfo->enumDstAlphaModeSel == _GOSD_SEINFO_BLENDING_DFB_ALPHA_1_CONST))
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[7]), PB00481_1C_DEST_ALPHA_Q1, pstBitBlitInfo->ucDstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[7].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[7].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    // DirectFB/OpenGL constant value setting
    if(pstBitBlitInfo->bEnableColorize == _TRUE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[8]), PB00481_14_SRC_COLOR_Q1, pstBitBlitInfo->ulConstClrValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[8].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[8].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(pstBitBlitInfo->bEnableSrcPremulcolor == _TRUE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[9]), PB00481_18_SRC_ALPHA_Q1, pstBitBlitInfo->ucConstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[9].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[9].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(pstBitBlitInfo->bEnableColorAlpha == _TRUE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[10]), PB00481_28_FB_COLORALPHA_Q1, pstBitBlitInfo->ucConstAlphaValueForBlendColor);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[10].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[10].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }
    if(pstBitBlitInfo->bEnableAlphaChannel == _TRUE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[11]), PB00481_18_SRC_ALPHA_Q1, pstBitBlitInfo->ucConstAlphaValue);
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[11].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[11].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    if(pstBitBlitInfo->enumSrc2LinearGradientModeSel != _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_NONE)
    {
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[12]), PB00481_14_SRC_COLOR_Q1, pstBitBlitInfo->ulStartClrValue);
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[13]), PB00481_68_SRC_LG_2_Q1, (pstBitBlitInfo->usClrStepXGreen << 16) | (pstBitBlitInfo->usClrStepXRed));
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[14]), PB00481_6C_SRC_LG_3_Q1, (pstBitBlitInfo->usClrStepXBlue << 16) | (pstBitBlitInfo->usClrStepXAlpha));
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[15]), PB00481_70_SRC_LG_4_Q1, (pstBitBlitInfo->usClrStepYGreen << 16) | (pstBitBlitInfo->usClrStepYRed));
        ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[16]), PB00481_74_SRC_LG_5_Q1, (pstBitBlitInfo->usClrStepYBlue << 16) | (pstBitBlitInfo->usClrStepYAlpha));
        switch (pstBitBlitInfo->enumSrc2LinearGradientModeSel)
        {
            case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_XY:
                ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[17]), PB00481_78_SRC_LG_6_Q1, 0);
                break;
            case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_X:
                ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[17]), PB00481_78_SRC_LG_6_Q1, 2);
                break;
            case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_Y:
                ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[17]), PB00481_78_SRC_LG_6_Q1, 3);
                break;

            case _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_NONE:
            default:
                break;
        }
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[12].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[12].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[13].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[13].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[14].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[14].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[15].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[15].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[16].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[16].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[17].stDWordReg.b4OpCode = _GOSD_SEINFO_OPCODE_NOP;
        unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[17].stDWordValue.ulRegisterValue = _GOSD_SEINFO_OPCODE_NOP;
    }

    // setting PB00481_34_SE20_HDHS_Q1 cmd
    ulStretchFactor = ScalerGosdSeCalculateStretchFactor(pstSrc2LayerInfo->usDataWidth, pstRsltLayerInfo->usDataWidth);
    ulStretchInitialPhase = ScalerGosdSeCalculateStretchPhase(pstSrc2LayerInfo->usDataWidth, pstRsltLayerInfo->usDataWidth);

    ulRegValue = 0;
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(0x0003FFFF), ulStretchFactor); // 0xB0048134[17:0]: H factor
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(0x01FC0000), (ulStretchInitialPhase << 18)); // 0xB0048134[24:18]: H init-phase
    ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[18]), PB00481_34_SE20_HDHS_Q1, ulRegValue);

    // setting PB00481_38_SE20_VDHS_Q1 cmd
    ulStretchFactor = ScalerGosdSeCalculateStretchFactor(pstSrc2LayerInfo->usDataHeight, pstRsltLayerInfo->usDataHeight);
    ulStretchInitialPhase = ScalerGosdSeCalculateStretchPhase(pstSrc2LayerInfo->usDataHeight, pstRsltLayerInfo->usDataHeight);

    ulRegValue = 0;
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(0x0003FFFF), ulStretchFactor); // 0xB0048138[17:0]: V factor
    ulRegValue = GOSDSE_DWORD_SETBIT(ulRegValue, ~(0x01FC0000), (ulStretchInitialPhase << 18)); // 0xB0048138[24:18]: V init-phase
    ScalerGosdSeWriteRegCmd(&(unSeCmd.stSeCmdStretchBitBlit.pstDWordReg[19]), PB00481_38_SE20_VDHS_Q1, ulRegValue);

    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b4Opcode = _GOSD_SEINFO_OPCODE_EXT_FMTFCV;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b5RsltFmt = pstRsltLayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b1LayCtrl = pstBitBlitInfo->bLayerControl;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b1LayNum = _TRUE;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b2RsltSwapChroma = _FALSE;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b2Src1SwapChroma = _FALSE;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b1YUVItu = _FALSE;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b1RsltMatrix = _FALSE;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b1SelOutAlpha = pstRsltLayerInfo->bSelectConst;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b5RsltArgbOrder = pstRsltLayerInfo->stSurface.enumArgbOrder;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b1RsltAfbcYuvtrans = pstRsltLayerInfo->stSurface.bAfbcYuvTrans;
    unSeCmd.stSeCmdStretchBitBlit.stDWord1.b5Src2ArgbOrder = pstSrc2LayerInfo->stSurface.enumArgbOrder;

    unSeCmd.stSeCmdStretchBitBlit.stDWord2.b13RsltOutX = pstRsltLayerInfo->usDataX;
    unSeCmd.stSeCmdStretchBitBlit.stDWord2.b13RsltOutY = pstRsltLayerInfo->usDataY;
    unSeCmd.stSeCmdStretchBitBlit.stDWord2.b2RsltRotate = pstRsltLayerInfo->enumRsltRotateModeSel;
    unSeCmd.stSeCmdStretchBitBlit.stDWord2.b2RsltMirror = pstRsltLayerInfo->enumRsltMirrorModeSel;

    unSeCmd.stSeCmdStretchBitBlit.stDWord3.b7RsltAddrIndexC2 = _FALSE;    // no use
    unSeCmd.stSeCmdStretchBitBlit.stDWord3.b7RsltAddrIndexC1 = 5;    // fixed
    unSeCmd.stSeCmdStretchBitBlit.stDWord3.b7RsltAddrIndex = 2;  // fixed

    if(pstSrc1LayerInfo->usDataWidth == _GOSD_SE_WIDTH_LIMITATION)
    {
        // Width=8192, InptW should Set as 0
        unSeCmd.stSeCmdStretchBitBlit.stDWord4.b13Src1InptW = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord4.b13Src1InptW = pstSrc1LayerInfo->usDataWidth;
    }
    if(pstSrc1LayerInfo->usDataHeight == _GOSD_SE_HEIGHT_LIMITATION)
    {
        // Height=8192, InptH should Set as 0
        unSeCmd.stSeCmdStretchBitBlit.stDWord4.b13Src1InptH = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord4.b13Src1InptH = pstSrc1LayerInfo->usDataHeight;
    }
    unSeCmd.stSeCmdStretchBitBlit.stDWord4.b5Src1Fmt = pstSrc1LayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdStretchBitBlit.stDWord4.b1Src1Matrix = _FALSE;

    unSeCmd.stSeCmdStretchBitBlit.stDWord5.b13Src1InptX = pstSrc1LayerInfo->usDataX;
    unSeCmd.stSeCmdStretchBitBlit.stDWord5.b13Src1InptY = pstSrc1LayerInfo->usDataY;
    unSeCmd.stSeCmdStretchBitBlit.stDWord5.b5Src1ArgbOrder = pstSrc1LayerInfo->stSurface.enumArgbOrder;
    unSeCmd.stSeCmdStretchBitBlit.stDWord5.b1Src1FcvStch = _TRUE;

    unSeCmd.stSeCmdStretchBitBlit.stDWord6.b7Src1AddrIndexC2 = _FALSE;    // no sue
    unSeCmd.stSeCmdStretchBitBlit.stDWord6.b7Src1AddrIndexC1 = 3;    // fixed
    unSeCmd.stSeCmdStretchBitBlit.stDWord6.b7Src1AddrIndex = 0;  // fixed
    unSeCmd.stSeCmdStretchBitBlit.stDWord6.b1Src1InputSel = pstSrc1LayerInfo->bSelectConst;
    unSeCmd.stSeCmdStretchBitBlit.stDWord6.b1Src1AfbcYuvtrans = pstSrc1LayerInfo->stSurface.bAfbcYuvTrans;

    unSeCmd.stSeCmdStretchBitBlit.stDWord7.b13Src2InptX = pstSrc2LayerInfo->usDataX;
    unSeCmd.stSeCmdStretchBitBlit.stDWord7.b13Src2InptY = pstSrc2LayerInfo->usDataY;
    unSeCmd.stSeCmdStretchBitBlit.stDWord7.b5Src2Fmt = pstSrc2LayerInfo->stSurface.enumFormat;
    unSeCmd.stSeCmdStretchBitBlit.stDWord7.b1Src2Matrix = _FALSE;

    unSeCmd.stSeCmdStretchBitBlit.stDWord8.b7Src2AddrIndexC2 = _FALSE;    // no sue
    unSeCmd.stSeCmdStretchBitBlit.stDWord8.b7Src2AddrIndexC1 = 4;    // fixed
    unSeCmd.stSeCmdStretchBitBlit.stDWord8.b7Src2AddrIndex = 1;  // fixed
    unSeCmd.stSeCmdStretchBitBlit.stDWord8.b1Src2InptSel = pstSrc2LayerInfo->bSelectConst;
    unSeCmd.stSeCmdStretchBitBlit.stDWord8.b2Src2SwapChroma = _FALSE;
    unSeCmd.stSeCmdStretchBitBlit.stDWord8.b1Src2AfbcYuvtrans = pstSrc2LayerInfo->stSurface.bAfbcYuvTrans;
    if(pstBitBlitInfo->enumSrc2LinearGradientModeSel == _GOSD_SEINFO_LINEARGRADIENT_DIRECTION_NONE)
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord8.b1Src2LinearGradient = _FALSE;
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord8.b1Src2LinearGradient = _TRUE;
    }

    unSeCmd.stSeCmdStretchBitBlit.stDWord9.b3LayerNumExt = _GOSD_SEINFO_OPERATION_MODE_STRETCH_BITBLIT;

    unSeCmd.stSeCmdStretchBitBlit.stDWord10.b4BlendSel = pstBitBlitInfo->enumModeSel;
    switch(pstBitBlitInfo->enumModeSel)
    {
        case _GOSD_SEINFO_BLENDING_ROP:
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b4RopCode = pstBitBlitInfo->enumRopCode;
            break;
        case _GOSD_SEINFO_BLENDING_ALPHA:
            unSeCmd.stSeCmdStretchBitBlit.stDWord9.b3SourceAlphaSel = pstBitBlitInfo->enumSrcAlphaModeSel;
            unSeCmd.stSeCmdStretchBitBlit.stDWord9.b3DestinationAlphaSel = pstBitBlitInfo->enumDstAlphaModeSel;

            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b2ColorKeySel = pstBitBlitInfo->enumColorKeyModeSel;
            break;
        case _GOSD_SEINFO_BLENDING_FB:
            unSeCmd.stSeCmdStretchBitBlit.stDWord9.b3SourceAlphaSel = pstBitBlitInfo->enumSrcAlphaModeSel;
            unSeCmd.stSeCmdStretchBitBlit.stDWord9.b3DestinationAlphaSel = pstBitBlitInfo->enumDstAlphaModeSel;

            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b2ColorKeySel = pstBitBlitInfo->enumColorKeyModeSel;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbDestinationPremultiply = pstBitBlitInfo->bEnableDstPremultiply;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbSourcePremulcolor = pstBitBlitInfo->bEnableSrcPremulcolor;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbSourcePremultiply = pstBitBlitInfo->bEnableSrcPremultiply;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbXor = pstBitBlitInfo->bEnableXor;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbColorize = pstBitBlitInfo->bEnableColorize;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbBlendColoralpha = pstBitBlitInfo->bEnableColorAlpha;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbBlendAlphachannel = pstBitBlitInfo->bEnableAlphaChannel;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbDemultiply = pstBitBlitInfo->bEnableDemultiply;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b4FbSourceColorBlendSel = pstBitBlitInfo->enumSrcClrModeSel;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b4FbDestinationColorBlendSel = pstBitBlitInfo->enumDstClrModeSel;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b4RopCode = pstBitBlitInfo->enumRopCode;
            break;
        case _GOSD_SEINFO_BLENDING_GL:
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b2ColorKeySel = pstBitBlitInfo->enumColorKeyModeSel;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbDestinationPremultiply = pstBitBlitInfo->bEnableDstPremultiply;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbSourcePremulcolor = pstBitBlitInfo->bEnableSrcPremulcolor;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbSourcePremultiply = pstBitBlitInfo->bEnableSrcPremultiply;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbXor = pstBitBlitInfo->bEnableXor;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbColorize = pstBitBlitInfo->bEnableColorize;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbBlendColoralpha = pstBitBlitInfo->bEnableColorAlpha;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbBlendAlphachannel = pstBitBlitInfo->bEnableAlphaChannel;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b1FbDemultiply = pstBitBlitInfo->bEnableDemultiply;
            unSeCmd.stSeCmdStretchBitBlit.stDWord10.b4RopCode = pstBitBlitInfo->enumRopCode;
#if(_HW_GOSD_SE_BITBLIT_OPENGL_CONSTANT_COEFF_SUPPORT == _ON)
            unSeCmd.stSeCmdStretchBitBlit.stDWord11.b7GlDestinationColorSel = pstBitBlitInfo->ucGLDstClrIndex;
            unSeCmd.stSeCmdStretchBitBlit.stDWord11.b7GlSourceColorSel = pstBitBlitInfo->ucGLSrcClrIndex;
            unSeCmd.stSeCmdStretchBitBlit.stDWord11.b7GlDestinationAlphaSel = pstBitBlitInfo->ucGLDstAlphaIndex;
            unSeCmd.stSeCmdStretchBitBlit.stDWord11.b7GlSourceAlphaSel = pstBitBlitInfo->ucGLSrcAlphaIndex;
#else
            unSeCmd.stSeCmdStretchBitBlit.stDWord11.b6GlDestinationColorSel = pstBitBlitInfo->b6GLDstClrIndex;
            unSeCmd.stSeCmdStretchBitBlit.stDWord11.b6GlSourceColorSel = pstBitBlitInfo->b6GLSrcClrIndex;
            unSeCmd.stSeCmdStretchBitBlit.stDWord11.b6GlDestinationAlphaSel = pstBitBlitInfo->b6GLDstAlphaIndex;
            unSeCmd.stSeCmdStretchBitBlit.stDWord11.b6GlSourceAlphaSel = pstBitBlitInfo->b6GLSrcAlphaIndex;
#endif
            break;
        default:
            break;
    }

    if(pstRsltLayerInfo->usDataWidth == _GOSD_SE_WIDTH_LIMITATION)
    {
        // Width=8192, OutW should Set as 0
        unSeCmd.stSeCmdStretchBitBlit.stDWord12.b13StretchOutW = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord12.b13StretchOutW = pstRsltLayerInfo->usDataWidth;
    }
    if(pstRsltLayerInfo->usDataHeight == _GOSD_SE_HEIGHT_LIMITATION)
    {
        // Height=8192, OutH should Set as 0
        unSeCmd.stSeCmdStretchBitBlit.stDWord12.b13StretchOutH = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord12.b13StretchOutH = pstRsltLayerInfo->usDataHeight;
    }
    if((pstSrc2LayerInfo->usDataWidth == pstRsltLayerInfo->usDataWidth) &&
       (pstSrc2LayerInfo->usDataHeight == pstRsltLayerInfo->usDataHeight))
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord12.b3StretchSrcSel = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord12.b3StretchSrcSel = 2; // fixed src2
    }
    if(pstRsltLayerInfo->usDataWidth != pstSrc2LayerInfo->usDataWidth)
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord12.b1StretchHorizontal = _ENABLE;
    }
    if(pstRsltLayerInfo->usDataHeight != pstSrc2LayerInfo->usDataHeight)
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord12.b1StretchVertical = _ENABLE;
    }
    unSeCmd.stSeCmdStretchBitBlit.stDWord12.b1StretchAlgo = pstStretchInfo->enumAlgoSel;

    if(pstSrc2LayerInfo->usDataWidth == _GOSD_SE_WIDTH_LIMITATION)
    {
        // Width=8192, InptW should Set as 0
        unSeCmd.stSeCmdStretchBitBlit.stDWord13.b13Src2InptW = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord13.b13Src2InptW = pstSrc2LayerInfo->usDataWidth;
    }
    if(pstSrc2LayerInfo->usDataHeight == _GOSD_SE_HEIGHT_LIMITATION)
    {
        // Height=8192, InptH should Set as 0
        unSeCmd.stSeCmdStretchBitBlit.stDWord13.b13Src2inptH = 0;
    }
    else
    {
        unSeCmd.stSeCmdStretchBitBlit.stDWord13.b13Src2inptH = pstSrc2LayerInfo->usDataHeight;
    }

    unSeCmd.stSeCmdStretchBitBlit.stDWord14.b13Src2OutX = pstRsltLayerInfo->usDataX;
    unSeCmd.stSeCmdStretchBitBlit.stDWord14.b13Src2OutY = pstRsltLayerInfo->usDataY;

    unSeCmd.stSeCmdStretchBitBlit.stDWordNop15.ulNop = _GOSD_SEINFO_OPCODE_NOP;

    unSeCmd.stSeCmdStretchBitBlit.stDWordNop16.ulNop = _GOSD_SEINFO_OPCODE_NOP;

    if(ScalerGosdSeWriteCmd(unSeCmd.pucSeCmdBuffer, sizeof(UnionGosdSeCmdExtfcvStretchBitBlit)) == -_FAIL)
    {
        return _GOSD_SYNC_FEEDBACK_ERROR;
    }

    // set executing surface list
    g_pulGosdSeExecutingSurfaceId[0] = pstSrc1LayerInfo->stSurface.ulSurfaceId;
    g_pulGosdSeExecutingSurfaceId[1] = pstSrc2LayerInfo->stSurface.ulSurfaceId;
    g_pulGosdSeExecutingSurfaceId[2] = pstRsltLayerInfo->stSurface.ulSurfaceId;
    // set surface status
    if(GOSD_GET_SURFACE_STATUS(pstSrc1LayerInfo->stSurface.ulSurfaceId) != _GOSD_SURFACE_DISPOSD_SHOWING)
    {
        GOSD_SET_SURFACE_STATUS(pstSrc1LayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_READ);
    }
    if(GOSD_GET_SURFACE_STATUS(pstSrc2LayerInfo->stSurface.ulSurfaceId) != _GOSD_SURFACE_DISPOSD_SHOWING)
    {
        GOSD_SET_SURFACE_STATUS(pstSrc2LayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_READ);
    }
    GOSD_SET_SURFACE_STATUS(pstRsltLayerInfo->stSurface.ulSurfaceId, _GOSD_SURFACE_SE_WORKING_WRITE);

    return ScalerGosdSeExecute();
}

#if(_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON)
//--------------------------------------------------
// Description  : GOSD_SE client BW Ctrl
// Input Value  : None
// Output Value : None
//--------------------------------------------------
void ScalerGosdSeSetBwCtrl(void)
{
    StructBwCtrlClientInfo stBwCtrlInfo = {0};

    ScalerGosdSeBwCtrlGetClientInfo(&stBwCtrlInfo);
    ScalerMemorySetBwCtrl(_MEM_CLIENT_GOSE_SE, _BW_CTRL_CLIENT_INDEX_DEFAULT, &stBwCtrlInfo);

    ScalerMemorySetBwCtrlEnable(_MEM_CLIENT_GOSE_SE, _GOSDSE_MEMORY_CLIENT_0_INDEX, _ENABLE);
}

//--------------------------------------------------
// Description  : Get BW Ctrl client info - GOSD SE
// Input Value  : Pointer to client info, ucTotalBwPercent_100x
// Output Value : None
//--------------------------------------------------
void ScalerGosdSeBwCtrlGetClientInfoByPercentage(StructBwCtrlClientInfo *pstInfo, BYTE ucTotalBwPercent_100x)
{
    DWORD ulTimeThd = 3552; // ~50us in mclk=933/2 MHz
    DWORD ulReqThd = 0;

    ulReqThd = GET_DWORD_MUL_DIV(ulTimeThd * 2, (DWORD)ucTotalBwPercent_100x, 100UL);
    ulReqThd = ulReqThd / _MEMORY_BUS_WIDTH * _MEMORY_BUS_WIDTH;
    if(ulReqThd < _MEMORY_BUS_WIDTH)
    {
        ulReqThd = 0;
    }
    else
    {
        ulReqThd -= _MEMORY_BUS_WIDTH;
    }

    pstInfo->bEnable = _TRUE;
    pstInfo->enumMode = _BW_CTRL_LEN_MODE;
    pstInfo->ulTimeThd = ulTimeThd;
    pstInfo->ulReqThd = ulReqThd;
}

//--------------------------------------------------
// Description  : Get BW Ctrl client info - GOSD SE
// Input Value  : Pointer to client info
// Output Value : None
//--------------------------------------------------
void ScalerGosdSeBwCtrlGetClientInfo(StructBwCtrlClientInfo *pstInfo)
{
    ScalerGosdSeBwCtrlGetClientInfoByPercentage(pstInfo, _GOSD_MEMORY_BW_DRAW);
}
#endif // #if(_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON)

#endif // #if(_IS_MAIN_PROCESS_CPU == _FALSE)

#endif // #if(_GOSD_SUPPORT == _ON)
