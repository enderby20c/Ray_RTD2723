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
// ID Code      : ScalerODInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_OD_FUNCTION == _ON)

#define CHECK_OD_PARAM_AVAILABLE(x)             (\
                                                    ((x) == _OD_PARAM_7_5_BPP) ||\
                                                    ((x) == _OD_PARAM_6_0_BPP) ||\
                                                    ((x) == _OD_PARAM_4_5_BPP)\
                                                )

#endif

//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
typedef enum
{
    _OD_PARAM_OFF,
    _OD_PARAM_4_5_BPP,
    _OD_PARAM_6_0_BPP,
    _OD_PARAM_7_5_BPP,
} EnumODParamIndex;

typedef enum
{
    _OD_OFF,
    _OD_USER,
#if(_OD_BY_POSITION_SUPPORT == _ON)
    _OD_USER_BYPOS,
#endif
} EnumODMode;

typedef struct
{
#if(_TWO_CHIP_DATA_EXCHANGE_SUPPORT == _ON)
    BYTE ucTableGroup;
    BYTE ucTableIndex;
#else
    BYTE ucBank;
    BYTE *pucTable;
#endif
} StructODTableInfo;

#if(_OD_BY_POSITION_SUPPORT == _ON)
typedef enum
{
    _OD_BYPOS_LINEAR_GLUT,
    _OD_BYPOS_NONLINEAR_GLUT,
} EnumODGLUTType;

typedef enum
{
    _OD_BYPOS_GAIN_RND_0BIT,
    _OD_BYPOS_GAIN_RND_1BIT,
    _OD_BYPOS_GAIN_RND_2BIT,
    _OD_BYPOS_GAIN_RND_3BIT,
    _OD_BYPOS_GAIN_RND_4BIT,
    _OD_BYPOS_GAIN_RND_5BIT,
    _OD_BYPOS_GAIN_RND_6BIT,
    _OD_BYPOS_GAIN_RND_7BIT,
} EnumODByPosODGainRNDBit;

typedef enum
{
    _OD_BYPOS_REGION_16LINE,
    _OD_BYPOS_REGION_32LINE,
    _OD_BYPOS_REGION_64LINE,
    _OD_BYPOS_REGION_128LINE,
} EnumODByPosRegionSize;

typedef struct
{
    BYTE ucDeltaGain;
    StructODTableInfo stODTableInfo;

    BYTE b1ODByPosEnable : 1;
    BYTE b2RegionSize : 2;
    StructODTableInfo stODByPosTableInfo;
} StructODUserByPosData;
#endif

typedef struct
{
    BYTE ucDeltaGain;
    StructODTableInfo stODTableInfo;
} StructODUserData;

typedef union
{
    StructODUserData stODUserData;
#if(_OD_BY_POSITION_SUPPORT == _ON)
    StructODUserByPosData stODUserByPosData;
#endif
} UnionODData;

typedef struct
{
    EnumODMode enumODMode;
    UnionODData unODData;
} StructODSetting;

typedef enum
{
    _OD_SUPPORT_STATUS,
    _OD_REALTIME_ENABLE_STATUS,
} EnumODStatusType;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************

