#include <ArduinoJson.h>
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

const char *filename = "/Abastecimentos.txt";
const int chipSelect = 5;
int quantidadeDeAbastecimentos = 5;
int bytesAbastecimentos = 369;
Abastecimento abastecimento;
Data data;

// Deve criar um abastecimento para realizar testes
void criarAbastecimentoFake(Abastecimento &abastecimento)
{

  abastecimento.id = 1;
  strlcpy(abastecimento.nome_bomba, "BOMBA_1", sizeof(abastecimento.nome_bomba));
  abastecimento.latitude = 199.99;
  abastecimento.longitude = 199.99;
  abastecimento.volume_abastecido = 500.00;

  strlcpy(abastecimento.data_inicial.dia, "2023-01-01 10:00:00", sizeof(abastecimento.data_inicial.dia));
  abastecimento.data_inicial.timezone_tipo = 3;
  strlcpy(abastecimento.data_inicial.timezone, "UTC", sizeof(abastecimento.data_inicial.timezone));

  strlcpy(abastecimento.data_final.dia, "2023-01-01 10:10:00", sizeof(abastecimento.data_final.dia));
  abastecimento.data_final.timezone_tipo = 3;
  strlcpy(abastecimento.data_final.timezone, "UTC", sizeof(abastecimento.data_final.timezone));

  abastecimento.id_frentista = 16651608;
  abastecimento.id_veiculo = 16651608;
  abastecimento.id_motorista = 16651608;

}

