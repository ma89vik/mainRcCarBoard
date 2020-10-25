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

#include "stm32f407xx.h"
#include "app_uart.h"
#include "printf.h"

#define fault_log LOG_ERROR


void fault_shutdown()
{
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
    log_panic("PC = %X, PSR = %X, LR/EXC_RETURN = %X\n", stacked_pc, stacked_psr, stacked_lr);
    log_panic("R0 = %X, R1 = %X, R2 = %X, R3 = %X, R12 = %X\n", stacked_r0, stacked_r1, stacked_r2, stacked_r3, stacked_r12);
    
    if (cfsr & 0x0080) {
        log_panic("MMFAR = %X\n", memmanage_fault_address);
    }

    if (cfsr & 0x8000) {
        log_panic("BFAR = %X\n", bus_fault_address);
    }

    while(1) {

    }
}