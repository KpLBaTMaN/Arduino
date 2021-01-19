#include <Arduino.h>

#include <IRremote.h>

const int RECV_PIN = 6;

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){

    //IF for reason
    if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        //REMOTE CASES
        switch(results.value){
          //Button up 0xFF629D
          case 0xFF629D:
            Serial.println("UP");
            break;
            
          //Button left 0xFF22DD
          case 0xFF22DD:
            Serial.println("Left");
            break;
            
          //Button right 0xFFC23D
          case 0xFFC23D:
            Serial.println("Right");
            break;
            
          //Button down 0xFFA857
          case 0xFFA857:
            Serial.println("Down");
            break;
            
          //Button OK 0xFF02FD
          case 0xFF02FD:
            Serial.println("OK");
            break;
          
          //Number 1 0xFF6897
          case 0xFF6897:
            Serial.println("Number:1");
            break;
          
          //Number 2 0xFF9867
          case 0xFF9867:
            Serial.println("Number:2");
            break;
            
          //Number 3 0xFFB04F
          case 0xFFB04F:
            Serial.println("Number:3");
            break;
            
          //Number 4 0xFF30CF
          case 0xFF30CF:
            Serial.println("Number:4");
            break;
          
          //Number 5 0xFF18E7
          case 0xFF18E7:
            Serial.println("Number:5");
            break;
          
          //Number 6 0xFF7A85
          case 0xFF7A85:
            Serial.println("Number:6");
            break;
          
          //Number 7 0xFF10EF
          case 0xFF10EF:
            Serial.println("Number:7");
            break;
          
          //Number 8 0xFF38C7
          case 0xFF38C7:
            Serial.println("Number:8");
            break;
          
          //Number 9 0xFF5AA5
          case 0xFF5AA5:
            Serial.println("Number:9");
            break;
          
          //Number 0 0xFF4AB5
          case 0xFF4AB5:
            Serial.println("Number:0");
            break;
          
          //Number * 0xFF42BD
          case 0xFF42BD:
            Serial.println("*");
            break; 
          
          //Number # 0xFF52AD
          case 0xFF52AD:
            Serial.println("#");
            break;
         }
      key_value = results.value;
      irrecv.resume(); 
  }
}