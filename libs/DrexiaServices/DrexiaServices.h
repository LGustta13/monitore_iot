/*
  DrexiaServices.h - Biblioteca para enviar sinais de comando
  e auxiliar na identificação pelo Dréxia.
  Criado pelo Luis Gustavo, 16 de Dezembro, 2022.
*/

#ifndef DREXIASERVICES_H
#define DREXIASERVICES_H

#include <Arduino.h>
#include <OneWire.h>
#include <AtuadorServices.h>

class DrexiaServices
{
public:
  DrexiaServices(int pino_one_wire, AtuadorServices &esp32);

  /** Funcao que realiza o setup do barramento OneWire
   * @param - void
   * @return - void
   */
  void setupOneWire(void);

  /** Funcao que resgata o código do cartão de identificação
   * sendo uma palavra de 4 bytes
   * 1 byte Fabricante e 3 bytes Código do Cartão
   * @param - void
   * @return - bool crc_valido: dados resgatados
   */
  bool getCodigoDoCartao32bits(void);

  /** Funcao que resgata o identificador do cartão
   * sendo uma palavra de 8 bytes
   * 1 byte CRC, VALUE, MANUFATURA, DS1990A e 4 bytes Código do Cartão
   * @param - void
   * @return - void
   */
  void getIdDoCartao64bits(void);

  /** Funcao que verifica os usuários identificados no barramento
   * @param - byte comando_barramento, byte vindo do barramento
   * @return - void
   */
  void emitirAudio(byte comando_barramento);

  /** Funcao que adota um tempo limite até que a próxima identificaçãp
   * ocorra
   * @param - bool motorista_ou_veiculo, condição para ser motorista ou veículo
   * @return - void
   */
  void intervaloEsperaParaIdentificacao(bool motorista_ou_veiculo);

  /** Verifica e armazena o ID do cartão lido pelo Dréxia
   * @param - byte comando_barramento, byte vindo do barramento
   * @return - void
   */
  void verificarUsuarioDoCartao(byte comando_barramento);

  /** Funcao que resgata o id do cartao registrado no momento
   * @param - void
   * @return - unsigned long _id_do_cartao, identificação atual
   */
  unsigned long getIdDoCartao(void);

  /** Funcao que seta o id do cartao registrado no momento
   * @param - unsigned long novo_id_do_cartao, identificação atual
   * @return - void
   */
  void setIdDoCartao(unsigned long);

  /** Funcao que resgata o buffer do barramento 1-Wire
   * @param - void
   * @return - byte* _buffer_1wire, array com os dados do barramento 1wire
   */
  byte *getBuffer1Wire(void);

private:
  int _pino_one_wire;
  byte _buffer_1wire[8];
  byte _comando_frentista = 0x00;
  byte _comando_veiculo = 0x01;
  byte _comando_motorista = 0x02;

  unsigned long _id_do_cartao;
  OneWire _barramento_drexia;
  AtuadorServices _esp32;
};

#endif