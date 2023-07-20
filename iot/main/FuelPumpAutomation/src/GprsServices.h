/*
 GprsServices.h - Biblioteca para trabalhar com o GPRS (SIM800L).
 Criado pelo Luis Gustavo, 24 de Fevereiro, 2023.
 Atualizada, 03 de Abril, 2023.
*/

#ifndef GPRSSERVICES_H
#define GPRSSERVICES_H

#define TINY_GSM_MODEM_SIM800

#include <Arduino.h>

#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

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
  bool conectarNaRede(void);

  /** Faz uma requisição HTTP
   * @param - void
   * @return - void
   */
  void requisicaoHttp(String token, String abastecimentosJson);

  /** Desconecta o módulo da rede GPRS
   * @param - void
   * @return - void
   */
  bool desconectarGprs(void);

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

  String getToken(void);

  void setToken(String token);

private:
  const char _apn[];
  const char _gprsUser[];
  const char _gprsPass[];
  const char _server[];
  char _resource[];
  char _token[];
  String _body;
};

#endif