/*
  I2cServices.cpp - Biblioteca para enviar sinais de comando
  e auxiliar no barramento I2C.
  Criado pelo Luis Gustavo, 26 de Dezembro, 2022.
*/

#include "I2cServices.h"

I2cServices::I2cServices(byte i2c_endereco_escravo, int pino_sda_i2c, int pino_scl_i2c, GpsServices &gps, AtuadorServices &esp32, DrexiaServices &drexia)
    : _gps(gps), _esp32(esp32), _drexia(drexia)

{
    _i2c_endereco_escravo = i2c_endereco_escravo;
    _pino_sda_i2c = pino_sda_i2c;
    _pino_scl_i2c = pino_scl_i2c;

    _comando_de_restart = 0x00;
    _comando_do_gps = 0x01;
    _comando_de_identificacao = 0x02;
    _comando_da_bomba = 0x03;

    _instance = this;

    setupI2c();
}

I2cServices *I2cServices::_instance;

void I2cServices::setupI2c(void)
{
    bool comunicacao_i2c_inicializada = WireSlave.begin(_pino_sda_i2c, _pino_scl_i2c, _i2c_endereco_escravo);
    if (comunicacao_i2c_inicializada == false)
    {
        Serial.println("Comunicação entre Raspberry e Esp32 não inicializada");
        while (1)
            delay(100);
    }

    WireSlave.onRequest(subrotina_de_requisicao);
    WireSlave.onReceive(subrotina_de_recebimento);
}

void I2cServices::enviarDadosDoGps(void)
{
    delay(50);
    _gps.getInfoDoGps();

    byte *ponteiro_buffer_rxtx = _gps.getBufferRxTx();

    for (int i = 0; i < 8; i++)
    {
        WireSlave.write(ponteiro_buffer_rxtx[i]);
        ponteiro_buffer_rxtx[i] = 0;
    }
}

void I2cServices::escreverNoBarramentoI2c(byte *ponteiro_buffer_1wire, bool identificacao_valida)
{
    if (identificacao_valida)
    {

        for (int i = 4; i > 0; i--)
        {
            WireSlave.write(ponteiro_buffer_1wire[i]);
            ponteiro_buffer_1wire[i] = 0;
        }
    }
    else
    {
        for (int i = 4; i > 0; i--)
        {
            WireSlave.write(0xFF);
            ponteiro_buffer_1wire[i] = 0;
        }
    }
}

void I2cServices::enviarDadosDoDrexia(void)
{
    delay(50);
    _drexia.verificarUsuarioDoCartao(_buffer_i2c[1]);

    unsigned long identificacao = _drexia.getIdDoCartao();
    byte *ponteiro_buffer_1wire = _drexia.getBuffer1Wire();
    int identificacao_invalida = 1;

    bool id_esta_valido = (identificacao != identificacao_invalida);

    escreverNoBarramentoI2c(ponteiro_buffer_1wire, id_esta_valido);
    _drexia.setIdDoCartao(0);
}

void I2cServices::enviarDadosDaBomba(void)
{
    unsigned long aux_volume = 0, volume_bytes = 0;
    float volume_float = 0;

    aux_volume = (aux_volume + _buffer_i2c[3]) << 8;
    aux_volume = (aux_volume + _buffer_i2c[2]) << 8;
    aux_volume = (aux_volume + _buffer_i2c[4]);
    volume_float = ((float)aux_volume) / 100;

    volume_bytes = _esp32.realizarAbastecimento(volume_float);

    // bloqueio(BOMBA_GATILHO_0, HIGH);
    // bloqueio(BOMBA_GATILHO_1, HIGH);

    // pulsoBomba(volume_float);
    // Serial.println("Abastecimento finalizado.\n");

    // bloqueio(BOMBA_GATILHO_0, LOW);
    // bloqueio(BOMBA_GATILHO_1, LOW);

    // volume_total = 0;
    // contador_pulsos = 0;
    // volume_instante = 0;
    // fluxo_combustivel = 0;

    // volume_bytes = (long)(volume_total * 100);

    _buffer_i2c[0] = volume_bytes >> 16;
    _buffer_i2c[1] = (volume_bytes >> 8) - ((_buffer_i2c[0]) << 8);
    _buffer_i2c[2] = volume_bytes - (((_buffer_i2c[0]) << 16) + ((_buffer_i2c[1]) << 8));

    WireSlave.write(0x01);
    for (int i = 0; i < 3; i++)
    {
        WireSlave.write(_buffer_i2c[i]);
    }
}

void I2cServices::eventoDeRequisicaoI2C(void)
{
    if (_buffer_i2c[0] == _comando_de_restart)
    {
        _esp32.reiniciarEsp32();
    }

    else if (_buffer_i2c[0] == _comando_do_gps)
    {
        enviarDadosDoGps();
    }

    else if (_buffer_i2c[0] == _comando_de_identificacao)
    {
        enviarDadosDoDrexia();
    }

    else if (_buffer_i2c[0] == _comando_da_bomba)
    {
        enviarDadosDaBomba();
    }
}

void I2cServices::eventoDeRecebimentoI2C(int bytes_do_barramento)
{
    for (int i = 0; i < bytes_do_barramento; i++)
    {
        _buffer_i2c[i] = WireSlave.read();
    }
}

void I2cServices::subrotina_de_requisicao(void)
{
    _instance->eventoDeRequisicaoI2C();
}

void I2cServices::subrotina_de_recebimento(int bytes_do_barramento)
{
    _instance->eventoDeRecebimentoI2C(bytes_do_barramento);
}