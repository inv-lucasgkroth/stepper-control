#define dBUILTIN_LED 2
#define dBUFFER_SIZE 16

typedef struct COM
{
    char tx_buffer[dBUFFER_SIZE];
    char rx_buffer[dBUFFER_SIZE];
    char tx_buffer_size;
} COM_t;