/*********************************************************
* LED Management
* This is the code that controls what displays on the 
* LED array.
**********************************************************/

#include <FastLED.h>

void enableRandom() {
  doRandom = true;
}

void disableRandom() {
  doRandom = false;
}



void allOff() {
  disableRandom();
  setColor(CRGB::Black);
}
