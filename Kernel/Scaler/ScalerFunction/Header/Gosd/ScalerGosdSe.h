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
// ID Code      : ScalerGosdSe.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __SCALER_GOSD_SE_H__
#define __SCALER_GOSD_SE_H__

#if(_GOSD_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#define GOSDSE_CMD0_REGSHIFT(x)                     ((x) - 0xB0048000UL)
#define GOSDSE_CMD1_REGSHIFT(x)                     ((x) - 0xB0048400UL)

#define GOSDSE_8TO32_BIG(arr)                       (TO_DWORD(*((arr) + 0), *((arr) + 1), *((arr) + 2), *((arr) + 3)))

#define GOSDSE_DWORD_SETBIT(ulValue, ulAnd, ulOr)   (((ulValue) & ((DWORD)(ulAnd))) | ((DWORD)(ulOr)))

#define _GOSDSE_CMDSIZE_FCV                         128
#define _GOSDSE_CMDSIZE_BITBLIT                     288
#define _GOSDSE_CMDSIZE_STRETCH                     160
#define _GOSDSE_CMDSIZE_STRETCHBITBLIT              320
#define _GOSDSE_CMDSIZE_FETCHCLUT                   16

// #define GOSDSE_8TO32_LITTLE(arr)    TO_DWORD((BYTE*)(arr + 0), (BYTE*)(arr + 1), (BYTE*)(arr + 2),(BYTE*)(arr + 3))

#if(_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON)
#define _GOSDSE_MEMORY_CLIENT_0_INDEX               _BW_CTRL_CLIENT_INDEX_DEFAULT
#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef struct
{
    DWORD ulNop;
} StructGosdSeCmdNop;

// Define struct of Cmd WriteRegister
typedef struct
{
    DWORD b4OpCode : 4;
    DWORD b12RegisterAddress : 12;
    DWORD b15Reserved : 15;
    DWORD b1Clut : 1;
} StructGosdSeCmdWriteRegisterDWord1;

typedef struct
{
    DWORD ulRegisterValue;
} StructGosdSeCmdWriteRegisterDWord2;

typedef struct
{
    StructGosdSeCmdWriteRegisterDWord1 stDWordReg;
    StructGosdSeCmdWriteRegisterDWord2 stDWordValue;
} StructGosdSeCmdWriteRegister;

// Define struct of Cmd Fetch Clut
typedef struct
{
    DWORD b4OpCode : 4;
    DWORD b2Entry : 2;
    DWORD b1Force : 1;
    DWORD b25Reserved : 25;
} StructGosdSeCmdFetchClutDWord1;

typedef struct
{
    DWORD ulSaddr;
} StructGosdSeCmdFetchClutDWord2;

typedef struct
{
    StructGosdSeCmdFetchClutDWord1 stDWordClut;
    StructGosdSeCmdFetchClutDWord2 stDWordSaddr;
    StructGosdSeCmdNop stDWordNop1;
    StructGosdSeCmdNop stDWordNop2;
} StructGosdSeCmdFetchClut;

// Define struct of Cmd ExtFcv
typedef struct
{
    DWORD b4Opcode : 4;
    DWORD b5RsltFmt : 5;
    DWORD b1LayCtrl : 1;
    DWORD b1LayNum : 1;
    DWORD b1Reserved0 : 1;
    DWORD b2RsltSwapChroma : 2;
    DWORD b2Src1SwapChroma : 2;
    DWORD b1YUVItu : 1;
    DWORD b1Reserved1 : 1;
    DWORD b1RsltMatrix : 1;
    DWORD b1SelOutAlpha : 1;
    DWORD b5RsltArgbOrder : 5;
    DWORD b1RsltAfbcYuvtrans : 1;
    DWORD b5Src2ArgbOrder : 5;
    DWORD b1Reserved3 : 1;
} StructGosdSeCmdExtfcvDWord1;

typedef struct
{
    DWORD b13RsltOutX : 13;
    DWORD b13RsltOutY : 13;
    DWORD b2Reserved0 : 2;
    DWORD b2RsltRotate : 2;
    DWORD b2RsltMirror : 2;
} StructGosdSeCmdExtfcvDWord2;

