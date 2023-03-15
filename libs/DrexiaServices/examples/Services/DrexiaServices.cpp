/*
  DrexiaServices.cpp - Biblioteca para enviar sinais de comando
  e auxiliar na identificação pelo Dréxia.
  Criado pelo Luis Gustavo, 16 de Dezembro, 2022.
*/

#include <DrexiaServices.h>

DrexiaServices::DrexiaServices(int pino_one_wire, AtuadorServices &esp32) : _esp32(esp32)
{
    _pino_one_wire = pino_one_wire;
    OneWire _barramento_drexia(pino_one_wire);

    setupOneWire();
}

void DrexiaServices::setupOneWire(void)
{
    pinMode(_pino_one_wire, INPUT);
}

bool DrexiaServices::getCodigoDoCartao32bits(void)
{
    bool crc_valido = true;

    _id_do_cartao = (_id_do_cartao + _buffer_1wire[4]) << 8;
    _id_do_cartao = (_id_do_cartao + _buffer_1wire[3]) << 8;
    _id_do_cartao = (_id_do_cartao + _buffer_1wire[2]) << 8;
    _id_do_cartao = (_id_do_cartao + _buffer_1wire[1]);

    if (OneWire::crc8(_buffer_1wire, 7) != _buffer_1wire[7])
    {
        Serial.print("CRC não é válido!\n");
        crc_valido = false;
    }

    return crc_valido;
}

void DrexiaServices::getIdDoCartao64bits(void)
{
    bool codigo_resgatado_com_sucesso = false;

    while (_barramento_drexia.search(_buffer_1wire))
    {
        codigo_resgatado_com_sucesso = getCodigoDoCartao32bits();
        if (!codigo_resgatado_com_sucesso)
        {
            return;
        }
    }
    _barramento_drexia.reset_search();
}

void DrexiaServices::emitirAudio(byte comando_barramento)
{
    if (comando_barramento == _comando_frentista)
    {
        // Manda um áudio
        Serial.println("Esperando identificação do FRENTISTA: ");
    }
    else if (comando_barramento == _comando_veiculo)
    {
        // Manda um áudio
        Serial.println("Esperando identificação do VEÍCULO: ");
    }
    else if (comando_barramento == _comando_motorista)
    {
        // Manda um áudio
        Serial.println("Esperando identificação do MOTORISTA: ");
    }
}

void DrexiaServices::intervaloEsperaParaIdentificacao(bool motorista_ou_veiculo)
{
    unsigned long contador = 0;
    unsigned long tempo_espera_limite = 10000;
    unsigned short int id_nao_identificado = 0;
    unsigned short int id_identificacao_osciosa = 1;

    while (_id_do_cartao == id_nao_identificado)
    {
        getIdDoCartao64bits();
        if (motorista_ou_veiculo)
        {
            contador++;
            if (contador >= tempo_espera_limite)
            {
                _id_do_cartao = id_identificacao_osciosa;
                _esp32.atuarNoBuzzer();
            }
        }
    }
}

void DrexiaServices::verificarUsuarioDoCartao(byte comando_barramento)
{
    bool motorista_ou_veiculo = false;

    if (comando_barramento != _comando_frentista)
    {
        motorista_ou_veiculo = true;
    }

    emitirAudio(comando_barramento);
    intervaloEsperaParaIdentificacao(motorista_ou_veiculo);

    _esp32.atuarNoBuzzer();
}

unsigned long DrexiaServices::getIdDoCartao(void)
{
    return _id_do_cartao;
}

void DrexiaServices::setIdDoCartao(unsigned long novo_id_do_cartao)
{
    _id_do_cartao = novo_id_do_cartao;
}

byte *DrexiaServices::getBuffer1Wire(void)
{
    return _buffer_1wire;
}
