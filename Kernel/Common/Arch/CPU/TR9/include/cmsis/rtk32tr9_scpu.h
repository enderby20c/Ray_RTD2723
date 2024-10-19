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

/**************************************************************************//**
 * @file     rtk32tr9_scpu.h
 * @brief    CMSIS RISCV# Core Peripheral Access Layer Header File for
 *           Device rtk32rx3081
 * @version  V3.10
 * @date     23. November 2012
 *
 * @note
 *
 ******************************************************************************/

#define TR9_SW_INT0_CTRL_ADDR               (0xA3000410)
#define TR9_SW_INT1_CTRL_ADDR               (0xA3000414)

#define SET_SCPU_SW_INT0()                  {\
                                                Scaler32SetDWord(TR9_SW_INT0_CTRL_ADDR, 1);\
                                                Scaler32GetDWord(TR9_SW_INT0_CTRL_ADDR);\
                                            }

#define SET_SCPU_SW_INT1()                  {\
                                                Scaler32SetDWord(TR9_SW_INT1_CTRL_ADDR, 1);\
                                                Scaler32GetDWord(TR9_SW_INT1_CTRL_ADDR);\
                                            }