typedef struct
{
    DWORD b7RsltAddrIndexC2 : 7;
    DWORD b1Reserved0 : 1;
    DWORD b7RsltAddrIndexC1 : 7;
    DWORD b1Reserved1 : 1;
    DWORD b7RsltAddrIndex : 7;
    DWORD b9Reserved2 : 9;
} StructGosdSeCmdExtfcvDWord3;

typedef struct
{
    DWORD b13Src1InptW : 13;
    DWORD b13Src1InptH : 13;
    DWORD b5Src1Fmt : 5;
    DWORD b1Src1Matrix : 1;
} StructGosdSeCmdExtfcvDWord4;

typedef struct
{
    DWORD b13Src1InptX : 13;
    DWORD b13Src1InptY : 13;
    DWORD b5Src1ArgbOrder : 5;
    DWORD b1Src1FcvStch : 1;
} StructGosdSeCmdExtfcvDWord5;

typedef struct
{
    DWORD b7Src1AddrIndexC2 : 7;
    DWORD b1Reserved0 : 1;
    DWORD b7Src1AddrIndexC1 : 7;
    DWORD b1Reserved1 : 1;
    DWORD b7Src1AddrIndex : 7;
    DWORD b1Reserved2 : 1;
    DWORD b1Src1InputSel : 1;
    DWORD b2Reserved3 : 2;
    DWORD b1Src1AfbcYuvtrans : 1;
    DWORD b4Reserved4 : 4;
} StructGosdSeCmdExtfcvDWord6;

typedef struct
{
    DWORD b13Src2InptX : 13;
    DWORD b13Src2InptY : 13;
    DWORD b5Src2Fmt : 5;
    DWORD b1Src2Matrix : 1;
} StructGosdSeCmdExtfcvDWord7;

typedef struct
{
    DWORD b7Src2AddrIndexC2 : 7;
    DWORD b1Reserved0 : 1;
    DWORD b7Src2AddrIndexC1 : 7;
    DWORD b1Reserved1 : 1;
    DWORD b7Src2AddrIndex : 7;
    DWORD b1Reserved2 : 1;
    DWORD b1Src2InptSel : 1;
    DWORD b2Src2SwapChroma : 2;
    DWORD b1Src2AfbcYuvtrans : 1;
    DWORD b1Src2LinearGradient : 1;
    DWORD b3Reserved3 : 3;
} StructGosdSeCmdExtfcvDWord8;

typedef struct
{
    DWORD b3SourceAlphaSel : 3;
    DWORD b1Reserved0 : 1;
    DWORD b3DestinationAlphaSel : 3;
    DWORD b1Reserved1 : 1;
    DWORD b3LayerNumExt : 3;
    DWORD b21Reserved2 : 21;
} StructGosdSeCmdExtfcvDWord9;

typedef struct
{
    DWORD b4RopCode : 4;
    DWORD b4FbDestinationColorBlendSel : 4;
    DWORD b4FbSourceColorBlendSel : 4;
    DWORD b1FbDemultiply : 1;
    DWORD b1FbBlendAlphachannel : 1;
    DWORD b1FbBlendColoralpha : 1;
    DWORD b1FbColorize : 1;
    DWORD b1FbXor : 1;
    DWORD b1FbSourcePremultiply : 1;
    DWORD b1FbSourcePremulcolor : 1;
    DWORD b1FbDestinationPremultiply : 1;
    // DWORD b1FbSourceColorTransparency : 1;
    DWORD b1Reserved0 : 1;
    // DWORD b1FbSourceColorTransform : 2;
    DWORD b2Reserved1 : 2;
    DWORD b2reserved2 : 2;
    DWORD b2ColorKeySel : 2;
    DWORD b4BlendSel : 4;
    DWORD b1Reserved3 : 1;
} StructGosdSeCmdExtfcvDWord10;

typedef struct
{
#if(_HW_GOSD_SE_BITBLIT_OPENGL_CONSTANT_COEFF_SUPPORT == _ON)
    DWORD b7GlDestinationColorSel : 7;
    DWORD b1Reserved0 : 1;
    DWORD b7GlSourceColorSel : 7;
    DWORD b1Reserved1 : 1;
    DWORD b7GlDestinationAlphaSel : 7;
    DWORD b1Reserved2 : 1;
    DWORD b7GlSourceAlphaSel : 7;
    DWORD b1Reserved3 : 1;
#else
    DWORD b6GlDestinationColorSel : 6;
    DWORD b2Reserved0 : 2;
    DWORD b6GlSourceColorSel : 6;
    DWORD b2Reserved1 : 2;
    DWORD b6GlDestinationAlphaSel : 6;
    DWORD b2Reserved2 : 2;
    DWORD b6GlSourceAlphaSel : 6;
    DWORD b2Reserved3 : 2;
#endif
} StructGosdSeCmdExtfcvDWord11;

