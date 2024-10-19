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
// ID Code      : ScalerDpMacTxInterface_User.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_DP_MAC_TX_SUPPORT == _ON)
//****************************************************************************
// DEFINITIONS / MACROS
//****************************************************************************
#if(_DP_TX_CONFIG_BY_USER_SUPPORT == _ON)
//--------------------------------------------------
// Macros of DP Tx Link Config Set by User
//--------------------------------------------------
#define GET_DP_MAC_TX_CONFIG_SETTING()                          (g_enumDpMacTxConfigSetting)
#define SET_DP_MAC_TX_CONFIG_SETTING(x)                         (g_enumDpMacTxConfigSetting = (x))
#endif

//--------------------------------------------------
// DP Tx LTTPR Mode Select
//--------------------------------------------------
#define _DP_TX_LTTPR_NON_LTTPR_MODE                             0x00
#define _DP_TX_LTTPR_TRANSPARENT_MODE                           0x01
#define _DP_TX_LTTPR_NON_TRANSPARENT_MODE                       0x02


//****************************************************************************
// STRUCT / TYPE / ENUM DEFINITTIONS
//****************************************************************************
//--------------------------------------------------
// Enumerations of DP Tx Link Config by User
//--------------------------------------------------
typedef enum
{
    _DP_TX_CONFIG_NONE = 0x00,
    _DP_TX_V11_1LANE_RBR = 0x01,
    _DP_TX_V11_2LANE_RBR = 0x02,
    _DP_TX_V11_4LANE_RBR = 0x03,
    _DP_TX_V11_1LANE_HBR = 0x04,
    _DP_TX_V11_2LANE_HBR = 0x05,
    _DP_TX_V11_4LANE_HBR = 0x06,
    _DP_TX_V12_1LANE_HBR2 = 0x07,
    _DP_TX_V12_2LANE_HBR2 = 0x08,
    _DP_TX_V12_4LANE_HBR2 = 0x09,
    _DP_TX_V14_1LANE_HBR3 = 0x0A,
    _DP_TX_V14_2LANE_HBR3 = 0x0B,
    _DP_TX_V14_4LANE_HBR3 = 0x0C,
} EnumDpMacTxConfig;

//--------------------------------------------------
// Enumerations of DP Tx Input Source
//--------------------------------------------------
typedef enum
{
    _DP_TX_SOURCE_NONE = 0x00,
    _DP_TX_SOURCE_MST2SST,
    _DP_TX_SOURCE_MST,
    _DP_TX_SOURCE_CLONE,
} EnumDPTxInputSource;

//****************************************************************************
// VARIABLE EXTERN
//****************************************************************************


//****************************************************************************
// FUNCTION EXTERN
//****************************************************************************


#endif
