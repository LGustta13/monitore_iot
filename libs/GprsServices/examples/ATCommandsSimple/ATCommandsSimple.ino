/*
TCP CONNECTION
AT+CSTT="smart.m2m.vivo.com.br","vivo","vivo" -> OK

IP CONNECTION
AT -> OK
AT+SAPBR=3,1,"Contype","GPRS" -> OK
AT+SAPBR=3,1,APN,"simplepm.algar.br" -> OK
AT+SAPBR=3,1,USER,"" -> OK 
AT+SAPBR=3,1,PWD,"" -> OK
AT+SAPBR=1,1 -> OK; iniciar conexão IP
AT+SAPBR=2,1 -> +SAPBR: 1,1,"10.230.0.176"; OK
AT+SAPBR=4,1 -> ver parâmetros setados; OK
AT+SAPBR=0,1 -> OK; finalizar comunicação GPRS

HTTP CONNECTION
AT+HTTPINIT -> OK
AT+HTTPPARA="CID", 1 -> OK
AT+HTTPPARA="URL","https://darwin-gps.com.br/api/motoristas/getRFIDMotoristas.php?chave=fc56dbc6d4652b315b86b71c8d688c1ccdea9c5f1fd07763d2659fde2e2fc49a" -> OK
AT+HTTPSCONT -> OK; salva o contexto, dados inseridos
AT+HTTPACTION=0 -> OK; +HTTPACTION:0,200,84 -- 0 é GET e 1 é POST
AT+HTTPREAD -> +HTTPREAD: 84; <Informa��o do retorno da requisi��o>; OK
AT+HTTPTERM -> OK; finalizar comunicação http

*/

void setup()
{
    // put your setup code here, to run once:
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    Serial.begin(9600);
    Serial2.begin(9600);
    Serial.println("\nExecutando método GET");
    digitalWrite(26, HIGH);
    digitalWrite(27, LOW);
}

void loop()
{
    updateSerial();
}

void updateSerial()
{
    if (Serial2.available())
    {
        Serial.write(Serial2.read());
    }
    if (Serial.available())
    {
        Serial2.write(Serial.read());
    }
}
