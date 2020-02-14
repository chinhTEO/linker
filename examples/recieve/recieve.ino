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
  mavlink.sync();
  if(millis() - delay_time > 1000)
  {

    Serial.println(mavlink.read(SPEED));
    delay_time = millis();
  }
}
