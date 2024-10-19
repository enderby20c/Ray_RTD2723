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
// ID Code      : Global.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#ifndef __ASSEMBLER__
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <Data_Type.h>
#endif

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Definitions of Physical Boolean
//--------------------------------------------------
#define _TRUE                                   1
#define _FALSE                                  0
#define _HIGH                                   1
#define _LOW                                    0
#define _ENABLE                                 1
#define _DISABLE                                0
#define _READ                                   1
#define _WRITE                                  0
#define _ON                                     1
#define _OFF                                    0
#define _SUCCESS                                1
#define _FAIL                                   0
#define _STABLE                                 1
#define _UNSTABLE                               0
#define _POSITIVE                               1
#define _NEGATIVE                               0
#define _NEWMODE                                1
#define _OLDMODE                                0
#define _ODD                                    1
#define _EVEN                                   0
#define _WAIT                                   1
#define _NOT_WAIT                               0
#define _RIGHT                                  1
#define _LEFT                                   0


//--------------------------------------------------
// Definitions of FW MAIN CPU ID
//--------------------------------------------------
#define _CPU_ID_KCPU                            0x03
#define _CPU_ID_SCPU                            0x04

//--------------------------------------------------
// Definitions of U2 Host FW Support Type
//--------------------------------------------------
#define _FW_NONE                                0x00
#define _FW_MAIN_LOOP                           0x01
#define _FW_FREE_RTOS                           0x02

//--------------------------------------------------
// Definitions of MAC Index for DSC
//--------------------------------------------------
#define _DSC_MAC_NONE                           0x00
#define _DSC_MAC_0                              _BIT0
#define _DSC_MAC_1                              _BIT1

#define _DSC_SRC_DP_MAC_PLL                     0
#define _DSC_SRC_DSC_MAC_PLL                    1

//--------------------------------------------------
// Definitions of Connection Status
//--------------------------------------------------
#define _DP_UNPLUG                              0
#define _DP_PLUG                                1

//--------------------------------------------------
// Definitions of Bits
//--------------------------------------------------
#define _BIT0                                   0x00000001U
#define _BIT1                                   0x00000002U
#define _BIT2                                   0x00000004U
#define _BIT3                                   0x00000008U
#define _BIT4                                   0x00000010U
#define _BIT5                                   0x00000020U
#define _BIT6                                   0x00000040U
#define _BIT7                                   0x00000080U
#define _BIT8                                   0x00000100U
#define _BIT9                                   0x00000200U
#define _BIT10                                  0x00000400U
#define _BIT11                                  0x00000800U
#define _BIT12                                  0x00001000U
#define _BIT13                                  0x00002000U
#define _BIT14                                  0x00004000U
#define _BIT15                                  0x00008000U
#define _BIT16                                  0x00010000UL
#define _BIT17                                  0x00020000UL
#define _BIT18                                  0x00040000UL
#define _BIT19                                  0x00080000UL
#define _BIT20                                  0x00100000UL
#define _BIT21                                  0x00200000UL
#define _BIT22                                  0x00400000UL
#define _BIT23                                  0x00800000UL
#define _BIT24                                  0x01000000UL
#define _BIT25                                  0x02000000UL
#define _BIT26                                  0x04000000UL
#define _BIT27                                  0x08000000UL
#define _BIT28                                  0x10000000UL
#define _BIT29                                  0x20000000UL
#define _BIT30                                  0x40000000UL
#define _BIT31                                  0x80000000UL

#define _BIT(hi_b, lo_b)                        (ScalerUtilGetBitSequence((hi_b), (lo_b)))

#define _6_BIT                                  0x003F
#define _8_BIT                                  0x00FF
#define _9_BIT                                  0x01FF
#define _10_BIT                                 0x03FF
#define _11_BIT                                 0x07FF
#define _12_BIT                                 0x0FFF
#define _13_BIT                                 0x1FFF
#define _14_BIT                                 0x3FFF
#define _15_BIT                                 0x7FFF
#define _16_BIT                                 0xFFFF
#define _19_BIT                                 0x07FFFF

