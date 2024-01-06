// /* USER CODE BEGIN Header */
// /**
//   ******************************************************************************
//   * @file           : main.c
//   * @brief          : Main program body
//   ******************************************************************************
//   * @attention
//   *
//   * This software is licensed under terms that can be found in the LICENSE file
//   * in the root directory of this software component.
//   * If no LICENSE file comes with this software, it is provided AS-IS.
//   *
//   ******************************************************************************
//   */
// /* USER CODE END Header */
// /* Includes ------------------------------------------------------------------*/
// #include "main.h"
// #include "accelerator_funcs.h"
// #include "rocc.h"
// #include <inttypes.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(void) {
//     printf("starting add test\n");
    
//     K_SET_SIZE(0b1000);
//     uint32_t* vec_0 = malloc(8 * sizeof(uint32_t));
//     uint32_t* vec_1 = malloc(8 * sizeof(uint32_t));
//     uint32_t* vec_out = malloc(8 * sizeof(uint32_t));
//     for (int i = 0; i < 8; i++) {
//         vec_0[i] = 0x40800000;
//         vec_1[i] = 0x40800000;
//     }

//     uint64_t accel_time_start = CLINT->MTIME;

//     asm volatile("fence");
//     K_SET_OUT(2);
//     asm volatile("fence");

//     asm volatile("fence");
//     K_LOAD(0, vec_0);
//     asm volatile("fence");

//     asm volatile("fence");
//     K_LOAD(1, vec_1);
//     asm volatile("fence");

//     asm volatile("fence");
//     K_ADD(0, 1)
//     asm volatile("fence");

//     asm volatile("fence");
//     K_STORE(2, vec_out);
//     asm volatile("fence");

//     uint64_t accel_time_end = CLINT->MTIME;

//     for (int i = 0; i < 8; i++) {
//         printf("Expecting addition result #%d in vec to be 0x41000000, is: %x \n", i, vec_out[i]);
//     }

//     uint64_t loop_time_start = CLINT->MTIME;
//     for (int i = 0; i < 8; i++) {
//         vec_out[i] = vec_0[i] + vec_1[i];
//     }
//     uint64_t loop_time_end = CLINT->MTIME;

//     printf("ADD: Num Cycles w/  Accelerator: %d", loop_time_end - loop_time_start);
//     printf("ADD: Num Cycles w/o Accelerator: %d", accel_time_end - accel_time_start);
//     printf("DONE\n");
//     return 0;
// }

// /*
//  * Main function for secondary harts
//  * 
//  * Multi-threaded programs should provide their own implementation.
//  */
// void __attribute__((weak, noreturn)) __main(void) {
//   while (1) {
//    asm volatile ("wfi");
//   }
// }
