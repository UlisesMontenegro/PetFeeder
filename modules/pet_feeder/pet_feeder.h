//=====[#include guards - begin]===============================================

#ifndef _PET_FEEDER_H_
#define _PET_FEEDER_H_

//=====[Declaration of public defines]=========================================

#define UPDATE_TIME_INCREMENT_MS  10
#define DEFAULT_EMPTY_PLATE_WEIGHT  50 // In [grams].
#define DEFAULT_FULL_PLATE_WEIGHT  100 // In [grams] (Food + plate).

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void petFeederInit();
void petFeederUpdate();

//=====[#include guards - end]=================================================

#endif // _PET_FEEDER_H_