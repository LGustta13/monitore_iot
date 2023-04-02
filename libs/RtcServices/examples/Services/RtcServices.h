/*
  RtcServices.h - Biblioteca para enviar e receber sinais do RTC
  pelo barramento UART.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
  Atualizado, 02 de Abril, 2023.
*/

#ifndef RTCSERVICES_H
#define RTCSERVICES_H

#include <Arduino.h>
#include <RTClib.h>

class RtcServices
{
public:
  /** Construtor
   * @param - void
   * @return - void
   */
  RtcServices(void);

  /** Acessa barramento i2c e salva data e horário
   * @param - void
   * @return - void
   */
  void handleDataHorarioAbastecimento(void);

  /** Retorna o horário do abastecimento
   * @param - void
   * @return - String horario: horário do abastecimento
   */
  String getHorario(void);

  /** Retorna a data do abastecimento
   * @param - void
   * @return - String data: horário do abastecimento
   */
  String getData(void);

private:
  RTC_DS1307 _rtc;
  String _horario;
  String _data;
};

#endif
