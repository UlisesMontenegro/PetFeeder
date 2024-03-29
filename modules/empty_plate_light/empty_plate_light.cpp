//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "empty_plate_light.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut emptyPlateLight(D7);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void emptyPlateLightInit()
{
    emptyPlateLight = OFF;
}

void emptyPlateLightUpdate()
{
}

void emptyPlateLightTurn(int state)
{
    emptyPlateLight = state;
}

//=====[Implementations of private functions]==================================