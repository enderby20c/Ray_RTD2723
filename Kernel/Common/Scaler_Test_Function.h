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
// ID Code      : Scaler_Test_Function.h No.0000
// Update Note  :
//----------------------------------------------------------------------------------------------------

//////////
// DDR3 //
//////////

//--------------------------------------------------
// DDR3 Phase Calibration or Phase Check (_ON : For All DDR3 Project)
//--------------------------------------------------
#define _DDR3_PHASE_CALIBRATION                                 _OFF
#define _DDR2_PHASE_CALIBRATION                                 _OFF
#define _DDR_BURN_IN_TEST                                       _OFF

#if(((_MEMORY_TYPE_CONFIG == _MEMORY_DDR3) && (_DDR3_PHASE_CALIBRATION == _ON)) ||\
    ((_MEMORY_TYPE_CONFIG == _MEMORY_DDR2) && (_DDR2_PHASE_CALIBRATION == _ON)))
#undef _MEMORY_PHASE_CALIBRATION_MODE
#define _MEMORY_PHASE_CALIBRATION_MODE                          _MEMORY_PHASE_CALIBRATION_FRC_MODE
#endif

#define _DDR3_PHASE_CAL_FRC_MODE_INTERNAL_PG                    _OFF

#if(((_DDR3_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)) ||\
    ((_DDR2_PHASE_CALIBRATION == _ON) && (_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)))

#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
#warning "NOTE: _FRAME_SYNC_LINE_BUFFER_SUPPORT Should Be _OFF!!!"
#endif

#endif

#if(_DDR_BURN_IN_TEST == _ON)
#if(_FRAME_SYNC_LINE_BUFFER_SUPPORT == _ON)
#warning "NOTE: _FRAME_SYNC_LINE_BUFFER_SUPPORT Should Be _OFF!!!"
#endif
#endif

#if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)
#if(_SDRAM_PHASE_CALIBRATION == _ON)
#warning "_SDRAM_PHASE_CALIBRATION Can Not Be Supported With No Memory!!!"
#endif

#if(_DDR1_PHASE_CALIBRATION == _ON)
#warning "_DDR1_PHASE_CALIBRATION Can Not Be Supported With No Memory!!!"
#endif

#if(_DDR3_PHASE_CALIBRATION == _ON)
#warning "_DDR3_PHASE_CALIBRATION Can Not Be Supported With No Memory!!!"
#endif

#if(_DDR3_PHASE_CHECK == _ON)
#warning "_DDR3_PHASE_CHECK Can Not Be Supported With No Memory!!!"
#endif
#endif // End of #if(_MEMORY_TYPE_CONFIG == _NO_MEMORY)


/////////////////
// FreeSync OD //
/////////////////

//--------------------------------------------------
// FreeSync Mode Measure OD Table (_ON : For FreeSync OD Measure)
//--------------------------------------------------
#define _FREESYNC_OD_MEASURE                                    _OFF

#if(_FREESYNC_OD_MEASURE == _ON)
#warning "_FREESYNC_OD_MEASURE is _ON!!!"

#if(_DEBUG_MESSAGE_SUPPORT == _OFF)
#warning "_DEBUG_MESSAGE_SUPPORT should be _ON!!!"
#endif
#endif


//////////////
// MHL Test //
//////////////

//--------------------------------------------------
// Debug Option For MHL (_ON : No CBUS Handshake ; _OFF : Need CBUS Handshake)
//--------------------------------------------------
#define _MHL_DEBUG_WITHOUT_CBUS_MODE                            _OFF


/////////////
// QC Test //
/////////////

//-----------------------------------------------
// Macro of PCB IO Toggle TEST Funtion
//-----------------------------------------------
#define _IO_TOGGLE_TEST_SUPPORT                                 _OFF

#if(_IO_TOGGLE_TEST_SUPPORT == _ON)
extern void IOToggleTest(void);
#endif


////////////////////
// Memory Test //
////////////////////

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR3)
#if(_DDR3_PHASE_CALIBRATION == _ON)
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
extern void ScalerDDR3OfflinePhaseCalFRCMode(void);
#endif
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
extern void ScalerDDR3OfflinePhaseCalMCUMode(void);
#endif
#endif
#endif

