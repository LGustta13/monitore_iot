/*
  AbastecimentoServices.cpp - Classe para criar um objeto de abastecimento.
  Criado pelo Luis Gustavo, 02 de Abril, 2023.
*/

#include "AbastecimentoServices.h"

AbastecimentoServices::AbastecimentoServices()
{
}

int getIdTanque(void)
{
    return _id_tanque;
}

void setIdTanque(int id)
{
    _id_tanque = id;
}

String getNomeTanque(void)
{
    return _nome_tanque;
}

void setNomeTanque(String nome)
{
    _nome_tanque = nome;
}

float getVolumeSaida(void)
{
    return _volume_saida;
}

void setVolumeSaida(float volume)
{
    _volume_saida = volume;
}

Localizacao getLocalizacaoBomba(void)
{
    return _gps;
}

void setLocalizacaoBomba(Localizacao localizacao)
{
    _gps = localizacao;
}

Data getDataInicial(void)
{
    return _inicio_abastecimento;
}

void setDataInicial(Data data_inicial)
{
    _inicio_abastecimento = data_inicial;
}

Data getDataFinal(void)
{
    return _fim_abastecimento;
}

void setDataFinal(Data data_final)
{
    _fim_abastecimento = data_final;
}

Identificacao getUsuarios(void)
{
    return _usuarios;
}

void setUsuarios(Identificacao usuarios)
{
    _usuarios = usuarios
}