#include <RTClib.h> // Inclui a Biblioteca

RTC_DS1307 rtc;

void setup()
{
    rtc.begin(); // Inicia o módulo RTC

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Ajuste Automático da hora e data
    // rtc.adjust(DateTime(2019, 11, 29, 10, 23, 00));   // Ajuste Manual (Ano, Mês, Dia, Hora, Min, Seg)

    Serial.begin(9600);
}

void loop()
{
    DateTime now = rtc.now();

    Serial.println("Imprimindo Horário e Data");

    Serial.print("Hora: ");             // Imprime o texto "Hora: "
    Serial.print(rtc.now().hour());     // Imprime a Hora
    Serial.print(":");                  // Imprime o texto entre aspas
    Serial.print(rtc.now().minute());   // Imprime o Minuto
    Serial.print(":");                  // Imprime o texto entre aspas
    Serial.println(rtc.now().second()); // Imprime o Segundo

    Serial.print("Data: ");           // Imprime o texto entre aspas
    Serial.print(rtc.now().day());    // Imprime o Dia
    Serial.print("-");                // Imprime o texto entre aspas
    Serial.print(rtc.now().month());  // Imprime o Mês
    Serial.print("-");                // Imprime o texto entre aspas
    Serial.println(rtc.now().year()); // Imprime o Ano

    delay(1000); // Aguarda 1 segundo e reinicia
}