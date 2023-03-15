#include <Arduino.h>
#include <ArduinoJson.h>

DynamicJsonDocument doc(256);

/** Função que inicializa variáveis, pinos e barramentos
  * @param - void
  * @return - void
  */
void setup(){
  Serial.begin(115200);

  
  led(LED_GREEN, LOW);
}

/** Função que controla o uso do sistema embarcado
  * @param - void
  * @return - void
  */
void loop(void){
  verifica_conexoes_wifi_mqtt();
  MQTT.loop();
  WireSlave.update();
  delay(500);
}
