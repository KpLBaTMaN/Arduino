#include <Arduino.h>


//https://www.youtube.com/watch?v=dany7ae_0ks&ab_channel=MakeUseOf
int LED = 11;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, LOW);
  delay(1000);
  digitalWrite(LED, HIGH);
  delay(1000);
}