/*
  MicroSdServices.h - Biblioteca para ler e escrever dados
  no módulo do cartão microSD.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
*/

#ifndef MICROSDSERVICES_H
#define MICROSDSERVICES_H

#include <Arduino.h>

#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include "Data.h"
#include "Abastecimento.h"

class MicroSdServices
{
public:
  MicroSdServices(int pino_sd, const char *filename_abastecimentos, const char *filename_frentistas, const char *filename_veiculos, const char *filename_motoristas);

  void inicializarMicroSd(void);

  /** Funcao que realiza o setup do módulo microSD
   * @param - void
   * @return - void
   */
  String getAbastecimento(void);

  /** Acessa os abastecimentos e salva em uma variável
   * @param -void
   * @return - String anastecimentos: abastecimentos
   */
  bool setAbastecimento(String abastecimento_serial);

  void printArquivo(void);

  float volumeParaAbastecer(int id_veiculo);

private:
  String _abastecimento_serial;
  const char *_filename;
  int _quantidadeDeAbastecimentos;
  int _bytesAbastecimentos;
  int _pino_moduloSD;
};

#endif