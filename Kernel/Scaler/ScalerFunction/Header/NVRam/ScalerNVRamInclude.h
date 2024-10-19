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
// ID Code      : ScalerNVRamInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
//--------------------------------------------------
// Flash Support List
//--------------------------------------------------
#define _FLASH_W25X20A                              0
#define _FLASH_W25X21CL                             1
#define _FLASH_PM25LV020                            2
// This is MX25L2026D, it is not same with MX25L2026E
#define _FLASH_MX25L2026                            3
#define _FLASH_EN25F20                              4
#define _FLASH_PM25LD020                            5
// It is the same with MX25L2026E and KH25L2026E
#define _FLASH_MX25L2025                            6
// It is the same with MX25L4026E and KH25L4026E and KH25L4006E
#define _FLASH_MX25L4006E                           7
#define _FLASH_SST25LF020A                          8
#define _FLASH_W25X41CL                             9
#define _FLASH_FM25F04                              10
#define _FLASH_N25S40                               11
#define _FLASH_A25L040                              12
//W25Q80DV use the same _FLASH_W25Q80BV
#define _FLASH_W25Q80BV                             13
#define _FLASH_PM25LQ020A                           14
#define _FLASH_MX25L4026D                           15
#define _FLASH_W25X40CL                             16
#define _FLASH_EN25F20A                             17
#define _FLASH_EN25F40A                             18
#define _FLASH_EN25Q40A                             19
//EN25Q80A and EN25Q80B use the same _FLASH_EN25Q80
#define _FLASH_EN25Q80                              20
// GD25Q080C use the same _FLASH_GD25Q080B
#define _FLASH_GD25Q80B                             21
#define _FLASH_GD25M21B                             22
#define _FLASH_GD25M41B                             23
// KH25L8006E and MX25V80066 use the same _FLASH_MX25L8006E
#define _FLASH_MX25L8006E                           24
#define _FLASH_PM25LQ080                            25
//GD25Q40C use the same _FLASH_GD25Q40B
#define _FLASH_GD25Q40B                             26
#define _FLASH_MX25L1606E                           27
#define _FLASH_MX25L3206E                           28
#define _FLASH_A25L016                              29
//W25Q16JVZPIQ use the same _FLASH_W25Q16DV
#define _FLASH_W25Q16DV                             30
#define _FLASH_A25L032                              31
#define _FLASH_W25Q32F                              32
#define _FLASH_GD25Q16                              33
#define _FLASH_MX25L1633E                           34
#define _FLASH_GD25Q16C                             35
//MX25L32356 use the same _FLASH_MX25L3233F
#define _FLASH_MX25L3233F                           36
#define _FLASH_PM25LQ040                            37
#define _FLASH_GD25Q41B                             38
#define _FLASH_EN25QH32A                            39
#define _FLASH_MX25V1635F                           40
#define _FLASH_AT25SF041                            41
#define _FLASH_MX25L6433F                           42
#define _FLASH_PM25LQ016                            43
#define _FLASH_GD25Q32C                             44
#define _FLASH_MX25V8035F                           45
#define _FLASH_AT25SF321                            46
#define _FLASH_FM25Q08A                             47
#define _FLASH_FM25Q04                              48
#define _FLASH_W25Q16JVSIM                          49
#define _FLASH_W25Q32JVSIM                          50
#define _FLASH_IS25LQ040B                           51
// MX25L3236FM2I-08G use the same _FLASH_KH25L3236F
#define _FLASH_KH25L3236F                           52
#define _FLASH_W25Q16JVSIQ                          53
#define _FLASH_MX25V4035F                           54
#define _FLASH_P25Q40H                              55
// This is different with FM25Q08A
#define _FLASH_FM25Q08                              56
//P25D80H use the same _FLASH_P25Q80H
#define _FLASH_P25Q80H                              57
#define _FLASH_P25Q16H                              58
#define _FLASH_BY25D40C                             59
#define _FLASH_GD25VQ16C                            60
#define _FLASH_MD25D80DT                            61
#define _FLASH_MD25D40DT                            62
#define _FLASH_EN25QH16B                            63
#define _FLASH_IS25LP080D                           64
#define _FLASH_BY25D40ASTIG                         65
#define _FLASH_BY25D16ASTIG                         66
#define _FLASH_BY25D80ASTIG                         67
#define _FLASH_XM25QH80B                            68
#define _FLASH_XM25QH40B                            69
#define _FLASH_XT25F08B                             70
#define _FLASH_W25Q32JVSSIQ                         71
//P25Q32SH use the same _FLASH_P25Q32H
#define _FLASH_P25Q32H                              72
#define _FLASH_W25Q128JVSQ                          73
#define _FLASH_XM25QH16C                            74
#define _FLASH_BY25Q80BSTIG                         75
#define _FLASH_XM25QH32CHIGT                        76
#define _FLASH_AT25SF041B                           77
#define _FLASH_AT25SF081B                           78
#define _FLASH_AT25SF321B                           79
#define _FLASH_W25Q64JVSIQ                          80
#define _FLASH_AT25SF161B                           81
#define _FLASH_EN25QH32B                            82
#define _FLASH_ZB25VQ40A                            83
// ZB25VQ80B use the same _FLASH_ZB25VQ80A
#define _FLASH_ZB25VQ80A                            84
#define _FLASH_ZB25VQ16A                            85
// UC25WQ80IAT and UC25HQ80IB use the same _FLASH_UC25HQ80IAT
#define _FLASH_UC25HQ80IAT                          86
#define _FLASH_IS25LP040E                           87
#define _FLASH_IS25LP016D                           88
#define _FLASH_ZB25VQ64B                            89
#define _FLASH_P25Q16SH                             90
#define _FLASH_EN25Q80C                             91
#define _FLASH_GD25Q64E                             92
#define _FLASH_PY25Q80HB                            93
#define _FLASH_GD25Q128E                            94
#define _FLASH_PY25Q128HA                           95
#define _FLASH_BY25Q32CSSIG                         96
#define _FLASH_EN25QE16A                            97
#define _FLASH_EN25QE32A                            98
#define _FLASH_P25Q64SH                             99
#define _FLASH_EN25QX64A                            100
#define _FLASH_EN25QX128A                           101
#define _FLASH_MX25L12833F                          102
#define _FLASH_EN25Q40B                             103
#define _FLASH_GT25Q80A                             104
#define _FLASH_UC25HQ16                             105
#define _FLASH_W25Q80RVSNIQ                         106
#define _FLASH_GT25Q16A                             107
#define _FLASH_GT25Q40C                             108
#define _FLASH_GT25Q32AU                            109
#define _FLASH_PY25Q16HB                            110
#define _FLASH_MX25L25645G                          111
#define _FLASH_PY25Q256HB                           112
#define _FLASH_PY25Q64HA                            113
#define _FLASH_PY25Q40HB                            114
#define _FLASH_FM25Q16                              115
#define _FLASH_FM25Q08B                             116
#define _FLASH_ZB25VQ16C                            117
#define _FLASH_UC25HD40I                            118
#define _FLASH_XM25QH256C                           119
#define _FLASH_FM25Q32B                             120
#define _FLASH_XM25QH64D                            121
#define _FLASH_FM25Q64A                             122
#define _FLASH_XM25QH128D                           123
#define _FLASH_TYPE_END                             124
#define _FLASH_TOTAL_COUNT                          _FLASH_TYPE_END
#define _FLASH_DEFAULT_TYPE                         _FLASH_W25X20A
#define _FLASH_UNDETECT                             0xFE

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Definitions of Version Code related Infor.
//--------------------------------------------------
typedef struct
{
    BYTE ucIDCheck1OpCode; // ID check 1 OP code(0x9F/0x90/0xAB)
    BYTE ucIDCheck1_ID0; // ID check 1 ID
    BYTE ucIDCheck1_ID1;
    BYTE ucIDCheck1_ID2;
    BYTE ucIDCheck2OpCode; // ID check 1 OP code(0x90/0xAB)
    BYTE ucIDCheck2_ID0; // ID check 1 ID
    BYTE ucIDCheck2_ID1;
    BYTE ucIDCheck2_ID2;
    BYTE ucWRENOpCode; // WREN OP code
    BYTE ucWRDisOpCode; // WRDis OP code
    BYTE ucPageEraseOpCode; // Page erase OP code
    BYTE ucUnprotectWRSR; // Unprotect status register value
    BYTE ucProtectWRSR; // Protect status register value
    BYTE ucProtectWRSR2; // Protect status register2 value
} StructFlashInformation;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))
extern BYTE g_ucNVRamFlashType;
#endif

//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************
#if((_FLASH_WRITE_FUNCTION_SUPPORT == _ON) || (_FLASH_WR_PROTECT == _ON))
extern void ScalerFlashDetectFlashType(void);
#if(_FLASH_WRITE_FUNCTION_SUPPORT == _ON)
#if(_HW_CPU32_IS_BOOT_CPU == _TRUE)
extern bit ScalerFlashWriteMainProcess(WORD usBank, WORD usAddr, WORD usLength, BYTE *pucData, bit bEnFlashSR, bit bDisFlashSR);
#endif
#endif
#endif
