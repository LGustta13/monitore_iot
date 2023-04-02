/*
  AbastecimentoServices.h - Classe para criar um objeto de abastecimento.
  Criado pelo Luis Gustavo, 02 de Abril, 2023.
*/

#ifndef ABASTECIMENTOSERVICES_H
#define ABASTECIMENTOSERVICES_H

#include <Arduino.h>

class AbastecimentoServices
{
public:
    /** Construtor do serviço
     * @param - void
     * @return - void
     */
    AbastecimentoServices(void);

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
    Data getDataInicial(void);

    /** Salva a data inicial do abastecimento
     * @param - Data data_inicial: data inicial do abastecimento
     * @return - void
     */
    void setDataInicial(Data data_inicial);

    /** Pega a data final do abastecimento
     * @param - void
     * @return - Data data_final: data final do abastecimento
     */
    Data getDataFinal(void);

    /** Salva a data final do abastecimento
     * @param - Data data_final: data final do abastecimento
     * @return - void
     */
    void setDataFinal(Data data_final);

    /** Pega os usuários identificados no abastecimento
     * @param - void
     * @return - Identificacao usuario: usuarios do abastecimento
     */
    Identificacao getUsuarios(void);

    /** Salva os usuários identificados no abastecimento
     * @param - Identificacao usuario: usuarios do abastecimento
     * @return - void
     */
    void setUsuarios(Identificacao usuarios);

private:
    int _id_tanque;
    String _nome_tanque;
    float _volume_saida;
    Localizacao _gps;
    Data _inicio_abastecimento;
    Data _fim_abastecimento;
    Identificacao _usuarios;
};

#endif