#include "linker.h"

linker::linker(){
    buffer_time = 0;
    buffer_position = 7;
}

linker::~linker(){

}

void linker::begin(unsigned long value){
    Serial.begin(value);
}
void linker::send(byte position, uint16_t value){
    uint8_t *value_8;
    uint8_t buffer[3];
    uint8_t header = position << 3;
    value_8 = (uint8_t *)&value;

    bitWrite(header, 2, bitRead(value_8[0],0));
    bitWrite(header, 1, bitRead(value_8[1],0));

    Serial.write(header | 0x01); 
    Serial.write((value_8[0] >> 1) << 1);   
    Serial.write((value_8[1] >> 1) << 1);   
}

void linker::reset(){
    buffer_time = 0;
    buffer_position = 0;
}

 void linker::portData(){
    uint8_t number[2];
    int package_num = (buffer[0] & 0b11111000) >> 3;
    number[0] = buffer[1] | (bitRead(buffer[0],2));
    number[1] = buffer[2] | (bitRead(buffer[0],1));
    package[package_num] = *((uint16_t *)number);
 }

void linker::update(){
    uint8_t charactor;
    if((millis() - buffer_time) > CUT_OFF_TIME)
        reset();

    while(Serial.available()){
        charactor = Serial.read();
        if(charactor & 0x01 == 0x01){
            if(buffer_position == 0){      
                buffer[buffer_position] = charactor;
                ++buffer_position;
                buffer_time = millis();
            }
        }else {
            if(buffer_position == 2){
                buffer[buffer_position] = charactor;
                portData();
                reset();
            }
            
            if(buffer_position == 1)
                buffer[buffer_position] = charactor;
                ++buffer_position;
                buffer_time = millis();
            }
        }
    }
}

unsigned int linker::read(int position){
    return int_num[position];
}
