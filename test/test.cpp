#include <iostream>
#include <stdint.h>
#include "utest.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

UTEST(linker, process_test){
    unsigned int test_count = 100000;

    while(test_count--) {
    uint8_t position = rand() % 32;

    uint8_t buffer[3];
    uint8_t *value_8;
    
    uint16_t value = rand() % 0xffff;
    value_8 = (uint8_t *)&value;

    unsigned int digit = 0;
    uint8_t header = position << 3;

    bitWrite(header, 2, bitRead(value_8[0],0));
    bitWrite(header, 1, bitRead(value_8[1],0));
    // Serial.write(header | 0x01); 
    // Serial.write((value_pos_1 >> 1) << 1);   
    // Serial.write((value_pos_2 >> 1) << 1);   

    buffer[0] = (header | 0x01 );
    buffer[1] = ((value_8[0] >> 1) << 1);
    buffer[2] = ((value_8[1] >> 1) << 1);

    // std::cout   << "header: " << (unsigned int)buffer[0] << std::endl
    //              << "value 1: "  << (unsigned int)buffer[1]  << std::endl
    //              << "value 2: "  << (unsigned int)buffer[2]  << std::endl;

    uint8_t number[2];
    int package_num = (buffer[0] & 0b11111000) >> 3;
    number[0] = buffer[1] | (bitRead(buffer[0],2));
    number[1] = buffer[2] | (bitRead(buffer[0],1));
    uint16_t out = *((uint16_t *)number);

    std::cout << "pos: " << package_num << std::endl
              << "value: " << out << std::endl;
    
    EXPECT_EQ(package_num, position);
    EXPECT_EQ(value, out);
    
    }
}

UTEST_MAIN();