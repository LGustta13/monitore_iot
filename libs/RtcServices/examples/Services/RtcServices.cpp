/*
  RtcServices.cpp - Biblioteca para enviar e receber sinais do RTC
  pelo barramento UART.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
  Atualizado, 02 de Abril, 2023.
*/

#include "RtcServices.h"

RtcServices::RtcServices(void)
{
  _rtc.begin();
  _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void RtcServices::handleDataHorarioAbastecimento(void)
{
  DateTime now = _rtc.now();
  _horario = String(rtc.now().hour()) + String(rtc.now().minute()) + String(rtc.now().second());
  _data = String(rtc.now().year()) + String(rtc.now().month()) + String(rtc.now().day());
  delay(1000);
}

String RtcServices::getHorario(void)
{
  return _horario;
}

String RtcServices::getData(void)
{
  return _data;
}

String RtcServices::getDataHorario(void)
{
  return _data + " " + _horario;
}