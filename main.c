/*

*/

#include<stdio.h>
#include<stdlib.h>

struct PID {
    float Kp; // Proportional gain constant
    float Ki; // Integral gain constant
    float Kd; // Derivative gain constant
    float Kaw; // anti-windup gain constant
    float T_C; // Time constant for derivative filtering
    float T; // time step
    float min; // min command
    float max; // max command
    float max_rate; // Max rate of change of the command
    float integral; // term of integral
    float prev_err; // previous error
    float prev_deriv; // previous derivative
    float prev_command_sat; // previous saturated command
    float prev_command; // previous command
};