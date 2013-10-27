#include <Servo.h>

const int doorServo = 11;

Servo doorLock;

void setup() {
  Serial.begin(9600);
  doorLock.attach(doorServo);  
}

void loop() {
//  doorLock.attach(doorServo);  
  //Serial.write("0");
  //doorLock.write(0);
  //delay(1000);

  Serial.println("90");
  Serial.println("Before: " + readRotation());
  doorLock.write(70);
  delay(5000);  
  Serial.println("After: " + readRotation());

  Serial.println("180");
  Serial.println(readRotation());
  doorLock.write(180);
  delay(5000);
  Serial.println(readRotation());  
  //doorLock.detach();
//  delay(5000);  
}

int readRotation(void) {
  int val = analogRead(A0);
  val = map(val, 0, 1023, 0, 179);
  return val;
}

void slowTurn(int angle) {
  int last = doorLock.read();
  int change = angle - last;
  change /= 50;
  int count = 0;
  while (last != angle && count < 50) {
    last += change;
    doorLock.write(last);
    count++;
    delay(2);
  }
  doorLock.write(angle);  
}
