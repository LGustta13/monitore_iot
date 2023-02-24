/*
 Services.ino - Biblioteca para trabalhar com o GPRS (SIM800L).
 Criado pelo Luis Gustavo, 24 de Fevereiro, 2023.
*/

/*
  Orientações:
  ESP32 PINOUT()
*/

/*
  Parâmetros de AtuadorServices:

*/

#include "GprsServices.h"

GprsServices sim800L();

void setup()
{
}

void loop()
{
    sim800L.updateDadosDaSerial();
}