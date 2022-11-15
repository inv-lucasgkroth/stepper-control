#include <Arduino.h>
#include "types.h"

#define dMOTOR_PULSE 13
#define dECHO_TASK_STACK_SIZE 2048

#define dTIMEOUT_COM_ELAPSE 500

void pre_transmit_485();
void post_transmit_485();

void com_handler(void *pvParameters);
void send_bytes();

void movimenta_motor(void *pvParameters);

unsigned long int timeOut = 0;

MOTOR_t motor;
COM_t com;

void setup()
{
  pinMode(MAX485_DE_RE, OUTPUT);
  pinMode(dBUILTIN_LED, OUTPUT); // Define dBUILTIN_LED como saida
  pinMode(dMOTOR_PULSE, OUTPUT); // Pino que envia pulsos para o driver do motor

  Serial.begin(9600); // Cria instancia da classe Serial, por default utiliza UART0 (TX0 - pino 41, RX0 - pino 40).

  bool state = false;

  com.readyToSend = 0;
  com.rx_buffer_size = 0;
  com.readyToReceived = 1;

  xTaskCreatePinnedToCore(com_handler, "com_handler", dECHO_TASK_STACK_SIZE, NULL, 1, NULL, ARDUINO_RUNNING_CORE);            // cria outra task no RTOS
  xTaskCreatePinnedToCore(movimenta_motor, "movimenta_motor_m1", dECHO_TASK_STACK_SIZE, NULL, 1, NULL, ARDUINO_RUNNING_CORE); // cria uma task no RTOS
}
void funcaoLixosaDoTarkos() // Falhou miseravelmente and steel falling
{
  if (Serial.available() > 0 && com.readyToReceived)
  {
    if (com.rx_buffer_size == 0)
    {
      timeOut = millis();
    }
    com.rx_buffer[com.rx_buffer_size] = Serial.read();
    com.rx_buffer_size++;

    if ((millis() - timeOut) >= dTIMEOUT_COM_ELAPSE && com.rx_buffer_size != 0)
    {
      com.readyToSend = 1;
      com.readyToReceived = 0;
      timeOut = millis();
    }
  }

  if (com.readyToSend && !com.readyToReceived)
  {
    int pos = 0;

    for (pos = 0; pos < com.rx_buffer_size; pos++) // copia rx_buffer para tx_buffer
    {
      com.tx_buffer[pos] = com.rx_buffer[pos];
      Serial.println(com.tx_buffer[pos]);
    }

    com.tx_buffer_size = com.rx_buffer_size;

    // Serial.print("Tamanho tx buffer: ");
    // Serial.print(com.tx_buffer_size);

    pre_transmit_485();
    send_bytes();
    delay(5);
    post_transmit_485();
    com.readyToSend = 0;
    com.rx_buffer_size = 0;
    com.readyToReceived = 1;
  }
}

void com_handler(void *pvParameters)
{
  (void)pvParameters;
  Serial.setTimeout(50);

  while (1) // funcao loop() AINDA nao utilizado devido a problemas com escopo
  {
    if (Serial.available() > 0)
    {
      com.tx_buffer_size = Serial.readBytes(com.rx_buffer, dBUFFER_SIZE);

      for (int pos = 0; pos < com.tx_buffer_size; pos++) // copia rx_buffer para tx_buffer
      {
        com.tx_buffer[pos] = com.rx_buffer[pos];
      }

      pre_transmit_485();
      send_bytes();
      Serial.flush();
      post_transmit_485();
    }
  }
}

void send_bytes()
{
  for (int pos = 0; pos < com.tx_buffer_size; pos++) // Envia pela serial conteudo do tx_buffer
  {
    digitalWrite(dBUILTIN_LED, HIGH);
    Serial.write(com.tx_buffer[pos]);
    digitalWrite(dBUILTIN_LED, LOW);
  }
  com.tx_buffer_size = 0;
}

void pre_transmit_485()
{
  digitalWrite(MAX485_DE_RE, 1);
}

void post_transmit_485()
{
  digitalWrite(MAX485_DE_RE, 0);
}

void movimenta_motor(void *pvParameters)
{
  (void)pvParameters;

  while (1)
  {
    if (!motor.state)
    {
      digitalWrite(dMOTOR_PULSE, HIGH);
      motor.state = true;
    }
    else
    {
      digitalWrite(dMOTOR_PULSE, LOW);
      motor.state = false;
    }
  }
  vTaskDelay(1 / portTICK_PERIOD_MS);
}

void loop() {}