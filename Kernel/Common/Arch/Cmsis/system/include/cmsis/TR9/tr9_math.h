/********************************************************************************/
/*   Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.        */
/*                                                                              */
/*   Commercial License Usage                                                   */
/*   This software component is confidential and proprietary to Realtek         */
/*   Semiconductor Corp. Disclosure, reproduction, redistribution, in whole     */
/*   or in part, of this work and its derivatives without express permission    */
/*   is prohibited.                                                             */
/********************************************************************************/

/* ----------------------------------------------------------------------
 * Project:      CMSIS DSP Library
 * Title:        arm_math.h
 * Description:  Public header file for CMSIS DSP Library
 *
 * $Date:        27. January 2017
 * $Revision:    V.1.5.1
 *
 * Target Processor: Cortex-M cores
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2010-2017 ARM Limited or its affiliates. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*   SPDX-License-Identifier: LicenseRef-Realtek-Proprietary AND Apache-2.0     */

#ifndef _TR9_MATH_H
#define _TR9_MATH_H

/* Compiler specific diagnostic adjustment */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"

#undef  __CMSIS_GENERIC         /* enable NVIC and Systick functions */
//#define __CMSIS_GENERIC         /* disable NVIC and Systick functions */
#include "core_tr9.h"
//#undef  __CMSIS_GENERIC         /* enable NVIC and Systick functions */
#include "string.h"
#include "math.h"

#pragma GCC diagnostic pop

#endif /* _TR9_MATH_H */

/**
 *
 * End of file.
 */
