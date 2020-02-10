#include "linker.h"

//MAXIUM is 31
#define SPEED 0


linker mavlink;
unsigned long delay_time;
void setup() {
  mavlink.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:

  //MAXIUM for value is (2^16 - 1)
  mavlink.send(SPEED, 255);
  delay(500);
}
