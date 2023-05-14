/*
  MicroSdServices.cpp - Biblioteca para ler e escrever dados
  no módulo do cartão microSD.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
*/

#include "MicroSdServices.h"

MicroSdServices::MicroSdServices(int pino)
{
  _pino_moduloSD = pino;
  inicializarMicroSd();
}

MicroSdServices::MicroSdServices(int pino, bool abastecimento_fake)
{
  _pino_moduloSD = pino;
  if (abastecimento_fake)
  {
    _abastecimentos = "[{\"tank_id\":5449,\"tank_name\":\"BOMBA TRANSPRINT CAJAMAR\",\"initial_volume\":\"NULL\",\"final_volume\":\"NULL\",\"drain_value\":400,\"utc_initial_date_time\":[{\"date\":\"2000-05-02 00:02:00\",\"timezone_type\":3,\"timezone\":\"UTC\"}],\"utc_final_date_time\":[{\"date\":\"2000-05-02 00:10:00\",\"timezone_type\":3,\"timezone\":\"UTC\"}],\"ident_pessoa_apoio\":16651608,\"ident_veiculo\":16651608,\"ident_motorista\":16651608}]";
  }
  inicializarMicroSd();
}

void MicroSdServices::inicializarMicroSd(void)
{
  if (!SD.begin(_pino_mosuloSD))
  {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC)
  {
    Serial.println("MMC");
  }
  else if (cardType == CARD_SD)
  {
    Serial.println("SDSC");
  }
  else if (cardType == CARD_SDHC)
  {
    Serial.println("SDHC");
  }
  else
  {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

String MicroSdServices::lerAbastecimentos(void)
{
}

void MicroSdServices::escreverAbastecimentos(String)
{
}