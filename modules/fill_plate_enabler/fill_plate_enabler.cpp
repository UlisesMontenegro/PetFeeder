//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "fill_plate_enabler.h"

//=====[Declaration of private defines]========================================

// #define EMPTY_PLATE_WEIGHT 0.2

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

PwmOut servomotor(D6);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

float dutyCycle;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void fillPlateEnablerInit()
{
    dutyCycle = 0.091;
    servomotor.write(dutyCycle);
    servomotor.period_ms(20);
}

void fillPlateEnablerUpdate()
{

}

void enablePlateFilling(){
    dutyCycle = 0.078;
    servomotor.write(dutyCycle);
}

void disablePlateFilling(){
    dutyCycle = 0.091;
    servomotor.write(dutyCycle);
}

//=====[Implementations of private functions]==================================