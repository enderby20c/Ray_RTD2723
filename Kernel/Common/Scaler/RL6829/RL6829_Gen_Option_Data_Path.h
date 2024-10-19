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
// ID Code      : RL6829_Gen_Option.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

////////
// HW //
////////
//--------------------------------------------------
// HW I-Domain Path Setting
//--------------------------------------------------
#define _HW_I_DOMAIN_PATH_COUNT                                 6

#define _HW_I_DOMAIN_M1_PATH_SUPPORT                            _ON
#define _HW_I_DOMAIN_M2_PATH_SUPPORT                            _ON
#define _HW_I_DOMAIN_S1_PATH_SUPPORT                            _ON
#define _HW_I_DOMAIN_S2_PATH_SUPPORT                            _ON
#define _HW_I_DOMAIN_S3_PATH_SUPPORT                            _ON
#define _HW_I_DOMAIN_S4_PATH_SUPPORT                            _ON

//--------------------------------------------------
// HW M-Domain Path Setting
//--------------------------------------------------
#define _HW_M_DOMAIN_M1_PATH_SUPPORT                            _ON
#define _HW_M_DOMAIN_M2_PATH_SUPPORT                            _ON
#define _HW_M_DOMAIN_S1_PATH_SUPPORT                            _ON
#define _HW_M_DOMAIN_S2_PATH_SUPPORT                            _ON
#define _HW_M_DOMAIN_S3_PATH_SUPPORT                            _ON
#define _HW_M_DOMAIN_S4_PATH_SUPPORT                            _ON

//--------------------------------------------------
// HW D-Domain Path Count  Max
//--------------------------------------------------
#define _HW_D_DOMAIN_PATH_COUNT                                 6
#define _HW_D_DOMAIN_RGN_COUNT_MAX                              6

#define _HW_D_DOMAIN_M1_PATH_SUPPORT                            _ON
#define _HW_D_DOMAIN_M2_PATH_SUPPORT                            _ON
#define _HW_D_DOMAIN_M3_PATH_SUPPORT                            _ON
#define _HW_D_DOMAIN_M4_PATH_SUPPORT                            _ON
#define _HW_D_DOMAIN_S1_PATH_SUPPORT                            _ON
#define _HW_D_DOMAIN_S2_PATH_SUPPORT                            _ON

//--------------------------------------------------
// HW I-Domain Input Path
//--------------------------------------------------
//! input path for PIP SUB region
#define _HW_SUB_REGION_INPUT_PATH                               ((GET_D_DOMAIN_PATH() == _D_DOMAIN_4_PATH) ? _INPUT_PATH_S3_S4 : _INPUT_PATH_S1_S2)


//--------------------------------------------------
// HW all data paths in I/M/D domains
//--------------------------------------------------
//! all HW I-domain paths
#define _HW_I_DOMAIN_INPUT_PATH_ALL                             (_INPUT_PATH_M1 | _INPUT_PATH_M2 | _INPUT_PATH_S1 | _INPUT_PATH_S2 | _INPUT_PATH_S3 | _INPUT_PATH_S4)

//! all HW M-domain paths
#define _HW_M_DOMAIN_DISP_PATH_ALL                              (_MDOMAIN_DISP_PATH_M1_M2 | _MDOMAIN_DISP_PATH_S1_S2 | _MDOMAIN_DISP_PATH_S3_S4)

//! all HW D-domain paths
#define _HW_D_DOMAIN_RGN_ALL                                    (_DDOMAIN_RGN_R1_A1 | _DDOMAIN_RGN_R1_A2 | _DDOMAIN_RGN_R2_A1 | _DDOMAIN_RGN_R2_A2 | _DDOMAIN_RGN_R3_A1 | _DDOMAIN_RGN_R3_A2)

//--------------------------------------------------
// HW M Domain Disp Sub Path
//--------------------------------------------------
// M Domain Disp Sub Path for PIP/ PBP LR mode
#define _HW_M_DOMAIN_DISP_SUB_PATH                              (_MDOMAIN_DISP_PATH_S1_S2)

//--------------------------------------------------
// HW Data Path speed Max
//--------------------------------------------------
#define _HW_DATA_PATH_SPEED_LIMIT                               (7000) // Unit: 0.1MHz
