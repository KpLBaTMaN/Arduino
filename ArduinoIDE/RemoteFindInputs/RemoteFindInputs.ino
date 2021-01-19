#include <IRremote.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

const int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}

//REMOTE CASES
//Button up 0xFF629D
//Button left 0xFF22DD
//Button right 0xFFC23D
//Button down 0xFFA857
//Button OK 0xFF02FD

//Number 1 0xFF6897
//Number 2 0xFF9867
//Number 3 0xFFB04F
//Number 4 0xFF30CF
//Number 5 0xFF18E7
//Number 6 0xFF7A85
//Number 7 0xFF10EF
//Number 8 0xFF38C7
//Number 9 0xFF5AA5
//Number 0 0xFF4AB5
//Number * 0xFF42BD
//Number # 0xFF52AD
