/*
  Services.ino - exemplo de uso das funções
  Criado pelo Luis Gustavo, 21 de Dezembro, 2022.
*/

/*
  Orientações:
  ESP32 PINOUT(13, -1, 4, -1, 32, 33, 27, 26)
  ARDUINO PINOUT(4, 5, 2, 3, 6, 7, 8, 9)
  DREXIA PINOUT(25)
*/

#include "I2cServices.h"

AtuadorServices esp32(32, 13, 16, 34, 33, 19, 18, 17);
DrexiaServices drexia(25, esp32);
GpsServices gps;
I2cServices i2c(0x21, 26, 27, gps, esp32, drexia);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
}
