/*

*/

#ifndef LOCALIZACAO_H
#define LOCALIZACAO_H

class Localizacao
{
public:
  Localizacao(void);

  void setLatitude(float latitude);

  float getLatitude(void);

  void setLongitude(float longitude);

  float getLongitude(void);

private:
  float _latitude;
  float _longitude;
};

#endif