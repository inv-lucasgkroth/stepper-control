#define dBUILTIN_LED 2
#define dBUFFER_SIZE 16

#define MAX485_DE_RE 22

typedef struct COM
{
    char tx_buffer[dBUFFER_SIZE];
    char rx_buffer[dBUFFER_SIZE];
    char tx_buffer_size;
} COM_t;