//REMOTE CONTROL PROJECT


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

//IR receiver
int IR = 6;

//D7 pins - NA
//D8 pins - NA

//LED pins
int led1 = 9; //RBG - RED
int led2 = 10; //RGB - GREEN
int led3 = 11; //RGB - BLUE
int led4 = 12; //BLUE 
int led5 = 13; //RED


void setup() {
  Serial.begin(9600);

  //irrecv.enableIRIn(); // Start the receiver

  //attachInterrupt(0, falling0, FALLING);
  //attachInterrupt(1, falling1, FALLING);

  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,HIGH);

  //LEDS
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT); 
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);

  //Swtiches
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  
  //for(char i=9;i<14;i++)
   //digitalWrite(i,LOW);

}



void loop() {


 // buzzer_();
  // put your main code here, to run repeatedly:
  var1 = digitalRead(KEY2);
  var2 = digitalRead(KEY3);

  if(var1 ==1){
    state = 1;
  }

  if(var2 == 1){
    state = 0;
  }

  if(state==1){
    led_display();
  }

  if(state ==0){
    if(state==0){
    //turn off all leds
     digitalWrite(led1,LOW);
     digitalWrite(led2,LOW);
     digitalWrite(led3,LOW);
     digitalWrite(led4,LOW);
     digitalWrite(led5,LOW);
   }
  }
}


void led_display()
{
   digitalWrite(led1,HIGH);
   delay(500);
   digitalWrite(led1,LOW);
   digitalWrite(led2,HIGH);
   delay(500);
   digitalWrite(led2,LOW);
   digitalWrite(led3,HIGH);
   delay(500);
   digitalWrite(led3,LOW);
   digitalWrite(led4,HIGH);
   delay(500);
   digitalWrite(led4,LOW);
   digitalWrite(led5,HIGH);
   delay(500);
   digitalWrite(led5,LOW);
}


void buzzer_(void)
{
 char i;  
 for(i=0;i<80;i++)// output a frequency sound
 { 
  digitalWrite(buzzer,LOW);// sound
  delay(1);//delay1ms 
  digitalWrite(buzzer,HIGH);//not sound
  delay(1);//ms delay 
 } 
 for(i=0;i<100;i++)// output a frequency sound
 { 
  digitalWrite(buzzer,LOW);// sound
  digitalWrite(buzzer,HIGH);//not sound
  delay(2);//2ms delay 
 }
}