//--------------------------------------------------
// Definitions of Clock Divider Number
//--------------------------------------------------
#define _DIV_1                                  1
#define _DIV_2                                  2
#define _DIV_3                                  3
#define _DIV_4                                  4
#define _DIV_5                                  5
#define _DIV_6                                  6
#define _DIV_7                                  7
#define _DIV_8                                  8
#define _DIV_9                                  9
#define _DIV_10                                 10
#define _DIV_11                                 11
#define _DIV_12                                 12
#define _DIV_13                                 13

//--------------------------------------------------
// Definitions of Null Pointer
//--------------------------------------------------
#define _NULL_POINTER                           ((void code *)0xFFFFFFFF)

//--------------------------------------------------
// Definitions of Checker
//--------------------------------------------------
#define _ERROR_PRONE_CODE                       (_TRUE)

//--------------------------------------------------
// Global Macros
//--------------------------------------------------
#define LOBYTE(w)                               ((BYTE)(w))
#define HIBYTE(w)                               ((BYTE)(((WORD)(w) >> 8) & 0x00FF))
#define LOWORD(dw)                              ((WORD)(dw))
#define HIWORD(dw)                              ((WORD)((dw) >> 16))
#define SEC(x)                                  ((WORD)(1000U * (x)))

#define DWORD_TO_BYTE(dw, ucByteIndex)          ((BYTE)(((dw) >> ((ucByteIndex) * 8)) & 0x00FF))

#define MAXOF(a, b)                             (((a) > (b)) ? (a) : (b))
#define MINOF(a, b)                             (((a) < (b)) ? (a) : (b))

#define MAXOF3(a, b, c)                         (MAXOF((MAXOF((a), (b))), (c)))

#define GET_TABLE_ELEMENT_NUM(tbl)              (sizeof((tbl)) / sizeof((tbl)[0]))

#define SHL(x, y)                               ((x) << (y))
#define SHR(x, y)                               ((x) >> (y))
#define AND(n1, n2)                             ((n1) & (n2))

#define ABSDWORD(x, y)                          (((x) > (y)) ? ((x) - (y)) : ((y) - (x)))

#define TO_WORD(byte_h, byte_l)                 (WORD)(((WORD)((BYTE)(byte_h)) << 8) |\
                                                       ((WORD)((BYTE)(byte_l)) << 0))

#define TO_DWORD(byte_hh, byte_hl,\
                 byte_lh, byte_ll)              (DWORD)(((DWORD)((BYTE)(byte_hh)) << 24) |\
                                                        ((DWORD)((BYTE)(byte_hl)) << 16) |\
                                                        ((DWORD)((BYTE)(byte_lh)) << 8) |\
                                                        ((DWORD)((BYTE)(byte_ll)) << 0))

#define WORD_TO_DWORD(word_h, word_l)           (((DWORD)(WORD)(word_h) << 16) | ((WORD)(word_l)))

#define LODWORD(qw)                             ((DWORD)(qw))
#define HIDWORD(qw)                             ((DWORD)((qw) >> 32))
#define TO_QWORD(dword_h, dword_l)              (((QWORD)(dword_h) << 32) | ((QWORD)(dword_l)))

#define CEILING(x, y)                           (((x) % (y)) ? ((((x) / (y)) + 1) * (y)) : (x))
#define CEILING_OF_INT_DIVISION(x, y)           (((x) % (y)) ? (((x) / (y)) + 1) : ((x) / (y)))

