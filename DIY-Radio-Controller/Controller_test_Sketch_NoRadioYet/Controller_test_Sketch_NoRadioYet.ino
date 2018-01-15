/* Radio-controller for toys (boats, cars, airplanes, quadcopters)
    Developed by Clovis Fritzen from 01/13/2018 and on 
    http://www.Fritzenlab.com.br
    
    
    ICSP MAP:
    
    -----------------------
    | DTR   | RX   | TX   |
    -----------------------
    |       | GND  | +5V  |
    -----------------------
 
 
 */
 

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)


const int LB= 2;
const int LEDLEFT= 3;
const int JOYB= 4;
const int LEDRIGHT= 5;
const int RB= 6;
const int DOWN= 7;
const int LEFT= 8;
const int RIGHT= 9;
const int UP= 10;
const int RADIO= 13;
const int TRIMMER= A0;
const int JOYVERTICAL= A1;
const int JOYHORIZONTAL= A2;



void setup() {
  
  Serial.begin(9600);
  
  pinMode(LB, INPUT);    
  pinMode(LEDLEFT, OUTPUT);
  pinMode(JOYB, INPUT); 
  pinMode(LEDRIGHT, OUTPUT); 
  pinMode(RB, INPUT); 
  pinMode(DOWN, INPUT); 
  pinMode(LEFT, INPUT); 
  pinMode(RIGHT, INPUT); 
  pinMode(UP, INPUT); 
  pinMode(RADIO, OUTPUT); 
    
}

void loop()
{
 
  if (LB == HIGH){
     interval = 200; 
  }
  if (RB == HIGH){
     interval = 400; 
  }
  if (DOWN == HIGH){
     interval = 600; 
  }
  if (LEFT == HIGH){
     interval = 800; 
  }
  if (UP == HIGH){
     interval = 1000; 
  }
  if (RIGHT == HIGH){
     interval = 1200; 
  }
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis; 
  
    int JOYHORIZONTALvalue = analogRead(JOYHORIZONTAL);
    int JOYVERTICALvalue = analogRead(JOYVERTICAL);
    int trimmervalue = analogRead(TRIMMER);
    
    Serial.print("TRIMMER= ");
    Serial.print(trimmervalue);
    Serial.print("  ||horizontal= ");
    Serial.print(JOYHORIZONTALvalue);
    Serial.print("  ||vertical= ");
    Serial.println(JOYVERTICALvalue);
    
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(LEDLEFT, ledState);
     digitalWrite(LEDRIGHT, ledState);
  }
}
