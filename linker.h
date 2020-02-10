#ifndef LINKER_H_
#define LINKER_H_ 1
#include <arduino.h>
#include <stdint.h>

#define MAX_PACK_NUM 32
#define MAX_TIME_WAITING 500
#define CUT_OFF_TIME 500

class linker{
    public:
        linker();
        ~linker();

        void begin(unsigned long value);
        void send(byte position, unsigned int value);

        void reset();
        void update();

        void portData();
        unsigned int read(int position);
    private:
        unsigned long buffer_time;
        uint8_t buffer[3];
        int buffer_position;
        uint16_t package[MAX_PACK_NUM];
};

#endif