//--------------------------------------------------
// Macros of controlling scaler registers with paged address
//--------------------------------------------------
#define GET_PAGED_ADDR(page, addr)              ((WORD)(((WORD)((BYTE)(page)) << 8) | ((BYTE)(addr))))
#define GET_PAGED_BYTE(page, pucAddr)           (ScalerGetByte(GET_PAGED_ADDR((page), (pucAddr))))
#define SET_PAGED_BYTE(page, pucAddr, ucValue)  {ScalerSetByte(GET_PAGED_ADDR((page), (pucAddr)), (ucValue));}
#define GET_PAGED_BIT(page, pucAddr, ucAnd)     (ScalerGetBit(GET_PAGED_ADDR((page), (pucAddr)), (ucAnd)))
#define SET_PAGED_BIT(page, pucAddr, ucAnd, ucOr)\
                                                {ScalerSetBit(GET_PAGED_ADDR((page), (pucAddr)), (ucAnd), (ucOr));}

#define GET_PAGED_ADDR_EXINT(page, addr)        ((WORD)(((WORD)((BYTE)(page)) << 8) | ((BYTE)(addr))))
#define GET_PAGED_BYTE_EXINT(page, pucAddr)     (ScalerGetByte_EXINT(GET_PAGED_ADDR_EXINT((page), (pucAddr))))
#define SET_PAGED_BYTE_EXINT(page, pucAddr, ucValue)\
                                                {ScalerSetByte_EXINT(GET_PAGED_ADDR_EXINT((page), (pucAddr)), (ucValue));}
#define GET_PAGED_BIT_EXINT(page, pucAddr, ucAnd)\
                                                (ScalerGetBit_EXINT(GET_PAGED_ADDR_EXINT((page), (pucAddr)), (ucAnd)))
#define SET_PAGED_BIT_EXINT(page, pucAddr, ucAnd, ucOr)\
                                                {ScalerSetBit_EXINT(GET_PAGED_ADDR_EXINT((page), (pucAddr)), (ucAnd), (ucOr));}

//--------------------------------------------------
// Macros of controlling scaler registers with offset address
//--------------------------------------------------
#define SCALER32_GET_OFFSET_ADDR(ulOffset, pulAddr)\
                                                ((pulAddr) + (ulOffset))
#define SCALER32_GET_OFFSET_DWORD(ulOffset, pulAddr)\
                                                (Scaler32GetDWord(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr))))
#define SCALER32_SET_OFFSET_DWORD(ulOffset, pulAddr, ulValue)\
                                                {Scaler32SetDWord(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ulValue));}
#define SCALER32_GET_OFFSET_WORD(ulOffset, pulAddr, ucWordIndex)\
                                                (Scaler32GetWord(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr), (ucWordIndex))))
#define SCALER32_SET_OFFSET_WORD(ulOffset, pulAddr, ucWordIndex, ulValue)\
                                                {Scaler32SetWord(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ucWordIndex), (ulValue));}
#define SCALER32_GET_OFFSET_BYTE(ulOffset, pulAddr, ucIndex)\
                                                (Scaler32GetByte(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ucIndex)))
#define SCALER32_SET_OFFSET_BYTE(ulOffset, pulAddr, ucIndex, ucValue)\
                                                {Scaler32SetByte(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ucIndex), (ucValue));}
#define SCALER32_GET_OFFSET_BIT(ulOffset, pulAddr, ulAnd)\
                                                (Scaler32GetBit(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ulAnd)))
#define SCALER32_SET_OFFSET_BIT(ulOffset, pulAddr, ulAnd, ulOr)\
                                                {Scaler32SetBit(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ulAnd), (ulOr));}

#define SCALER32_GET_OFFSET_DWORD_EXINT0(ulOffset, pulAddr)\
                                                (Scaler32GetDWord_EXINT0(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr))))
#define SCALER32_SET_OFFSET_DWORD_EXINT0(ulOffset, pulAddr, ulValue)\
                                                {Scaler32SetDWord_EXINT0(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ulValue));}
#define SCALER32_GET_OFFSET_WORD_EXINT0(ulOffset, pulAddr, ucWordIndex)\
                                                (Scaler32GetWord_EXINT0(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr), (ucWordIndex))))
#define SCALER32_SET_OFFSET_WORD_EXINT0(ulOffset, pulAddr, ucWordIndex, ulValue)\
                                                {Scaler32SetWord_EXINT0(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ucWordIndex), (ulValue));}
