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

struct Object{
    float m;    //Mass of the object
    float k;    // dampening constant of the object
    float F_Max; //Max force applied
    float F_Min; //Min force applied
    float T; //time step
    float V; //Velocity
    float Z; //Position
};

float PID_Step(struct PID *pid, float measurement, float setpoint){

    /*
    Inputs: pointer to PID struct, current measurement 
    of the process variable, and the desired setpoint 
    for the process variable.
    
    Outputs: command_sat(saturated command) which is the output
    command of the PID controller. It is saturated by the min, max,
    and max_rate vars found in the PID struct
    */
    float err;
    float command;
    float command_sat;
    float deriv_filt;

    err = setpoint - measurement;
    float AntiWindup = pid->Kaw*(pid->prev_command_sat-pid->prev_command)*pid->T;

    pid->integral += pid->Ki*err*pid->T + AntiWindup;

    deriv_filt = (err - pid->prev_err + pid->prev_deriv) / (pid->T + pid->T_C); // I dont understand derivative calculation tbh

    command = pid->Kp * err + pid->integral + pid->Kd * deriv_filt;

    pid->prev_command = command; 

    if (command > pid->max){
        command = pid->max;
    }
    else if (command < pid->min){
        command = pid->min;
    }
    else{
        command_sat = command;
    }
    if (command_sat > pid->prev_command_sat + pid->max_rate * pid->T){
        command_sat = pid->prev_command_sat + pid->T;
    }
    else if (command_sat < pid->prev_command_sat - pid->max_rate * pid->T){
        command_sat = pid->prev_command_sat - pid->T;
    }
    else{}
    return command_sat;

}

float Object_step(struct Object *obj, float F){
    /*
    Inputs: takes in the Object struct and the force 
    currently applied to the object
    Outputs: Position in meters using var Z
    */
   float dv_dt;
   float F_sat;

   if (F > obj->F_Max){
    F_sat = obj->F_Max;
   }
   else if (F < obj->F_Min){
    F_sat = obj->F_Min;
   }
   else {F_sat = F;}

   dv_dt = (F_sat - obj->k * obj->V) / obj->m; //THIS IS A NEWTONS FIRST LAW EQUATION YOOO

   obj->V += dv_dt * obj->T;
   obj->Z += obj->V * obj->T;

   return obj->Z;
}

int main(){
    
}