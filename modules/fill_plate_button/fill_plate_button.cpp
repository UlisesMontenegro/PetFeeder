//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "fill_plate_button.h"

//=====[Declaration of private defines]========================================

//#define DEBOUNCE_TIME_MS 20

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn fillPlateButton(D1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

bool fillPlateButtonPressed;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void fillPlateButtonInit()
{
    fillPlateButton.mode(PullUp);
    fillPlateButtonPressed = false;
}

void fillPlateButtonUpdate()
{
    if(fillPlateButton.read() == LOW){
        fillPlateButtonPressed = true;
    }else{
        fillPlateButtonPressed = false;
    }
}

bool isButtonPressed(){
    return fillPlateButtonPressed;
}

void pressButton(){
    fillPlateButtonPressed = true;
}

//=====[Implementations of private functions]==================================