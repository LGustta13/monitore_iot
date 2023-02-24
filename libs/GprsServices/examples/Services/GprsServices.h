/*
 GprsServices.h - Biblioteca para trabalhar com o GPRS (SIM800L).
 Criado pelo Luis Gustavo, 24 de Fevereiro, 2023.
*/

#ifndef GPRSSERVICES_H
#define GPRSSERVICES_H

#include <Arduino.h>

class GprsServices
{
public:
  /** Registra e executa o setup dos pinos
   * @param - int bomba_gatilho_0,
   * @return - void
   */
  GprsServices(void);

  /** Registra e executa o setup dos pinos
   * @param - int bomba_gatilho_0,
   * @return - void
   */
  void setupGprs(void);

  /** Registra e executa o setup dos pinos
   * @param - int bomba_gatilho_0,
   * @return - void
   */
  void updateDadosDaSerial(void);

};

#endif