/*
 GprsServices.cpp - Biblioteca para trabalhar com o GPRS (SIM800L).
 Criado pelo Luis Gustavo, 24 de Fevereiro, 2023.
 Atualizada, 03 de Abril, 2023.
*/

#include "GprsServices.h"

GprsServices::GprsServices(void)
{
  setupGprs();
}

void GprsServices::setupGprs(void)
{
  SerialMon.begin(115200);
  delay(10);
  SerialAT.begin(9600);
  delay(6000);
}

void GprsServices::inicializarGprs(void)
{
  modem.restart();

#if TINY_GSM_USE_GPRS
  // Unlock your SIM card with a PIN if needed
  if (GSM_PIN && modem.getSimStatus() != 3)
  {
    modem.simUnlock(GSM_PIN);
  }
#endif
}

void GprsServices::conectarNaRede(void)
{
  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork())
  {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isNetworkConnected())
  {
    SerialMon.println("Network connected");
  }

#if TINY_GSM_USE_GPRS
  // GPRS connection parameters are usually set after network registration
  SerialMon.print(F("Connecting to "));
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass))
  {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isGprsConnected())
  {
    SerialMon.println("GPRS connected");
  }
#endif
}

void GprsServices::requsicaoHttp(void)
{
  SerialMon.print(F("Performing HTTPS GET request... "));
  http.connectionKeepAlive(); // Currently, this is needed for HTTPS
  int err = http.get(resource);
  if (err != 0)
  {
    SerialMon.println(F("failed to connect"));
    delay(10000);
    return;
  }

  int status = http.responseStatusCode();
  SerialMon.print(F("Response status code: "));
  SerialMon.println(status);
  if (!status)
  {
    delay(10000);
    return;
  }

  SerialMon.println(F("Response Headers:"));
  while (http.headerAvailable())
  {
    String headerName = http.readHeaderName();
    String headerValue = http.readHeaderValue();
    SerialMon.println("    " + headerName + " : " + headerValue);
  }

  int length = http.contentLength();
  if (length >= 0)
  {
    SerialMon.print(F("Content length is: "));
    SerialMon.println(length);
  }
  if (http.isResponseChunked())
  {
    SerialMon.println(F("The response is chunked"));
  }

  String body = http.responseBody();
  SerialMon.println(F("Response:"));
  SerialMon.println(body);

  SerialMon.print(F("Body length is: "));
  SerialMon.println(body.length());

  http.stop();
  SerialMon.println(F("Server disconnected"));
}

void GprsServices::desconectarGprs(void)
{
#if TINY_GSM_USE_GPRS
  modem.gprsDisconnect();
  SerialMon.println(F("GPRS disconnected"));
#endif
}

void GprsServices::updateDadosSerial(void)
{
  if (Serial2.available())
  {
    Serial.write(Serial2.read());
  }
  if (Serial.available())
  {
    Serial2.write(Serial.read());
  }
}

String GprsServices::getBody(void)
{
  return body;
}

void