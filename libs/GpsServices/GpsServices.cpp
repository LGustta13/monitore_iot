/*
  GpsServices.cpp - Biblioteca para enviar sinais de comando
  e auxiliar no monitoramento pelo Gps.
  Criado pelo Luis Gustavo, 26 de Dezembro, 2022.
  Atualizado, 02 de Abril, 2023.
*/

#include "GpsServices.h"

Localizacao::Localizacao(void)
{
    _latitude = 0;
    _longitude = 0;
}

void Localizacao::setLatitude(float latitude)
{
    _latitude = latitude;
}

float Localizacao::getLatitude(void)
{
    return _latitude;
}

void Localizacao::setLongitude(float longitude)
{
    _longitude = longitude;
}

float Localizacao::getLongitude(void)
{
    return _longitude;
}

GpsServices::GpsServices(void)
{
    TinyGPSPlus _gps;
    Localizacao _localizacao();
    Serial2.begin(9600);
}

void GpsServices::getInfoGps(void)
{
    _latitude = (float)(_gps.location.lat(), 6);
    _longitude = (float)(_gps.location.lng(), 6);

    _localizacao.setLatitude(_latitude);
    _localizacao.setLongitude(_longitude);
}

void GpsServices::handleLatitudeLongitude(void)
{
    bool dados_verificados = false, dados_da_porta_serial_resgatados = false, dados_de_localizacao_validos = false;

    while (dados_verificados == false)
    {
        dados_da_porta_serial_resgatados = _gps.encode(Serial2.read());
        if (dados_da_porta_serial_resgatados)
        {
            dados_de_localizacao_validos = _gps.location.isValid();
            if (dados_de_localizacao_validos)
            {
                getInfoGps();
                dados_verificados = true;
            }
            else
            {
                Serial.print(F("INVALIDO"));
            }
        }
    }
}

LocalizacaoServices GpsServices::getLocalizacao(void)
{
    return _localizacao;
}