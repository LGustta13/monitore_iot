/*
  GpsServices.h - Biblioteca para enviar sinais de comando
  e auxiliar no monitoramento pelo Gps.
  Criado pelo Luis Gustavo, 26 de Dezembro, 2022.
*/

#ifndef GPSSERVICES_H
#define GPSSERVICES_H

#include <Arduino.h>
#include <TinyGPSPlus.h>

class GpsServices
{
public:
    GpsServices(void);

    /** Funcao que realiza o setup do barramento serial para o GPS
     * @param - void
     * @return - void
     */
    void setupGps(void);

    /** Funcao que resgata o dado de latitude já tratado
     * @param - void
     * @return - void
     */
    void getDadosDeLatitude(void);

    /** Funcao que resgata o dado de longitude já tratado
     * @param - void
     * @return - void
     */
    void getDadosDeLongitude(void);

    /** Verifica os valores de latitude e longitude pelo GPS e atualiza o buffer da uart (rx e tx)
     * @param - void
     * @return - void
     */
    void getInfoDoGps(void);

    /** Função que resgata o buffer do barramento UART/RXTX
     * @param - void
     * @return - byte buffer_rxtx: array com dados do barramento serial
     */
    byte *getBufferRxTx(void);

private:
    byte _buffer_rxtx[8];
    TinyGPSPlus _gps;
};

#endif