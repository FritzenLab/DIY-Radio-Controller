#define enA 9
#define enB 3
#define in1 10
#define in2 11
#define in3 5
#define in4 6

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  
}

void loop() {
  
  analogWrite(enA, 100);
  analogWrite(enB, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(500);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(50);
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in3, HIGH);
  analogWrite(enA, 100);
  analogWrite(enB, 150);
  delay(500);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(50);
  
  
}