// Deve acessar o cartão SD por algum abastecimento, se não cria-se um de teste por padrão
void criarAbastecimentoSD(const char *filename, Abastecimento &abastecimento)
{
  // Acessa arquivo
  File file = SD.open(filename);
  StaticJsonDocument<1056> root;

  // Transforma a string no cartão SD em um objeto JSON
  DeserializationError error = deserializeJson(root, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  abastecimento.id = root["tank_id"] | 1;
  strlcpy(abastecimento.nome_bomba, root["tank_name"] | "BOMBA_1", sizeof(abastecimento.nome_bomba));
  abastecimento.latitude = root["initial_volume"] | 199.99;
  abastecimento.longitude = root["final_volume"] | 199.99;
  abastecimento.volume_abastecido = root["drain_value"] | 500.00;

  JsonObject utc_initial_date_time = root["utc_initial_date_time"];
  strlcpy(abastecimento.data_inicial.dia, utc_initial_date_time["date"] | "2023-01-01 10:00:00", sizeof(abastecimento.data_inicial.dia));
  abastecimento.data_inicial.timezone_tipo = utc_initial_date_time["timezone_type"] | 3;
  strlcpy(abastecimento.data_inicial.timezone, utc_initial_date_time["timezone"] | "UTC", sizeof(abastecimento.data_inicial.timezone));

  JsonObject utc_final_date_time = root["utc_final_date_time"];
  strlcpy(abastecimento.data_final.dia, utc_final_date_time["date"] | "2023-01-01 10:10:00", sizeof(abastecimento.data_final.dia));
  abastecimento.data_final.timezone_tipo = utc_final_date_time["timezone_type"] | 3;
  strlcpy(abastecimento.data_final.timezone, utc_final_date_time["timezone"] | "UTC", sizeof(abastecimento.data_final.timezone));

  abastecimento.id_frentista = root["ident_pessoa_apoio"] | 16651608;
  abastecimento.id_veiculo = root["ident_veiculo"] | 16651608;
  abastecimento.id_motorista = root["ident_motorista"] | 16651608;

  file.close();
}

// Salva os abastecimentos no cartão de memória, no formato de array de objetos
void saveAbastecimentosArray(const char *filename, Abastecimento &abastecimento)
{
  File file = SD.open(filename);

  // +2 por conta dos colchetes do array []
  StaticJsonDocument<(quantidadeDeAbastecimentos*bytesAbastecimentos)+2> root;

  DeserializationError error = deserializeJson(root, file);
  if (error)
    Serial.println(F("Nenhum abastecimento inicial no arquivo"));

  file.close();

  // Append new element
  JsonObject obj = root.createNestedObject();
  obj["tank_id"] = abastecimento.id;
  obj["tank_name"] = abastecimento.nome_bomba;
  obj["initial_volume"] = abastecimento.latitude;
  obj["final_volume"] = abastecimento.longitude;
  obj["drain_value"] = abastecimento.volume_abastecido;

  JsonObject utc_initial_date_time = obj.createNestedObject("utc_initial_date_time");
  utc_initial_date_time["date"] = abastecimento.data_inicial.dia;
  utc_initial_date_time["timezone_type"] = abastecimento.data_inicial.timezone_tipo;
  utc_initial_date_time["timezone"] = abastecimento.data_inicial.timezone;

  JsonObject utc_final_date_time = obj.createNestedObject("utc_final_date_time");
  utc_final_date_time["date"] = abastecimento.data_final.dia;
  utc_final_date_time["timezone_type"] = abastecimento.data_final.timezone_tipo;
  utc_final_date_time["timezone"] = abastecimento.data_final.timezone;

  obj["ident_pessoa_apoio"] = abastecimento.id_frentista;
  obj["ident_veiculo"] = abastecimento.id_veiculo;
  obj["ident_motorista"] = abastecimento.id_motorista;

  file = SD.open(filename, FILE_WRITE);
  if (serializeJson(root, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }
  file.close();
}

// Salvar um abastecimento no cartão de memória, sem vetorizar
void saveAbastecimento(const char *filename, const Abastecimento &abastecimento)
{

  File file = SD.open(filename, FILE_APPEND);
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }

  StaticJsonDocument<768> root;

  root["tank_id"] = abastecimento.id;
  root["tank_name"] = abastecimento.nome_bomba;
  root["initial_volume"] = abastecimento.latitude;
  root["final_volume"] = abastecimento.longitude;
  root["drain_value"] = abastecimento.volume_abastecido;

  JsonObject utc_initial_date_time = root.createNestedObject("utc_initial_date_time");
  utc_initial_date_time["date"] = abastecimento.data_inicial.dia;
  utc_initial_date_time["timezone_type"] = abastecimento.data_inicial.timezone_tipo;
  utc_initial_date_time["timezone"] = abastecimento.data_inicial.timezone;

  JsonObject utc_final_date_time = root.createNestedObject("utc_final_date_time");
  utc_final_date_time["date"] = abastecimento.data_final.dia;
  utc_final_date_time["timezone_type"] = abastecimento.data_final.timezone_tipo;
  utc_final_date_time["timezone"] = abastecimento.data_final.timezone;

  root["ident_pessoa_apoio"] = abastecimento.id_frentista;
  root["ident_veiculo"] = abastecimento.id_veiculo;
  root["ident_motorista"] = abastecimento.id_motorista;

  if (serializeJson(root, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
}

// Exibir os dados do arquivo
void printArquivo(const char *filename)
{

  File file = SD.open(filename);
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

// PAREI AQUIIIIIIIIIIIII
// hOW TO SEND A json DOCUMENT IN AN httP REQUEST
// https://arduinojson.org/v6/how-to/use-arduinojson-with-httpclient/
// tentar ler os dados do file pelo desserialize e salvar (serialize) em uma string json, para usar na requisição do módulo GSM

void saveNaVariavel(const char *filename)
{
  String data = "";

  if (SD.exists(filename)) {
    File file = SD.open(filename);

    if (!file)
    {
      Serial.println(F("Failed to read file"));

    } else {

      // Extract each characters by one by one
      while (file.available())
      {
        data = file.readString();
        file.close();
      }
      
      Serial.println("Conteúdo do arquivo");
      Serial.println(data);
    }

  } else {
    Serial.println("O arquivo não existe!");
  }
}

// Deletar o arquivo
void deleteArquivo(const char *filename)
{
  SD.remove(filename);
}

void setup()
{
  // Iniciar o monitor serial
  Serial.begin(9600);

  while (!Serial)
    continue; // Aguardando a conexão serial

  Serial.println("(1) para gerar um abastecimento");
  Serial.println("(2) para salvar o abastecimento no microSD");
  Serial.println("(3) para printar os abastecimentos");
  Serial.println("(4) para deletar os abastecimentos");

  // Inicializar o cartão SD
  while (!SD.begin(chipSelect))
  {
    Serial.println(F("Failed to initialize SD library"));
    delay(1000);
  }

  // Neste ponto o cartão inicializou com sucesso
}

void loop()
{

  // Verifica se tem algum valor disponível na serial
  while (Serial.available() == 0)
  {
  }

  int menuChoice = Serial.parseInt();

  // Verifica qual caso se encaixa o valor
  switch (menuChoice)
  {
  case 1:
    // Should load default config if run for the first time
    Serial.println(F("Generating a supply..."));
    criarAbastecimentoFake(abastecimento);
    break;

  case 2:
    // Create configuration file
    Serial.println(F("Saving supplies..."));
    saveAbastecimentosArray(filename, abastecimento);
    break;

  case 3:
    // Printar os dados do arquivo
    Serial.println(F("Printing suplies..."));
    printArquivo(filename);
    break;

  case 4:
    // Deletar o arquivo
    Serial.println(F("Deleting file with supplies..."));
    deleteArquivo(filename);

  case 5:
    // Salvar na variável
    Serial.println(F("Saving in a variable and printing..."));
    saveNaVariavel(filename);

  default:
    Serial.println();
  }
}
