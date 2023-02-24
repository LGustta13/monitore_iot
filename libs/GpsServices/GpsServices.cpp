/*
  GpsServices.cpp - Biblioteca para enviar sinais de comando
  e auxiliar no monitoramento pelo Gps.
  Criado pelo Luis Gustavo, 26 de Dezembro, 2022.
*/

#include "GpsServices.h"

GpsServices::GpsServices(void)
{
    TinyGPSPlus _gps;
    setupGps();
}

void GpsServices::setupGps(void)
{
    Serial2.begin(9600);
}

void GpsServices::getDadosDeLatitude(void)
{
    signed int raw_data_latitude;
    raw_data_latitude = (signed int)(_gps.location.lat() * 1000000);
    _buffer_rxtx[0] = (raw_data_latitude >> 24);
    _buffer_rxtx[1] = (raw_data_latitude >> 16) & 255;
    _buffer_rxtx[2] = (raw_data_latitude >> 8) & 255;
    _buffer_rxtx[3] = (raw_data_latitude)&255;
}

void GpsServices::getDadosDeLongitude(void)
{
    signed int raw_data_longitude;
    raw_data_longitude = (signed int)(_gps.location.lng() * 1000000);
    _buffer_rxtx[4] = (raw_data_longitude >> 24);
    _buffer_rxtx[5] = (raw_data_longitude >> 16) & 255;
    _buffer_rxtx[6] = (raw_data_longitude >> 8) & 255;
    _buffer_rxtx[7] = (raw_data_longitude)&255;
}

void GpsServices::getInfoDoGps(void)
{
    signed int raw_data_latitude, raw_data_longitude;
    bool dados_verificados = false, dados_da_porta_serial_resgatados = false, dados_de_localizacao_validos = false;

    while (dados_verificados == false)
    {
        dados_da_porta_serial_resgatados = _gps.encode(Serial2.read());
        if (dados_da_porta_serial_resgatados)
        {
            dados_de_localizacao_validos = _gps.location.isValid();
            if (dados_de_localizacao_validos)
            {
                getDadosDeLatitude();
                getDadosDeLongitude();
                dados_verificados = true;
            }
            else
            {
                Serial.print(F("INVALIDO"));
            }
        }
    }
}

byte *GpsServices::getBufferRxTx(void)
{
    return _buffer_rxtx;
}