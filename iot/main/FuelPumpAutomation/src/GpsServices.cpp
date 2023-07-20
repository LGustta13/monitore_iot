/*
  GpsServices.cpp - Biblioteca para enviar sinais de comando
  e auxiliar no monitoramento pelo Gps.
  Criado pelo Luis Gustavo, 26 de Dezembro, 2022.
  Atualizado, 02 de Abril, 2023.
*/

#include "GpsServices.h"

GpsServices::GpsServices(void)
{
  Serial2.begin(9600);
}

void GpsServices::getInfoGps(void)
{
  float latitude = (float)(_gps.location.lat(), 6);
  float longitude = (float)(_gps.location.lng(), 6);

  _localizacao.setLatitude(latitude);
  _localizacao.setLongitude(longitude);
}

void GpsServices::handleLatitudeLongitude(void)
{
  bool dados_verificados = false;
  bool dados_da_porta_serial_resgatados = false;
  bool dados_de_localizacao_validos = false;

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

Localizacao GpsServices::getLocalizacao(void)
{
  return _localizacao;
}