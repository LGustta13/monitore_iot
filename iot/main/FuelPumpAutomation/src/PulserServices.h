/*
  AtuadorServices.h - Biblioteca para enviar sinais de comando
  aos atuadores do sistema.
  Criado pelo Luis Gustavo, 29 de Novembro, 2022.
  Atualização, 02 de Abril, 2023.
*/

#ifndef PULSERSERVICES_H
#define PULSERSERVICES_H

#include <Arduino.h>

class PulserServices
{
public:
  /**
   * @param -
   * @return - void
   */
  PulserServices();

  PulserServices(float limite_de_abastecimento, float fator_de_calibracao, int limiar_de_tensao, int pino_sensor_0, int pino_sensor_1);

  void setupPulser(void);

  void setLimiteAbastecimento(float limite_de_abastecimento);

  float getLimiteAbastecimento(void);

  void setCalibracao(float fator_de_calibracao);

  float getCalibracao(void);

  void setLimiarTensao(int limiar_de_tensao);

  int getLimiarTensao(void);

  void setExtrato(float extrato);

  float getExtrato(void);

  bool handleContagemPulsos(void);

  int receberPulsosDoGatilhoZero(void);

  int receberPulsosDoGatilhoUm(void);

private:
  float _limite_de_abastecimento;
  float _fator_de_calibracao;
  int _limiar_de_tensao;
  float _extrato;
  int _pino_sensor_0;
  int _pino_sensor_1;
};

#endif
