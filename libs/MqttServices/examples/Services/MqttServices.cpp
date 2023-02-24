/*
  MqttServices.cpp - Biblioteca para manipulação do protocolo MQTT.
  Criado pelo Luis Gustavo, 02 de Janeiro, 2023.
*/

#include "MqttServices.h"

MqttServices::MqttServices(const char *topico_de_subscricao, const char *topico_de_publicacao, const char *id_da_comunicacao, const char *ssid, const char *senha, const char *broker_mqtt, int broker_porta, AtuadorServices &esp32, DrexiaServices &drexia, GpsServices &gps)
 : _esp32(esp32), _drexia(drexia), _gps(gps), _doc(256)
{
    _topico_de_subscricao = topico_de_subscricao;
    _topico_de_publicacao = topico_de_publicacao;
    _id_da_comunicacao = id_da_comunicacao;

    _ssid = ssid;
    _senha = senha;
    _broker_mqtt = broker_mqtt;
    _broker_porta = broker_porta;

    _instance = this;

    WiFiClient _espClient;
    PubSubClient _mqtt(_espClient);

    setupMqtt();
}

MqttServices *MqttServices::_instance;

void MqttServices::subrotina_de_callback(char *topic, byte *payload, unsigned int length)
{
    _instance->callbackMqtt(topic, payload, length);  
}

void MqttServices::setupMqtt(void)
{
    reconexaoMqtt();
    inicializarMqtt();
}

void MqttServices::reconexaoMqtt()
{
    _esp32.atuarNoLedVermelho(LOW);
    while (!_mqtt.connected())
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(_broker_mqtt);
        if (_mqtt.connect(_id_da_comunicacao))
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            _mqtt.subscribe(_topico_de_subscricao);
            _esp32.atuarNoLedVermelho(HIGH);
        }
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentativa de conexao em 2s");
            delay(2000);
        }
    }
}

void MqttServices::inicializarMqtt(void)
{
    _mqtt.setServer(_broker_mqtt, _broker_porta);
    _mqtt.setCallback(subrotina_de_callback);
}

void MqttServices::reconexaoWifi(void)
{
    _esp32.atuarNoLedAzul(LOW);
    if (WiFi.status() == WL_CONNECTED)
    {
        _esp32.atuarNoLedAzul(HIGH);
        return;
    }

    WiFi.begin(_ssid, _senha);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }

    Serial.println();
    _esp32.atuarNoLedAzul(HIGH);
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(_ssid);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void MqttServices::verificarConexoesWifiMqtt(void)
{
    reconexaoWifi();
    if (!_mqtt.connected())
        reconexaoMqtt();
}

void MqttServices::callbackMqtt(char *topic, byte *payload, unsigned int length)
{
    _esp32.atuarNoLedVerde(HIGH);
    DeserializationError error = deserializeJson(_doc, payload, length);

    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
    }

    eventoDeRequisicaoMqtt();
    _esp32.atuarNoLedVerde(LOW);
}

void MqttServices::eventoDeRequisicaoMqtt(void)
{
    if(_doc["comando1"] == _comando_de_restart)
    {
        _esp32.reiniciarEsp32();
    }
    
    else if (_doc["comando1"] == _comando_do_gps)
    {
        enviarDadosDoGps();
    }

    else if (_doc["comando1"] == _comando_de_identificacao)
    {
        enviarDadosDoDrexia();
    }

    else if (_doc["comando1"] == _comando_da_bomba)
    {
        enviarDadosDaBomba();
    }
}

void MqttServices::enviarDadosDoGps(void)
{
    delay(50);
    _gps.getInfoDoGps();
    byte *ponteiro_buffer_rxtx = _gps.getBufferRxTx();

    JsonArray array = _doc.to<JsonArray>();

    for (int i = 0; i < 8; i++)
    {
        array.add(ponteiro_buffer_rxtx[i]);
        ponteiro_buffer_rxtx[i] = 0;
    }

    serializeJson(_doc, _buffer);
    _mqtt.publish(_topico_de_publicacao, _buffer);
}

void MqttServices::escreverNoBarramentoMqtt(byte *ponteiro_buffer_1wire, bool identificacao_valida)
{
    JsonArray array = _doc.to<JsonArray>();
    
    if (identificacao_valida)
    {
        for (int i = 4; i > 0; i--)
        {
            array.add(ponteiro_buffer_1wire[i]); // Talvez posso passar o id_cartao direto, pois já pega os hexadecimais deslocados!!!
            ponteiro_buffer_1wire[i] = 0;
        }
        serializeJson(_doc, _buffer);
        _mqtt.publish(_topico_de_publicacao, _buffer);
    }
    else
    {
        for (int i = 4; i > 0; i--)
        {
            array.add(0xFF);
            ponteiro_buffer_1wire[i] = 0;
        }
        serializeJson(_doc, _buffer);
        _mqtt.publish(_topico_de_publicacao, _buffer);
    }
}

void MqttServices::enviarDadosDoDrexia(void)
{
    delay(50);
    byte comando_de_usuario = _doc["comando2"];

    _drexia.verificarUsuarioDoCartao(comando_de_usuario);
    unsigned long identificacao = _drexia.getIdDoCartao();
    byte *ponteiro_buffer_1wire = _drexia.getBuffer1Wire();
    int identificacao_invalida = 1;

    bool id_esta_valido = (identificacao != identificacao_invalida);

    escreverNoBarramentoMqtt(ponteiro_buffer_1wire, id_esta_valido);
    _drexia.setIdDoCartao(0);
}

void MqttServices::enviarDadosDaBomba(void)
{
    unsigned long aux_volume = 0, volume_bytes = 0;
    float volume_float = 0;
    byte buffer_auxiliar[3];

    aux_volume = (aux_volume + _doc["comando2"].as<unsigned long>()) << 8;
    aux_volume = (aux_volume + _doc["comando3"].as<unsigned long>()) << 8;
    aux_volume = (aux_volume + _doc["comando4"].as<unsigned long>());
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

    buffer_auxiliar[0] = volume_bytes >> 16;
    buffer_auxiliar[1] = (volume_bytes >> 8) - ((buffer_auxiliar[0]) << 8);
    buffer_auxiliar[2] = volume_bytes - (((buffer_auxiliar[0]) << 16) + ((buffer_auxiliar[1]) << 8));

    JsonArray array = _doc.to<JsonArray>();

    array.add(0x01);
    for (int i = 0; i < 3; i++)
    {
        array.add(buffer_auxiliar[i]);
        buffer_auxiliar[i] = 0;
    }

    serializeJson(_doc, _buffer);
    _mqtt.publish(_topico_de_publicacao, _buffer);
}