typedef struct
{
    DWORD b13StretchOutW : 13;
    DWORD b13StretchOutH : 13;
    DWORD b3StretchSrcSel : 3;
    DWORD b1StretchHorizontal : 1;
    DWORD b1StretchVertical : 1;
    DWORD b1StretchAlgo : 1;
} StructGosdSeCmdExtfcvDWord12;

typedef struct
{
    DWORD b13Src2InptW : 13;
    DWORD b13Src2inptH : 13;
    DWORD b6Reserved : 6;
} StructGosdSeCmdExtfcvDWord13;

typedef struct
{
    DWORD b13Src2OutX : 13;
    DWORD b13Src2OutY : 13;
    DWORD b6Reserved : 6;
} StructGosdSeCmdExtfcvDWord14;

typedef struct
{
    DWORD b13StretchOutW : 13;
    DWORD b13StretchOutH : 13;
    DWORD b3StretchSrcSel : 3;
    DWORD b1StretchHorizontal : 1;
    DWORD b1StretchVertical : 1;
    DWORD b1StretchAlgo : 1;
} StructGosdSeCmdExtfcvDWord15;

typedef struct
{
    StructGosdSeCmdWriteRegister pstDWordBaddr[4];
    StructGosdSeCmdWriteRegister pstDWordPitch[4];

    StructGosdSeCmdWriteRegister pstDWordReg[4];

    StructGosdSeCmdExtfcvDWord1 stDWord1;
    StructGosdSeCmdExtfcvDWord2 stDWord2;
    StructGosdSeCmdExtfcvDWord3 stDWord3;
    StructGosdSeCmdExtfcvDWord4 stDWord4;
    StructGosdSeCmdExtfcvDWord5 stDWord5;
    StructGosdSeCmdExtfcvDWord6 stDWord6;
    StructGosdSeCmdNop stDWordNop7;
    StructGosdSeCmdNop stDWordNop8;
} StructGosdSeCmdExtfcvFcv;

typedef struct
{
    StructGosdSeCmdWriteRegister pstDWordBaddr[6];
    StructGosdSeCmdWriteRegister pstDWordPitch[6];

    StructGosdSeCmdWriteRegister pstDWordReg[18];

    StructGosdSeCmdExtfcvDWord1 stDWord1;
    StructGosdSeCmdExtfcvDWord2 stDWord2;
    StructGosdSeCmdExtfcvDWord3 stDWord3;
    StructGosdSeCmdExtfcvDWord4 stDWord4;
    StructGosdSeCmdExtfcvDWord5 stDWord5;
    StructGosdSeCmdExtfcvDWord6 stDWord6;
    StructGosdSeCmdExtfcvDWord7 stDWord7;
    StructGosdSeCmdExtfcvDWord8 stDWord8;
    StructGosdSeCmdExtfcvDWord9 stDWord9;
    StructGosdSeCmdExtfcvDWord10 stDWord10;
    StructGosdSeCmdExtfcvDWord11 stDWord11;
    StructGosdSeCmdNop stDWordNop12;
} StructGosdSeCmdExtfcvBitBlit;

typedef struct
{
    StructGosdSeCmdWriteRegister pstDWordBaddr[4];
    StructGosdSeCmdWriteRegister pstDWordPitch[4];

    StructGosdSeCmdWriteRegister pstDWordReg[6];

    StructGosdSeCmdExtfcvDWord1 stDWord1;
    StructGosdSeCmdExtfcvDWord2 stDWord2;
    StructGosdSeCmdExtfcvDWord3 stDWord3;
    StructGosdSeCmdExtfcvDWord4 stDWord4;
    StructGosdSeCmdExtfcvDWord5 stDWord5;
    StructGosdSeCmdExtfcvDWord6 stDWord6;
    StructGosdSeCmdExtfcvDWord7 stDWord7;
    StructGosdSeCmdExtfcvDWord8 stDWord8;
    StructGosdSeCmdExtfcvDWord9 stDWord9;
    StructGosdSeCmdExtfcvDWord10 stDWord10;
    StructGosdSeCmdExtfcvDWord11 stDWord11;
    StructGosdSeCmdExtfcvDWord12 stDWord12;
} StructGosdSeCmdExtfcvStretch;

