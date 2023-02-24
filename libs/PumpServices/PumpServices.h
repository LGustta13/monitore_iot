#ifndef PUMPSERVICES_H
#define PUMPSERVICES_H

#include <Arduino.h>

#define TEMPO_DEBOUNCE 1000
#define FATOR_CALIBRACAO 4.5

/** Calculo de volume e aquisição do pulso
 * @param - float maximo_volume: quantidade máxima de volume permitido
 * @return - void
 */
void pulsoBomba(float maximo_volume);

/** Funcao auxiliar de pulsoBomba() para a contagem dos pulsos
 * @param - void
 * @return - void
 */
void contagemPulsos(void);

#endif