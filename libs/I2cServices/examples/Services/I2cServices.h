/*
  I2cServices.h - Biblioteca para enviar sinais de comando
  e auxiliar no barramento I2C.
  Criado pelo Luis Gustavo, 26 de Dezembro, 2022.
*/

#ifndef I2CSERVICES_H
#define I2CSERVICES_H

#include <Arduino.h>
#include <WireSlave.h>
#include <GpsServices.h>
#include <AtuadorServices.h>
#include <DrexiaServices.h>

class I2cServices
{
public:
  I2cServices(byte i2c_endereco_escravo, int pino_sda_i2c, int pino_scl_i2c, GpsServices &gps, AtuadorServices &esp32, DrexiaServices &drexia);

  /** Funcao que realiza o setup do barramento I2C
   * @param - void
   * @return - void
   */
  void setupI2c(void);

  /** Função que controla o objeto do gps e
   * envia os dados por barramento I2C
   * @param - void
   * @return - void
   */
  void enviarDadosDoGps(void);

  /** Função auxiliar que envia dados pelo barramento I2C
   * @param - void
   * @return - byte *ponteiro_buffer_1wire: dados de identificação,
   *         - bool identificacao_valida: usuario encontrado na identificação
   */
  void escreverNoBarramentoI2c(byte *ponteiro_buffer_1wire, bool identificacao_valida);

  /** Função que controla o objeto do dréxia e
   * envia os dados por barrmaneto I2C
   * @param - void
   * @return - void
   */
  void enviarDadosDoDrexia(void);

  /** Função que controla o objeto da bomba e
   * envia os dados por GPIO's
   * @param - void
   * @return - void
   */
  void enviarDadosDaBomba(void);

  /** Função que inicializa uma subrotina assim que algum comando de leitura é enviado pelo master do barramento
   * Master - Raspberry PI 4
   * @param - void
   * @return - void
   */
  void eventoDeRequisicaoI2C(void);

  /** Função que inicializa uma subrotina assim que algum comando de escrita é enviado pelo master do barramento
   * Master - Raspberry PI 4
   * Função que dispara a subrotina - smbus.write_bytes()
   * @param - int bytes_barramento: quantidade de bytes lidos no barramento
   * @return - void
   */
  void eventoDeRecebimentoI2C(int bytes_do_barramento);

  /** Subrotina para ser usada como callback em onRequest
   * @param - void
   * @return - void
   */
  static void subrotinaDeRequisicao(void);

  /** Subrotina para ser usada como callback em onReceive
   * @param - int bytes_barramento: quantidade de bytes lidos no barramento
   * @return - void
   */
  static void subrotinaDeRecebimento(int bytes_do_barramento);

private:
  byte _i2c_endereco_escravo;
  byte _buffer_i2c[128];
  int _pino_sda_i2c;
  int _pino_scl_i2c;

  byte _comando_de_restart;
  byte _comando_do_gps;
  byte _comando_de_identificacao;
  byte _comando_da_bomba;

  static I2cServices *_instance;

  GpsServices _gps;
  AtuadorServices _esp32;
  DrexiaServices _drexia;
};

#endif
