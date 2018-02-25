/*   Arduino Long Range Wireless Communication using HC-12
     Example 03 - Stepper Motor Control using Accelerometer - Receiver, Stepper Motor

    by Dejan Nedelkovski, www.HowToMechatronics.com
*/
#include <SoftwareSerial.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

char incomingByte;
String readBuffer = "";

// defines pins numbers
const int dirPin = 4;
const int stepPin = 3;
const int button = 2;

int currentAngle = 0;
int lastAngle = 0;
int rotate = 0;

void setup() {
  Serial.begin(9600);             // Open serial port to computer
  HC12.begin(9600);               // Open serial port to HC12

  // Sets the two pins as Outputs
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  // Microswitch input, with internal pull-up resistor activated
  pinMode(button, INPUT_PULLUP);
  delay(10);
  digitalWrite(dirPin, HIGH);
  boolean startingPosition = true;
  while (startingPosition) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);
    if (digitalRead(button) == LOW) {
      startingPosition = false;
    }
  }
  delay(100);
}
void loop() {
  readBuffer = "";
  boolean start = false;
  // Reads the incoming angle
  while (HC12.available()) {             // If HC-12 has data
    incomingByte = HC12.read();          // Store each icoming byte from HC-12
    delay(5);
    // Reads the data between the start "s" and end marker "e"
    if (start == true) {
      if (incomingByte != 'e') {
        readBuffer += char(incomingByte);    // Add each byte to ReadBuffer string variable
      }
      else {
        start = false;
      }
    }
    // Checks whether the received message statrs with the start marker "s"
    else if ( incomingByte == 's') {
      start = true; // If true start reading the message
    }
  }
  // Converts the string into integer
  currentAngle = readBuffer.toInt();
  // Makes sure it uses angles between 0 and 180
  if (currentAngle > 0 && currentAngle < 180) {
    // Convert angle value to steps (depending on the selected step resolution)
    // A cycle = 200 steps, 180deg = 100 steps ; Resolution: Sixteenth step x16
    currentAngle = map(currentAngle, 0, 180, 0, 1600); 
    //Serial.println(currentAngle); // Prints the angle on the serial monitor
    digitalWrite(dirPin, LOW); // Enables the motor to move in a particular direction
    // Rotates the motor the amount of steps that differs from the previous positon
    if (currentAngle != lastAngle) {
      if (currentAngle > lastAngle) {
        rotate = currentAngle - lastAngle;
        for (int x = 0; x < rotate; x++) {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(400);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(400);
        }
      }
      // rotate the other way
      if (currentAngle < lastAngle) {
        rotate = lastAngle - currentAngle;
        digitalWrite(dirPin, HIGH);        //Changes the rotations direction
        for (int x = 0; x < rotate; x++) {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(400);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(400);
        }
      }
    }
    lastAngle = currentAngle;  // Remembers the current/ last positon
  }
}
