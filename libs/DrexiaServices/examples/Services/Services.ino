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
  Serial.begin(9600);

  drexia.getCodigoDoCartao32bits();
  drexia.getIdDoCartao64bits();
  drexia.emitirAudio(0x01);
  drexia.intervaloEsperaParaIdentificacao(true);
  drexia.verificarUsuarioDoCartao(0x01);
}

void loop()
{
}
