/*

*/

#include "Localizacao.h"

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