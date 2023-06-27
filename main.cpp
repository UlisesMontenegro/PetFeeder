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
    //float currentWeight;
    char buffer[3];
    HX711 balanza(D0, D5);
    bleComStringWrite("Empezando");
    long valor;
    long valorTara;
    float peso;
    
    valorTara = balanza.getValue();                                           // On récupère la valeur de la Tare
    //petFeederInit();
    while (true) {
        delay(200);                                                       // Attente de 200 millisecondes
        valor = balanza.getValue();                                        // On récupère la valeur du module
        peso = ((float)valor-(float)valorTara)/143200;         // Convertionde la valeur de l'ADC en grammes
        //petFeederUpdate();
        buffer[0] = (char)peso;
        buffer[1] = '\r';
        buffer[1] = '\n';
        bleComStringWrite(buffer);
    }
}

