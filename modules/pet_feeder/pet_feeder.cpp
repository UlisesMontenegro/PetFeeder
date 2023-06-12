//=====[Libraries]=============================================================

#include "pet_feeder.h"
#include "arm_book_lib.h"
#include "empty_plate_light.h"
#include "weight_sensor.h"
#include "fill_plate_button.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void petFeederInit()
{
    //Initialize each module.
    emptyPlateLightInit();
    weightSensorInit();
    fillPlateButtonInit();
}

void petFeederUpdate()
{
    //Update each module.
    emptyPlateLightUpdate();
    weightSensorUpdate();
    fillPlateButtonUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================