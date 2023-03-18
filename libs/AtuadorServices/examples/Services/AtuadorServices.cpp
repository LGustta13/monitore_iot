/*
  AtuadorServices.cpp - Biblioteca para enviar sinais de comando
  aos atuadores do sistema.
  Criado pelo Luis Gustavo, 29 de Novembro, 2022.
  Atualização de funcionalidades, 16 de Março, 2023.
*/

#include "AtuadorServices.h"

AtuadorServices::AtuadorServices(int bomba_gatilho_0, int bomba_gatilho_1, int pino_sensor_0, int pino_sensor_1, int pino_buzzer, int pino_led_verde, int pino_led_vermelho, int pino_led_azul)
{
    _bomba_gatilho_0 = bomba_gatilho_0;
    _bomba_gatilho_1 = bomba_gatilho_1;
    _pino_sensor_0 = pino_sensor_0;
    _pino_sensor_1 = pino_sensor_1;
    _pino_buzzer = pino_buzzer;
    _pino_led_verde = pino_led_verde;
    _pino_led_vermelho = pino_led_vermelho;
    _pino_led_azul = pino_led_azul;

    _contador_pulsos_sensor_0 = 0;
    _contador_pulsos_sensor_1 = 0;
    _tempo_debounce = 1000;
    _fator_calibracao = 4.5;
    _restart = 0;

    _instance0 = this;
    _instance1 = this;

    setupAtuadores();
}

/** Preciso destas duas declarações para o programa reconhecer as instâncias
 * e executar as rotinas das interrupções*/
AtuadorServices *AtuadorServices::_instance0;
AtuadorServices *AtuadorServices::_instance1;

void AtuadorServices::setupAtuadores(void)
{
    pinMode(_bomba_gatilho_0, OUTPUT);
    pinMode(_bomba_gatilho_1, OUTPUT);
    pinMode(_pino_buzzer, OUTPUT);
    pinMode(_pino_sensor_0, INPUT_PULLUP);
    pinMode(_pino_sensor_1, INPUT_PULLUP);
    pinMode(_pino_led_verde, OUTPUT);
    pinMode(_pino_led_vermelho, OUTPUT);
    pinMode(_pino_led_azul, OUTPUT);
}

void AtuadorServices::atuarNoReleDeBloqueioZero(bool valor)
{
    digitalWrite(_bomba_gatilho_0, valor);
}

void AtuadorServices::atuarNoReleDeBloqueioUm(bool valor)
{
    digitalWrite(_bomba_gatilho_1, valor);
}

void AtuadorServices::atuarNoBuzzer()
{
    digitalWrite(_pino_buzzer, HIGH);
    delay(50);
    digitalWrite(_pino_buzzer, LOW);
    delay(50);
    digitalWrite(_pino_buzzer, HIGH);
    delay(50);
    digitalWrite(_pino_buzzer, LOW);
}

void AtuadorServices::atuarNoLedVermelho(bool valor)
{
    digitalWrite(_pino_led_vermelho, valor);
}

void AtuadorServices::atuarNoLedAzul(bool valor)
{
    digitalWrite(_pino_led_azul, valor);
}

void AtuadorServices::atuarNoLedVerde(bool valor)
{
    digitalWrite(_pino_led_verde, valor);
}

int AtuadorServices::receberPulsosDoGatilhoZero(void)
{
    int valor_porta_analogica = analogRead(_pino_sensor_0);
    return valor_porta_analogica;
}

int AtuadorServices::receberPulsosDoGatilhoUm(void)
{
    int valor_porta_analogica = analogRead(_pino_sensor_1);
    return valor_porta_analogica;
}

void AtuadorServices::reiniciarArduino(void)
{
    _restart();
}

void AtuadorServices::reiniciarEsp32(void)
{
    //    ESP.restart();
}

void AtuadorServices::subrotina_do_sensor_0(void)
{
    _instance0->contagemDosPulsosSensor0();
}

void AtuadorServices::subrotina_do_sensor_1(void)
{
    _instance1->contagemDosPulsosSensor1();
}

void AtuadorServices::contagemDosPulsosSensor1(void)
{
    _contador_pulsos_sensor_1++;
}

void AtuadorServices::contagemDosPulsosSensor0(void)
{
    _contador_pulsos_sensor_0++;
}

float AtuadorServices::getPulsosDaBombaPorParalelismo(float volume_a_ser_abastecido)
{
    float qtd_1 = 0, in1 = 0, qtd_0 = 0, in0 = 0, qtd_t = 0;
    int timer = (40 * 4);
    volume_a_ser_abastecido -= 23;

    return volume_a_ser_abastecido;
}

