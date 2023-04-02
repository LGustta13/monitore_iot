/*
  AbastecimentoServices.cpp - Classe para criar um objeto de abastecimento.
  Criado pelo Luis Gustavo, 02 de Abril, 2023.
*/

#include "AbastecimentoServices.h"

AbastecimentoServices::AbastecimentoServices()
{
}

int AbastecimentoServices::getIdTanque(void)
{
    return _id_tanque;
}

void AbastecimentoServices::setIdTanque(int id)
{
    _id_tanque = id;
}

String AbastecimentoServices::getNomeTanque(void)
{
    return _nome_tanque;
}

void AbastecimentoServices::setNomeTanque(String nome)
{
    _nome_tanque = nome;
}

float AbastecimentoServices::getVolumeSaida(void)
{
    return _volume_saida;
}

void AbastecimentoServices::setVolumeSaida(float volume)
{
    _volume_saida = volume;
}

Localizacao AbastecimentoServices::getLocalizacaoBomba(void)
{
    return _gps;
}

void AbastecimentoServices::setLocalizacaoBomba(Localizacao localizacao)
{
    _gps = localizacao;
}

Data AbastecimentoServices::getDataInicial(void)
{
    return _inicio_abastecimento;
}

void AbastecimentoServices::setDataInicial(Data data_inicial)
{
    _inicio_abastecimento = data_inicial;
}

Data AbastecimentoServices::getDataFinal(void)
{
    return _fim_abastecimento;
}

void AbastecimentoServices::setDataFinal(Data data_final)
{
    _fim_abastecimento = data_final;
}

Identificacao AbastecimentoServices::getUsuarios(void)
{
    return _usuarios;
}

void AbastecimentoServices::setUsuarios(Identificacao usuarios)
{
    _usuarios = usuarios
}