/*
  Services.ino - exemplo de uso das funções
  Criado pelo Luis Gustavo, 29 de Novembro, 2022.
*/

/*
  Orientações:
  ESP32 PINOUT(32, 13, 16, 34, 33, 19, 18, 17)
  ARDUINO PINOUT(4, 5, 2, 3, 6, 7, 8, 9)
*/

/*
  Parâmetros de AtuadorServices:
  1. bomba_gatilho_0        \ RELÉ DE BLOQUEIO
  2. bomba_gatilho_1        /
  3. pino_sensor_0          \ PULSOS
  4. pino_sensor_1          /
  5. pino_buzzer            \
  5. pino_led_verde         | BUZZER E LEDS
  7. pino_led_vermelho      |
  8. pino_led_azul          /
*/

#include "AtuadorServices.h"

AtuadorServices esp32(32, 13, 16, 34, 33, 19, 18, 17);

void timeout(void){
  Serial.begin(9600);
  Serial.println("Iniciando abastecimento em 3,2,1...");
  delay(3000);
}

void setup() 
{
  timeout();
  Serial.println(esp32.realizarAbastecimento(50));
}

void loop()
{
  
}
