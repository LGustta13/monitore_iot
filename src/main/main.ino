/**
  * @Description: RASPBERRY_ESP32_DREXIA.ino
  * @Author: Luis Gustavo - TECHNOLOG
  * 
  * Sketch desenvolvido para integração entre ESP32 e Raspberry Pi 3B pelo barramento I2C
  * (baseado no código desenvolvido por Gutierrez <https://github.com/gutierrezps/ESP32_I2C_Slave>)
  * Barramento 1Wire utilizado para o Dréxia
  * (baseado no código desenvolvido por Paul Stoffregen <https://github.com/PaulStoffregen/OneWire>)
  * Comunicação serial utilizada para o GPS
  * (baseada no código desenvolvido por Mikal Hart <https://github.com/mikalhart/TinyGPSPlus>)
  * 
  * @Last modified:
  * 02/05/2022 - CRIAÇÃO DO SKETCH
  * 02/05/2022 - LÓGICA DE VOLUME E ATUALIZAÇÃO DO BLOQUEIO
  * 10/05/2022 - LÓGICA DRÉXIA PARA IDENTIFICAR VÁRIOS CARTÕES E BUZZER
  * 11/05/2022 - LÓGICA RTC E PERÍODO DE VIAGEM
  * 18/05/2022 - ACESSO AOS ARQUIVOS .CSV
  * 19/05/2022 - TEMPORIZADOR E API DE ACESSO AOS DADOS
  * 23/05/2022 - LÓGICA GPS
  * 05/10/2022 - LÓGICA COM MQTT
  */

#include <OneWire.h>
#include <WireSlave.h>
#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define TEMPO_DEBOUNCE 1000
#define FATOR_CALIBRACAO 4.5
#define I2C_SLAVE_ADDR 0x21
#define SDA_PIN 26
#define SCL_PIN 27
#define ONE_WIRE_PIN 25
#define BOMBA_GATILHO_0 32
#define BOMBA_GATILHO_1 13
#define PINO_SENSOR_1 35
#define PINO_SENSOR_0 14
#define PINO_BUZZER 33
#define LED_GREEN 19
#define LED_RED 18
#define LED_BLUE 17

#define TOPICO_SUBSCRIBE "topic/VMtoESP32"
#define TOPICO_PUBLISH "topic/ESP32toVM"

#define ID_MQTT "DEVKIT_ESP32"

OneWire  ds(ONE_WIRE_PIN);
TinyGPSPlus gps;
WiFiClient espClient;
PubSubClient MQTT(espClient);
DynamicJsonDocument doc(256);

// Variáveis globais para a rede wi-fi que será conectada
const char* SSID = "DESKTOP-NC2B4VE 9669";
const char* PASSWORD = "1223334444"; 
const char* BROKER_MQTT = "test.mosquitto.org";
int BROKER_PORT = 1883;

// Variável global que registra o id do cartão pelo dréxia
unsigned long id_cartao = 0;

// Variáveis globais para o contador de pulsos da bomba de combustível
unsigned long contador_pulsos = 0, tempo_antes = 0;
float fluxo_combustivel = 0, volume_instante = 0, volume_total = 0;

// Definição dos buffers que registram os dados do barramento I2C, 1WIRE e RXTX
byte buffer_i2c[128], buffer_1wire[8], buffer_rxtx[8];

/** Reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
  *          em caso de sucesso na conexão ou reconexão, o subscribe dos tópicos é refeito.
  * @param - void
  * @return - void
  */
void reconnect_mqtt(void) 
{
    led(LED_RED, LOW);
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
            led(LED_RED, HIGH);
            
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
    
}

/** Reconecta-se ao WiFi
  *
  * @param - void
  * @return - void
  */
void reconnect_wifi() 
{
    led(LED_BLUE, LOW);
    if (WiFi.status() == WL_CONNECTED){
        led(LED_BLUE, HIGH);
        return;
    }
          
    WiFi.begin(SSID, PASSWORD);
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println();
    led(LED_BLUE, HIGH);
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

/** Inicializa parâmetros de conexão MQTT(endereço do  
  *         broker, porta e seta função de callback)
  * @param - void
  * @return - void
  */
void init_mqtt(void) 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT); 
    MQTT.setCallback(mqtt_callback);            
}

/* Verifica o estado das conexões WiFI e ao broker MQTT. 
 *         Em caso de desconexão (qualquer uma das duas), a conexão
 *         é refeita.
 * @param - void
 * @return - void
 */
