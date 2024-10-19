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
// ID Code      : RTD2020DataExchangeInclude.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//--------------------------------------------------
// Data Exchange Command User Data Type
//--------------------------------------------------
typedef enum
{
    _DATA_EXCHANGE_USER_CMD_NONE = 0x00,
    _DATA_EXCHANGE_USER_DATA_OD_GAIN,
    _DATA_EXCHANGE_USER_DATA_OD_USER,
    _DATA_EXCHANGE_USER_DATA_OD_USER_BYPOS,
    _DATA_EXCHANGE_USER_DATA_OD_ENABLE,
} EnumDataExchangeUserDataType;

typedef enum
{
    _OD_USER_DATA_OD_MODE,
    _OD_USER_DATA_OD_GAIN,
    _OD_USER_DATA_OD_TABLE_GROUP,
    _OD_USER_DATA_OD_TABLE_INDEX,
    //-------------------------------------
    _DATA_EXCHANGE_USER_DATA_OD_USER_CONTENT_LEN,
} EnumDataExchangeUserDataOdUserContent;

typedef enum
{
    _OD_USER_BYPOS_DATA_OD_MODE,
    _OD_USER_BYPOS_DATA_OD_GAIN,
    _OD_USER_BYPOS_DATA_OD_TABLE_GROUP,
    _OD_USER_BYPOS_DATA_OD_TABLE_INDEX,

    _OD_USER_BYPOS_DATA_BYPOS_ENABLE,
    _OD_USER_BYPOS_DATA_BYPOS_REGION_SIZE,
    _OD_USER_BYPOS_DATA_BYPOS_TABLE_INDEX,
    //-------------------------------------
    _DATA_EXCHANGE_USER_DATA_OD_USER_BYPOS_CONTENT_LEN,
} EnumDataExchangeUserDataOdUserByPosContent;
