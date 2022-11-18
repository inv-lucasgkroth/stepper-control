#include <Arduino.h>

// multitask
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// saida PWM
#include "driver/adc.h"
#include "driver/ledc.h"

#include "types.h"
#include "biliotecaQualquer.h"

MOTOR_t motor;
COM_t com;

void setup()
{
  pinMode(dMAX485_DE_RE, OUTPUT);
  pinMode(dBUILTIN_LED, OUTPUT); // Define dBUILTIN_LED como saida
  // pinMode(dMOTOR_PULSE, 155);    // Pino que envia pulsos para o driver do motor

  Serial.begin(9600); // Cria instancia da classe Serial, por default utiliza UART0 (TX0 - pino 41, RX0 - pino 40).

  bool state = false;

  com.rx_buffer_last_pos = 0;

  TaskHandle_t com;
  TaskHandle_t mov_stepper;

  // xTaskCreatePinnedToCore(com_handler, "com_handler", STACK_SIZE, NULL, 1, &com, 1);
  xTaskCreatePinnedToCore(movimenta_motor, "movimenta_motor_m1", STACK_SIZE, NULL, 3, &mov_stepper, 0);

  // xTaskCreatePinnedToCore(
  //     Task1code,  /* Função da tarefa */
  //     "Lembrete", /* nome da tarefa */
  //     10000,      /* Tamanho (bytes) */
  //     NULL,       /* parâmetro da tarefa */
  //     1,          /* prioridade da tarefa */
  //     &Task1,     /* observa a tarefa criada */
  //     0);         /* tarefa alocada ao núcleo 0 */
}

void com_handler(void *pvParameters)
{
  (void)pvParameters;

  // Serial.setTimeout(50);

  while (1) // funcao loop() AINDA nao utilizado devido a problemas com escopo
  {
    u_int32_t n_bytes = Serial.available();

    if (n_bytes > 0)
    {
      com.tx_buffer_last_pos = Serial.readBytes(com.rx_buffer, n_bytes);

      for (int pos = 0; pos < com.tx_buffer_last_pos; pos++) // copia rx_buffer para tx_buffer
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
  for (int pos = 0; pos < com.tx_buffer_last_pos; pos++) // Envia pela serial conteudo do tx_buffer
  {
    Serial.write(com.tx_buffer[pos]);
  }
}

void pre_transmit_485()
{
  digitalWrite(dMAX485_DE_RE, 1);
}

void post_transmit_485()
{
  digitalWrite(dMAX485_DE_RE, 0);
}

void setPWM_and_time_step_motor(int pwmChannel, int pwmResolution, int freq, int delayTimeMs)
{
  Serial.println("freq");
  Serial.println(freq);
  Serial.println("PWMChannel");
  Serial.println(pwmChannel);
  Serial.println("PWMResolution");
  Serial.println(pwmResolution);

  ledcSetup(pwmChannel, freq, pwmResolution);
  ledcWrite(pwmChannel, delayTimeMs);
  vTaskDelay(delayTimeMs / portTICK_PERIOD_MS);
}

void movimenta_motor(void *pvParameters)
{
  (void)pvParameters;

  unsigned int freq;
  const int PWMChannel = 0;
  const int PWMResolution = 10;
  ledcAttachPin(dMOTOR_PULSE, PWMChannel);

  for (;;)
  {

    Serial.println("incrementando");
    for (freq = dMIN_FREQ; freq <= dMAX_FREQ; freq = freq + 100)
    {
      setPWM_and_time_step_motor(PWMChannel, PWMResolution, freq, 50);
    }
    Serial.println("decrementando");
    for (freq = dMAX_FREQ; freq >= dMIN_FREQ; freq = freq - 100)
    {
      setPWM_and_time_step_motor(PWMChannel, PWMResolution, freq, 50);
    }
  }
}

void loop() {}