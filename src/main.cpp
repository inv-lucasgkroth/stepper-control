#include <Arduino.h>
#include "types.h"

void preTransmission();
void postTransmission();

void setup()
{
  pinMode(MAX485_DE_RE, OUTPUT);
  pinMode(dBUILTIN_LED, OUTPUT); // Define dBUILTIN_LED como saida

  Serial.begin(9600); // Cria instancia da classe Serial, por default utiliza UART0 (TX0 - pino 41, RX0 - pino 40).

  COM_t com;

  while (1) // funcao loop() AINDA nao utilizado devido a problemas com escopo
  {

    if (Serial.available() > 0)
    {
      com.tx_buffer_size = Serial.readBytes(com.rx_buffer, dBUFFER_SIZE);

      for (int pos = 0; pos < com.tx_buffer_size; pos++) // copia rx_buffer para tx_buffer
      {
        com.tx_buffer[pos] = com.rx_buffer[pos];
      }

      preTransmission();
      delay(5);

      for (int pos = 0; pos < com.tx_buffer_size; pos++) // Envia pela serial conteudo do tx_buffer
      {
        digitalWrite(dBUILTIN_LED, HIGH);
        Serial.write(com.tx_buffer[pos]);
        digitalWrite(dBUILTIN_LED, LOW);
      }

      delay(5);
      postTransmission();
    }
  }
}

void preTransmission()
{
  digitalWrite(MAX485_DE_RE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_DE_RE, 0);
}

void loop()
{
}