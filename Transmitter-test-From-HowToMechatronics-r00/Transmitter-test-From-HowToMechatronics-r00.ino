/*   Arduino Long Range Wireless Communication using HC-12
     Example 03 - Stepper Motor Control using Accelerometer - Transmitter, Accelerometer
    by Dejan Nedelkovski, www.HowToMechatronics.com
*/

#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

float angle;
int lastAngle = 0;
int count = 0;
int angleSum = 0;

//--- Accelerometer Register Addresses
#define Power_Register 0x2D
#define X_Axis_Register_DATAX0 0x32 // Hexadecima address for the DATAX0 internal register.
#define X_Axis_Register_DATAX1 0x33 // Hexadecima address for the DATAX1 internal register.
#define Y_Axis_Register_DATAY0 0x34
#define Y_Axis_Register_DATAY1 0x35
#define Z_Axis_Register_DATAZ0 0x36
#define Z_Axis_Register_DATAZ1 0x37
int ADXAddress = 0x53;  //Device address in which is also included the 8th bit for selecting the mode, read in this case.
int X0, X1, X_out;
int Y0, Y1, Y_out;
int Z1, Z0, Z_out;
float Xa, Ya, Za;

void setup() {
  HC12.begin(9600);               // Open serial port to HC12
  Wire.begin(); // Initiate the Wire library
  Serial.begin(9600);
  delay(100);

  Wire.beginTransmission(ADXAddress);
  Wire.write(Power_Register); // Power_CTL Register
  // Enable measurement
  Wire.write(8); // Bit D3 High for measuring enable (0000 1000)
  Wire.endTransmission();
}
void loop() {
  // X-axis
  Wire.beginTransmission(ADXAddress); // Begin transmission to the Sensor
  //Ask the particular registers for data
  Wire.write(X_Axis_Register_DATAX0);
  Wire.write(X_Axis_Register_DATAX1);
  Wire.endTransmission(); // Ends the transmission and transmits the data from the two registers
  Wire.requestFrom(ADXAddress, 2); // Request the transmitted two bytes from the two registers
  if (Wire.available() <= 2) { //
    X0 = Wire.read(); // Reads the data from the register
    X1 = Wire.read();
    /* Converting the raw data of the X-Axis into X-Axis Acceleration
      - The output data is Two's complement
      - X0 as the least significant byte
      - X1 as the most significant byte */
    X1 = X1 << 8;
    X_out = X0 + X1;
    Xa = X_out / 256.0; // Xa = output value from -1 to +1, Gravity acceleration acting on the X-Axis
  }
  //Serial.print("Xa= ");
  //Serial.println(X_out);

  // Y-Axis
  Wire.beginTransmission(ADXAddress);
  Wire.write(Y_Axis_Register_DATAY0);
  Wire.write(Y_Axis_Register_DATAY1);
  Wire.endTransmission();
  Wire.requestFrom(ADXAddress, 2);
  if (Wire.available() <= 2) {
    Y0 = Wire.read();
    Y1 = Wire.read();
    Y1 = Y1 << 8;
    Y_out = Y0 + Y1;
    Ya = Y_out / 256.0;
  }

  // Combine X and Y values for getting the angle value from 0 to 180 degrees
  if (Y_out > 0) {
    angle = map(Y_out, 0, 256, 90, 0);
  }
  else if (Y_out < 0) {
    angle = map(Y_out, 256, 0, 90, 0);
    angle = 90 - angle;
  }
  if (X_out < 0 & Y_out < 0) {
    angle = 180;
  }
  if (X_out < 0 & Y_out >0) {
    angle = 0;
  }
  
  // float to int
  int angleInt = int(angle);
  // Makes 100 accelerometer readings and sends the average for smoother result
  angleSum = angleSum + angleInt;
  count++;
  if (count >= 100) {
    angleInt = angleSum / 100;
    angleSum = 0;
    count = 0;
    // Some more smoothing of acceleromter reading - sends the new angle only if it differes from the previous one by +-2
    if (angleInt > lastAngle + 2 || angleInt < lastAngle - 2) {
      Serial.println(angleInt);
      String angleString = String(angleInt);
      //sends the angle value with start marker "s" and end marker "e"
      HC12.print("s" + angleString + "e");
      delay(10);
      lastAngle = angleInt;
      angleSum = 0;
      count = 0;
    }
  }
}
