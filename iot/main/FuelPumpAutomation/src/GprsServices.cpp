#include "GprsServices.h"

GprsServices::GprsServices(void)
{
  _apn = "";
  _gprsUser = "";
  _gprsPass = "";
  _server = "";
  _resource = "";
  _body = "";

  setupGprs();
}

GprsServices::GprsServices(String apn, String gprs_usuario, String gprs_senha, String servidor, String recurso)
{
  _apn = apn;
  _gprs_usuario = gprs_usuario;
  _gprs_senha = gprs_senha;
  _servidor = servidor;
  _recurso = recurso;
  _body = "";

  setupGprs();
}

void GprsServices::setupGprs(void)
{

#define SerialAT Serial2
#define TINY_GSM_RX_BUFFER 10000
#define GSM_BAUD 9600
#define TINY_GSM_USE_GPRS true

  TinyGsmClient client(modem);
  const int port = 80;

  HttpClient http(client, server, port);
  delay(10);
  SerialAT.begin(9600);
  delay(6000);
}

void GprsServices::inicializarGprs(void)
{
  modem.restart();
  String modemInfo = modem.getModemInfo();

#if TINY_GSM_USE_GPRS
  // Unlock your SIM card with a PIN if needed
  if (GSM_PIN && modem.getSimStatus() != 3)
  {
    modem.simUnlock(GSM_PIN);
  }
#endif
}

bool GprsServices::conectarNaRede(void)
{
  if (!modem.waitForNetwork())
  {
    delay(10000);
    return false;
  }

  if (modem.isNetworkConnected())
  {
    Serial.println("Conectado na rede");
  }

#if TINY_GSM_USE_GPRS

  if (!modem.gprsConnect(_apn, _gprs_usuario, _gprs_senha))
  {
    delay(10000);
    return false;
  }

  if (modem.isGprsConnected())
  {
    Serial.println("Conexão GPRS sucedida");
  }
#endif

  return true;
}

bool GprsServices::requisicaoHttp(String token, String abastecimentosJson)
{
  http.connectionKeepAlive();
  int err = http.get(resource);
  if (err != 0)
  {
    delay(10000);
    return;
  }

  int status = http.responseStatusCode();
  if (!status)
  {
    delay(10000);
    return;
  }

  setBody(http.responseBody());
  http.stop();
  return true;
}

bool GprsServices::desconectarGprs(void)
{
#if TINY_GSM_USE_GPRS
  modem.gprsDisconnect();
  setBody("");
#endif

  return true;
}

String GprsServices::getBody(void)
{
  return _body;
}

void GprsServices::setBody(String body)
{
  _body = body;
}

String GprsServices::getUsuario(void)
{
  return _usuario;
}

void GprsServices::setUsuario(String usuario)
{
  _usuario = usuario;
}

String GprsServices::getSenha(void)
{
  return _senha;
}

void GprsServices::setSenha(String senha)
{
  _senha = senha;
}

String GprsServices::getServidor(void)
{
  return _servidor;
}

void GprsServices::setServidor(String servidor)
{
  _servidor = servidor;
}

String GprsServices::getApn(void)
{
  return _apn;
}

void GprsServices::setApn(String apn)
{
  _apn = apn;
}

String GprsServices::getRecurso(void)
{
  return _recurso;
}

void GprsServices::setRecurso(String recurso)
{
  _recurso = recurso;
}
