
// reference: http://www.instructables.com/id/Arduino-weather-station-with-RF433-MHz-modules/
// Antenna improvement: http://www.instructables.com/id/433-MHz-Coil-loaded-antenna/
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
float temp = 0.00;
int sensor = A1;
char msg[6];
int sent = 0;

void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
     
    digitalWrite(13, HIGH); 
    String analogicos = String(analogRead(A0), DEC) + "," + String(analogRead(A1), DEC) + "," + String(analogRead(A2), DEC) + "," + String(analogRead(A3), DEC) + "," + String(analogRead(A4), DEC) + "," + String(analogRead(A5), DEC) + "\n";
    // Length (with one extra character for the null terminator)
    int str_len = analogicos.length(); 
    // Prepare the character array (the buffer) 
    char msg[str_len];
    analogicos.toCharArray(msg, str_len);
    
    //dtostrf(sent, 6,0,msg);
    //dtostrf(analogicos, 6,0,msg)
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(13, LOW); 
    delay(1000);
}



