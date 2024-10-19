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
// ID Code      : "RL6952_Example_HDMI_MultiEdid.h" No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

#if(_OSD_TYPE == _REALTEK_2020_OSD)

//****************************************************************************
// EDID LOCATION TABLES
//****************************************************************************
// Users Decide the location of Dx HdmiEdid to Edid Index
#if((_D3_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D3_MAX_HDMI_EDID_COUNT <= _HDMI_EXT_EDID_MAX_CNT))
// Only allow first 12 Index Choose Embeded or External, others force to Embedded Edid
BYTE code tD3_EdidLocatedTable[_D3_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EXTERNAL,   // EDID Index 1

#if(_D3_MAX_HDMI_EDID_COUNT > 2)
    _HDMI_EDID_EXTERNAL,   // EDID Index 2
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 3)
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 4)
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 5)
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 6)
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 7)
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 8)
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 9)
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 10)
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
#endif

#if(_D3_MAX_HDMI_EDID_COUNT > 11)
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
#endif
};

#elif((_D3_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D3_MAX_HDMI_EDID_COUNT > _HDMI_EXT_EDID_MAX_CNT))

BYTE code tD3_EdidLocatedTable[12] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EXTERNAL,   // EDID Index 1
    _HDMI_EDID_EXTERNAL,   // EDID Index 2
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
};

#endif

#if((_D4_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D4_MAX_HDMI_EDID_COUNT <= _HDMI_EXT_EDID_MAX_CNT))
// Only allow first 12 Index Choose Embeded or External, others force to Embedded Edid
BYTE code tD4_EdidLocatedTable[_D4_MAX_HDMI_EDID_COUNT] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EXTERNAL,   // EDID Index 1

#if(_D4_MAX_HDMI_EDID_COUNT > 2)
    _HDMI_EDID_EXTERNAL,   // EDID Index 2
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 3)
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 4)
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 5)
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 6)
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 7)
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 8)
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 9)
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 10)
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
#endif

#if(_D4_MAX_HDMI_EDID_COUNT > 11)
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
#endif
};

#elif((_D4_HDMI_MULTI_EDID_SUPPORT == _ON) && (_D4_MAX_HDMI_EDID_COUNT > _HDMI_EXT_EDID_MAX_CNT))

BYTE code tD4_EdidLocatedTable[12] =
{
    _HDMI_EDID_EXTERNAL,   // EDID Index 0
    _HDMI_EDID_EXTERNAL,   // EDID Index 1
    _HDMI_EDID_EXTERNAL,   // EDID Index 2
    _HDMI_EDID_EMBEDDED,   // EDID Index 3
    _HDMI_EDID_EMBEDDED,   // EDID Index 4
    _HDMI_EDID_EMBEDDED,   // EDID Index 5
    _HDMI_EDID_EMBEDDED,   // EDID Index 6
    _HDMI_EDID_EMBEDDED,   // EDID Index 7
    _HDMI_EDID_EMBEDDED,   // EDID Index 8
    _HDMI_EDID_EMBEDDED,   // EDID Index 9
    _HDMI_EDID_EMBEDDED,   // EDID Index 10
    _HDMI_EDID_EMBEDDED,   // EDID Index 11
};

#endif

BYTE code tNullEdidTable[1] = {0};

// All Port's Assembly HDMI Multi-EDID Index Loaction Table
BYTE * code tEdidMultiLocatedTable[] =
{
    tNullEdidTable,
    tNullEdidTable,
    tNullEdidTable,
#if(_D3_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD3_EdidLocatedTable,
#else
    tNullEdidTable,
#endif

#if(_D4_HDMI_MULTI_EDID_SUPPORT == _ON)
    tD4_EdidLocatedTable,
#else
    tNullEdidTable,
#endif
    tNullEdidTable,
};

#endif // End of #if(_OSD_TYPE == _REALTEK_2020_OSD)
