/*
  AtuadorServices.h - Biblioteca para enviar sinais de comando
  aos atuadores do sistema.
  Criado pelo Luis Gustavo, 29 de Novembro, 2022.
*/

#ifndef ATUADORSERVICES_H
#define ATUADORSERVICES_H

#include <Arduino.h>

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
  AtuadorServices(int bomba_gatilho_0, int bomba_gatilho_1, int pino_sensor_0, int pino_sensor_1, int pino_buzzer, int pino_led_verde, int pino_led_vermelho, int pino_led_azul);

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
  void atuarNoBuzzer(void);

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

  /** Funcao que pega os pulsos do gatilho ZERO
   *  @param - int pino: pino reservado para conectar o sinal de controle
   *  @return - int value: valor entre 0 e 255
   */
  int receberPulsosDoGatilhoZero(void);

  /** Funcao que pega os pulsos do gatilho UM
   *  @param - int pino: pino reservado para conectar o sinal de controle
   *  @return - int value: valor entre 0 e 255
   */
  int receberPulsosDoGatilhoUm(void);

  /** Função que reinicia o Esp32
   * @param - void
   * @return - void
   */
  void reiniciarEsp32(void);

  /** Função que incrementa a contagem dos pulsos
   * @param - void
   * @return - void
   */
  void contagemDosPulsosSensor0(void);

  /** Função que incrementa a contagem dos pulsos
   * @param - void
   * @return - void
   */
  void contagemDosPulsosSensor1(void);

  /** Subrotina chamada assim que a interrupção é identificada pelo sensor 0
   * @param - void
   * @return - void
   */
  static void subrotina_do_sensor_0(void);

  /** Subrotina chamada assim que a interrupção é identificada pelo sensor 1
   * @param - void
   * @return - void
   */
  static void subrotina_do_sensor_1(void);

  /** Função que realiza o processo de bastecimento
   *  As portas de entrada são monitoradas por Threads
   *  @param - float volume_a_ser_abastecido, volume limite
   *  @return - float volume_dos_pulsos, volume calculado
   */
  float getPulsosDaBombaPorParalelismo(float volume_a_ser_abastecido);

  /** Função que realiza o processo de abastecimento
   *  As portas de entrada são monitoradas por Interrupção
   * @param - float volume_a_ser_abastecido, volume limite
   * @return - float volume_dos_pulsos, volume calculado
   */
  float getPulsosDaBombaPorInterrupcao(float volume_a_ser_abastecido);

  /** Versão 2*/
  float getPulsosDaBombaPorInterrupcao_v2(float volume_a_ser_abastecido);

  /** Versão 3*/
  float getPulsosDaBombaPorInterrupcao_v3(float volume_a_ser_abastecido);

  /** Função que inicializa o processo de abastecimento liberando os relés
   * @param - float volume_a_ser_abastecido, volume limite
   * @return - float volume_dos_pulsos, volume calculado
   */
  float realizarAbastecimento(float volume_a_ser_abastecido);

  /** Função que reinicia o Arduino
   * @param - void
   * @return - void
   */
  void reiniciarArduino(void);

private:
  int _bomba_gatilho_0;
  int _bomba_gatilho_1;
  int _pino_sensor_0;
  int _pino_sensor_1;
  int _pino_buzzer;
  int _pino_led_verde;
  int _pino_led_vermelho;
  int _pino_led_azul;

  static AtuadorServices *_instance0;
  static AtuadorServices *_instance1;
  volatile unsigned long _contador_pulsos_sensor_0;
  volatile unsigned long _contador_pulsos_sensor_1;
  unsigned long _tempo_debounce;
  unsigned long _fator_calibracao;

  void (*_restart)(void);
};

#endif
