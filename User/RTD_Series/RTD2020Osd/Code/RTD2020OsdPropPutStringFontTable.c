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
// ID Code      : RTD2020OsdPropPutStringFontTable.c No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "RTD2020UserInclude.h"

//****************************************************************************
// CODE TABLES
//****************************************************************************

//--------------------------------------------------
// Font Body Table
//--------------------------------------------------
#include "./TextTableBody/RTD2020OsdTextTableBody_0.h"

#include "./TextTableBody/RTD2020OsdTextTableBody_English.h"

#include "./TextTableBody/RTD2020OsdTextTableBody_Chinese.h"

#include "./TextTableBody/RTD2020OsdTextTableBody_FontTableDefine.h"

//--------------------------------------------------
// Description  :
// Input Value  : None
// Output Value : None
//--------------------------------------------------
BYTE OsdPutStringPropFontTable(BYTE ucLanguage, WORD usFontPoint)
{
    if(ucLanguage >= (sizeof(tOSD_TABLE_LANGUAGE_FONT_BODY) / sizeof(tOSD_TABLE_LANGUAGE_FONT_BODY[0])))
    {
        ucLanguage = 0;
    }

    return *(tOSD_TABLE_LANGUAGE_FONT_BODY[ucLanguage] + usFontPoint);
}

