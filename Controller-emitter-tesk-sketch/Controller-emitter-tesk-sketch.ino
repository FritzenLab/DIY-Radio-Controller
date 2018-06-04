#define S1 2
#define S2 6
#define S3 7
#define S4 8
#define S5 10
#define S6 9
#define JOYSW 4
#define LED1 3
#define LED2 5
#define TXRADIO 12
#define RXRADIO 13
#define JOYY A2
#define JOYX A1

#include <SoftwareSerial.h>
SoftwareSerial HC12(12, 13); // HC-12 TX Pin, HC-12 RX Pin

int valorX;
int valorY;




// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  HC12.begin(9600);

  
}

// the loop function runs over and over again forever
void loop() {
  
  
  valorX = analogRead(JOYX);
  valorY = analogRead(JOYY);

    
  if ((valorX <= 768) && (valorX >= 256) && (valorY <= 768) && (valorY >= 256)){ // PARADO
    HC12.write('0');
  }
  if ((valorX <= 256) && (valorY <= 768) && (valorY >= 256)){ // FRENTE
    HC12.write('1');
  }
  if ((valorX >= 768) && (valorY <= 768) && (valorY >= 256)){ // TRÁS
    HC12.write('2');
  }
  if ((valorX <= 768) && (valorX >= 256) && (valorY <= 256)){ // DIREITA
    HC12.write('3');
  }
  if ((valorX <= 768) && (valorX >= 256) && (valorY >= 768)){ // ESQUERDA
    HC12.write('4');
  }
  if ((valorX <= 256) && (valorY <= 256)){ // FRENTE-DIREITA
    HC12.write('5');
  }
  if ((valorX <= 256) && (valorY >= 768)){ // FRENTE-ESQUERDA
    HC12.write('6');
  }
  if ((valorX >= 768) && (valorY <= 256)){ // TRÁS-DIREITA
    HC12.write('7');
  }
  if ((valorX >= 768) && (valorY >= 768)){ // TRÁS-ESQUERDA
    HC12.write('8');
  }
  delay(50);

  
}

