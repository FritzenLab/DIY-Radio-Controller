    /*    Arduino Long Range Wireless Communication using HC-12
                          Example 01
       by Dejan Nedelkovski, www.HowToMechatronics.com
    */
    #include <SoftwareSerial.h>
    SoftwareSerial HC12(7, 4); // HC-12 TX Pin, HC-12 RX Pin

    int Str4;
    
    void setup() {
      Serial.begin(9600);             // Serial port to computer
      HC12.begin(9600);               // Serial port to HC12
    }
    void loop() {
      while (HC12.available()) {        // If HC-12 has data
        Str4= HC12.read();
        Serial.write(Str4);      // Send the data to Serial monitor
        
      }
      
    }
