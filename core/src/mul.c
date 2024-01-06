
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
//     printf("starting mul test\n");
    
//     printf("starting \n");

//     K_SET_SIZE(0b100);
//     K_SET_SIZE(0b1000);
//     K_SET_OUT(2);


//     uint32_t * vec_1 = malloc(8 * sizeof(uint32_t));
//     uint32_t * vec_2 = malloc(8 * sizeof(uint32_t));
//     int i;
    
//     for (i = 0; i < 8; i++) {
//         vec_1[i] = 0x40800000;
//         vec_2[i] = 0x40800000;
//     }

//     uint64_t accel_time_start = CLINT->MTIME;    

//     K_LOAD(0, vec_1); //store vec1

//     printf("Done with first load \n");
//     K_LOAD(1, vec_2); //store vec2

//     printf("Done with second load \n");

//     asm volatile("fence");
//     K_MUL(0, 1);
//     asm volatile("fence");
//     printf("Done with Mul \n");
    

//     uint32_t vec_empty[] = { 0, 0, 0, 0, 0, 0, 0, 0};
//     asm volatile("fence");
//     K_STORE(2, vec_empty);
//     asm volatile("fence");

//     uint64_t accel_time_end = CLINT->MTIME;

//     for (i = 0; i < 8; i++) {
//         printf("Expecting multiplication result #%d in vec to be 0x41800000, is: %x \n", i, vec_empty[i]);
//     }

//     uint64_t loop_time_start = CLINT->MTIME;
//     for (int i = 0; i < 8; i++) {
//         vec_empty[i] = vec_1[i] * vec_2[i];
//     }
//     uint64_t loop_time_end = CLINT->MTIME;

//     printf("Num Cycles w/  Accelerator: %d", loop_time_end - loop_time_start);
//     printf("Num Cycles w/o Accelerator: %d", accel_time_end - accel_time_start);
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
