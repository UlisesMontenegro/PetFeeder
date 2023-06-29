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
#include "ble_com.h"
#include "arm_book_lib.h"
#include "HX711.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{   
    
    /*//float currentWeight;
    char buffer[100];
    HX711 balanza(D0, D5);
    bleComStringWrite("Empezando");
    long valor=0;
    long valorTara=0;
    float peso=0.0;
    
    //valorTara = balanza.getValue();
    valorTara = balanza.averageValue(10);*/
    petFeederInit();
    while (true) {
        //delay(200);
        //valor = balanza.getValue();
        //valor = balanza.averageValue(10);
        //peso = ((float)valor-(float)valorTara)/143200;
        //peso = (valor-valorTara);
        petFeederUpdate();
        //sprintf(buffer, "Peso: %d", (int)peso);
        //bleComStringWrite(buffer);
    }
}

