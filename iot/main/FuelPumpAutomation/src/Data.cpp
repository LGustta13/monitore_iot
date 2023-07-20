/*

*/

#include "Data.h"

Data::Data()
{
  _timezone_type = "UTC";
  _timezone = 3;
  _data = "2000-01-01T00:00:00.001Z";
}

void Data::setData(String data)
{
  _data = data;
}

String Data::getData(void)
{
  return _data;
}

void Data::setTimezoneType(String type)
{
  _timezone_type = type;
}

String Data::getTimezoneType(void)
{
  return _timezone_type;
}

void Data::setTimezone(int timezone)
{
  _timezone = timezone;
}

int Data::getTimezone(void)
{
  return _timezone;
}