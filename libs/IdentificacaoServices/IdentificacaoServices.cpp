/*
  IdentificacaoServices.cpp - Classe para gerar um objeto de identificação
  Criado pelo Luis Gustavo, 01 de Abril, 2023.
  Atualizado, 02 de Abril, 2023.
*/

#include "IdentificacaoServices.h"

IdentificacaoServices::IdentificacaoServices()
{
  setIdFrentista(0);
  setIdMotorista(0);
  setIdVeiculo(0);
  setIdUsuario("frentista");
}

int IdentificacaoServices::getIdFrentista(void)
{
  return _id_frentista;
}

void IdentificacaoServices::setIdFrentista(int id)
{
  _id_frentista = id;
}

int IdentificacaoServices::getIdVeiculo(void)
{
  return _id_veiculo;
}

void IdentificacaoServices::setIdVeiculo(int id)
{
  _id_veiculo = id;
}

int IdentificacaoServices::getIdMotorista(void)
{
  return _id_motorista;
}

void IdentificacaoServices::setIdMotorista(int id)
{
  _id_motorista = id;
}

String IdentificacaoServices::getIdUsuario(void)
{
  return _id_usuario;
}

void IdentificacaoServices::setIdUsuario(String nome)
{
  _id_usuario = nome;
}
