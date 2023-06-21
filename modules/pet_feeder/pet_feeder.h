//=====[#include guards - begin]===============================================

#ifndef _PET_FEEDER_H_
#define _PET_FEEDER_H_

//=====[Declaration of public defines]=========================================

#define UPDATE_TIME_INCREMENT_MS  10
#define DEFAULT_EMPTY_PLATE_WEIGHT  0.2 // In [grams].
#define DEFAULT_FULL_PLATE_WEIGHT  0.8 // In [grams] (Food + plate).

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void petFeederInit();
void petFeederUpdate();
void updatePlateWeight();
void updateFoodPortion();
void configurationMode();

//=====[#include guards - end]=================================================

#endif // _PET_FEEDER_H_