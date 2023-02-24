/*
  MqttServices.h - Biblioteca para manipulação do protocolo MQTT.
  Criado pelo Luis Gustavo, 02 de Janeiro, 2023.
*/

#ifndef MQTTSERVICES_H
#define MQTTSERVICES_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <AtuadorServices.h>
#include <DrexiaServices.h>
#include <GpsServices.h>

class MqttServices
{
public:
  MqttServices(const char *topico_de_subscricao, const char *topico_de_publicacao, const char *id_da_comunicacao, const char *ssid, const char *senha, const char *broker_mqtt, int broker_porta, AtuadorServices &esp32, DrexiaServices &drexia, GpsServices &gps);

  /** Funcao que realiza o setup do MQTT
   * @param - void
   * @return - void
   */
  void setupMqtt(void);

  /** Reconecta-se ao broker MQTT
   * (caso ainda não esteja conectado ou em caso de a conexão cair)
   * em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
   * @param - void
   * @return - void
   */
  void reconexaoMqtt(void);

  /** Reconecta-se ao WiFi
   *
   * @param - void
   * @return - void
   */
  void reconexaoWifi(void);

  /** Inicializa parâmetros de conexão MQTT(endereço do
   *         broker, porta e seta função de callback)
   * @param - void
   * @return - void
   */
  void inicializarMqtt(void);

  /** Verifica o estado das conexões WiFI e ao broker MQTT.
   *         Em caso de desconexão (qualquer uma das duas), a conexão
   *         é refeita.
   * @param - void
   * @return - void
   */
  void verificarConexoesWifiMqtt(void);

  /** Função de callback esta função é chamada toda vez que uma informação de
   *    um dos tópicos subescritos chega)
   * @param - void
   * @return - void
   */
  void callbackMqtt(char *topic, byte *payload, unsigned int length);

  /** Função que inicializa uma subrotina assim que algum comando de leitura é enviado pelo master do barramento
   * Master - Raspberry PI 4
   * Função que dispara a subrotina - smbus.read_bytes()
   * @param - void
   * @return - void
   */
  void eventoDeRequisicaoMqtt(void);

  /** Função que controla o objeto do dréxia e
   * envia os dados por barramento 1-wire
   * @param - void
   * @return - void
   */
  void enviarDadosDoDrexia(void);

  /** Função que controla o objeto do gps e
   * envia os dados por barramento UART
   * @param - void
   * @return - void
   */
  void enviarDadosDoGps(void);

  /** Função que controla o objeto da bomba e
   * envia os dados por GPIO's
   * @param - void
   * @return - void
   */
  void enviarDadosDaBomba(void);

  /** Função auxiliar que envia dados aos tópicos do Mmqtt
   * @param - void
   * @return - byte *ponteiro_buffer_1wire: dados de identificação,
   *         - bool identificacao_valida: usuario encontrado na identificação
   */
  void escreverNoBarramentoMqtt(byte *ponteiro_buffer_1wire, bool identificacao_valida);

  /** Subrotina para ser usada como callback em setCallback
   * @param - void
   * @return - void
   */
  static void subrotina_de_callback(char *topic, byte *payload, unsigned int length);

private:
  const char *_topico_de_subscricao;
  const char *_topico_de_publicacao;
  const char *_id_da_comunicacao;
  const char *_ssid;
  const char *_senha;
  const char *_broker_mqtt;
  int _broker_porta;

  WiFiClient _espClient;
  PubSubClient _mqtt;
  AtuadorServices _esp32;
  GpsServices _gps;
  DrexiaServices _drexia;
  DynamicJsonDocument _doc;

  static MqttServices *_instance;

  byte _comando_de_restart = 0x00;
  byte _comando_do_gps = 0x01;
  byte _comando_de_identificacao = 0x02;
  byte _comando_da_bomba = 0x03;

  char _buffer[256];
};

#endif
