#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

struct Data{
  char dia[20];
  int timezone_tipo;
  char timezone[3];
};

struct Abastecimento{
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
Abastecimento abastecimento; 
Data data;

void loadAbastecimento(const char *filename, Abastecimento &abastecimento){
  File file = SD.open(filename);
  StaticJsonDocument<1024> root;

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

void saveAbastecimento(const char *filename, const Abastecimento &abastecimento){
  SD.remove(filename);

  File file = SD.open(filename, FILE_APPEND);
  if (!file) {
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

  if (serializeJson(root, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
}

void printFile(const char *filename) {
  
  File file = SD.open(filename);
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  file.close();
}

void setup() {
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Initialize SD library
  while (!SD.begin(5)) {
    Serial.println(F("Failed to initialize SD library"));
    delay(1000);
  }

  // Should load default config if run for the first time
  Serial.println(F("Loading configuration..."));
  loadAbastecimento(filename, abastecimento);

  // Create configuration file
  Serial.println(F("Saving configuration..."));
  saveAbastecimento(filename, abastecimento);

  // Dump config file
  Serial.println(F("Print config file..."));
  printFile(filename);
}

void loop(){

}

  
