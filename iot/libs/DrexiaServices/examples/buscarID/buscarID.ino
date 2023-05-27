// This sketch looks for 1-wire devices and
// prints their addresses (serial number) to
// the UART, in a format that is useful in Arduino sketches
// Tutorial:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

// 0x01, 0x56, 0xB8, 0x44, 0x00, 0x08, 0x00, 0x48

#include <OneWire.h>

OneWire ds(25); // Connect your 1-wire device to pin 3

void setup(void)
{
    Serial.begin(115200);
}

void discoverOneWireDevices(void)
{
    byte i;
    byte present = 0;
    unsigned int data = 0;
    byte addr[8];

    // Serial.print("...\n\r");
    while (ds.search(addr))
    {
        Serial.print("\n\rEncontrado dispositivo:\n\r");
        for (i = 0; i < 8; i++)
        {
            Serial.print("0x");
            // Utiliza esse if pq quando o byte é igual a 15 decimal ou menor, precisa printar o 0 antes do valor, ou seja
            // 00001111 => passa no if => 0x0 => passa no segundo print => 0x0F => passa no segundo if => 0x0F,
            if (addr[i] < 16)
            {
                Serial.print('0');
            }
            Serial.print(addr[i], HEX);
            if (i < 7)
            {
                Serial.print(", ");
            }
        }

        // Verifica o Checksum, que está na posição 7 de addr, no último byte transmitido
        if (OneWire::crc8(addr, 7) != addr[7])
        {
            Serial.print("CRC is not valid!\n");
            return;
        }

        // Para o drexia. será printado id do cartão que foi utilizado
        data = (data + addr[4]) << 8;
        data = (data + addr[3]) << 8;
        data = (data + addr[2]) << 8;
        data = (data + addr[1]);
        Serial.print("\n\nCHECKSUM: ");
        Serial.println(addr[7], DEC);
        Serial.print("CONST VALUE: ");
        Serial.println(addr[6], DEC);
        Serial.print("MANUFACTURER: ");
        Serial.println(addr[5], DEC);
        Serial.print("CARD DATA: ");
        Serial.println(data, DEC);
        Serial.print("CODE DS1990A: ");
        Serial.println(addr[0], DEC);

        ds.reset_search();
        delay(5000);
        return;
    }
}

void loop(void)
{
    discoverOneWireDevices();
    delay(100);
}