/**
 * Copyright 2020 Marius
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stm32f405xx.h"
#include "app_uart.h"
#include "log.h"

#define fault_log LOG_ERROR


void fault_init(void)
{
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);


    /* Cover are around 0x0 */
    MPU_Region_InitTypeDef mpu_init = {
        .Enable = MPU_REGION_ENABLE,
        .Number = MPU_REGION_NUMBER0,
        .BaseAddress = 0x0,
        .Size = MPU_REGION_SIZE_128B,

        .DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE,
        .AccessPermission =  MPU_REGION_NO_ACCESS,
        .TypeExtField = MPU_TEX_LEVEL0,
        .IsBufferable = MPU_ACCESS_NOT_BUFFERABLE,
        .IsCacheable = MPU_ACCESS_CACHEABLE,
        .IsShareable = MPU_ACCESS_NOT_SHAREABLE,
        .SubRegionDisable = 0,
    };

    HAL_MPU_ConfigRegion(&mpu_init);


}

static void fault_shutdown(void)
{
    /* Abort any pending UART transaction to prepare for logging */
    log_abort();
    /* Shutdown critical systems, e.g. PWM */
}

void fault_hardfault_handler_c(unsigned long *hardfault_args, unsigned int lr_value)
{
    unsigned long stacked_r0;
    unsigned long stacked_r1;
    unsigned long stacked_r2;
    unsigned long stacked_r3;
    unsigned long stacked_r12;
    unsigned long stacked_lr;
    unsigned long stacked_pc;
    unsigned long stacked_psr;
    unsigned long cfsr;
    unsigned long bus_fault_address;
    unsigned long memmanage_fault_address;

    fault_shutdown();

    bus_fault_address = SCB->BFAR;
    memmanage_fault_address = SCB->MMFAR;
    cfsr = SCB->CFSR;
    
    stacked_r0 = ((unsigned long) hardfault_args[0]);
    stacked_r1 = ((unsigned long) hardfault_args[1]);
    stacked_r2 = ((unsigned long) hardfault_args[2]);
    stacked_r3 = ((unsigned long) hardfault_args[3]);
    stacked_r12 = ((unsigned long) hardfault_args[4]);
    stacked_lr = ((unsigned long) hardfault_args[5]);
    stacked_pc = ((unsigned long) hardfault_args[6]);
    stacked_psr = ((unsigned long) hardfault_args[7]);

    log_panic("Hardfault!\n");
    log_panic("PC = 0x%X, PSR = 0x%X, LR/EXC_RETURN = 0x%X\n", stacked_pc, stacked_psr, stacked_lr);
    log_panic("R0 = 0x%X, R1 = 0x%X, R2 = 0x%X, R3 = 0x%X, R12 = 0x%X\n", stacked_r0, stacked_r1, stacked_r2, stacked_r3, stacked_r12);
    
    if (cfsr & 0x0080) {
        log_panic("MMFAR = 0x%X\n", memmanage_fault_address);
    }

    if (cfsr & 0x8000) {
        log_panic("BFAR = 0x%X\n", bus_fault_address);
    }

    while(1) {

    }
}