#if(_MEMORY_TYPE_CONFIG == _MEMORY_DDR2)
#if(_DDR2_PHASE_CALIBRATION == _ON)
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_FRC_MODE)
extern void ScalerDDR2OfflinePhaseCalFRCMode(void);
#endif
#if(_MEMORY_PHASE_CALIBRATION_MODE == _MEMORY_PHASE_CALIBRATION_MCU_MODE)
extern void ScalerDDR2OfflinePhaseCalMCUMode(void);
#endif
#endif
#endif

#if(_DDR_BURN_IN_TEST == _ON)
extern void ScalerDDRBurnInCRCTest(void);
#endif

//////////////////////
// DP Freesync Test //
//////////////////////

//--------------------------------------------------
// DP Force Freesync Support
//--------------------------------------------------
#define _DP_FORCE_FREESYNC_SUPPORT                              _OFF


#if(_DP_FORCE_FREESYNC_SUPPORT == _ON)
#if(_DP_FREESYNC_SUPPORT == _OFF)
#warning "_DP_FREESYNC_SUPPORT Should Be _ON When _DP_FORCE_FREESYNC_SUPPORT _ON"
#endif
#endif


////////////////////////
// HDMI Freesync Test //
////////////////////////

//--------------------------------------------------
// HDMI Force Freesync Support
//--------------------------------------------------
#define _HDMI_FORCE_FREESYNC_SUPPORT                            _OFF


#if(_HDMI_FORCE_FREESYNC_SUPPORT == _ON)
#if(_HDMI_FREESYNC_SUPPORT == _OFF)
#warning "_HDMI_FREESYNC_SUPPORT Should Be _ON When _HDMI_FORCE_FREESYNC_SUPPORT _ON"
#endif
#endif


///////////////////
// HDMI VRR Test //
///////////////////

//--------------------------------------------------
// HDMI Force VRR Support
//--------------------------------------------------
#define _HDMI_FORCE_VRR_SUPPORT                                 _OFF


#if(_HDMI_FORCE_VRR_SUPPORT == _ON)
#if(_HDMI21_VRR_SUPPORT == _OFF)
#warning "_HDMI21_VRR_SUPPORT Should Be _ON When _HDMI_FORCE_VRR_SUPPORT _ON"
#endif
#endif


//////////////////////
// EAGLE SIGHT Test //
//////////////////////
#if(_EAGLE_SIGHT_SUPPORT == _ON)
#ifndef _EAGLE_SIGHT_FREERUN_SUPPORT
#define _EAGLE_SIGHT_FREERUN_SUPPORT                            _OFF
#endif
#endif


//////////////////////
// Dt Range Test    //
//////////////////////

//--------------------------------------------------
// Dt Range Test
//--------------------------------------------------
#ifndef _DT_RANGE_TEST_SUPPORT
#define _DT_RANGE_TEST_SUPPORT                                  _OFF
#endif

#ifndef _DT_TEST_FORCE_10_BITS
#define _DT_TEST_FORCE_10_BITS                                  _OFF
#endif

#if((_FRAMESYNC_MODE_FIX_LASTLINE == _ON) && (_DRR_SUPPORT == _ON))
#define _DT_RANGE_TEST_FRAMENUM                                 24
#else
#define _DT_RANGE_TEST_FRAMENUM                                 4
#endif

#if(_DT_RANGE_TEST_SUPPORT == _ON)
#if(_DEBUG_MESSAGE_AUTOTEST == _OFF)
#warning "_DEBUG_MESSAGE_AUTOTEST should be _ON!!!"
#endif
#endif

/////////////////////
// Checker options //
/////////////////////
#ifndef __CHECKER__
#define __CHECKER__                                             _OFF
#endif

#if(__CHECKER__ == _ON)
#undef ScalerGetBit
#define ScalerGetBit(usAddr, ucAnd)                             (ucAnd)

#undef ScalerGetBit_EXINT
#define ScalerGetBit_EXINT(usAddr, ucAnd)                       (ucAnd)
#endif
