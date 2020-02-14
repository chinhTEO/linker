#ifndef LINKER_H_
#define LINKER_H_ 1
#include <arduino.h>
#include <stdint.h>
#include <SoftwareSerial.h>

#define MAX_PACK_NUM 32

#define SYNC_TIMER      300
#define SYNC_TIME_OUT   1000
#define CUT_OFF_TIME    500

class linker{
    public:
        linker();
        linker(SoftwareSerial *softSerial)
        ~linker();

        void begin(unsigned long value);
        void set(byte position, unsigned int value);
        
        bool isConnected();

        void sync();

        void portData();
        unsigned int read(int position);

    private:
        unsigned long buffer_time;
        unsigned long last_recieve_time;
        unsigned long last_send_time;
        
        uint8_t buffer[3];
        int buffer_position;
        
        uint16_t package[MAX_PACK_NUM];
        uint16_t package_local[MAX_PACK_NUM]
        uint8_t package_ptr;

        SoftwareSerial *softSerial;

        void sendHeartBeat();
        void reset();
};

#endif
