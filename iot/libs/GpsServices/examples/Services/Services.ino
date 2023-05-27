/*
  Services.ino - exemplo de uso das funções
  Criado pelo Luis Gustavo, 26 de Dezembro, 2022.
*/

#include "GpsServices.h"

// Configura o gps
GpsServices gps;

void setup()
{
    Serial.begin(9600);

    gps.getInfoDoGps();
    gps.getDadosDeLongitude();
    gps.getDadosDeLatitude();
    // gps.getBufferRxTx();
}

void loop()
{
}
