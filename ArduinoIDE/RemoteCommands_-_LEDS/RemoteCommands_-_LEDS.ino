#include <IRremote.h>

//GLOBLE VARIABLES
//state
int state =0;
int var1 = 0;
int var2 = 0;

//INTERFACE 
//button pins
int KEY2 = 2;
int KEY3 = 3;

//Temp. & humidty sensor pin
int DTH = 4; 

//buzzer pin
int buzzer = 5;

//REMOTE Variables
const int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

//D7 pins - NA
//D8 pins - NA

//LED pins
int led1 = 9; //RBG - RED
int led2 = 10; //RGB - GREEN
int led3 = 11; //RGB - BLUE
int led4 = 12; //BLUE 
int led5 = 13; //RED

void setup(){
  Serial.begin(9600);

  //Swtiches
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);

  //LEDS
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT); 
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);


  //IR
  irrecv.enableIRIn();
  //irrecv.blink13(true); //Blink method for IR
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
            led_RGB_red();
            break;
          
          //Number 2 0xFF9867
          case 0xFF9867:
            Serial.println("Number:2");
            led_RGB_green();
            break;
            
          //Number 3 0xFFB04F
          case 0xFFB04F:
            Serial.println("Number:3");
            led_RGB_blue();
            break;
            
          //Number 4 0xFF30CF
          case 0xFF30CF:
            Serial.println("Number:4");
            led_blue();
            break;
          
          //Number 5 0xFF18E7
          case 0xFF18E7:
            Serial.println("Number:5");
            led_red();
            break;
          
          //Number 6 0xFF7A85
          case 0xFF7A85:
            Serial.println("Number:6");
            led_RGB_yellow();
            break;
          
          //Number 7 0xFF10EF
          case 0xFF10EF:
            Serial.println("Number:7");
            led_RGB_magneta();
            break;
          
          //Number 8 0xFF38C7
          case 0xFF38C7:
            Serial.println("Number:8");
            led_RGB_cyan();
            break;
          
          //Number 9 0xFF5AA5
          case 0xFF5AA5:
            Serial.println("Number:9");
            led_RGB_white();
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

void led_RGB_red(){
  digitalWrite(led1,HIGH);
  delay(500);
  digitalWrite(led1,LOW);
}
void led_RGB_green(){
  digitalWrite(led2,HIGH);
  delay(500);
  digitalWrite(led2,LOW);
}

void led_RGB_blue(){
  digitalWrite(led3,HIGH);
  delay(500);
  digitalWrite(led3,LOW);
}

void led_red(){
  digitalWrite(led4,HIGH);
  delay(500);
  digitalWrite(led4,LOW);
}

void led_blue(){
  digitalWrite(led5,HIGH);
  delay(500);
  digitalWrite(led5,LOW);
}

void led_RGB_yellow(){
  //RED + GREEN
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  delay(1000);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
}

void led_RGB_magneta(){
  //RED + BLUE
  digitalWrite(led1,HIGH);
  digitalWrite(led3,HIGH);
  delay(1000);
  digitalWrite(led1,LOW);
  digitalWrite(led3,LOW);
}

void led_RGB_cyan(){
  //GREEN + BLUE
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  delay(1000);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}

void led_RGB_white(){
  //GREEN + BLUE + RED
   digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  delay(1000);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}
