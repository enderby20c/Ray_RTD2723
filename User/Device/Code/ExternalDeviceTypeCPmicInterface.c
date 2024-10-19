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
// ID Code      : ExternalDeviceTypeCPmicInterface.c
// Update Note  :
//----------------------------------------------------------------------------------------------------

#include "UserCommonInclude.h"
#include "../Header/TypeC_Pmic_SILERGY_SY9329.h"
#include "../Header/TypeC_Pmic_ONSEMI_NCP81239.h"
#include "../Header/TypeC_Pmic_SILERGY_SY9228.h"
#include "../Header/TypeC_Pmic_System_Solution.h"
#include "../Header/TypeC_Pmic_INTERSIL_RAA489800.h"
#include "../Header/TypeC_Pmic_SILERGY_SY8665.h"
#include "../Header/TypeC_Pmic_MPS_MP4247.h"
#include "../Header/TypeC_Pmic_VISHAY_SIC437A.h"

#if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && ((_PORT_CTRL_EMBEDDED_SUPPORT == _ON) || (_PORT_CTRL_TCPM_SUPPORT == _ON)) && (_TYPE_C_PMIC_SUPPORT == _ON))

//****************************************************************************
// FUNCTION DEFINITIONS
//****************************************************************************
//--------------------------------------------------
// Description  : Type-C PMIC Initial Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicACOnInitial(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329ACOnInitial(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239ACOnInitial(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228ACOnInitial(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionACOnInitial(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800ACOnInitial(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665ACOnInitial(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247ACOnInitial(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aACOnInitial(enumTypeCPcbPort);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Type-C PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicUnattachReset(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset(enumTypeCPcbPort);
#endif
            break;

        default:
            break;
    }
}

//--------------------------------------------------
// Description  : Type-C PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicUnattachReset_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_EXINT0(enumTypeCPcbPort);
#endif
            break;

        default:
            break;
    }
}

#if(_PORT_CTRL_TCPM_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C PMIC Reset Settings
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : None
//--------------------------------------------------
void ExternalDeviceInterfaceTypeCPmicUnattachReset_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            // ExternalDeviceInterfaceTypeCPmicSy9329UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            // ExternalDeviceInterfaceTypeCPmicNcp81239UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            ExternalDeviceInterfaceTypeCPmicSy9228UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            ExternalDeviceInterfaceTypeCPmicSysSolutionUnattachReset_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            // ExternalDeviceInterfaceTypeCPmicRaa489800UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            // ExternalDeviceInterfaceTypeCPmicSy8665UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            // ExternalDeviceInterfaceTypeCPmicMp4247UnattachReset_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            // ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachReset_WDINT(enumTypeCPcbPort);
#endif
            break;

        default:
            break;
    }
}
#endif // End of #if(_PORT_CTRL_TCPM_SUPPORT == _ON)

