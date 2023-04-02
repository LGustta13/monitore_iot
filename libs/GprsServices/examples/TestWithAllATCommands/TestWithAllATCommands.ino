/*  More information at: https://www.aeq-web.com/
 *  ESP32 SIM800 HTTP POST TEST | V 1.0_2020-AUG-18
 */
 
// #define SIM800L_RX     27
// #define SIM800L_TX     26
// #define SIM800L_PWRKEY 4
// #define SIM800L_RST    5
// #define SIM800L_POWER  23

String apn = "simplepm.algar.br";                    //APN
String apn_u = "";                     //APN-Username
String apn_p = "";                     //APN-Password
String url = "http://testserver.aeq-web.com/sim800_test/sim800.php";  //URL of Server

void setup()
{
  // pinMode(SIM800L_POWER, OUTPUT);
  // digitalWrite(SIM800L_POWER, HIGH);

  Serial.begin(115200);
  Serial.println("ESP32+SIM800L AT CMD Test");
  Serial2.begin(9600, SERIAL_8N1);
  delay(15000);
  while (Serial2.available()) {
    Serial.write(Serial2.read());
  }
  delay(2000);
  gsm_config_gprs();
}


void loop() {
  gsm_http_post("param=TestFromMySim800");
  delay(30000);
}

void gsm_http_post( String postdata) {
  Serial.println(" --- Start GPRS & HTTP --- ");
  gsm_send_serial("AT+SAPBR=1,1");
  gsm_send_serial("AT+SAPBR=2,1");
  gsm_send_serial("AT+HTTPINIT");
  gsm_send_serial("AT+HTTPPARA=CID,1");
  gsm_send_serial("AT+HTTPPARA=URL," + url);
  gsm_send_serial("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
  gsm_send_serial("AT+HTTPDATA=192,5000");
  gsm_send_serial(postdata);
  gsm_send_serial("AT+HTTPACTION=1");
  gsm_send_serial("AT+HTTPREAD");
  gsm_send_serial("AT+HTTPTERM");
  gsm_send_serial("AT+SAPBR=0,1");
}

void gsm_config_gprs() {
  Serial.println(" --- CONFIG GPRS --- ");
  gsm_send_serial("AT+SAPBR=3,1,Contype,GPRS");
  gsm_send_serial("AT+SAPBR=3,1,APN," + apn);
  if (apn_u != "") {
    gsm_send_serial("AT+SAPBR=3,1,USER," + apn_u);
  }
  if (apn_p != "") {
    gsm_send_serial("AT+SAPBR=3,1,PWD," + apn_p);
  }
}

void gsm_send_serial(String command) {
  Serial.println("Send ->: " + command);
  Serial2.println(command);
  long wtimer = millis();
  while (wtimer + 3000 > millis()) {
    while (Serial2.available()) {
      Serial.write(Serial2.read());
    }
  }
  Serial.println();
}