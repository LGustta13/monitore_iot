#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

struct Abastecimento{
  int id;
  char nome_bomba[25];
  float latitude;
  float longitude;
  float volume_abastecido;
  char data_inicial[20];
  char data_final[20];
  int id_frentista;
  int id_motorista;
  int id_veiculo;
};

const char *filename = "/Abastecimentos.txt";
Abastecimento abastecimento; 

void loadAbastecimento(const char *filename, Abastecimento &abastecimento){
  File file = SD.open(filename);
  StaticJsonDocument<768> root;

  DeserializationError error = deserializeJson(root, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));
    
  abastecimento.id = root["tank_id"];
  strlcpy(abastecimento.nome_bomba, root["tank_name"], sizeof(abastecimento.nome_bomba));
  abastecimento.latitude = root["initial_volume"];
  abastecimento.longitude = root["final_volume"];
  abastecimento.volume_abastecido = root["drain_value"];
  strlcpy(abastecimento.data_inicial, root["utc_initial_date_time"], sizeof(abastecimento.data_inicial));
  strlcpy(abastecimento.data_final, root["utc_final_date_time"], sizeof(abastecimento.data_final));
  abastecimento.id_frentista = root["ident_pessoa_apoio"];
  abastecimento.id_veiculo = root["ident_veiculo"];
  abastecimento.id_motorista = root["ident_motorista"];

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
  root["utc_initial_date_time"] = abastecimento.data_inicial;
  root["utc_final_date_time"] = abastecimento.data_final;
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

  
