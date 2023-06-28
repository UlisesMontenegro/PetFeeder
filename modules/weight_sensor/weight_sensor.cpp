//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "weight_sensor.h"
#include "HX711.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

HX711 balance(D0, D5);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

long currentWeight;
long tareValue;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void weightSensorInit()
{
    currentWeight = 0;
    tareValue = balance.averageValue(5);
}

void weightSensorUpdate()
{
    long value = balance.averageValue(5);
    currentWeight = (value - tareValue);
    // printf("Potentiometer Value: %.f", currentWeight);
}

long sensedWeight(){
    return currentWeight;
}

//=====[Implementations of private functions]==================================