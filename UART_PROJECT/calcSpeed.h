
#include "TimerOne.h"

int hallS = 0;
float speed = 0;

void speedCal() {
  speed = hallS*2*PI*0.6;
  hallS=0;
}

void speedInc() {
  hallS++;
}
