// #include "mmio.h"
// #include "rose.h"

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
// #include <riscv-pk/encoding.h>


#define ROSE_REQ_PID_OBS 0x16

#define ROSE_SET_TARGETS  0x20

// #define KP_ANGLE 10.0f
// #define KD_ANGLE 0.1f
// #define KP_POS 1.0f
// #define KD_POS 0.0f

#define KP_ANGLE 41.20f
#define KD_ANGLE 2.16f
#define KP_POS 5.26f
#define KD_POS 1.14f

#define SPIKE 1

// Gemmini test code
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
// #include "gemmini_testutils.h"
#define OUTPUT_STATIONARY 0
#define CHECK_RESULT 1
#define NO_BIAS 1
#define MAT_DIM_I 1
#define MAT_DIM_K 4
#define MAT_DIM_J 1
#define FULL_BIAS_WIDTH 1
// #if FULL_BIAS_WIDTH
// typedef acc_t ACC_T;
// #else
// typedef elem_t ACC_T;
// #endif

// Beginning of LQR test code
#include "rocc.h"
#include "bitcasts.h"

float lqr_test(float theta, float theta_dot, float pos, float vel) {

    float t_row1[4];
    float y_xhat1[4];
    t_row1[0] = KP_ANGLE;
    t_row1[1] = KD_ANGLE;
    t_row1[2] = KP_POS;
    t_row1[3] = KD_POS;
    y_xhat1[0] = theta;
    y_xhat1[1] = theta_dot;
    y_xhat1[2] = pos;
    y_xhat1[3] = vel;

    uint32_t sum = 0;
    asm volatile ("fence");
    ROCC_INSTRUCTION_SS(0, t_row1, y_xhat1, 0);   // passing two vector base       
    ROCC_INSTRUCTION_DS(0, sum, 4, 1);  // passing result pointer and the length
    asm volatile ("fence");
    return fp32_from_bits(sum);
}
// End of LQR test code


// Beginning of Kalman test code
#include "rocc.h"
#include "kalman.h"

uint64_t concatenate_uint32t(uint32_t x, uint32_t y) {
    uint64_t z = y;
    z |= ((uint64_t)x << 32);
    return z;
}

float kalman_test(float theta, float theta_dot, float pos, float vel) {

    uint32_t vec_1[] = { 0x40800000, 0x40800000, 0x40800000, 0x40800000, 0x40800000, 0x40800000, 0x40800000, 0x40800000};
    uint32_t vec_2[] = { 0x40800000, 0x40800000, 0x40800000, 0x40800000, 0x40800000, 0x40800000, 0x40800000, 0x40800000};
    uint32_t lower = 1; //vec #
    uint32_t upper = 4; //vec size 
    uint64_t vec_3 = concatenate_uint32t(upper, lower); //got vec3
    printf("Vec3: %lx \n",vec_3);
    lower = 2;
    uint64_t vec_4 = concatenate_uint32t(upper, lower); //got vec4
    printf("Vec4: %lx \n",vec_4);

    // v0 comes from rs1, v1 comes from rs2, and addr comes from rs2
    /** vec[rs1:v0] = M[rs2:addr] */
    // #define K_LOAD(rs1, rs2)
    uint64_t rd;

    asm volatile("fence");
    K_LOAD(vec_3, vec_1); //store vec1
    K_LOAD(vec_4, vec_2); //store vec2
    K_DOT_PROD(rd, vec_3, vec_4);
    asm volatile("fence");

    printf("Expecting dot product to be 128 (0x43000000), is: %lx \n", rd);
    return 0;
}

uint32_t buf[8];

// int read_pid_obs_nonblock(float * obs) {
// 	send_obs_req(ROSE_REQ_PID_OBS);
//   return read_obs_rsp_nonblock((void *) obs);
// }

float calc_action(float * obs) {
  float theta = obs[1];
  float theta_dot = obs[3];

  float pos = obs[0];
  float vel = obs[2];

  /*
  printf("Contacting Gemmini\n");
  float action_gem = gemmini_test(theta, theta_dot, pos, vel);
  printf("Gemmini action %x\n", action_gem);
  */
  
  printf("Contacting LQR\n");
  float action_lqr = lqr_test(theta, theta_dot, pos, vel);
  printf("LQR action %x\n", action_lqr);

  printf("Contacting Kalman\n");
  float action_kalman = kalman_test(theta, theta_dot, pos, vel);
  printf("Kalman action %x\n", action_kalman);

  float action = KP_ANGLE * theta + KD_ANGLE * theta_dot + KP_POS * pos + KD_POS * vel;
  printf("Regular action %x\n", action);

  return action;
}

int main(void)
{
  uint32_t cnt = 0;
  float obs[4] = {0, 0, 0, 0};
  float action;

  // printf("Starting pd test code: KP: %f, KD: %f, KP_POS: %f, KD_POS: %f ...\n", KP_ANGLE, KD_ANGLE, KP_POS, KD_POS);
  printf("Starting pd test code: KP: %x, KD: %x, KP_POS: %x, KD_POS: %x ...\n", KP_ANGLE, KD_ANGLE, KP_POS, KD_POS);
  printf("MAT_DIM_I: %d\n", MAT_DIM_I);
  printf("MAT_DIM_J: %d\n", MAT_DIM_J);
  printf("MAT_DIM_K: %d\n", MAT_DIM_K);

  calc_action(obs);

}

void __attribute__((weak, noreturn)) __main(void) {
  while (1) {
   asm volatile ("wfi");
  }
}
