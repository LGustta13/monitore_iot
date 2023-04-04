/*
  MicroSdServices.h - Biblioteca para ler e escrever dados
  no módulo do cartão microSD.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
*/

#ifndef MICROSDSERVICES_H
#define MICROSDSERVICES_H

#include <Arduino.h>

class MicroSdServices
{
public:
  MicroSdServices(void);

  /** Funcao que realiza o setup do módulo microSD
   * @param - void
   * @return - void
   */
  void setupMicroSd(void);

  /** Descrição
   * @param -
   * @return -
   */
  void salvarAbastecimento(void);

  /** Descrição
   * @param -
   * @return -
   */
  void resgatarAbastecimento(void);
};

#endif