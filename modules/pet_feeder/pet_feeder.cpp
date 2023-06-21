//=====[Libraries]=============================================================

#include "pet_feeder.h"
#include "arm_book_lib.h"
#include "empty_plate_light.h"
#include "weight_sensor.h"
#include "fill_plate_button.h"
#include "ble_com.h"

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

//=====[Declaration and initialization of private global variables]============

plateState_t plateState;
operatingMode_t operatingMode;
int emptyPlateWeight;
int foodPortionWeight;
bool buttonPressed;
bool updatePlateWeight;
bool updateFoodPortion;

//=====[Declarations (prototypes) of private functions]========================

static void runNormalMode();
static void runConfigurationMode();

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
    bleComUpdate();

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

void updatePlateWeight(){
    updatePlateWeight = true;
}

void updateFoodPortion(){
    updateFoodPortion = true;
} 

void buttonPressed(){
    buttonPressed = true;
}

void configurationMode(){
    operatingMode = CONFIGURATION_MODE;
}

//=====[Implementations of private functions]==================================

static void runNormalMode(){
    switch(plateState){
        case PLATE_FULL:
            if(sensedWeight() == DEFAULT_EMPTY_PLATE_WEIGHT){
                emptyPlateLightTurn(ON);
                bleComStringWrite("PEM\r\n");
                plateState = PLATE_EMPTY;
            }else if(buttonPressed == true){
                // fillPlate(); ---> Servomotor's method.
                bleComStringWrite("PFI\r\n");
                plateState = PLATE_FILLING;
            }
        break;
        case PLATE_FILLING:
            if(sensedWeight() == DEFAULT_FULL_PLATE_WEIGHT){
                bleComStringWrite("PFU\r\n");
                plateState = PLATE_FULL;
            }
        break;
        case PLATE_EMPTY:
            if(buttonPressed == true){
                // fillPlate(); ---> Servomotor's method.
                bleComStringWrite("PFI\r\n");
                plateState = PLATE_FILLING;
            }
        break;
    }
}

static void runConfigurationMode(){
    if(updatePlateWeight == true){
        emptyPlateWeight = sensedWeight();
        updatePlateWeight = false;
    }else if(updateFoodPortion == true){
        foodPortionWeight = sensedWeight();
        updateFoodPortion = false;
    }
    operatingMode = NORMAL_MODE;
}