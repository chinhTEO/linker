#include "linker.h"
#include <SoftwareSerial.h>


SoftwareSerial mySerial(10, 11); // RX, TX

//MAXIUM is 31
#define SPEED 0

linker mavlink(&mySerial);
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
