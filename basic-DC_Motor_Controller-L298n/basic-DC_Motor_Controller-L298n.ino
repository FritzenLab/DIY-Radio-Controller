#define OUT1 8
#define OUT2 10
#define OUT3 11
#define OUT4 12
#define OUT5 9
#define OUT6 6
#define OUT7 5
#define OUT8 3
#define PIN2 2
#define PIN13 13
#define Analog2 A2
#define Analog3 A3
#define Analog4_SDA A4
#define Analog5_SCL A5
#define RXRADIO 4
#define TXRADIO 7

#include <SoftwareSerial.h>
SoftwareSerial HC12(7, 4); // HC-12 TX Pin, HC-12 RX Pin

int incomeInfo;

// the setup function runs once when you press reset or power the board
void setup() {
  
  
  pinMode(OUT1, OUTPUT);  
  //pinMode(OUT2, OUTPUT);
  //pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(OUT5, OUTPUT);
  pinMode(OUT6, OUTPUT);
  pinMode(OUT7, OUTPUT);
  pinMode(OUT8, OUTPUT);
  pinMode(PIN2, OUTPUT);  
  pinMode(PIN13, OUTPUT);
  pinMode(Analog2, OUTPUT);
  pinMode(Analog3, OUTPUT);

  HC12.begin(9600);
    
}

// the loop function runs over and over again forever
void loop() {
  int pwm = 150;
 analogWrite(OUT2, pwm); // Send PWM signal to L298N Enable pin
 analogWrite(OUT3, pwm); // Send PWM signal to L298N Enable pin

 if(HC12.available()) {        // If HC-12 has data
        incomeInfo= HC12.read();
        //Serial.write();      // Send the data to Serial monitor
  }

  switch (incomeInfo) {
  case '0':
    digitalWrite(OUT5, LOW);
    digitalWrite(OUT6, LOW);
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT1, LOW);
    break;
  case '1':
    digitalWrite(OUT5, LOW);
    digitalWrite(OUT6, HIGH);
    digitalWrite(OUT4, HIGH);
    digitalWrite(OUT1, LOW);
    break;
  case '2':
    digitalWrite(OUT5, HIGH);
    digitalWrite(OUT6, LOW);
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT1, HIGH);
    break;
  case '3':
    digitalWrite(OUT5, HIGH);
    digitalWrite(OUT6, LOW);
    digitalWrite(OUT4, HIGH);
    digitalWrite(OUT1, LOW);
    break;
  case '4':
    digitalWrite(OUT5, LOW);
    digitalWrite(OUT6, HIGH);
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT1, HIGH);
    break;
  case '5':
    digitalWrite(OUT5, LOW);
    digitalWrite(OUT6, LOW);
    digitalWrite(OUT4, HIGH);
    digitalWrite(OUT1, LOW);
    break;
  case '6':
    digitalWrite(OUT5, LOW);
    digitalWrite(OUT6, HIGH);
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT1, LOW);
    break; 
  case '7':
    digitalWrite(OUT5, LOW);
    digitalWrite(OUT6, LOW);
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT1, HIGH);
    break;
  case '8':
    digitalWrite(OUT5, HIGH);
    digitalWrite(OUT6, LOW);
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT1, LOW);
    break;        
  default:

  break;
    
}
delay(40);
}

