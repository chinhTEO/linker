#include "linker.h"

//MAXIUM is 31
#define SPEED 0


linker mavlink;
unsigned long delay_time;
void setup() {
  mavlink.begin(9600);  
  
  //MAXIUM for value is (2^16 - 1)
  mavlink.set(SPEED, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  mavlink.sync();
  
  if(mavlink.isConnected()){
    //  
  }else
  {
    /* code */
  }
  
  delay(500);
}


