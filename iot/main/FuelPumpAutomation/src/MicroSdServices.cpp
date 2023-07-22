/*
  REVISÃO: (22/07) Necessita verificar as funcionalidades
*/

#include "MicroSdServices.h"

MicroSdServices::MicroSdServices(int pino_sd, String filename_abastecimentos, String filename_frentistas, String filename_veiculos, String filename_motoristas)
{
  _file_abastecimentos = filename_abastecimentos;
  _file_frentistas = filename_frentistas;
  _file_motoristas = filename_motoristas;
  _file_veiculos = filename_veiculos;
  _pino_moduloSD = pino_sd;
  _quantidade_abastecimentos = 0;

  inicializarMicroSd();
}

void MicroSdServices::inicializarMicroSd(void)
{
  if (!SD.begin(_pino_moduloSD))
  {
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    return;
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

String MicroSdServices::acessarAbastecimentos(void)
{
  String abastecimentos = "";

  if (SD.exists(_file_abastecimentos))
  {
    File file = SD.open(_file_abastecimentos);

    if (!file)
    {
      Serial.println(F("Falha ao ler arquivo"));
    }
    else
    {

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

String MicroSdServices::acessarFrentistas(void)
{
  String frentistas = "";

  if (SD.exists(_file_frentistas))
  {
    File file = SD.open(_file_frentistas);

    if (!file)
    {
      Serial.println(F("Falha ao ler arquivo"));
    }
    else
    {

      while (file.available())
      {
        frentistas = file.readString();
        file.close();
      }

      Serial.println("Conteúdo do arquivo");
      Serial.println(frentistas);
    }
  }
  else
  {
    Serial.println("O arquivo não existe!");
  }

  return frentistas
}

String MicroSdServices::acessarMotoristas(void)
{
  String motoristas = "";

  if (SD.exists(_file_motoristas))
  {
    File file = SD.open(_file_motoristas);

    if (!file)
    {
      Serial.println(F("Falha ao ler arquivo"));
    }
    else
    {

      while (file.available())
      {
        motoristas = file.readString();
        file.close();
      }

      Serial.println("Conteúdo do arquivo");
      Serial.println(motoristas);
    }
  }
  else
  {
    Serial.println("O arquivo não existe!");
  }

  return motoristas
}

String MicroSdServices::acessarVeiculos(void)
{
  String veiculos = "";

  if (SD.exists(_file_veiculos))
  {
    File file = SD.open(_file_veiculos);

    if (!file)
    {
      Serial.println(F("Falha ao ler arquivo"));
    }
    else
    {

      while (file.available())
      {
        veiculos = file.readString();
        file.close();
      }

      Serial.println("Conteúdo do arquivo");
      Serial.println(veiculos);
    }
  }
  else
  {
    Serial.println("O arquivo não existe!");
  }

  return veiculos
}

void MicroSdServices::salvarAbastecimento(String abastecimento_serial)
{
  File file = SD.open(_file_abastecimentos);

  StaticJsonDocument<(_quantidade_abastecimentos * 800) + 2> root;

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
    return;
  }

  JsonObject obj = root.createNestedObject();
  obj["tank_id"] = doc["id"];
  obj["tank_name"] = doc["nome_bomba"];
  obj["latitide"] = doc["latitude"];
  obj["longitude"] = doc["longitude"];
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

  file = SD.open(_file_abastecimentos, FILE_WRITE);
  if (serializeJson(root, file) == 0)
  {
    Serial.println(F("Falha ao escrever no arquivo"));
    return;
  }
  file.close();
}

float MicroSdServices::buscarLimiteAbastecimento(int id_veiculo)
{
}