//--------------------------------------------------
// Description  : Control Type-C PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Control Type-C PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Control Type-C PMIC to Directed Voltage
// Input Value  : enumTypeCPcbPort : PCB Port
//                bPowerDirection : _PD_POWER_SNK / _PD_POWER_SRC
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVoltageCurrentSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, WORD usVoltage, WORD usCurrent)
{
    enumPowerDirection = enumPowerDirection;
    usVoltage = usVoltage;
    usCurrent = usCurrent;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVoltageCurrentSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, usVoltage, usCurrent);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Turn off Type-C PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Turn off Type-C PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_EXINT0(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Turn off Type-C PMIC
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicTurnOff_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329TurnOff_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239TurnOff_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228TurnOff_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionTurnOff_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800TurnOff_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665TurnOff_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247TurnOff_WDINT(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTurnOff_WDINT(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    enumEn = enumEn;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge(enumTypeCPcbPort, enumEn);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    enumEn = enumEn;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_EXINT0(enumTypeCPcbPort, enumEn);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC VBUS Discharge Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumEn : _ENABLE / _DISABLE
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicVbusDischarge_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDischarge enumEn)
{
    enumEn = enumEn;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247VbusDischarge_WDINT(enumTypeCPcbPort, enumEn);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbusDischarge_WDINT(enumTypeCPcbPort, enumEn);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_EXINT0(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC Switch Control
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumSwitchControl : _ENABLE / _DISABLE
//                enumPowerDirection : _SRC / _SNK
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicSwitchControl_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicSwitchControl enumSwitchControl, EnumTypeCPmicDirection enumPowerDirection)
{
    enumSwitchControl = enumSwitchControl;
    enumPowerDirection = enumPowerDirection;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247SwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aSwitchControl_WDINT(enumTypeCPcbPort, enumSwitchControl, enumPowerDirection);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

#if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_EXINT0(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC Output Mode Setting
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerDirection : _SRC / _SNK
//                enumOutputPdoType : PDO Type
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicPpsOutputModeSetting_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPmicDirection enumPowerDirection, EnumTypeCPDPdoType enumOutputPdoType)
{
    enumPowerDirection = enumPowerDirection;
    enumOutputPdoType = enumOutputPdoType;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247PpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPpsOutputModeSetting_WDINT(enumTypeCPcbPort, enumPowerDirection, enumOutputPdoType);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C PMIC Read Output Status
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Output Mode (Fixed Voltage/PPS)
//--------------------------------------------------
EnumTypeCPmicOperationMode ExternalDeviceInterfaceTypeCPmicReadPpsOperationModeStatus_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPpsOperationModeStatus_EXINT0(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_NONE_MODE_OPERATION;
}
#endif // End of #if(_PORT_CTRL_EMB_PD3_PPS_SUPPORT == _ON)

#if(_EMB_TYPE_C_PMIC_DEBUG == _ON)
//--------------------------------------------------
// Description  : Type-C PMIC Status
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicDebugCheckStatus(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329DebugCheckStatus(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239DebugCheckStatus(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228DebugCheckStatus(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionDebugCheckStatus(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800DebugCheckStatus(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665DebugCheckStatus(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247DebugCheckStatus(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aDebugCheckStatus(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}
#endif // End of #if(_EMB_TYPE_C_PMIC_DEBUG == _ON)

#if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C PMIC VBUS Current Reading
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : usCurrent : 0 ~ 500 (Unit = 10mA)
//--------------------------------------------------
WORD ExternalDeviceInterfaceTypeCPmicReadPmicAdcCurrentValue(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ReadPmicAdcCurrentValue(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aReadPmicAdcCurrentValue(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return 0x00;
}
#endif // End of #if(_TYPE_C_PMIC_FW_POLLING_OCP_SUPPORT == _ON)

#if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)
//--------------------------------------------------
// Description  : PMIC Vbus Force Off Config
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control result (Fail/Success)
//--------------------------------------------------
EnumTypeCPmicControlResult ExternalDeviceInterfaceTypeCPmicForceOffConfig(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9329)
            return ExternalDeviceInterfaceTypeCPmicSy9329ForceOffConfig(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_NCP81239)
            return ExternalDeviceInterfaceTypeCPmicNcp81239ForceOffConfig(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY9228)
            return ExternalDeviceInterfaceTypeCPmicSy9228ForceOffConfig(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SYS_SOLUTION)
            return ExternalDeviceInterfaceTypeCPmicSysSolutionForceOffConfig(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_RAA489800)
            return ExternalDeviceInterfaceTypeCPmicRaa489800ForceOffConfig(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_SY8665)
            return ExternalDeviceInterfaceTypeCPmicSy8665ForceOffConfig(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_MP4247)
            return ExternalDeviceInterfaceTypeCPmicMp4247ForceOffConfig(enumTypeCPcbPort);

#elif(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aForceOffConfig(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}
#endif // End of #if(_PORT_CTRL_EMB_UNATTACH_HW_FORCE_VBUS_OFF == _ON)

/////////////////////////////////////
// EIZO PMIC SIC437A CUSTOMIZED FW //
/////////////////////////////////////
#if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
//--------------------------------------------------
// Description  : Type-C Attached Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicAttachProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aAttachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Unattached Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicUnattachProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Unattached Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicUnattachProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aUnattachProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Power Transition Start Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                usVoltage : 300 ~ 2100 (Unit = 10mV)
//                usCurrent : 0 ~ 500 (Unit = 10mA)
//                pusSrcAdjustPowerTime : 25 ~ 35 (Unit = ms)
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicTransitionStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, WORD usVoltage, WORD usCurrent, WORD *pusSrcAdjustPowerTime)
{
    usVoltage = usVoltage;
    usCurrent = usCurrent;
    pusSrcAdjustPowerTime = pusSrcAdjustPowerTime;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionStartProc_EXINT0(enumTypeCPcbPort, usVoltage, usCurrent, pusSrcAdjustPowerTime);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Power Transition Ready Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicTransitionReadyProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aTransitionReadyProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Power Role Swap Start Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicPRSwapStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Power Role Swap Inital Sink Rcv. PS_RDY Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicPRSwapToSrcProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aPRSwapToSrcProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Send/Receive Hard Reset Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicHardRstStartProc(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Send/Receive Hard Reset Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicHardRstStartProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Send/Receive Hard Reset Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicHardRstStartProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstStartProc_WDINT(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C as SRC and Vbus Has Turned Off During Hard Reset Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicHardRstVbusOffProc(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aHardRstVbusOffProc(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Detect OCP Event Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicOcpProc(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Detect OCP Event Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicOcpProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Detect OCP Event Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicOcpProc_WDINT(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOcpProc_WDINT(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Detect OVP Event Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicOvpProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort)
{
    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aOvpProc_EXINT0(enumTypeCPcbPort);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}

//--------------------------------------------------
// Description  : Type-C Vbus 5V Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Vbus Check Type : _TYPE_C_VBUS_CHECK_0V / _TYPE_C_VBUS_CHECK_5V
//--------------------------------------------------
EnumTypeCVbusCheckType ExternalDeviceInterfaceTypeCPmicVbus5VReadyProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus5VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_VBUS_CHECK_NONE;
}

//--------------------------------------------------
// Description  : Type-C Vbus 0V Power Control Flow
// Input Value  : enumTypeCPcbPort : PCB Port
//                enumPowerRole : _TYPE_C_POWER_SRC / _TYPE_C_POWER_SNK
// Output Value : Control Result : _SUCCESS / _FAIL
//--------------------------------------------------
BYTE ExternalDeviceInterfaceTypeCPmicVbus0VReadyProc_EXINT0(EnumTypeCPcbPort enumTypeCPcbPort, EnumTypeCPowerRole enumPowerRole)
{
    enumPowerRole = enumPowerRole;

    switch(enumTypeCPcbPort)
    {
        case _D0_TYPE_C_PORT:
#if(_D0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D1_TYPE_C_PORT:
#if(_D1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _D2_TYPE_C_PORT:
#if(_D2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P0_TYPE_C_PORT:
#if(_P0_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P1_TYPE_C_PORT:
#if(_P1_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P2_TYPE_C_PORT:
#if(_P2_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P3_TYPE_C_PORT:
#if(_P3_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _P4_TYPE_C_PORT:
#if(_P4_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        case _ADAPTOR_TYPE_C_PORT:
#if(_ADAPTOR_TYPE_C_PMIC_TYPE == _PMIC_VISHAY_SIC437A)
            return ExternalDeviceInterfaceTypeCPmicVishaySic437aVbus0VReadyProc_EXINT0(enumTypeCPcbPort, enumPowerRole);
#endif
            break;

        default:

            break;
    }

    return _TYPE_C_PMIC_CONTROL_FAIL;
}
#endif // End of #if(_TYPE_C_EIZO_CUSTOMIZED_PMIC_SIC437A_SUPPORT == _ON)
#endif // End of #if((_TYPE_C_PORT_CTRL_SUPPORT == _ON) && (_PORT_CTRL_EMBEDDED_SUPPORT == _ON) && (_TYPE_C_PMIC_SUPPORT == _ON))

