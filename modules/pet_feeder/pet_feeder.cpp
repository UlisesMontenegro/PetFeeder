//=====[Libraries]=============================================================

#include "pet_feeder.h"
#include "arm_book_lib.h"
#include "empty_plate_light.h"
#include "weight_sensor.h"
#include "fill_plate_button.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum{
    NORMAL_MODE,
    CONFIGURATION_MODE
} operatingMode_t;

typedef enum{
    PLATE_FULL,
    PLATE_FILLING,
    PLATE_EMPTY
} plateState_t;

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

operatingMode_t operatingMode;
bool buttonPressed;
bool updatePlateWeight;
bool updateFoodPortion;

//=====[Declaration and initialization of private global variables]============

plateState_t plateState;
int emptyPlateWeight;
int foodPortionWeight;

//=====[Declarations (prototypes) of private functions]========================

void runNormalMode();
void runConfigurationMode();

//=====[Implementations of public functions]===================================

void petFeederInit()
{
    //Initialize each module.
    operatingMode = NORMAL_MODE;
    plateState = PLATE_FULL;
    buttonPressed = false;
    updatePlateWeight = false;
    updateFoodPortion = false;
    emptyPlateWeight = DEFAULT_EMPTY_PLATE_WEIGHT;
    foodPortionWeight = DEFAULT_FULL_PLATE_WEIGHT;
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
    //bleComUpdate(); ---> UPDATE BLE MODULE.

    switch(operatingMode){
        case NORMAL_MODE:
            runNormalMode();
        break;
        case CONFIGURATION_MODE:
            runConfigurationMode();
        break;
    }
    delay(UPDATE_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================

void runNormalMode(){
    switch(plateState){
        case PLATE_FULL:
            if(sensedWeight() == DEFAULT_EMPTY_PLATE_WEIGHT){
                emptyPlateLightTurn(ON);
                // bleComWrite("PEM\r\n"); ---> Notifies smartphone that the plate is empty.
                plateState = PLATE_EMPTY;
            }else if(buttonPressed == true){
                // fillPlate(); ---> Servomotor's method.
                // bleComWrite("PFI\r\n"); ---> Notifies smartphone that the plate is being filled.
                plateState = PLATE_FILLING;
            }
        break;
        case PLATE_FILLING:
            if(sensedWeight() == DEFAULT_FULL_PLATE_WEIGHT){
                // bleComWrite("PFU\r\n"); ---> Notifies smartphone that the plate is full.
                plateState = PLATE_FULL;
            }
        break;
        case PLATE_EMPTY:
            if(buttonPressed == true){
                // fillPlate(); ---> Servomotor's method.
                // bleComWrite("PFI\r\n"); ---> Notifies smartphone that the plate is being filled.
                plateState = PLATE_FILLING;
            }
        break;
    }
}

void runConfigurationMode(){
    if(updatePlateWeight == true){
        emptyPlateWeight = sensedWeight();
        updatePlateWeight = false;
    }else if(updateFoodPortion == true){
        foodPortionWeight = sensedWeight();
        updateFoodPortion = false;
    }
    operatingMode = NORMAL_MODE;
}