typedef struct
{
    StructGosdSeCmdWriteRegister pstDWordBaddr[6];
    StructGosdSeCmdWriteRegister pstDWordPitch[6];

    StructGosdSeCmdWriteRegister pstDWordReg[20];

    StructGosdSeCmdExtfcvDWord1 stDWord1;
    StructGosdSeCmdExtfcvDWord2 stDWord2;
    StructGosdSeCmdExtfcvDWord3 stDWord3;
    StructGosdSeCmdExtfcvDWord4 stDWord4;
    StructGosdSeCmdExtfcvDWord5 stDWord5;
    StructGosdSeCmdExtfcvDWord6 stDWord6;
    StructGosdSeCmdExtfcvDWord7 stDWord7;
    StructGosdSeCmdExtfcvDWord8 stDWord8;
    StructGosdSeCmdExtfcvDWord9 stDWord9;
    StructGosdSeCmdExtfcvDWord10 stDWord10;
    StructGosdSeCmdExtfcvDWord11 stDWord11;
    StructGosdSeCmdExtfcvDWord12 stDWord12;
    StructGosdSeCmdExtfcvDWord13 stDWord13;
    StructGosdSeCmdExtfcvDWord14 stDWord14;
    StructGosdSeCmdNop stDWordNop15;
    StructGosdSeCmdNop stDWordNop16;
} StructGosdSeCmdExtfcvStretchBitBlit;

typedef struct
{
    StructGosdSeCmdWriteRegister stCmd;
    StructGosdSeCmdNop stDWordNop1;
    StructGosdSeCmdNop stDWordNop2;
} StructGosdSeCmdWriteRegister1;

typedef union
{
    StructGosdSeCmdWriteRegister1 stSeCmdWriteReg;
    BYTE pucSeCmdBuffer[16];
} UnionGosdSeCmdWriteReg;

typedef union
{
    StructGosdSeCmdFetchClut stSeCmdFetchClut;
    BYTE pucSeCmdBuffer[_GOSDSE_CMDSIZE_FETCHCLUT];
}UnionGosdSeCmdFetchClut;

typedef union
{
    StructGosdSeCmdExtfcvFcv stSeCmdFcv;
    BYTE pucSeCmdBuffer[_GOSDSE_CMDSIZE_FCV];
}UnionGosdSeCmdExtfcvFcv;

typedef union
{
    StructGosdSeCmdExtfcvBitBlit stSeCmdBitBlit;
    BYTE pucSeCmdBuffer[_GOSDSE_CMDSIZE_BITBLIT];
}UnionGosdSeCmdExtfcvBitBlit;

typedef union
{
    StructGosdSeCmdExtfcvStretch stSeCmdStretch;
    BYTE pucSeCmdBuffer[_GOSDSE_CMDSIZE_STRETCH];
}UnionGosdSeCmdExtfcvStretch;

typedef union
{
    StructGosdSeCmdExtfcvStretchBitBlit stSeCmdStretchBitBlit;
    BYTE pucSeCmdBuffer[_GOSDSE_CMDSIZE_STRETCHBITBLIT];
}UnionGosdSeCmdExtfcvStretchBitBlit;


//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if(_GOSD_FW_COMPILE_RESPONSE_FLOW == _TRUE)
extern void ScalerGosdSeSetRegStretch(StructGosdSeStretchConfig *pstStretchConfig);
#if(_GOSD_MEMORY_BW_CTRL_SUPPORT == _ON)
extern void ScalerGosdSeSetBwCtrl(void);
extern void ScalerGosdSeBwCtrlGetClientInfoByPercentage(StructBwCtrlClientInfo *pstInfo, BYTE ucTotalBwPercent_100x);
extern void ScalerGosdSeBwCtrlGetClientInfo(StructBwCtrlClientInfo *pstInfo);
#endif
#endif
#endif // #if(_GOSD_SUPPORT == _ON)

#endif // End of #ifndef __SCALER_GOSD_SE_H__
