/*
  Services.ino - exemplo de uso das funções de identificação pelo dréxia
  Criado pelo Luis Gustavo, 21 de Dezembro, 2022.
*/

/*
  Orientações:
  DREXIA PINOUT(25)
*/

#include "DrexiaServices.h"
#include "Identificacao.h"


// Configura o Drexia
DrexiaServices drexia(25);
Identificacao id;

int incomingByte = 0;

void setup()
{
  Serial.begin(9600);
  drexia.getIdDoCartao64bits();
  Serial.println("OK");
}

void loop()
{
  
  while (Serial.available() == 0)
  {
  }

  incomingByte = Serial.parseInt();

  switch (incomingByte) {
    case 111:
    Serial.println(drexia.getIdDoCartao());
    break;

    case 222:
    id.setIdFrentista(drexia.getIdDoCartao());
    break;

    case 333:
    drexia.setIdDoCartao(0);
    break;

    case 444:
    Serial.println(id.getIdFrentista());
    break;

    default:

    break;
  }
}
