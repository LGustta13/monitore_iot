/*
  RtcServices.h - Biblioteca para enviar e receber sinais do RTC
  pelo barramento UART.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
*/

#ifndef RTCSERVICES_H
#define RTCSERVICES_H

#include <Arduino.h>

class RtcServices
{
public:
  /** Descrição
   * @param -
   * @return -
   */
  RtcServices(void);

  /** Funcao que realiza o setup dos pinos
   * @param - void
   * @return - void
   */
  void setupRtc(void);

  /** Descrição
   * @param -
   * @return -
   */
  void funcionalidade(void);
};

#endif
