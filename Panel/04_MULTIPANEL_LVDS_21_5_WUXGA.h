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

#if(_PANEL_TYPE == _MULTIPANEL_LVDS_21_5_WUXGA)
//----------------------------------------------------------------------------------------------------
// ID Code      : _MULTIPANEL_LVDS_21_5_WUXGA.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////////////
// General Info //
//////////////////

//--------------------------------------------------
// Definitions for Panel Style
//--------------------------------------------------
#define _PANEL_STYLE                            _PANEL_LVDS

//--------------------------------------------------
// Definitions for LVDS Panel Configuration
//--------------------------------------------------
#define _PANEL_LVDS_OUTPUT_PORT                 _LVDS_2_PORT
#define _PANEL_LVDS_PANEL_SECTION               _LVDS_PANEL_1_SECTION
#define _PANEL_LVDS_TABLE_TYPE                  _LVDS_BIT_MAP_TABLE_1_3

//--------------------------------------------------
// Definitions for MultiPanel Support
//--------------------------------------------------
#define _PANEL_EXIST_MULTIPANEL                 _ON
#define _PANEL_MULTIPANEL_VARIABLE              _OFF


///////////////
// Parameter //
///////////////
#include <RTDMultiPanelTable/MultiPanel_template.h>


/////////////
// Display //
/////////////

//--------------------------------------------------
// Definitions for Frame Sync Margin (Unit: 0.1Hz)
//--------------------------------------------------
#define _PANEL_FRAME_SYNC_MARGIN                20


////////////////////
// VGA Auto Color //
////////////////////



///////////////////////////
// Color Characteristics //
///////////////////////////



/////////////////////////
// Color Default Table //
/////////////////////////

//--------------------------------------------------
// Color Default Value
//--------------------------------------------------
#include <RTDColorDefaultTable/ColorTableInclude.h>

#endif // End of #if(_PANEL_TYPE == _MULTIPANEL_LVDS_21_5_WUXGA)
