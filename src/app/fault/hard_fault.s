// Copyright 2020 Marius
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Hardfault wrapper, extracts the stack pointer



.text
.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb
.type HardFault_Handler, %function
.global HardFault_Handler
.global HardFault_Handler_c

HardFault_Handler:
    tst     lr, #4
    mrs     r0, msp /* Stack was using MSP */
    mov     r1, lr /* second param */
    ldr     r2,=fault_hardfault_handler_c
    bx      r2
    .end