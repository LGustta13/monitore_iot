/*
  MicroSdServices.cpp - Biblioteca para ler e escrever dados
  no módulo do cartão microSD.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
*/

#include "MicroSdServices.h"

MicroSdServices::MicroSdServices(int pino_sd)
{
  _pino_moduloSD = pino;
  inicializarMicroSd();
}

void MicroSdServices::inicializarMicroSd(void)
{
  if (!SD.begin(_pino_moduloSD))
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

String MicroSdServices::getAbastecimento(void)
{
}

void MicroSdServices::setAbastecimento(String abastecimento_serial)
{
}