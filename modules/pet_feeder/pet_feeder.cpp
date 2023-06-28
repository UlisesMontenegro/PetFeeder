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
long emptyPlateWeight;
long fullPlateWeight;
long foodPortionWeight;
bool updatePlateWeightSignal;
bool updateFoodPortionSignal;
char buffer[100];

//=====[Declarations (prototypes) of private functions]========================

static void runNormalMode();
static void runConfigurationMode();

//=====[Implementations of public functions]===================================

void petFeederInit()
{
    //Initialize each module.
    bleComStringWrite("Welcome to PetFeeder!");
    operatingMode = NORMAL_MODE;
    plateState = PLATE_FULL;
    updatePlateWeightSignal = false;
    updateFoodPortionSignal = false;
    emptyPlateWeight = DEFAULT_EMPTY_PLATE_WEIGHT;
    fullPlateWeight = DEFAULT_FULL_PLATE_WEIGHT;
    foodPortionWeight = fullPlateWeight - emptyPlateWeight;
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
    updatePlateWeightSignal = true;
}

void updateFoodPortion(){
    updateFoodPortionSignal = true;
} 

void configurationMode(){
    operatingMode = CONFIGURATION_MODE;
}

//=====[Implementations of private functions]==================================

static void runNormalMode(){
    switch(plateState){
        case PLATE_FULL:
            if(sensedWeight() <= emptyPlateWeight){
                sprintf(buffer, "Empty Plate Weight: %d", (int)emptyPlateWeight);
                bleComStringWrite(buffer);
                sprintf(buffer, "Sensed Weight: %d", (int)sensedWeight());
                bleComStringWrite(buffer);
                emptyPlateLightTurn(ON);
                bleComStringWrite("Plate Empty");
                plateState = PLATE_EMPTY;
            }else if(isButtonPressed() == true){
                enablePlateFilling();
                emptyPlateLightTurn(OFF);
                bleComStringWrite("Plate Filling");
                plateState = PLATE_FILLING;
            }
        break;
        case PLATE_FILLING:
            sprintf(buffer, "Sensed Weight: %d", (int)sensedWeight());
            bleComStringWrite(buffer);
            if(sensedWeight() >= fullPlateWeight){
                emptyPlateLightTurn(OFF);
                disablePlateFilling();
                bleComStringWrite("Plate Full");
                plateState = PLATE_FULL;
            }
        break;
        case PLATE_EMPTY:
            if(isButtonPressed() == true){
                enablePlateFilling();
                bleComStringWrite("Plate Filling");
                plateState = PLATE_FILLING;
            }
        break;
    }
}

static void runConfigurationMode(){
    bleComStringWrite("Running Configuration Mode");
    if(updatePlateWeightSignal == true){
        emptyPlateWeight = sensedWeight();
        fullPlateWeight = emptyPlateWeight + foodPortionWeight;
        updatePlateWeightSignal = false;
        plateState = PLATE_EMPTY;
        operatingMode = NORMAL_MODE;
        bleComStringWrite("Plate Weight Updated");
    }else if(updateFoodPortionSignal == true){
        fullPlateWeight = sensedWeight();
        foodPortionWeight = fullPlateWeight-emptyPlateWeight;
        updateFoodPortionSignal = false;
        plateState = PLATE_FULL;
        operatingMode = NORMAL_MODE;
        bleComStringWrite("Full Portion Updated");
    }
}