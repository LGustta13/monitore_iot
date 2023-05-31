/*
  Abastecimento.h - Classe para criar um objeto de abastecimento.
  Criado pelo Luis Gustavo, 02 de Abril, 2023.
*/

#ifndef ABASTECIMENTO_H
#define ABASTECIMENTO_H

#include "Localizacao.h"

class Abastecimento
{
public:
  /** Construtor do serviço
   * @param - void
   * @return - void
   */
  Abastecimento(void);

  /** Pega o id do tanque
   * @param - void
   * @return - int id: id do tanque
   */
  int getIdTanque(void);

  /** Salva o id do tanque
   * @param - int id: id do tanque
   * @return - void
   */
  void setIdTanque(int id);

  /** Pega o nome do tanque
   * @param - void
   * @return - String nome: nome do tanque
   */
  String getNomeTanque(void);

  /** Salva o nome do tanque
   * @param - String nome: nome do tanque
   * @return - void
   */
  void setNomeTanque(String nome);

  /** Pega o volume de saida da bomba
   * @param - void
   * @return - float volume: volume de saída
   */
  float getVolumeSaida(void);

  /** Salva o volume de saida da bomba
   * @param - float volume: volume de saída
   * @return - void
   */
  void setVolumeSaida(float volume);

  /** Pega a localização da bomba
   * @param - void
   * @return - Localizacao localizacao: localizacao da bomba
   */
  Localizacao getLocalizacaoBomba(void);

  /** Salva a localização da bomba
   * @param - Localizacao localizacao: localizacao da bomba
   * @return - void
   */
  void setLocalizacaoBomba(Localizacao localizacao);

  /** Pega a data inicial do abastecimento
   * @param - void
   * @return - Data data_inicial: data inicial do abastecimento
   */
  String getDataInicial(void);

  /** Salva a data inicial do abastecimento
   * @param - Data data_inicial: data inicial do abastecimento
   * @return - void
   */
  void setDataInicial(String data_inicial);

  /** Pega a data final do abastecimento
   * @param - void
   * @return - Data data_final: data final do abastecimento
   */
  String getDataFinal(void);

  /** Salva a data final do abastecimento
   * @param - Data data_final: data final do abastecimento
   * @return - void
   */
  void setDataFinal(String data_final);

  /** Pega os usuários identificados no abastecimento
   * @param - void
   * @return - Identificacao usuario: usuarios do abastecimento
   */
  IdentificacaoServices getUsuarios(void);

  /** Salva os usuários identificados no abastecimento
   * @param - Identificacao usuario: usuarios do abastecimento
   * @return - void
   */
  void setUsuarios(IdentificacaoServices usuarios);

private:
  int _id_tanque;
  String _nome_tanque;
  float _volume_saida;
  Localizacao _localizacao;
  String _inicio_abastecimento;
  String _fim_abastecimento;
  Identificacao _usuarios;
};

#endif