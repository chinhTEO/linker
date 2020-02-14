#include "linker.h"
#include "stdio.h"

linker::linker(){
    this->softSerial = null;
    buffer_time = 0;
    buffer_position = 7;
}

linker::linker(SoftwareSerial *softSerial){
    this->softSerial = softSerial;
    buffer_time = 0;
    buffer_position = 7;
}

linker::~linker(){

}

void linker::begin(unsigned long value){
    if(softSerial == null)
        Serial.begin(value);
    else
        softSerial->begin(value);
}

void linker::set(byte position, uint16_t value){
    uint8_t *value_8;
    uint8_t buffer[3];
    uint8_t header = position << 3;
    value_8 = (uint8_t *)&value;

    bitWrite(header, 2, bitRead(value_8[0],0));
    bitWrite(header, 1, bitRead(value_8[1],0));


    if(softSerial == null){
        Serial.write(header | 0x01); 
        Serial.write((value_8[0] >> 1) << 1);   
        Serial.write((value_8[1] >> 1) << 1); 
    }else{
        softSerial->write(header | 0x01); 
        softSerial->write((value_8[0] >> 1) << 1);   
        softSerial->write((value_8[1] >> 1) << 1); 
    }

    package_local[position] = value;
}

bool linker::isConnected(){
    return (millis() - sync_time) > SYNC_TIME_OUT ? false : true;
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

void linker::sendHeartBeat(){
    send(package_ptr, package_local[package_ptr]);
   
    package_ptr ++;
    
    if(package_ptr >= 31){
        package_ptr = 0;
    }
}

void linker::sync(){
    uint8_t charactor;

    if((millis() - last_send_time) > SYNC_TIMER){
        sendHeartBeat();
        last_send_time = millis();
    }

    if((millis() - buffer_time) > CUT_OFF_TIME)
        reset();

    if(softSerial == null){
        while(Serial.available()){
            last_recieve_time = millis();

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
                
                if(buffer_position == 1){
                    buffer[buffer_position] = charactor;
                    ++buffer_position;
                    buffer_time = millis();
                }

            }
        }
    }else{
        while(softSerial->available()){
            last_recieve_time = millis();

            charactor = softSerial->read();

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
                
                if(buffer_position == 1){
                    buffer[buffer_position] = charactor;
                    ++buffer_position;
                    buffer_time = millis();
                }

            }
        }
    }
}

unsigned int linker::read(int position){
    return package[position];
}
