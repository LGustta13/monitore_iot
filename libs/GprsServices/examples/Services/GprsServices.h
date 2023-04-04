/*
 GprsServices.h - Biblioteca para trabalhar com o GPRS (SIM800L).
 Criado pelo Luis Gustavo, 24 de Fevereiro, 2023.
 Atualizada, 03 de Abril, 2023.
*/

#ifndef GPRSSERVICES_H
#define GPRSSERVICES_H

#include <Arduino.h>
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

#define TINY_GSM_MODEM_SIM800
#define SerialMon Serial
#define SerialAT Serial2
#define TINY_GSM_RX_BUFFER 1024
#define GSM_BAUD 9600
#define USE_SSL
#define TINY_GSM_USE_GPRS true
// #define DUMP_AT_COMMANDS

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

#ifdef USE_SSL &&defined TINY_GSM_MODEM_HAS_SSL
TinyGsmClientSecure client(modem);
const int port = 443;
#else
TinyGsmClient client(modem);
const int port = 80;
#endif

HttpClient http(client, server, port);

class GprsServices
{

public:
  /** Construtor que chama o setup
   * @param - void
   * @return - void
   */
  GprsServices(void);

  /** Inicializa a serial do monitor e do módulo
   * @param - int bomba_gatilho_0,
   * @return - void
   */
  void setupGprs(void);

  /** Inicializa e cria conexão IP
   * @param - void
   * @return - void
   */
  void inicializarGprs(void);

  /** Conecta o módulo na rede
   * @param - void
   * @return - void
   */
  void conectarNaRede(void);

  /** Faz uma requisição HTTP
   * @param - void
   * @return - void
   */
  void requsicaoHttp(void);

  /** Desconecta o módulo da rede GPRS
   * @param - void
   * @return - void
   */
  void desconectarGprs(void);

  /** Registra e executa o setup dos pinos
   * @param - int bomba_gatilho_0,
   * @return - void
   */
  void updateDadosSerial(void);

  /** Pega o body da requisição
   * @param - int bomba_gatilho_0,
   * @return - void
   */
  void getBody(void);

private:
  const char apn[] = "simplepm.algar.br";
  const char gprsUser[] = "";
  const char gprsPass[] = "";
  const char server[] = "darwin-gps.com.br";
  char resource[] = "/api/motoristas/getRFIDMotoristas.php?chave=fc56dbc6d4652b315b86b71c8d688c1ccdea9c5f1fd07763d2659fde2e2fc49a";
  String body;
}

#endif