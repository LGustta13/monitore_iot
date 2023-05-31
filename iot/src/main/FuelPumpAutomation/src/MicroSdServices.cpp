/*
  MicroSdServices.cpp - Biblioteca para ler e escrever dados
  no módulo do cartão microSD.
  Criado pelo Luis Gustavo, 15 de Março, 2023.
*/

#include "MicroSdServices.h"

MicroSdServices::MicroSdServices(int pino_sd, const char *filename_abastecimentos, const char *filename_frentistas, const char *filename_veiculos, const char *filename_motoristas)
{
  _filename = filename;
  _pino_moduloSD = pino;
  _quantidadeDeAbastecimentos = 5;
  _bytesAbastecimentos = 380;
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
  String abastecimentos = "";

  if (SD.exists(_filename))
  {
    File file = SD.open(_filename);

    if (!file)
    {
      Serial.println(F("Failed to read file"));
    }
    else
    {

      // Extract each characters by one by one
      while (file.available())
      {
        abastecimentos = file.readString();
        file.close();
      }

      Serial.println("Conteúdo do arquivo");
      Serial.println(abastecimentos);
    }
  }
  else
  {
    Serial.println("O arquivo não existe!");
  }

  return abastecimentos
}

bool MicroSdServices::setAbastecimento(String abastecimento_serial)
{
  File file = SD.open(_filename);

  StaticJsonDocument<(quantidadeDeAbastecimentos * bytesAbastecimentos) + 2> root;

  DeserializationError error = deserializeJson(root, file);
  if (error)
    Serial.println(F("Nenhum abastecimento inicial no arquivo"));

  file.close();

  StaticJsonDocument<abastecimento_serial.length()> doc;

  DeserializationError error = deserializeJson(doc, abastecimento_serial);

  // Verificar se houve algum erro durante a deserialização
  if (error)
  {
    Serial.print("Falha ao deserializar o JSON: ");
    Serial.println(error.c_str());
    return false;
  }

  // Append new element
  JsonObject obj = root.createNestedObject();
  obj["tank_id"] = doc["id"];
  obj["tank_name"] = doc["nome_bomba"];
  obj["initial_volume"] = doc["latitude"];
  obj["final_volume"] = doc["longitude"];
  obj["drain_value"] = doc["volume_abastecido"];

  JsonObject utc_initial_date_time = obj.createNestedObject("utc_initial_date_time");
  utc_initial_date_time["date"] = doc["data_inicial"]["dia"];
  utc_initial_date_time["timezone_type"] = doc["data_inicial"]["timezone_tipo"];
  utc_initial_date_time["timezone"] = doc["data_inicial"]["timezone"];

  JsonObject utc_final_date_time = obj.createNestedObject("utc_final_date_time");
  utc_final_date_time["date"] = doc["data_final"]["dia"];
  utc_final_date_time["timezone_type"] = doc["data_final"]["timezone_tipo"];
  utc_final_date_time["timezone"] = doc["data_final"]["timezone"];

  obj["ident_pessoa_apoio"] = doc["id_frentista"];
  obj["ident_veiculo"] = doc["id_veiculo"];
  obj["ident_motorista"] = doc["id_motorista"];

  file = SD.open(_filename, FILE_WRITE);
  if (serializeJson(root, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
    return false;
  }
  file.close();

  return true;
}

// Exibir os dados do arquivo
void MicroSdServices::printArquivo(void)
{

  File file = SD.open(_filename);
  if (!file)
  {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available())
  {
    Serial.print((char)file.read());
  }
  Serial.println();

  file.close();
}

float MicroSdServices::volumeParaAbastecer(int id_veiculo)
{
}