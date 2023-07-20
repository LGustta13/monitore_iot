
/*
I2C device found at address 0x27 - Display LCD
I2C device found at address 0x50 - Módulo FRAM memória
I2C device found at address 0x68 - RTC DS1307
*/

#include "AtuadorServices.h"
#include "PulserServices.h"
#include "RtcServices.h"
#include "GpsServices.h"

AtuadorServices esp32(14, -1, 13, 33, 27, 26);
PulserServices pulser(2, 0.005, 400, 4, -1);
RtcServices rtc;
GpsServices gps;

int incomingByte = 0;

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop()
{

  while (Serial.available() == 0)
  {
  }

  incomingByte = Serial.parseInt();

  switch (incomingByte) {
    case 11:
    esp32.atuarNoReleDeBloqueioZero(HIGH);
    delay(1000);
    esp32.atuarNoReleDeBloqueioZero(LOW);
    break;

    case 22:
    esp32.atuarNoBuzzer(500);
    break;

    case 33:
    esp32.atuarNoLedVerde(HIGH);
    delay(1000);
    esp32.atuarNoLedVerde(LOW);
    break;

    case 44:
    esp32.atuarNoLedAzul(HIGH);
    delay(1000);
    esp32.atuarNoLedAzul(LOW);
    break;

    case 55:
    esp32.reiniciarEsp32();
    break;

    case 66:
    esp32.atuarNoReleDeBloqueioZero(HIGH);
    pulser.handleContagemPulsos();
    esp32.atuarNoDisplay("Extrato", String(pulser.getExtrato()));
    esp32.atuarNoReleDeBloqueioZero(LOW);
    break;

    // LCD
    case 77:
    esp32.atuarNoDisplay("Identifique-se!", "");
    break;

    case 25:
    esp32.atuarNoDisplay("Frentista","");
    break;

    case 26:
    esp32.atuarNoDisplay("Veiculo","");
    break;

    case 27:
    esp32.atuarNoDisplay("Motorista","");
    break;

    case 28:
    esp32.atuarNoDisplay("Identificado!","3800284");
    break;

    case 29:
    esp32.atuarNoDisplay("Identificado!","4105688");
    break;

    case 30:
    esp32.atuarNoDisplay("Identificado!","3395371");
    break;

    case 31:
    rtc.handleDataHorarioAbastecimento();
    Serial.println(String(rtc.getData()));
    break;

    // case 32:
    // digitalWrite(2, HIGH);
    // gps.handleLatitudeLongitude();
    // Serial.println(gps.getLocalizacao().getLatitude());
    // digitalWrite(2, LOW);
    // break;

    default:
    break;
  }
}

