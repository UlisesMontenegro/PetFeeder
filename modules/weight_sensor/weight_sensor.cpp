//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "weight_sensor.h"
#include "empty_plate_light.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn potentiometer(A1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

float currentWeight;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void weightSensorInit()
{
    currentWeight = 0.0;
}

void weightSensorUpdate()
{
    currentWeight = potentiometer.read();
    // printf("Potentiometer Value: %.f", currentWeight);
}

float sensedWeight(){
    return currentWeight;
}

//=====[Implementations of private functions]==================================