#define SCALER32_GET_OFFSET_BYTE_EXINT0(ulOffset, pulAddr, ucIndex)\
                                                (Scaler32GetByte_EXINT0(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ucIndex)))
#define SCALER32_SET_OFFSET_BYTE_EXINT0(ulOffset, pulAddr, ucIndex, ucValue)\
                                                {Scaler32SetByte_EXINT0(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ucIndex), (ucValue));}
#define SCALER32_GET_OFFSET_BIT_EXINT0(ulOffset, pulAddr, ulAnd)\
                                                (Scaler32GetBit_EXINT0(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ulAnd)))
#define SCALER32_SET_OFFSET_BIT_EXINT0(ulOffset, pulAddr, ulAnd, ulOr)\
                                                {Scaler32SetBit_EXINT0(SCALER32_GET_OFFSET_ADDR((ulOffset), (pulAddr)), (ulAnd), (ulOr));}


//--------------------------------------------------
// Macro of Get Data bit
//--------------------------------------------------
#define GET_DATA_BIT7(x)                        ((bit)((x) & _BIT7))
#define GET_DATA_BIT6(x)                        ((bit)((x) & _BIT6))
#define GET_DATA_BIT5(x)                        ((bit)((x) & _BIT5))
#define GET_DATA_BIT4(x)                        ((bit)((x) & _BIT4))
#define GET_DATA_BIT3(x)                        ((bit)((x) & _BIT3))
#define GET_DATA_BIT2(x)                        ((bit)((x) & _BIT2))
#define GET_DATA_BIT1(x)                        ((bit)((x) & _BIT1))
#define GET_DATA_BIT0(x)                        ((bit)((x) & _BIT0))

//--------------------------------------------------
// Macro of BYTE Pointer
//--------------------------------------------------
#define BYTEPTR(var)                            ((BYTE *)&(var))

//--------------------------------------------------
// Macro of unaligned access
//--------------------------------------------------
#define UNALIGNED_DWORD_COPY(pulDest, pulsrc)   (((StructUnAlignedDWord *)(pulDest))->ulUnalignedDWORD = ((StructUnAlignedDWord *)(pulsrc))->ulUnalignedDWORD)

//--------------------------------------------------
// Value for input port / port type value
//--------------------------------------------------
#define GET_INPUT_PORT_VALUE(x)                 ((x) >> 4)
#define GET_PORT_TYPE_VALUE(x)                  ((x) & 0x0F)

//--------------------------------------------------
// Value for Dx input port
//--------------------------------------------------
#define _VALUE_A0_INPUT_PORT                    0x00
#define _VALUE_D0_INPUT_PORT                    0x01
#define _VALUE_D1_INPUT_PORT                    0x02
#define _VALUE_D2_INPUT_PORT                    0x03
#define _VALUE_D3_INPUT_PORT                    0x04
#define _VALUE_D4_INPUT_PORT                    0x05
#define _VALUE_D5_INPUT_PORT                    0x06
#define _VALUE_D6_INPUT_PORT                    0x07
#define _VALUE_D7_INPUT_PORT                    0x08
#define _VALUE_D8_INPUT_PORT                    0x09
#define _VALUE_D9_INPUT_PORT                    0x0A
#define _VALUE_D12_INPUT_PORT                   0x0B
#define _VALUE_D13_INPUT_PORT                   0x0C
#define _VALUE_D14_INPUT_PORT                   0x0D
#define _VALUE_D15_INPUT_PORT                   0x0E
#define _VALUE_NO_INPUT_PORT                    0x0F

//--------------------------------------------------
// Value for Px output port
//--------------------------------------------------
#define _VALUE_P0_OUTPUT_PORT                   0x00
#define _VALUE_P1_OUTPUT_PORT                   0x01
#define _VALUE_P2_OUTPUT_PORT                   0x02
#define _VALUE_P3_OUTPUT_PORT                   0x03
#define _VALUE_P4_OUTPUT_PORT                   0x04
#define _VALUE_OUTPUT_PORT_NUM                  0x05

