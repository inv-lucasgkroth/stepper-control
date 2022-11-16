#define dBUILTIN_LED 2
#define dBUFFER_SIZE 256

#define MAX485_DE_RE 22

typedef struct COM
{
    unsigned char tx_buffer[dBUFFER_SIZE];
    unsigned char rx_buffer[dBUFFER_SIZE];
    int rx_buffer_last_pos;
    int tx_buffer_last_pos;
} COM_t;

typedef struct MOTOR
{
    u_int16_t pulses;
    bool enable = false;
    bool dir = false;
    bool state = false;
} MOTOR_t;