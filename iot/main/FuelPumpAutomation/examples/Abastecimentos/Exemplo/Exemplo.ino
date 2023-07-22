/*
  Services.ino - exemplo de uso das funções
  Criado pelo Luis Gustavo, 02 de Abril, 2023.
*/

/*
  Orientações:
*/

/*
  Parâmetros de AbastecimentoServices:
  * se necessário!
*/

#include "Abastecimento.h"

// utilizado de forma global
Abastecimento abastecimento;

// para ser criado durante a execução do código, new Object()
Identificacao *id;

int incomingByte = 0;

void teste(void){
  id = new Identificacao();
  id->setIdFrentista(123456);
  id->setIdVeiculo(654321);
  id->setIdMotorista(135790);
  Serial.println("OK");
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available() == 0)
  {
  }

  incomingByte = Serial.parseInt();

  switch (incomingByte) {
    case 11:
    abastecimento.setIdTanque(150);
    abastecimento.setNomeTanque("CAJAMAR");
    abastecimento.setVolumeSaida(750.40);
    
    // Acesso ao RTC
    abastecimento.setDataInicial("2023-07-08T20:23:23.999Z");
    abastecimento.setDataFinal("2023-07-08T22:23:23.999Z");
    abastecimento.setUsuarios(id->getIdFrentista(), id->getIdVeiculo(), id->getIdMotorista());
    abastecimento.setLocalizacaoBomba(30.1234, 21.4432);
    Serial.println("OK");
    break;

    case 22:
    Serial.println(abastecimento.getDataInicial().getData());
    Serial.println(abastecimento.getDataFinal().getTimezone());
    Serial.println(abastecimento.getIdTanque());
    Serial.println(abastecimento.getNomeTanque());
    Serial.println(abastecimento.getUsuarios().getIdFrentista());
    Serial.println(abastecimento.getLocalizacaoBomba().getLatitude());
    Serial.println("OK");
    break;

    case 33:
    id = new Identificacao();
    id->setIdFrentista(123456);
    id->setIdVeiculo(654321);
    id->setIdMotorista(135790);
    Serial.println("OK");
    break;

    case 44:
    id = new Identificacao();
    id->setIdFrentista(99999);
    id->setIdVeiculo(99999);
    id->setIdMotorista(99999);
    Serial.println("OK");
    break;

    // Nunca acessar o id após a deleção! Criar outra instância depois
    case 55:
    delete id;
    id = NULL;
    Serial.println("OK");
    break;

    case 66:
    Serial.println(id->getIdFrentista());
    Serial.println("OK");
    break;

    // Utilizando dentro de função
    case 77:
    teste();
    Serial.println("OK");
    break;

    default:
    break;
  }
}