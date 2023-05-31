/*
  Abastecimento.cpp - Classe para criar um objeto de abastecimento.
  Criado pelo Luis Gustavo, 02 de Abril, 2023.
*/

#include "Abastecimento.h"

Abastecimento::Abastecimento()
{
}

int Abastecimento::getIdTanque(void)
{
  return _id_tanque;
}

void Abastecimento::setIdTanque(int id)
{
  _id_tanque = id;
}

String Abastecimento::getNomeTanque(void)
{
  return _nome_tanque;
}

void Abastecimento::setNomeTanque(String nome)
{
  _nome_tanque = nome;
}

float Abastecimento::getVolumeSaida(void)
{
  return _volume_saida;
}

void Abastecimento::setVolumeSaida(float volume)
{
  _volume_saida = volume;
}

Localizacao Abastecimento::getLocalizacaoBomba(void)
{
  return _localizacao;
}

void Abastecimento::setLocalizacaoBomba(Localizacao localizacao)
{
  _localizacao = localizacao;
}

String Abastecimento::getDataInicial(void)
{
  return _inicio_abastecimento;
}

void Abastecimento::setDataInicial(String data_inicial)
{
  _inicio_abastecimento = data_inicial;
}

String Abastecimento::getDataFinal(void)
{
  return _fim_abastecimento;
}

void Abastecimento::setDataFinal(String data_final)
{
  _fim_abastecimento = data_final;
}

Identificacao Abastecimento::getUsuarios(void)
{
  return _usuarios;
}

void Abastecimento::setUsuarios(Identificacao usuarios)
{
  _usuarios = usuarios
}