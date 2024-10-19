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
// ID Code      : EnergyStarTable.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------
//****************************************************************************
// CODE TABLES
//****************************************************************************

#ifdef __USER_COMMON_COLOR__

BYTE code tENERGY_STAR_ACTIVE_RANGE[] =
{
// The average of (R+G+B) value to setting different backlight.
//  0   1   2   3   4    5    6    7    8    9    10   11   12   13   14
    43, 59, 76, 85, 97, 104, 111, 120, 125, 133, 138, 143, 150, 154, 160,
};

BYTE code tENERGY_STAR_BACKLIGHT_TABLE[] =
{
// The percentage of OSD backlight value in each average of (R+G+B) value. (unit: %)
//  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
    64, 66, 68, 71, 73, 76, 78, 80, 83, 85, 88, 90, 92, 95, 97, 100,
};

#endif

