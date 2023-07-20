#include "Abastecimento.h"
// #include "RtcServices.h"
// #include "GpsServices.h"
// #include "PulserServices.h"
#include "AtuadorServices.h"

// utilizado de forma global
AtuadorServices esp32(14, -1, 13, 33, 27, 26);
Abastecimento abastecimento;
RtcServices rtc;
GpsServices gps;
PulserServices pulser(50, 0.05, 400, 4, -1);

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
    case 10:
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

    // case 11:
    // Serial.println(abastecimento.getDataInicial().getData());
    // Serial.println(abastecimento.getDataFinal().getTimezone());
    // Serial.println(abastecimento.getIdTanque());
    // Serial.println(abastecimento.getNomeTanque());
    // Serial.println(abastecimento.getUsuarios().getIdFrentista());
    // Serial.println(abastecimento.getLocalizacaoBomba().getLatitude());
    // Serial.println("OK");
    // break;

    // case 12:
    // id = new Identificacao();
    // id->setIdFrentista(123456);
    // id->setIdVeiculo(654321);
    // id->setIdMotorista(135790);
    // Serial.println("OK");
    // break;

    // case 13:
    // id = new Identificacao();
    // id->setIdFrentista(99999);
    // id->setIdVeiculo(99999);
    // id->setIdMotorista(99999);
    // Serial.println("OK");
    // break;

    // // Nunca acessar o id após a deleção! Criar outra instância depois
    // case 14:
    // delete id;
    // id = NULL;
    // Serial.println("OK");
    // break;

    // case 15:
    // Serial.println(id->getIdFrentista());
    // Serial.println("OK");
    // break;

    // // Utilizando dentro de função
    // case 16:
    // teste();
    // Serial.println("OK");
    // break;

    // case 17:
    // // rtc.handleDataHorarioAbastecimento();
    // // Serial.println(rtc.getData());
    // // Serial.println(rtc.getHorario());
    // // Serial.println("OK");
    // break;

    // case 18:
    // // gps.handleLatitudeLongitude();
    // // Serial.println(gps.getLocalizacao().getLatitude());
    // // Serial.println(gps.getLocalizacao().getLongitude());
    // // Serial.println("OK");
    // break;

    // case 19:
    // esp32.atuarNoReleDeBloqueioZero(HIGH);
    // delay(1000);
    // esp32.atuarNoReleDeBloqueioZero(LOW);
    // break;

    // case 20:
    // esp32.atuarNoBuzzer(500);
    // break;

    // case 21:
    // esp32.atuarNoLedVerde(HIGH);
    // delay(1000);
    // esp32.atuarNoLedVerde(LOW);
    // break;

    // case 22:
    // esp32.atuarNoLedAzul(HIGH);
    // delay(1000);
    // esp32.atuarNoLedAzul(LOW);
    // break;

    // case 23:
    // esp32.reiniciarEsp32();
    // break;

    // case 24:

    // esp32.atuarNoReleDeBloqueioZero(HIGH);
    // pulser.handleContagemPulsos();
    
    // // while(count < 100){
    // //   sensorValue = esp32.receberPulsosDoGatilhoZero();
    // //   if (sensorValue > 400 and flag == false) {
    // //     count++;
    // //     Serial.println(count);
    // //     flag = true;
    // //   }

    // //   if (sensorValue == 0 and flag == true){
    // //     flag = false;
    // //   }
    // // }
    // // count = 0;
    // esp32.atuarNoReleDeBloqueioZero(LOW);
    // break;

    // // LCD
    // case 25:
    // esp32.atuarNoDisplay("Frentista","");
    // break;

    // case 26:
    // esp32.atuarNoDisplay("Veiculo","");
    // break;

    // case 27:
    // esp32.atuarNoDisplay("Motorista","");
    // break;

    // case 28:
    // esp32.atuarNoDisplay("Identificado!","3800284");
    // break;

    // case 29:
    // esp32.atuarNoDisplay("Identificado!","4105688");
    // break;

    // case 30:
    // esp32.atuarNoDisplay("Identificado!","3395371");
    // break;

    default:
    break;
  }
}