/*! @mainpage PetFeeder
 * @date Thursday, March 16, 2023
 * @authors Ulises Montenegro
 *
 * @note First version of the main behaviour of the project.
 * When the potentiometer (acts as a weight sensor) reachs a defined value, the LED turns on.
 * When the button is pressed, the LED turns off.
 * Potentiometer: PINX
 * Led: 
 * Button: 
 */


//=====[Libraries]=============================================================

#include "mbed.h"
#include "pet_feeder.h"
#include "arm_book_lib.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{   
    petFeederInit();
    while (true) {
        petFeederUpdate();  
    }
}

