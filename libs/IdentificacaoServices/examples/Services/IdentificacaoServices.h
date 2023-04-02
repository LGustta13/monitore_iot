/*
  IdentificacaoServices.h - Classe para gerar um objeto de identificação
  Criado pelo Luis Gustavo, 01 de Abril, 2023.
*/

#ifndef IDENTIFICACAOSERVICES_H
#define IDENTIFICACAOSERVICES_H

#include <Arduino.h>

class IdentificacaoServices
{
public:
  /** Construtor que gera o abastecimento
   * @param -
   * @return -
   */
  IdentificacaoServices(void);

  /** Retorna o id do Frentista
   * @param - void
   * @return - int id: identificador do frentista
   */
  int getIdFrentista(void);

  /** Salva o id do Frentista
   * @param - int id: identificador do frentista
   * @return - void
   */
  void setIdFrentista(int id);

  /** Retorna o id do Motorista
   * @param - void
   * @return - int id: identificador do Motorista
   */
  int getIdMotorista(void);

  /** Salva o id do Motorista
   * @param - int id: identificador do Motorista
   * @return - void
   */
  void setIdMotorista(int id);

  /** Retorna o id do Veiculo
   * @param - void
   * @return - int id: identificador do Veiculo
   */
  int getIdVeiculo(void);

  /** Salva o id do Veiculo
   * @param - int id: identificador do Veiculo
   * @return - void
   */
  void setIdVeiculo(int id);

  /** Retorna o nome do último usuário identificado
   * @param - void
   * @return - int id: nome do usuário
   */
  String getIdUsuario(void);

  /** Salva o nome do último usuário identificado
   * @param - int id: nome do usuário
   * @return - void
   */
  void setIdUsuario(String nome);

private:
  int _id_frentista;
  int _id_motorista;
  int _id_veiculo;
  String _ultimo_identificado;
};

#endif