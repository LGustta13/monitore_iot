/*
 Services.ino - Biblioteca para trabalhar com o GPRS (SIM800L).
 Criado pelo Luis Gustavo, 24 de Fevereiro, 2023.
*/

/*
  Orientações:
  ESP32 PINOUT()
*/

/*
  Parâmetros de AtuadorServices:

*/

#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

TinyGsm modem(serialGsm);
TinyGsmClient client(modem);
const char apn[] = "simplepm.algar.br";
const char gprsUser[] = "";
const char gprsPass[] = "";
const char server[] = "darwin-gps.com.br";
const char chave[] = ""
const int port = 80;
char resource[] = "/api/motoristas/getRFIDMotoristas.php?chave=fc56dbc6d4652b315b86b71c8d688c1ccdea9c5f1fd07763d2659fde2e2fc49a";

bool useWifi = true;
const char wifiUser[] = "Los tres mosqueteros-2.4G";
const char wifiPass[] = "corona2030";

void setup() {
  // Inicialização do modem
  Serial2.begin(9600);
  delay(2000);
  
  if (!useWifi){
    // Conexão à rede GSM/GPRS
    modem.restart();
    String modemInfo = modem.getModemInfo();
    Serial.print("Modem: ");
    Serial.println(modemInfo);
    
    if (!modem.waitForNetwork()) {
      Serial.println("Sem rede disponível");
      while (true);
    }
    
    if (modem.isNetworkConnected()) {
      Serial.println("Conectado à rede");
    }
    
    // Conexão GPRS
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      Serial.println("Falha na conexão GPRS");
      while (true);
    }

    if (modem.isGprsConnected()) {
      Serial.println("Conectado ao GPRS");
    }
  }

  if (useWifi) {
    // Wifi connection parameters must be set before waiting for the network
    Serial.print(F("Setting SSID/password..."));
    if (!modem.networkConnect(wifiSSID, wifiPass)) {
      Serial.println(" fail");
      delay(5000);
      return;
    }
    Serial.println(" success");
  }

}

void loop() {

  // Configuração da requisição HTTP GET
  HttpClient http(client, server, port);
  http.beginRequest();
  http.get(resource);  // Substitua pelo seu endpoint
  http.endRequest();

  // Leitura da resposta
  int statusCode = http.responseStatusCode();
  String response = http.responseBody();

  Serial.print("Status da resposta: ");
  Serial.println(statusCode);
  Serial.print("Resposta: ");
  Serial.println(response);

  delay(10000);  // Aguarda 5 segundos antes de fazer a próxima requisição
}