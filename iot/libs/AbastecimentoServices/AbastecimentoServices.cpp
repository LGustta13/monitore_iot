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
    return _localizacao;
}

void AbastecimentoServices::setLocalizacaoBomba(Localizacao localizacao)
{
    _localizacao = localizacao;
}

String AbastecimentoServices::getDataInicial(void)
{
    return _inicio_abastecimento;
}

void AbastecimentoServices::setDataInicial(String data_inicial)
{
    _inicio_abastecimento = data_inicial;
}

String AbastecimentoServices::getDataFinal(void)
{
    return _fim_abastecimento;
}

void AbastecimentoServices::setDataFinal(String data_final)
{
    _fim_abastecimento = data_final;
}

IdentificacaoServices AbastecimentoServices::getUsuarios(void)
{
    return _usuarios;
}

void AbastecimentoServices::setUsuarios(IdentificacaoServices usuarios)
{
    _usuarios = usuarios
}