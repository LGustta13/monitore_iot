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
#include <WiFi.h>

const char apn[] = "simplepm.algar.br";
const char gprsUser[] = "";
const char gprsPass[] = "";
const char server[] = "darwin-gps.com.br";
const char chave[] = "";
const int port = 80;
const char resource[] = "/api/abastecimentos/getAbastecimentosInternoBomba.php?chave=a73b320dc0d3a57c03f897eb28ca91e623c5ee635db59476ba3178c90b94019f";

bool useWifi = true;
const char wifiUser[] = "Los tres mosqueteros-2.4G";
const char wifiPass[] = "corona2030";

TinyGsm modem(Serial2);
TinyGsmClient client(modem);

void setup()
{
  // Inicialização do modem
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(2000);

  if (!useWifi)
  {
    // Conexão à rede GSM/GPRS
    modem.restart();
    String modemInfo = modem.getModemInfo();
    Serial.print("Modem: ");
    Serial.println(modemInfo);

    if (!modem.waitForNetwork())
    {
      Serial.println("Sem rede disponível");
      while (true)
        ;
    }

    if (modem.isNetworkConnected())
    {
      Serial.println("Conectado à rede");
    }

    // Conexão GPRS
    if (!modem.gprsConnect(apn, gprsUser, gprsPass))
    {
      Serial.println("Falha na conexão GPRS");
      while (true)
        ;
    }

    if (modem.isGprsConnected())
    {
      Serial.println("Conectado ao GPRS");
    }
  }

  else if (useWifi)
  {
    WiFi.begin(wifiUser, wifiPass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Conectando ao WiFi...");
    }

    Serial.println("Conexão WiFi estabelecida!");
    }
}

void loop()
{

  if(!useWifi){
    // Configuração da requisição HTTP GET

    HttpClient http(client, server);

    http.beginRequest();
    http.get(resource); // Substitua pelo seu endpoint
    http.endRequest();

    // Leitura da resposta
    int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    Serial.print("Status da resposta: ");
    Serial.println(statusCode);
    Serial.print("Resposta: ");
    Serial.println(response);

    delay(10000); // Aguarda 5 segundos antes de fazer a próxima requisição
  }

  else if (useWifi){
    Serial.println("Realizando uma requisição...");
    if (WiFi.status() == WL_CONNECTED) {
    HttpClient http(client, server);

    // Configuração da requisição HTTP GET
    http.get(resource);  // Substitua pelo caminho do recurso desejado

    // Envio da requisição
    int statusCode = http.responseStatusCode();
    String responseBody = http.responseBody();

    Serial.print("Status da resposta: ");
    Serial.println(statusCode);
    Serial.print("Resposta: ");
    Serial.println(responseBody);
    }

    delay(5000);  // Aguarda 5 segundos antes de fazer a próxima requisição
  }
  
}