/*
  MicroSdServices.h - Biblioteca para ler e escrever dados
  no módulo do cartão microSD.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
*/

#ifndef MICROSDSERVICES_H
#define MICROSDSERVICES_H

#include <Arduino.h>
#include <ArduinoJSON.h>
#include <SD.h>
#include <SPI.h>

struct Data
{
  char dia[20];
  int timezone_tipo;
  char timezone[3];
};

struct Abastecimento
{
  int id;
  char nome_bomba[25];
  float latitude;
  float longitude;
  float volume_abastecido;
  Data data_inicial;
  Data data_final;
  int id_frentista;
  int id_motorista;
  int id_veiculo;
};

class MicroSdServices
{
public:
  MicroSdServices(int pino_sd);

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
  void setAbastecimento(String abastecimento_serial);

private:
  String _abastecimento_serial;
  const char *filename;
  int _pino_moduloSD;
};

#endif