void verifica_conexoes_wifi_mqtt(void)
{
    reconnect_wifi(); 
    if (!MQTT.connected()) 
        reconnect_mqtt(); 
} 

/** Verifica os valores de latitude e longitude pelo GPS e atualiza o buffer da uart (rx e tx)
  * @param - void
  * @return - void
  */
void infoGps(){
  signed int latitude_bytes, longitude_bytes;
  bool condicao_serial = false;
  
  while((condicao_serial == false)){
    if (gps.encode(Serial2.read())){
      if (gps.location.isValid()){
        latitude_bytes = (signed int)(gps.location.lat()*1000000);
        buffer_rxtx[0] = (latitude_bytes >> 24);
        buffer_rxtx[1] = (latitude_bytes >> 16) & 255;
        buffer_rxtx[2] = (latitude_bytes >> 8) & 255;
        buffer_rxtx[3] = (latitude_bytes) & 255;

        longitude_bytes = (signed int)(gps.location.lng()*1000000);
        buffer_rxtx[4] = (longitude_bytes >> 24);
        buffer_rxtx[5] = (longitude_bytes >> 16) & 255;
        buffer_rxtx[6] = (longitude_bytes >> 8) & 255;
        buffer_rxtx[7] = (longitude_bytes) & 255;

        condicao_serial = true;
      }
      else{
        Serial.print(F("INVALID"));
      }
    }
  }
}

/** Verifica o ID do cartão pelo Dréxia
  * @param - void
  * @return - void
  */
void infoDrexia(){
  
  while(ds.search(buffer_1wire)){
    id_cartao = (id_cartao+buffer_1wire[4])<<8;
    id_cartao = (id_cartao+buffer_1wire[3])<<8;
    id_cartao = (id_cartao+buffer_1wire[2])<<8;
    id_cartao = (id_cartao+buffer_1wire[1]);
  
    if ( OneWire::crc8( buffer_1wire, 7) != buffer_1wire[7])
    {
      Serial.print("CRC não é válido!\n");
      return;
    }
  }
  ds.reset_search();
}

/** Calculo de volume e aquisição do pulso
  * @param - float maximo_volume: quantidade máxima de volume permitido
  * @return - void
  */
void pulsoBomba(float maximo_volume){
 
  int timer = 160, contador_timer = 0;
  maximo_volume = ((maximo_volume) - 23);

  attachInterrupt(digitalPinToInterrupt(PINO_SENSOR_0), contagemPulsos, FALLING); // Contagem de pulsos do sensor
  attachInterrupt(digitalPinToInterrupt(PINO_SENSOR_1), contagemPulsos, FALLING);  
 
  while (contador_timer<timer and volume_total<maximo_volume){
    if ( ((millis() - tempo_antes) >= TEMPO_DEBOUNCE)){
      fluxo_combustivel = ((1000.0 / (millis() - tempo_antes)) * contador_pulsos) / FATOR_CALIBRACAO;  // Conversao do valor de pulsos para L/min
      
      volume_instante = fluxo_combustivel / 60;  // Cálculo do volume em L passado pelo sensor
      volume_total += volume_instante; // Armazenamento do volume
  
      contador_pulsos = 0; // Reinicializacao do contador de pulsos
      tempo_antes = millis(); // Atualizacao da variável tempo_antes
    }

    if(contador_pulsos == 0){
      contador_timer++;
      delay(250);
    } else{
      Serial.println((String)"Volume: "+volume_total+" L" );
      contador_timer = 0;
    }
  }

  detachInterrupt(PINO_SENSOR_0); // Desabilita a interrupcao para realizar a conversao do valor de pulsos
  detachInterrupt(PINO_SENSOR_1);
}

/** Funcao auxiliar de pulsoBomba() para a contagem dos pulsos
  * @param - void
  * @return - void
  */
void contagemPulsos(){
  
    contador_pulsos++;
}

/** Funcao chamada quando necessário atuar no relé de bloqueio
  * @param - int pin: pino reservado para conectar o sinal de controle
  *          bool valor: nível lógico de atuação, sendo HIGH ou LOW
  * @return - void
  */
void bloqueio(int pin, bool valor){
  
  digitalWrite(pin, valor);   
}

/** Funcao chamada quando necessário atuar no buzzer
  * @param - void
  * @return - void
  */
