/*
  RtcServices.cpp - Biblioteca para enviar e receber sinais do RTC
  pelo barramento UART.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
  Atualizado, 02 de Abril, 2023.
*/

#include "RtcServices.h"

RtcServices::RtcServices(void) : _rtc()
{
}

void RtcServices::handleDataHorarioAbastecimento(void)
{
  _rtc.begin();
  // _rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  DateTime now = _rtc.now();

  char buf1[] = "YYYY-MM-DDThh:mm:ssZ";
  _data = now.toString(buf1);
}

String RtcServices::getData(void)
{
  return _data;
}