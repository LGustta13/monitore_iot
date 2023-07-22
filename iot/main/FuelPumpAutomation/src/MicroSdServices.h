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
  MicroSdServices(int pino_sd, String filename_abastecimentos, String filename_frentistas, String filename_veiculos, String filename_motoristas);

  void inicializarMicroSd(void);

  String acessarAbastecimentos(void);

  String acessarFrentistas(void);

  String acessarMotoristas(void);

  String acessarVeiculos(void);

  void salvarAbastecimento(String abastecimento_serial);

  float buscarLimiteAbastecimento(int id_veiculo);

private:
  String _file_abastecimentos;
  String _file_frentistas;
  String _file_motoristas;
  String _file_veiculos;
  int _quantidade_abastecimentos;
  int _pino_moduloSD;
};

#endif