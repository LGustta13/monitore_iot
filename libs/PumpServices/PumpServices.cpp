#include "PumpServices.h"

// Variáveis globais para o contador de pulsos da bomba de combustível
unsigned long contador_pulsos = 0, tempo_antes = 0;
float fluxo_combustivel = 0, volume_instante = 0, volume_total = 0;

void pulsoBomba(float maximo_volume)
{

    int timer = 160, contador_timer = 0;
    maximo_volume = ((maximo_volume)-23);

    attachInterrupt(digitalPinToInterrupt(PINO_SENSOR_0), contagemPulsos, FALLING); // Contagem de pulsos do sensor
    attachInterrupt(digitalPinToInterrupt(PINO_SENSOR_1), contagemPulsos, FALLING);

    while (contador_timer < timer and volume_total < maximo_volume)
    {
        if (((millis() - tempo_antes) >= TEMPO_DEBOUNCE))
        {
            fluxo_combustivel = ((1000.0 / (millis() - tempo_antes)) * contador_pulsos) / FATOR_CALIBRACAO; // Conversao do valor de pulsos para L/min

            volume_instante = fluxo_combustivel / 60; // Cálculo do volume em L passado pelo sensor
            volume_total += volume_instante;          // Armazenamento do volume

            contador_pulsos = 0;    // Reinicializacao do contador de pulsos
            tempo_antes = millis(); // Atualizacao da variável tempo_antes
        }

        if (contador_pulsos == 0)
        {
            contador_timer++;
            delay(250);
        }
        else
        {
            Serial.println((String) "Volume: " + volume_total + " L");
            contador_timer = 0;
        }
    }

    detachInterrupt(PINO_SENSOR_0); // Desabilita a interrupcao para realizar a conversao do valor de pulsos
    detachInterrupt(PINO_SENSOR_1);
}

void contagemPulsos()
{

    contador_pulsos++;
}