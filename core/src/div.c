
// #include "main.h"
// #include "accelerator_funcs.h"
// #include "rocc.h"
// #include <inttypes.h>
// #include <stdio.h>
// #include <stdlib.h>

// uint64_t concatenate_uint32t(uint32_t x, uint32_t y) {
//     uint64_t z = y;
//     z |= ((uint64_t)x << 32);
//     return z;
// }

// int main(void) {
//     printf("starting Div test\n");
    
//     //K_SET_SIZE(0b1000);
//     uint32_t* vec_0 = malloc(8 * sizeof(uint32_t));
//     uint32_t* vec_1 = malloc(8 * sizeof(uint32_t));
//     uint32_t* vec_out = malloc(8 * sizeof(uint32_t));
//     for (int i = 0; i < 8; i++) {
//         vec_0[i] = 0x41000000;
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
//     K_DIV(0, 1)
//     asm volatile("fence");

//     asm volatile("fence");
//     K_STORE(2, vec_out);
//     asm volatile("fence");

//     uint64_t accel_time_end = CLINT->MTIME;

//     for (int i = 0; i < 8; i++) {
//         printf("Expecting division result #%d in vec to be 0x40000000, is: %x \n", i, vec_out[i]);
//     }

//     uint64_t loop_time_start = CLINT->MTIME;
//     for (int i = 0; i < 8; i++) {
//         vec_out[i] = vec_0[i] / vec_1[i];
//     }
//     uint64_t loop_time_end = CLINT->MTIME;

//     printf("DIV: Num Cycles w/  Accelerator: %d", accel_time_end - accel_time_start);
//     printf("DIV: Num Cycles w/o Accelerator: %d", loop_time_end - loop_time_start);

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
