#ifndef TYPES_H_
#define TYPES_H_

#define dBUILTIN_LED GPIO_NUM_2
#define STACK_SIZE 2048

#define dBUFFER_SIZE 256
#define dMAX485_DE_RE 22

void com_handler(void *pvParameters);
void send_bytes();
void pre_transmit_485();
void post_transmit_485();

typedef struct COM
{
    unsigned char tx_buffer[dBUFFER_SIZE];
    unsigned char rx_buffer[dBUFFER_SIZE];
    int rx_buffer_last_pos;
    int tx_buffer_last_pos;
} COM_t;

#define dMOTOR_PULSE GPIO_NUM_13
#define dMAX_FREQ 3000
#define dMIN_FREQ 500

void movimenta_motor(void *pvParameters);

typedef struct MOTOR
{
    u_int16_t pulses;
    bool enable = false;
    bool dir = false;
    bool state = false;
} MOTOR_t;

#endif