void buzzer(){
  
  digitalWrite(PINO_BUZZER, HIGH);
  delay(50);
  digitalWrite(PINO_BUZZER, LOW);
  delay(50);
}  

void led(int pino, bool value){
  digitalWrite(pino, value);
}  

/** Funcao chamada quando necessário atuar no buzzer
  * @param - byte comando: comando enviado pelo master da comunicação
  * @return - void
  */
void checarId(byte comando){
  
  unsigned long aux_id = 0;
  if(comando == 0x00){
    Serial.println("Esperando identificação do FRENTISTA: ");
  } else if (comando == 0x01){
    Serial.println("Esperando identificação do VEÍCULO: ");
  } else if (comando == 0x02){
    Serial.println("Esperando identificação do MOTORISTA: ");
  }

  delay(50);
  while(id_cartao == 0){
    infoDrexia();
    if(comando != 0x00){
      aux_id++;
      if(aux_id >= 10000){
        id_cartao = 1;
        buzzer();
      }
    }
  }
  buzzer();
} 

/** Função que inicializa uma subrotina assim que algum comando de leitura é enviado pelo master do barramento
  * Master - Raspberry PI 4
  * Função que dispara a subrotina - smbus.read_bytes()
  * @param - byte comando: comando enviado pelo master da comunicação
  * @return - void
  */
void requestEvent(void){
  if(buffer_i2c[0] == 0x03){
    switch ( buffer_i2c[1] )
    {
      case 0x00:
      {
          ESP.restart();
      }
    
      case 0x01:
      {
          delay(50);
          infoGps();
          for(int i = 0; i<8; i++){
             WireSlave.write(buffer_rxtx[i]);
             buffer_rxtx[i] = 0;
          }
          break;
      }
  
      case 0x02:
      {
          delay(50);
          checarId(buffer_i2c[2]);
  
          if(id_cartao != 1){
            for (int i = 4; i>0; i--){
              WireSlave.write(buffer_1wire[i]);
              buffer_1wire[i] = 0;
            }
          } else {
            for (int i = 4; i>0; i--){
              WireSlave.write(0xFF);
              buffer_1wire[i] = 0;
            }
          }
          id_cartao = 0;          
          break;
      }
      
      case 0x03:
      {
          unsigned long aux_volume = 0, volume_bytes = 0;
          float volume_float = 0;
          
          Serial.print("Abastecendo:\n ");
          aux_volume = (aux_volume+buffer_i2c[2])<<8;
          aux_volume = (aux_volume+buffer_i2c[3])<<8;
          aux_volume = (aux_volume+buffer_i2c[4]);
          volume_float = ((float)aux_volume)/100;
  
          bloqueio(BOMBA_GATILHO_0, HIGH);
          bloqueio(BOMBA_GATILHO_1, HIGH);
          
          pulsoBomba(volume_float);
          Serial.println("Abastecimento finalizado.\n");
  
          bloqueio(BOMBA_GATILHO_0, LOW);
          bloqueio(BOMBA_GATILHO_1, LOW);
          
          volume_total = 0;
          contador_pulsos = 0;
          volume_instante = 0;
          fluxo_combustivel = 0;
  
          volume_bytes = (long)(volume_total*100);
          buffer_i2c[0] = volume_bytes >> 16;
          buffer_i2c[1] = (volume_bytes >> 8) - ((buffer_i2c[0]) << 8);
          buffer_i2c[2] = volume_bytes - (((buffer_i2c[0]) << 16) + ((buffer_i2c[1]) << 8));
  
          WireSlave.write(0x01);
          for (int i = 0; i<3; i++){
            WireSlave.write(buffer_i2c[i]);
          }       
          
          break;
      }
    }
  } else {
    byte comando1 = doc["comando1"];
    byte comando2 = doc["comando2"];
    byte comando3 = doc["comando3"];
    byte comando4 = doc["comando4"];
    char buffer[256] = "";
    
    switch ( comando1 )
    {
      case 0x00:
      {
        //////////////// Enviar código!
          JsonArray array = doc.to<JsonArray>();
          array.add(0x00);
          serializeJson(doc, buffer);
          MQTT.publish(TOPICO_PUBLISH, buffer);
          ESP.restart();
      }
      case 0x01:
      {
          delay(50);
          infoGps();
  
          JsonArray array = doc.to<JsonArray>(); 
  
          for(int i = 0; i<8; i++){
            array.add(buffer_rxtx[i]);
            buffer_rxtx[i] = 0;  
          }
  
          serializeJson(doc, buffer);
          MQTT.publish(TOPICO_PUBLISH, buffer);
          break;
      }
  
      case 0x02:
      {
          delay(50);
          checarId(comando2);

          JsonArray array = doc.to<JsonArray>();
          
          if(id_cartao != 1){
            for (int i = 4; i>0; i--){
              array.add(buffer_1wire[i]);   // Talvez posso passar o id_cartao direto, pois já pega os hexadecimais deslocados!!!
              buffer_1wire[i] = 0;
            }
            serializeJson(doc, buffer);
            MQTT.publish(TOPICO_PUBLISH, buffer);
            
          } else {
            for (int i = 4; i>0; i--){
              array.add(0xFF);
              buffer_1wire[i] = 0;
            }

            serializeJson(doc, buffer);
            MQTT.publish(TOPICO_PUBLISH, buffer);
          }
          id_cartao = 0;          
          break;
      }
      
      case 0x03:
      {
          unsigned long aux_volume = 0, volume_bytes = 0;
          float volume_float = 0;
          
          Serial.print("Abastecendo:\n ");
          aux_volume = (aux_volume+comando2)<<8;
          aux_volume = (aux_volume+comando3)<<8;
          aux_volume = (aux_volume+comando4);
          volume_float = ((float)aux_volume)/100;
  
          bloqueio(BOMBA_GATILHO_0, HIGH);
          bloqueio(BOMBA_GATILHO_1, HIGH);
          
          pulsoBomba(volume_float);
          Serial.println("Abastecimento finalizado.\n");
  
          bloqueio(BOMBA_GATILHO_0, LOW);
          bloqueio(BOMBA_GATILHO_1, LOW);
          
          volume_total = 0;
          contador_pulsos = 0;
          volume_instante = 0;
          fluxo_combustivel = 0;
  
          volume_bytes = (long)(volume_total*100);
          buffer_i2c[0] = volume_bytes >> 16;
          buffer_i2c[1] = (volume_bytes >> 8) - ((buffer_i2c[0]) << 8);
          buffer_i2c[2] = volume_bytes - (((buffer_i2c[0]) << 16) + ((buffer_i2c[1]) << 8));

          JsonArray array = doc.to<JsonArray>();
         
          array.add(0x01);
          for (int i = 0; i<3; i++){
              array.add(buffer_i2c[i]);
              buffer_i2c[i] = 0;
          }     
            
          serializeJson(doc, buffer);
          MQTT.publish(TOPICO_PUBLISH, buffer);
          
          break;
      }
    }
  }
  
}

