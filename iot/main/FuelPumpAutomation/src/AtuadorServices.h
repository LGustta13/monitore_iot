/*
  AtuadorServices.h - Biblioteca para enviar sinais de comando
  aos atuadores do sistema.
  Criado pelo Luis Gustavo, 29 de Novembro, 2022.
  Atualização, 02 de Abril, 2023.
*/

#ifndef ATUADORSERVICES_H
#define ATUADORSERVICES_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class AtuadorServices
{
public:
  /** Registra e executa o setup dos pinos
   * @param - int bomba_gatilho_0,
   *          int bomba_gatilho_1,
   *          int pino_sensor_0,
   *          int pino_sensor_1,
   *          int pino_buzzer,
   *          int pino_led_verde,
   *          int pino_led_vermelho,
   *          int pino_led_azul
   * @return - void
   */
  AtuadorServices(int bomba_gatilho_0, int bomba_gatilho_1, int pino_buzzer, int pino_led_verde, int pino_led_vermelho, int pino_led_azul);

  /** Funcao que realiza o setup dos pinos
   * @param - void
   * @return - void
   */
  void setupAtuadores(void);

  /** Funcao chamada quando necessário atuar no relé de bloqueio ZERO
   * @param - int pino: pino reservado para conectar o sinal de controle
   *          bool valor: nível lógico de atuação, sendo HIGH ou LOW
   * @return - void
   */
  void atuarNoReleDeBloqueioZero(bool valor);

  /** Funcao chamada quando necessário atuar no relé de bloqueio UM
   * @param - int pino: pino reservado para conectar o sinal de controle
   *          bool valor: nível lógico de atuação, sendo HIGH ou LOW
   * @return - void
   */
  void atuarNoReleDeBloqueioUm(bool valor);

  /** Funcao chamada quando necessário atuar no buzzer
   * @param - int pino: pino reservado para conectar o sinal de controle
   * @return - void
   */
  void atuarNoBuzzer(int tempo_delay);

  /** Funcao chamada quando necessário atuar no LED VERMELHO
   * @param - int pino: pino reservado para conectar o sinal de controle
   *          bool valor: nível lógico de atuação, sendo HIGH ou LOW
   * @return - void
   */
  void atuarNoLedVermelho(bool valor);

  /** Funcao chamada quando necessário atuar no LED AZUL
   * @param - int pino: pino reservado para conectar o sinal de controle
   *          bool valor: nível lógico de atuação, sendo HIGH ou LOW
   * @return - void
   */
  void atuarNoLedAzul(bool valor);

  /** Funcao chamada quando necessário atuar no LED VERDE
   * @param - int pino: pino reservado para conectar o sinal de controle
   *          bool valor: nível lógico de atuação, sendo HIGH ou LOW
   * @return - void
   */
  void atuarNoLedVerde(bool valor);

  void atuarNoDisplay(String mensagem_linha1, String mensagem_linha2);

  /** Função que reinicia o Esp32
   * @param - void
   * @return - void
   */
  void reiniciarEsp32(void);

private:
  int _bomba_gatilho_0;
  int _bomba_gatilho_1;
  int _pino_buzzer;
  int _pino_led_verde;
  int _pino_led_vermelho;
  int _pino_led_azul;

  LiquidCrystal_I2C _lcd;
};

#endif
