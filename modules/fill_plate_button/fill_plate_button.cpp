//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "fill_plate_button.h"
#include "empty_plate_light.h"
#include "pet_feeder.h"

//=====[Declaration of private defines]========================================

#define DEBOUNCE_TIME_MS 40

//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_PRESSED,
    BUTTON_UNPRESSED,
    BUTTON_DEBOUNCING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn fillPlateButton(D1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

buttonState_t fillPlateButtonState;
int debounceAccumulatedTime;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void fillPlateButtonInit()
{
    fillPlateButton.mode(PullUp);
    fillPlateButtonState = BUTTON_UNPRESSED;
    debounceAccumulatedTime = 0;
}

void fillPlateButtonUpdate()
{
    switch(fillPlateButtonState){

        case BUTTON_UNPRESSED:
            emptyPlateLightTurn(ON);
            debounceAccumulatedTime = 0;
            if(fillPlateButton.read() == LOW){
                fillPlateButtonState = BUTTON_DEBOUNCING;
            }
            break;

        case BUTTON_DEBOUNCING:
            if(debounceAccumulatedTime >= DEBOUNCE_TIME_MS){
                if(fillPlateButton.read() == LOW){
                    fillPlateButtonState = BUTTON_PRESSED;
                }
                else{
                    fillPlateButtonState = BUTTON_UNPRESSED;
                }
            }
            else{
                debounceAccumulatedTime = debounceAccumulatedTime + UPDATE_TIME_INCREMENT_MS;
            }
            break;

        case BUTTON_PRESSED:
            debounceAccumulatedTime = 0;
            emptyPlateLightTurn(OFF);
            if(fillPlateButton.read() == HIGH){
                fillPlateButtonState = BUTTON_DEBOUNCING;
            }
            break;

        default:
            fillPlateButtonState = BUTTON_UNPRESSED;
            break;
    }
    
    /*
    if(fillPlateButton.read() == 0){
        fillPlateButtonState = BUTTON_PRESSED;
    }
    else{
        fillPlateButtonState = BUTTON_UNPRESSED;
    }
    if(fillPlateButtonState == BUTTON_PRESSED){
        emptyPlateLightTurn(OFF);
    }
    else{
        emptyPlateLightTurn(ON);
    }*/
}

//=====[Implementations of private functions]==================================