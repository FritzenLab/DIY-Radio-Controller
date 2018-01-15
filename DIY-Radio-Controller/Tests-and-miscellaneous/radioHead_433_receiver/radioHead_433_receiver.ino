
// reference: http://www.instructables.com/id/Arduino-weather-station-with-RF433-MHz-modules/
// Antenna improvement: http://www.instructables.com/id/433-MHz-Coil-loaded-antenna/
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600); // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    digitalWrite(13, LOW); 
    uint8_t buf[25];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      //Serial.print("Message: ");
      Serial.println((char*)buf);         
    }
    digitalWrite(13, HIGH); 
}


