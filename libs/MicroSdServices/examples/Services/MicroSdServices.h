/*
  MicroSdServices.h - Biblioteca para ler e escrever dados
  no módulo do cartão microSD.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
*/

#ifndef MICROSDSERVICES_H
#define MICROSDSERVICES_H

#include <Arduino.h>
#include <ArduinoJSON>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

class MicroSdServices
{
public:
    MicroSdServices(int pino);
    MicroSdServices(int pino, bool abastecimento_fake);

    /** Funcao que realiza o setup do módulo microSD
     * @param - void
     * @return - void
     */
    void inicializarMicroSd(void);

    /** Acessa os abastecimentos e salva em uma variável
     * @param -void
     * @return - String anastecimentos: abastecimentos
     */
    String lerAbastecimentos(void);

    /** Escreve os abastecimentos e salva em uma variável
     * @param -void
     * @return - String anastecimentos: abastecimentos
     */
    String escreverAbastecimentos(void);

  private:
  String _abastecimentos;
  int _pino_moduloSD;
};

#endif