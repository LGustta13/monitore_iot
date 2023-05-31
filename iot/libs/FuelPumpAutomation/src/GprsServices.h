/*
 GprsServices.h - Biblioteca para trabalhar com o GPRS (SIM800L).
 Criado pelo Luis Gustavo, 24 de Fevereiro, 2023.
 Atualizada, 03 de Abril, 2023.
*/

#ifndef GPRSSERVICES_H
#define GPRSSERVICES_H

#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

#define TINY_GSM_MODEM_SIM800
#define SerialMon Serial
#define SerialAT Serial2
#define TINY_GSM_RX_BUFFER 10000
#define GSM_BAUD 9600
#define TINY_GSM_USE_GPRS true
#define DUMP_AT_COMMANDS

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
  void requsicaoHttp(String token, String abastecimentosJson);

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
  String getBody(void);

private:
  const char apn[] = "simplepm.algar.br";
  const char gprsUser[] = "";
  const char gprsPass[] = "";
  const char server[] = "darwin-gps.com.br";
  char resource[] = "/api/abastecimentos/getAbastecimentosInternoBomba.php?chave=4eef24c6b8248c2271f6663f44ec0de3c2535ca396a22cf60051137d71721309";
  String _body;
}

#endif