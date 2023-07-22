/*
  AtuadorServices.cpp - Biblioteca para receber os pulsos.
  Criado pelo Luis Gustavo, 29 de Novembro, 2022.
  Atualização, 02 de Abril, 2023.
*/

#include "PulserServices.h"

PulserServices::PulserServices()
{
  _limite_de_abastecimento = 0;
  _fator_de_calibracao = 1;
  _limiar_de_tensao = 400;
  setupPulser();
}

PulserServices::PulserServices(float limite_de_abastecimento, float fator_de_calibracao, int limiar_de_tensao, int pino_sensor_0, int pino_sensor_1)
{
  _limite_de_abastecimento = limite_de_abastecimento;
  _fator_de_calibracao = fator_de_calibracao;
  _limiar_de_tensao = limiar_de_tensao;
  _pino_sensor_0 = pino_sensor_0;
  _pino_sensor_1 = pino_sensor_1;
  setupPulser();
}

void PulserServices::setupPulser(void)
{
  pinMode(_pino_sensor_0, INPUT_PULLDOWN);
  pinMode(_pino_sensor_1, INPUT_PULLDOWN);
}

void PulserServices::setLimiteAbastecimento(float limite_de_abastecimento)
{
  _limite_de_abastecimento = limite_de_abastecimento;
}

float PulserServices::getLimiteAbastecimento(void)
{
  return _limite_de_abastecimento;
}

void PulserServices::setCalibracao(float fator_de_calibracao)
{
  _fator_de_calibracao = fator_de_calibracao;
}

float PulserServices::getCalibracao(void)
{
  return _fator_de_calibracao;
}

void PulserServices::setLimiarTensao(int limiar_de_tensao)
{
  _limiar_de_tensao = limiar_de_tensao;
}

int PulserServices::getLimiarTensao(void)
{
  return _limiar_de_tensao;
}

void PulserServices::setExtrato(float extrato)
{
  _extrato = extrato;
}

float PulserServices::getExtrato(void)
{
  return _extrato;
}

bool PulserServices::handleContagemPulsos(void)
{
  bool finalizado = false;
  bool flag = false;
  float extrato = 0;
  int sensorValue0 = 0;
  int sensorValue1 = 0;
  int contagem = 0;

  if (_limite_de_abastecimento == 0)
  {
    return finalizado;
  }

  while (extrato < _limite_de_abastecimento)
  {
    sensorValue0 = receberPulsosDoGatilhoZero();
    // sensorValue1 = receberPulsosDoGatilhoUm();
    // if ((sensorValue0 > _limiar_de_tensao or sensorValue1 > _limiar_de_tensao) and flag == false)
    if ((sensorValue0 > _limiar_de_tensao) and flag == false)
    {
      contagem++;
      extrato = (float)contagem * _fator_de_calibracao;
      Serial.println(extrato);
      flag = true;
    }

    // if ((sensorValue0 == 0 or sensorValue1 == 0) and flag == true)
    if ((sensorValue0 == 0) and flag == true)
    {
      flag = false;
    }
  }
  finalizado = true;
  setExtrato(extrato);

  return finalizado;
}

int PulserServices::receberPulsosDoGatilhoZero(void)
{
  int value = analogRead(_pino_sensor_0);
  return value;
}

int PulserServices::receberPulsosDoGatilhoUm(void)
{
  int value = analogRead(_pino_sensor_1);
  return value;
}