//=====[Libraries]=============================================================

#include "pet_feeder.h"
#include "arm_book_lib.h"
#include "empty_plate_light.h"
#include "weight_sensor.h"
#include "fill_plate_button.h"
#include "ble_com.h"
#include "fill_plate_enabler.h"

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
float emptyPlateWeight;
float foodPortionWeight;
bool buttonPressedSignal;
bool updatePlateWeightSignal;
bool updateFoodPortionSignal;

//=====[Declarations (prototypes) of private functions]========================

static void runNormalMode();
static void runConfigurationMode();

//=====[Implementations of public functions]===================================

void petFeederInit()
{
    //Initialize each module.
    operatingMode = NORMAL_MODE;
    plateState = PLATE_FULL;
    buttonPressedSignal = false;
    updatePlateWeightSignal = false;
    updateFoodPortionSignal = false;
    emptyPlateWeight = DEFAULT_EMPTY_PLATE_WEIGHT;
    foodPortionWeight = DEFAULT_FULL_PLATE_WEIGHT;
    emptyPlateLightInit();
    weightSensorInit();
    fillPlateButtonInit();
    fillPlateEnablerInit();
}

void petFeederUpdate()
{
    //Update each module.
    //emptyPlateLightUpdate();
    weightSensorUpdate();
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
    updatePlateWeightSignal = true;
}

void updateFoodPortion(){
    updateFoodPortionSignal = true;
} 

void buttonPressed(){
    buttonPressedSignal = true;
}

void configurationMode(){
    operatingMode = CONFIGURATION_MODE;
}

//=====[Implementations of private functions]==================================

static void runNormalMode(){
    switch(plateState){
        case PLATE_FULL:
            if(sensedWeight() == emptyPlateWeight){
                emptyPlateLightTurn(ON);
                bleComStringWrite("PEM\r\n");
                plateState = PLATE_EMPTY;
            }else if(buttonPressedSignal == true){
                enablePlateFilling();
                bleComStringWrite("PFI\r\n");
                plateState = PLATE_FILLING;
            }
        break;
        case PLATE_FILLING:
            if(sensedWeight() == foodPortionWeight){
                emptyPlateLightTurn(OFF);
                disablePlateFilling();
                bleComStringWrite("PFU\r\n");
                plateState = PLATE_FULL;
            }
        break;
        case PLATE_EMPTY:
            if(buttonPressedSignal == true){
                enablePlateFilling();
                bleComStringWrite("PFI\r\n");
                plateState = PLATE_FILLING;
            }
        break;
    }
}

static void runConfigurationMode(){
    if(updatePlateWeightSignal == true){
        emptyPlateWeight = sensedWeight();
        updatePlateWeightSignal = false;
    }else if(updateFoodPortionSignal == true){
        foodPortionWeight = sensedWeight();
        updateFoodPortionSignal = false;
    }
    operatingMode = NORMAL_MODE;
}