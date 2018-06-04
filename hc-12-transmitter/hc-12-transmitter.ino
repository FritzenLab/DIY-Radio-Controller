    /*    Arduino Long Range Wireless Communication using HC-12
                          Example 01
       by Dejan Nedelkovski, www.HowToMechatronics.com
    */
    #include <SoftwareSerial.h>
    SoftwareSerial HC12(12, 13); // HC-12 TX Pin, HC-12 RX Pin

    char Str3[6] = {'1', '2', '3', '4', ',','\0'};
    
    void setup() {
      //Serial.begin(9600);             // Serial port to computer
      HC12.begin(9600);               // Serial port to HC12
    }
    void loop() {
      
         delay(1000);
        HC12.write(Str3);      // Send that data to HC-12
      
    }