//--------------------------------------------------
// Value for port type
//--------------------------------------------------
#define _VALUE_PORT_NONE                        0x00
#define _VALUE_PORT_VGA                         0x01
#define _VALUE_PORT_DVI                         0x02
#define _VALUE_PORT_HDMI                        0x03
#define _VALUE_PORT_DP                          0x04
#define _VALUE_PORT_MHL                         0x05
#define _VALUE_PORT_HDMI20                      0x06
#define _VALUE_PORT_DUAL_DVI                    0x07

//--------------------------------------------------
// Value for TypeC Port
//--------------------------------------------------
#define _VALUE_D0_TYPE_C_PORT                   0x00
#define _VALUE_D1_TYPE_C_PORT                   0x01
#define _VALUE_D2_TYPE_C_PORT                   0x02
#define _VALUE_D3_TYPE_C_PORT                   0x03
#define _VALUE_D4_TYPE_C_PORT                   0x04
#define _VALUE_D5_TYPE_C_PORT                   0x05
#define _VALUE_D6_TYPE_C_PORT                   0x06
#define _VALUE_P0_TYPE_C_PORT                   0x10
#define _VALUE_P1_TYPE_C_PORT                   0x11
#define _VALUE_P2_TYPE_C_PORT                   0x12
#define _VALUE_P3_TYPE_C_PORT                   0x13
#define _VALUE_P4_TYPE_C_PORT                   0x14
#define _VALUE_ADAPTOR_TYPE_C_PORT              0x20
#define _VALUE_NO_TYPE_C_PORT                   0xFF

//--------------------------------------------------
// Value for Embedded TypeC Port
//--------------------------------------------------
#define _VALUE_EMB_TYPE_C_NOT_EXIST             0x00
#define _VALUE_EMB_TYPE_C_0                     0x01
#define _VALUE_EMB_TYPE_C_1                     0x02
#define _VALUE_EMB_TYPE_C_2                     0x03
#define _VALUE_EMB_TYPE_C_3                     0x04

//--------------------------------------------------
// Value for Audio Path
//--------------------------------------------------
#define _PATH_0                                 0x00
#define _PATH_1                                 0x01


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
#ifndef __ASSEMBLER__
//--------------------------------------------------
// Enumerations of Input Port List
//--------------------------------------------------
typedef enum
{
    _A0_INPUT_PORT = _VALUE_A0_INPUT_PORT,
    _D0_INPUT_PORT = _VALUE_D0_INPUT_PORT,
    _D1_INPUT_PORT = _VALUE_D1_INPUT_PORT,
    _D2_INPUT_PORT = _VALUE_D2_INPUT_PORT,
    _D3_INPUT_PORT = _VALUE_D3_INPUT_PORT,
    _D4_INPUT_PORT = _VALUE_D4_INPUT_PORT,
    _D5_INPUT_PORT = _VALUE_D5_INPUT_PORT,
    _D6_INPUT_PORT = _VALUE_D6_INPUT_PORT,
    _D7_INPUT_PORT = _VALUE_D7_INPUT_PORT,
    _D8_INPUT_PORT = _VALUE_D8_INPUT_PORT,
    _D9_INPUT_PORT = _VALUE_D9_INPUT_PORT,
    _D12_INPUT_PORT = _VALUE_D12_INPUT_PORT,
    _D13_INPUT_PORT = _VALUE_D13_INPUT_PORT,
    _D14_INPUT_PORT = _VALUE_D14_INPUT_PORT,
    _D15_INPUT_PORT = _VALUE_D15_INPUT_PORT,
    _NO_INPUT_PORT = _VALUE_NO_INPUT_PORT,
} EnumInputPort;

