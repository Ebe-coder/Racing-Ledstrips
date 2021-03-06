/**
  Section: Included Files
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "PI.h"

/**
  Section: PI Module APIs
 */

static int sensorHeight = 0;
static int setpoint = 100; //240 = top, 0 = bottom
static int error = 0;
static float integral = 0;
static float ki = 0.005;
static float kp = 1;
static int dutycycle;

int PI_GetSensorHeight(void){
    return sensorHeight;
}

void PI_SetSetpoint(int value){
    setpoint = value;
}

void PI_SetKp(float value){
    kp = value;
}

void PI_SetKi(float value){
    ki = value;
}

void PI(void) {
    int sumError = 0;
    while (1){
    sensorHeight = (int) ADC_GetResult(); //resultaat van ADC

    error = setpoint - sensorHeight;
    sumError += error; 
    
    dutycycle = (int) (kp * error + ki * sumError);

    PWM5_LoadDutyValue((uint16_t) dutycycle); // output pwm signaal voor hoogte  
    }
    
}

/**
 End of File
 */