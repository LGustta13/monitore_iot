/*
  GpsServices.h - Biblioteca para enviar sinais de comando
  e auxiliar no monitoramento pelo Gps.
  Criado pelo Luis Gustavo, 26 de Dezembro, 2022.
  Atualizado, 02 de Abril, 2023.
*/

#ifndef GPSSERVICES_H
#define GPSSERVICES_H

#include <Arduino.h>
#include <TinyGPSPlus.h>

class GpsServices
{
public:
  /** Construtor, inicializa a serial I2C
   * @param - void
   * @return - void
   */
  GpsServices(void);

  /** Funcao que resgata o dado de latitude
   * @param - void
   * @return - float latitude: latitude
   */
  float getLatitude(void);

  /** Funcao que resgata o dado de longitude
   * @param - void
   * @return - float longitude: longitude
   */
  float getLongitude(void);

  /** Lógica para validar o GPS
   * @param - void
   * @return - void
   */
  void handleLatitudeLongitude(void);

  /** Pega os valores de latitude e longitude pelo GPS
   * @param - void
   * @return - void
   */
  void getInfoGps(void);

private:
  TinyGPSPlus _gps;
  float _latitude;
  float _longitude;
};

#endif