//--------------------------------------------------
// Enumerations of Output Port List
//--------------------------------------------------
typedef enum
{
    _P0_OUTPUT_PORT = _VALUE_P0_OUTPUT_PORT,
    _P1_OUTPUT_PORT = _VALUE_P1_OUTPUT_PORT,
    _P2_OUTPUT_PORT = _VALUE_P2_OUTPUT_PORT,
    _P3_OUTPUT_PORT = _VALUE_P3_OUTPUT_PORT,
    _P4_OUTPUT_PORT = _VALUE_P4_OUTPUT_PORT,
    _OUTPUT_PORT_NUM = _VALUE_OUTPUT_PORT_NUM,
    _NO_OUTPUT_PORT = 0xFF,
} EnumOutputPort;

//--------------------------------------------------
// Enumerations of eDp Output Port List
//--------------------------------------------------
typedef enum
{
    _DISPLAY_DP_TX_PORT_0 = 0x00,
    _DISPLAY_DP_TX_PORT_1,
    _DISPLAY_DP_TX_PORT_2,
    _DISPLAY_DP_TX_PORT_3,
    _DISPLAY_DP_TX_PORT_MAX,
    _DISPLAY_DP_TX_NO_PORT = 0xFF,
} EnumDisplayDpTxOutputPort;

//--------------------------------------------------
// Enumerations of Port Type List
//--------------------------------------------------
typedef enum
{
    _PORT_NONE = _VALUE_PORT_NONE,
    _PORT_VGA = _VALUE_PORT_VGA,
    _PORT_DVI = _VALUE_PORT_DVI,
    _PORT_HDMI = _VALUE_PORT_HDMI,
    _PORT_DP = _VALUE_PORT_DP,
    _PORT_MHL = _VALUE_PORT_MHL,
    _PORT_HDMI20 = _VALUE_PORT_HDMI20,
    _PORT_DUAL_DVI = _VALUE_PORT_DUAL_DVI,
} EnumPortType;

//--------------------------------------------------
// Enumerations of PCB TypeC Port List
//--------------------------------------------------
typedef enum
{
    _D0_TYPE_C_PORT = _VALUE_D0_TYPE_C_PORT,
    _D1_TYPE_C_PORT = _VALUE_D1_TYPE_C_PORT,
    _D2_TYPE_C_PORT = _VALUE_D2_TYPE_C_PORT,
    _D3_TYPE_C_PORT = _VALUE_D3_TYPE_C_PORT,
    _D4_TYPE_C_PORT = _VALUE_D4_TYPE_C_PORT,
    _D5_TYPE_C_PORT = _VALUE_D5_TYPE_C_PORT,
    _D6_TYPE_C_PORT = _VALUE_D6_TYPE_C_PORT,
    _P0_TYPE_C_PORT = _VALUE_P0_TYPE_C_PORT,
    _P1_TYPE_C_PORT = _VALUE_P1_TYPE_C_PORT,
    _P2_TYPE_C_PORT = _VALUE_P2_TYPE_C_PORT,
    _P3_TYPE_C_PORT = _VALUE_P3_TYPE_C_PORT,
    _P4_TYPE_C_PORT = _VALUE_P4_TYPE_C_PORT,
    _ADAPTOR_TYPE_C_PORT = _VALUE_ADAPTOR_TYPE_C_PORT,
    _NO_TYPE_C_PORT = _VALUE_NO_TYPE_C_PORT,
} EnumTypeCPcbPort;

//--------------------------------------------------
// Enumerations of Type-C Pin Assignment Mode
//--------------------------------------------------
typedef enum
{
    _TYPE_C_PIN_ASSIGNMENT_NONE = 0x00,
    _TYPE_C_PIN_ASSIGNMENT_C = 0x04,
    _TYPE_C_PIN_ASSIGNMENT_D = 0x08,
    _TYPE_C_PIN_ASSIGNMENT_E = 0x10,
    _TYPE_C_PIN_ASSIGNMENT_F = 0x20,
}EnumTypeCPinCfgType;