float AtuadorServices::getPulsosDaBombaPorInterrupcao_v3(float volume_a_ser_abastecido)
{
    while (true)
    {
        Serial.println(_contador_pulsos_sensor_1);
        // Serial.println(analogRead(_pino_sensor_1));
    }
}

float AtuadorServices::getPulsosDaBombaPorInterrupcao_v2(float volume_a_ser_abastecido)
{
    float qtd_1 = 0;
    float in1 = 0;
    float qtd_0 = 0;
    float in0 = 0;
    float qtd_t = 0;
    float timer = (40 * 4);

    volume_a_ser_abastecido = ((volume_a_ser_abastecido)-23);

    for (int i = 0; i < timer; ++i)
    {
        Serial.println(_contador_pulsos_sensor_0);
        if (_contador_pulsos_sensor_0 > 0 or _contador_pulsos_sensor_1 > 0)
        {
            // Serial.println(_contador_pulsos_sensor_0);
            i = 0;
            //
            //            if (_contador_pulsos_sensor_1 >= in1)
            //            {
            //                in1 = _contador_pulsos_sensor_1;
            //            }
            //            else
            //            {
            //                qtd_1 = (qtd_1 + in1);
            //                in1 = _contador_pulsos_sensor_1;
            //            }
            //
            //            if (_contador_pulsos_sensor_0 >= in0)
            //            {
            //                in0 = _contador_pulsos_sensor_0;
            //            }
            //            else
            //            {
            //                qtd_0 = (qtd_0 + in0);
            //                in0 = _contador_pulsos_sensor_0;
            //            }
            //
            //            qtd_t = (qtd_0 + qtd_1 + in0 + in1);
            //
            //            if (qtd_t >= volume_a_ser_abastecido)
            //            {
            //                i = timer;
            //            }
            //
            //            Serial.println(qtd_t);
        }
        else
        {
            //            Serial.println(qtd_t);
        }
        delay(250);
    }

    return qtd_t;
}

float AtuadorServices::getPulsosDaBombaPorInterrupcao(float volume_a_ser_abastecido)
{
    int timer_ate_desativar_a_bomba = 160;
    int timer_contagem_atual = 0;
    unsigned long millis_do_loop_anterior = 0;
    float fluxo_combustivel_em_Lmin = 0;
    float fluxo_combustivel_em_Lseg = 0;
    float volume_total = 0;

    volume_a_ser_abastecido = ((volume_a_ser_abastecido)-23);

    while (timer_contagem_atual < timer_ate_desativar_a_bomba and volume_total < volume_a_ser_abastecido)
    {
        if (((millis() - millis_do_loop_anterior) >= _tempo_debounce)) //
        {
            fluxo_combustivel_em_Lmin = ((1000.0 / (millis() - millis_do_loop_anterior)) * _contador_pulsos_sensor_0) / _fator_calibracao; // Conversao do valor de pulsos para L/min

            fluxo_combustivel_em_Lseg = fluxo_combustivel_em_Lmin / 60; // Cálculo do volume em L passado pelo sensor
            volume_total += fluxo_combustivel_em_Lseg;                  // Armazenamento do volume

            _contador_pulsos_sensor_0 = 0;      // Reinicializacao do contador de pulsos
            millis_do_loop_anterior = millis(); // Atualizacao da variável tempo_antes
        }

        if (_contador_pulsos_sensor_0 == 0)
        {
            timer_contagem_atual++;
            //            delay(250);
        }
        else
        {
            Serial.println((String) "Volume: " + volume_total + " L");
            timer_contagem_atual = 0;
        }
    }

    _contador_pulsos_sensor_0 = 0;
    return volume_total;
}

float AtuadorServices::realizarAbastecimento(float volume_a_ser_abastecido)
{
    float volume_dos_pulsos;

    attachInterrupt(digitalPinToInterrupt(_pino_sensor_0), subrotina_do_sensor_0, FALLING);
    attachInterrupt(digitalPinToInterrupt(_pino_sensor_1), subrotina_do_sensor_1, FALLING);

    atuarNoReleDeBloqueioUm(HIGH);
    atuarNoReleDeBloqueioZero(HIGH);

    volume_dos_pulsos = getPulsosDaBombaPorInterrupcao_v3(volume_a_ser_abastecido);

    detachInterrupt(digitalPinToInterrupt(_pino_sensor_0));
    detachInterrupt(digitalPinToInterrupt(_pino_sensor_1));

    atuarNoReleDeBloqueioUm(LOW);
    atuarNoReleDeBloqueioZero(LOW);

    return volume_dos_pulsos;
}
