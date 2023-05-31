/*
  DrexiaServices.cpp - Biblioteca para enviar sinais de comando
  e auxiliar na identificação pelo Dréxia.
  Criado pelo Luis Gustavo, 16 de Dezembro, 2022.
  Atualização, 02 de Abril, 2023
*/

#include "DrexiaServices.h"

DrexiaServices::DrexiaServices(int pino_one_wire)
{
  _pino_one_wire = pino_one_wire;
  OneWire _barramento_drexia(pino_one_wire);
  setIdDoCartao(0);

  setupOneWire();
}

void DrexiaServices::setupOneWire(void)
{
  pinMode(_pino_one_wire, INPUT);
}

bool DrexiaServices::getCodigoDoCartao32bits(void)
{
  bool crc_valido = true;

  _id_do_cartao = (_id_do_cartao + _buffer_1wire[4]) << 8;
  _id_do_cartao = (_id_do_cartao + _buffer_1wire[3]) << 8;
  _id_do_cartao = (_id_do_cartao + _buffer_1wire[2]) << 8;
  _id_do_cartao = (_id_do_cartao + _buffer_1wire[1]);

  if (OneWire::crc8(_buffer_1wire, 7) != _buffer_1wire[7])
  {
    Serial.print("CRC não é válido!\n");
    crc_valido = false;
  }

  return crc_valido;
}

void DrexiaServices::getIdDoCartao64bits(void)
{
  bool codigo_resgatado_com_sucesso = false;

  while (_barramento_drexia.search(_buffer_1wire))
  {
    codigo_resgatado_com_sucesso = getCodigoDoCartao32bits();
    if (!codigo_resgatado_com_sucesso)
    {
      return;
    }
  }
  _barramento_drexia.reset_search();
}

int DrexiaServices::getIdDoCartao(void)
{
  return _id_do_cartao;
}

void DrexiaServices::setIdDoCartao(int id)
{
  _id_do_cartao = id;
}

byte *DrexiaServices::getBuffer1Wire(void)
{
  return _buffer_1wire;
}
