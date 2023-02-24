/*
  Services.ino - exemplo de uso das funções
  Criado pelo Luis Gustavo, 21 de Dezembro, 2022.
*/

#include "DrexiaServices.h"
#include <AtuadorServices.h>

// Configura os atuadores
AtuadorServices esp32(32, 12, 16, 34, 33, 19, 18, 17);

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
