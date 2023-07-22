/*
  Identificacao.cpp - Classe para gerar um objeto de identificação
  Criado pelo Luis Gustavo, 01 de Abril, 2023.
  Atualizado, 02 de Abril, 2023.
*/

#include "Identificacao.h"

Identificacao::Identificacao()
{
  _id_frentista = 0;
  _id_veiculo = 0;
  _id_motorista = 0;
}

int Identificacao::getIdFrentista(void)
{
  return _id_frentista;
}

void Identificacao::setIdFrentista(int id)
{
  _id_frentista = id;
}

int Identificacao::getIdVeiculo(void)
{
  return _id_veiculo;
}

void Identificacao::setIdVeiculo(int id)
{
  _id_veiculo = id;
}

int Identificacao::getIdMotorista(void)
{
  return _id_motorista;
}

void Identificacao::setIdMotorista(int id)
{
  _id_motorista = id;
}
