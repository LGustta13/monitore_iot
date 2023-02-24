/*
  Services.ino - Biblioteca para manipulação do protocolo MQTT.
  Criado pelo Luis Gustavo, 02 de Janeiro, 2023.
*/

/*
  Orientações para os testes:
  1. Criar um tópico em uma máquina remota
  2. Compartilhar o ponto de acesso com o ESP32
*/

/*
  Parâmetros de MqttServices:
  1. topico_de_subscricao   \
  2. topico_de_publicacao   | TÓPICOS
  3. id_da_comunicacao      /
  4. ssid                   \ PONTO DE ACESSO
  5. senha                  /
  6. broker_mqtt            \ BROKER
  7. broker_porta           /
  8. esp32                  
  9. drexia
  10.gps
*/

#include "MqttServices.h"

Serial.begin(9600);

AtuadorServices esp32(32, 13, 16, 34, 33, 19, 18, 17);
DrexiaServices drexia(25, esp32);
GpsServices gps;
MqttServices mqtt("topico/toESP32", "topico/fromESP32", "devkitESP32_Gustta", "technolog32", "12345678", "test.mosquitto.org", 1883, esp32, drexia, gps);

void setup()
{
  // mqtt.reconexaoMqtt();
  // mqtt.reconexaoWifi();
  // mqtt.inicializarMqtt();
  // mqtt.verificarConexoesWifiMqtt();
  // mqtt.eventoDeRequisicaoMqtt();
  // mqtt.enviarDadosDaBomba();
  // mqtt.enviarDadosDoGps();
  // mqtt.enviarDadosDoDrexia();
}

void loop()
{
}
