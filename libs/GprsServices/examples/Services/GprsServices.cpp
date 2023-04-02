/*
 GprsServices.cpp - Biblioteca para trabalhar com o GPRS (SIM800L).
 Criado pelo Luis Gustavo, 24 de Fevereiro, 2023.
*/

#include "GprsServices.h"

GprsServices::GprsServices(void)
{
  setupGprs();
}

void GprsServices::setupGprs(void)
{
  Serial.begin(115200);
  Serial2.begin(115200);
}

void GprsServices::updateDadosDaSerial(void)
{
  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
  if (Serial.available()) {
    Serial2.write(Serial.read());
  }
}

void 