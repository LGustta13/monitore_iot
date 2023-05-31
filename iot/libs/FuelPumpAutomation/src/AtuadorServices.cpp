/*
  AtuadorServices.cpp - Biblioteca para enviar sinais de comando
  aos atuadores do sistema.
  Criado pelo Luis Gustavo, 29 de Novembro, 2022.
  Atualização, 02 de Abril, 2023.
*/

#include "AtuadorServices.h"

AtuadorServices::AtuadorServices(int bomba_gatilho_0, int bomba_gatilho_1, int pino_sensor_0, int pino_sensor_1, int pino_buzzer, int pino_led_verde, int pino_led_vermelho, int pino_led_azul)
{
  _bomba_gatilho_0 = bomba_gatilho_0;
  _bomba_gatilho_1 = bomba_gatilho_1;
  _pino_sensor_0 = pino_sensor_0;
  _pino_sensor_1 = pino_sensor_1;
  _pino_buzzer = pino_buzzer;
  _pino_led_verde = pino_led_verde;
  _pino_led_vermelho = pino_led_vermelho;
  _pino_led_azul = pino_led_azul;
  _restart = 0;

  setupAtuadores();
}

void AtuadorServices::setupAtuadores(void)
{
  pinMode(_bomba_gatilho_0, OUTPUT);
  pinMode(_bomba_gatilho_1, OUTPUT);
  pinMode(_pino_buzzer, OUTPUT);
  pinMode(_pino_sensor_0, INPUT_PULLUP);
  pinMode(_pino_sensor_1, INPUT_PULLUP);
  pinMode(_pino_led_verde, OUTPUT);
  pinMode(_pino_led_vermelho, OUTPUT);
  pinMode(_pino_led_azul, OUTPUT);
}

void AtuadorServices::atuarNoReleDeBloqueioZero(bool valor)
{
  digitalWrite(_bomba_gatilho_0, valor);
}

void AtuadorServices::atuarNoReleDeBloqueioUm(bool valor)
{
  digitalWrite(_bomba_gatilho_1, valor);
}

void AtuadorServices::atuarNoBuzzer(int tempo_delay)
{
  digitalWrite(_pino_buzzer, HIGH);
  delay(tempo_delay);
  digitalWrite(_pino_buzzer, LOW);
  delay(tempo_delay);
  digitalWrite(_pino_buzzer, HIGH);
  delay(tempo_delay);
  digitalWrite(_pino_buzzer, LOW);
}

void AtuadorServices::atuarNoLedVermelho(bool valor)
{
  digitalWrite(_pino_led_vermelho, valor);
}

void AtuadorServices::atuarNoLedAzul(bool valor)
{
  digitalWrite(_pino_led_azul, valor);
}

void AtuadorServices::atuarNoLedVerde(bool valor)
{
  digitalWrite(_pino_led_verde, valor);
}

void AtuadorServices::reiniciarArduino(void)
{
  _restart();
}

void AtuadorServices::reiniciarEsp32(void)
{
  //    ESP.restart();
}