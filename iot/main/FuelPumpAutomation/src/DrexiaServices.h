/*
  DrexiaServices.h - Biblioteca para enviar sinais de comando
  e auxiliar na identificação pelo Dréxia.
  Criado pelo Luis Gustavo, 16 de Dezembro, 2022.
  Atualização, 02 de Abril, 2023
*/

#ifndef DREXIASERVICES_H
#define DREXIASERVICES_H

#include <Arduino.h>

#include <OneWire.h>

class DrexiaServices
{
public:
  DrexiaServices(int pino_one_wire);

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
  bool getCodigoDoCartao32bits(byte _buffer_1wire[]);

  /** Funcao que resgata o identificador do cartão
   * sendo uma palavra de 8 bytes
   * 1 byte CRC, VALUE, MANUFATURA, DS1990A e 4 bytes Código do Cartão
   * @param - void
   * @return - void
   */
  void handleCartao64bits(void);

  /** Funcao que resgata o id do cartao registrado no momento
   * @param - void
   * @return - int _id_do_cartao, identificação atual
   */
  int getIdDoCartao(void);

  void setIdDoCartao(int);

private:
  int _pino_one_wire;
  int _id_do_cartao;
  OneWire _barramento_drexia;
};

#endif