/** Função que inicializa uma subrotina assim que algum comando de escrita é enviado pelo master do barramento
  * Master - Raspberry PI 4
  * Função que dispara a subrotina - smbus.write_bytes()
  * @param - int bytes_barramento: quantidade de bytes lidos no barramento
  * @return - void
  */
void receiveEvent(int bytes_barramento){
  
  for(int i = 0; i<bytes_barramento; i++){
    buffer_i2c[i] = WireSlave.read();
  }
}

/** Função de callback esta função é chamada toda vez que uma informação de 
  *    um dos tópicos subescritos chega)
  * @param - void
  * @return - void
  **/
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    led(LED_GREEN, HIGH);
    DeserializationError error = deserializeJson(doc, payload, length);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    requestEvent();
    led(LED_GREEN, LOW);
}

/** Função que inicializa variáveis, pinos e barramentos
  * @param - void
  * @return - void
  */
void setup(){
  Serial.begin(115200);
  Serial2.begin(9600);
  pinMode(BOMBA_GATILHO_0, OUTPUT);
  pinMode(BOMBA_GATILHO_1, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  pinMode(PINO_SENSOR_0, INPUT_PULLUP);
  pinMode(PINO_SENSOR_1, INPUT_PULLUP);
  pinMode(ONE_WIRE_PIN, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  if (!(WireSlave.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR)))
  {
    Serial.println("Comunicação entre Raspberry e Esp32 não inicializada");
    while (1)
      delay(100);
  }

  reconnect_wifi();
  init_mqtt(); 
  led(LED_GREEN, LOW);
  
  WireSlave.onRequest(requestEvent);
  WireSlave.onReceive(receiveEvent);
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
