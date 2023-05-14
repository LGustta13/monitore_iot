/*
  Services.ino - exemplo de uso das funções
  Criado pelo Luis Gustavo, 21 de Dezembro, 2022.
*/

/*
  Orientações:
  ESP32 PINOUT(13, -1, 4, -1, 32, 33, 27, 26)
  ARDUINO PINOUT(4, 5, 2, 3, 6, 7, 8, 9)
  DREXIA PINOUT(32, 12, 16, 34, 33, 19, 18, 17)
*/

#include "DrexiaServices.h"
#include <AtuadorServices.h>

// Configura os atuadores
AtuadorServices esp32(13, -1, 4, -1, 32, 33, 27, 26);

// Configura o Drexia
DrexiaServices drexia(25, esp32);

void setup()
{
}

void loop()
{
}

byte _comando_frentista = 0x00;
byte _comando_veiculo = 0x01;
byte _comando_motorista = 0x02;

/** Funcao que verifica os usuários identificados no barramento
 * @param - byte comando_barramento, byte vindo do barramento
 * @return - void
 */
void emitirAudio(byte comando_barramento);

/** Funcao que adota um tempo limite até que a próxima identificaçãp
 * ocorra
 * @param - bool motorista_ou_veiculo, condição para ser motorista ou veículo
 * @return - void
 */
void intervaloEsperaParaIdentificacao(bool motorista_ou_veiculo);

/** Verifica e armazena o ID do cartão lido pelo Dréxia
 * @param - byte comando_barramento, byte vindo do barramento
 * @return - void
 */
void verificarUsuarioDoCartao(byte comando_barramento);

void DrexiaServices::emitirAudio(byte comando_barramento)
{
  if (comando_barramento == _comando_frentista)
  {
    // Manda um áudio
    Serial.println("Esperando identificação do FRENTISTA: ");
  }
  else if (comando_barramento == _comando_veiculo)
  {
    // Manda um áudio
    Serial.println("Esperando identificação do VEÍCULO: ");
  }
  else if (comando_barramento == _comando_motorista)
  {
    // Manda um áudio
    Serial.println("Esperando identificação do MOTORISTA: ");
  }
}

void DrexiaServices::intervaloEsperaParaIdentificacao(bool motorista_ou_veiculo)
{
  unsigned long contador = 0;
  unsigned long tempo_espera_limite = 10000;
  unsigned short int id_nao_identificado = 0;
  unsigned short int id_identificacao_osciosa = 1;

  while (_id_do_cartao == id_nao_identificado)
  {
    getIdDoCartao64bits();
    if (motorista_ou_veiculo)
    {
      contador++;
      if (contador >= tempo_espera_limite)
      {
        _id_do_cartao = id_identificacao_osciosa;
        _esp32.atuarNoBuzzer();
      }
    }
  }
}

void DrexiaServices::verificarUsuarioDoCartao(byte comando_barramento)
{
  bool motorista_ou_veiculo = false;

  if (comando_barramento != _comando_frentista)
  {
    motorista_ou_veiculo = true;
  }

  emitirAudio(comando_barramento);
  intervaloEsperaParaIdentificacao(motorista_ou_veiculo);

  _esp32.atuarNoBuzzer();
}