//--------------------------------------------------
// Enumerations of Embedded Type-C Module
//--------------------------------------------------
typedef enum
{
    _EMB_TYPE_C_NOT_EXIST = _VALUE_EMB_TYPE_C_NOT_EXIST,
    _EMB_TYPE_C_0 = _VALUE_EMB_TYPE_C_0,
    _EMB_TYPE_C_1 = _VALUE_EMB_TYPE_C_1,
    _EMB_TYPE_C_2 = _VALUE_EMB_TYPE_C_2,
    _EMB_TYPE_C_3 = _VALUE_EMB_TYPE_C_3,
}EnumTypeCEmbeddedList;

//--------------------------------------------------
// Enumerations of Hub DSP Index
//--------------------------------------------------
typedef enum
{
    _HUB_DSP0 = 0x00,
    _HUB_DSP1 = 0x01,
    _HUB_DSP2 = 0x02,
    _HUB_DSP3 = 0x03,
}EnumHubDsp;

//--------------------------------------------------
// Enumerations of USB Hub Switch Result From OSD
//--------------------------------------------------
typedef enum
{
    _HUB_D0_TYPE_C_PORT = _VALUE_D0_TYPE_C_PORT,
    _HUB_D1_TYPE_C_PORT = _VALUE_D1_TYPE_C_PORT,
    _HUB_D2_TYPE_C_PORT = _VALUE_D2_TYPE_C_PORT,
    _HUB_TYPE_B_PORT = 0x0F,
    _HUB_NONE_PORT = 0xF0,
}EnumUsbHubOSDResult;

//--------------------------------------------------
// Enumerations of ISP Subcode
//--------------------------------------------------
typedef enum
{
    _SCALER_BOOT_ENABLE_ISP_CHANNEL_OP_CODE = 0x01,
    _SCALER_BOOT_GET_ISP_START_ADDR_OP_CODE,
    _SCALER_BOOT_GET_ISP_USER_KEY_ADDR_OP_CODE,
    _SCALER_BOOT_GET_ISP_USER_FLAG_ADDR_OP_CODE,
    _SCALER_BOOT_GET_ISP_USER_SIGN_ADDR_OP_CODE,
    _SCALER_BOOT_GET_VERIFY_COPY_RESULT_OP_CODE,
    _SCALER_BOOT_SWITCH_CODE_OP_CODE,
    _SCALER_BOOT_GET_ISP_CURRENT_KEY_ADDR_OP_CODE,
    _SCALER_BOOT_GET_DUAL_BANK_INFO_OP_CODE,
    _SCALER_BOOT_GET_DUAL_BANK_BUNDLE_VERSION_OP_CODE, // 0x0A
    _SCALER_BOOT_SET_DUAL_BANK_BUNDLE_VERSION_OP_CODE,
    _SCALER_BOOT_GET_ISP_BACKGROUND_WRITE_TIME_OP_CODE, // 0x0C
} EnumISPSubOpCode;

//--------------------------------------------------
// Enumerations for decompress
//--------------------------------------------------
typedef enum
{
    _DECOMPRESS_SUCCESS,
    _DECOMPRESS_ERROR_INVALID_MAGIC_NUMBER,
    _DECOMPRESS_ERROR_WRT_BUFFER_OVERFLOW,
    _DECOMPRESS_ERROR_REF_OFFSET_UNDERFLOW,
    _DECOMPRESS_ERROR_INTPUT_DATA_ERROR,
    _DECOMPRESS_ERROR_EOF,
} EnumDecompressStatus;

//--------------------------------------------------
// Struct of unaligned access
//--------------------------------------------------
typedef struct
{
    __attribute__((packed))
    DWORD ulUnalignedDWORD;
} StructUnAlignedDWord;

typedef struct
{
    __attribute__((packed))
    WORD usUnalignedWORD;
} StructUnAlignedWord;

#endif

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#ifndef __ASSEMBLER__
extern void __initialize_off_region_sections(void);
extern void __initialize_ddr_sections(void);
#endif

//****************************************************************************
// Extra Include
//****************************************************************************
#ifndef __ASSEMBLER__
#include <MultiCpuHandShake.h>
#include <3rdParty.h>
#endif

#endif // End of #ifndef __GLOBAL_H__
