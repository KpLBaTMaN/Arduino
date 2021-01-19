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

//Variables
int buzzerControl = 1;
int buzzerIncrement = 1; //using for frz sound change - delay
int buzzerState = 0; //buzzerStateControl - set off default

//Variables for LEDs
int RED_LED_STATE = 0;
int GREEN_LED_STATE = 0;
int BLUE_LED_STATE = 0;

//Variable for controlling RBG lights
int colorControlVal =0;
int toggle_var_rainbowColours = 0;



/*
//RBG Variables
int RED_COLOUR_ANALOG = 0;
int GREEN_COLOUR_ANALOG = 0;
int BLUE_COLOUR_ANALOG = 0;

//VALUE
int RGB_INCREMENT_VALUE = 8;
int RED_COLOUR_ANALOG_VALUE = 0;
*/

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

  //BUZZER
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,HIGH);


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
            buzzer_up();
            break;
            
          //Button left 0xFF22DD
          case 0xFF22DD:
            Serial.println("Left");
            //analog_remote_left();
            colorControlVal-=1;
            break;
            
          //Button right 0xFFC23D
          case 0xFFC23D:
            Serial.println("Right");
            //analog_remote_right();
            colorControlVal+=1;
            break;
            
          //Button down 0xFFA857
          case 0xFFA857:
            Serial.println("Down");
            buzzer_down();
            break;
            
          //Button OK 0xFF02FD
          case 0xFF02FD:
            Serial.println("OK");
            toggle_buzzer();
            break;
          
          //Number 1 0xFF6897
          case 0xFF6897:
            Serial.println("Number:1");
            toggle_red_led();
            break;
          
          //Number 2 0xFF9867
          case 0xFF9867:
            Serial.println("Number:2");
             toggle_green_led();
            break;
            
          //Number 3 0xFFB04F
          case 0xFFB04F:
            Serial.println("Number:3");
            toggle_blue_led();
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
            toggle_rainbowColours();
            break;
          
          //Number * 0xFF42BD
          case 0xFF42BD:
            Serial.println("*");
           // redColourCange();
            break;
          
          //Number # 0xFF52AD
          case 0xFF52AD:
            Serial.println("#");
            testLoop();
            break;
           //PHONE FRONT 0xDBC8CB72
           case 0xDBC8CB72:
              Serial.println("PHONE");
              break;
         }
      key_value = results.value;
      irrecv.resume(); 
  }
  //Test methods
  //analog();
  //Light();
  LM35();

  //Run methods
  buzzer_play();
  display_led_RBG();
  //analogColour();
  rainbowColours();
}

void testLoop(){

  for(int i = 0; i <= 255; i+=5){
    setColour(i,0,0);
    delay(10);
    Serial.println(i);
  }
  for(int i = 255; i >= 0; i-=5){
    setColour(i,0,0);
    delay(10);
    Serial.println(i);
  }
  for(int i = 0; i <= 255; i+=5){
    setColour(0,i,0);
    delay(10);
    Serial.println(i);
  }
  for(int i = 255; i >= 0; i-=5){
    setColour(0,i,0);
    delay(10);
    Serial.println(i);
  }
  /*
  for(int i = 0; i <= 255; i+=5){
    setColour(0,0,i);
    delay(10);
    Serial.println(i);
  }
  for(int i = 255; i >= 0; i-=5){
    setColour(0,0,i);
    delay(10);
    Serial.println(i);
  }
  */
}



/*
void testLoop(){
  for(int index = 0; index < 255; index++){
    setColour(index,index,index);
    delay(10);
    Serial.println(index);
  }
  for(int index = 255; index > 0; index++){
    setColour(index,index,index);
    delay(100);
    Serial.println(index);
  }
}
*/
//Press 0 project - light project 
//Pressing 0 will go analog from red on, red off, green on, green off, blue on, blue off
void rainbowColours(){
  if(toggle_var_rainbowColours == 1){
    
    //Loop for states
    if(colorControlVal<0){
    colorControlVal=7;
    }
    if(colorControlVal>7){
      colorControlVal=0;
    }
    
    if(colorControlVal == 0){
       //Show none
       RED_LED_STATE = 0;
       GREEN_LED_STATE = 0;
       BLUE_LED_STATE = 0;   
    }else if (colorControlVal == 1){
      //Show red
      RED_LED_STATE = 1;
      GREEN_LED_STATE = 0;
      BLUE_LED_STATE = 0;
      
    }else if (colorControlVal == 2){
      //show green
      RED_LED_STATE = 0;
      GREEN_LED_STATE = 1;
      BLUE_LED_STATE = 0;
    }else if(colorControlVal == 3){
      //show blue
      RED_LED_STATE = 0;
      GREEN_LED_STATE = 0;
      BLUE_LED_STATE = 1;
    }else if(colorControlVal == 4){
      //show red + green = yellow
      RED_LED_STATE = 1;
      GREEN_LED_STATE = 1;
      BLUE_LED_STATE = 0;
    }else if(colorControlVal == 5){
      //show red + blue = Magenta
      RED_LED_STATE = 1;
      GREEN_LED_STATE = 0;
      BLUE_LED_STATE = 1;
    }else if(colorControlVal == 6){
      //show green + blue = cyan
      RED_LED_STATE = 0;
      GREEN_LED_STATE = 1;
      BLUE_LED_STATE = 1;
    }else if(colorControlVal == 7){
      //show red + green + blue = white
      RED_LED_STATE = 1;
      GREEN_LED_STATE = 1;
      BLUE_LED_STATE = 1;
    }
    
  }
}

void toggle_rainbowColours(){
  if(toggle_var_rainbowColours==1){
    toggle_var_rainbowColours = 0;
  } else{
    toggle_var_rainbowColours = 1;
  }
}

//buzzer control
void buzzer_play(){
  if(buzzerState == 1){
    digitalWrite(buzzer,LOW);// sound
    delay(buzzerControl);//delay 
    digitalWrite(buzzer,HIGH);//not sound
    delay(buzzerControl);//delay 
  }
}

void toggle_buzzer(){
  if(buzzerState==1){
    buzzerState = 0;
  } else{
    buzzerState = 1;
  }
}

void buzzer_up(){
  buzzerControl -= buzzerIncrement;
  if(buzzerControl <= 0){
    buzzerControl =1;
  }
}

void buzzer_down(){
  buzzerControl += buzzerIncrement;
  if(buzzerControl >= 20){
    buzzerControl =20;
  }
}

void toggle_red_led(){
  if(RED_LED_STATE==1){
    RED_LED_STATE = 0;
  } else{
    RED_LED_STATE = 1;
  }
}

void toggle_green_led(){
  if(GREEN_LED_STATE==1){
    GREEN_LED_STATE = 0;
  } else{
    GREEN_LED_STATE = 1;
  }
}

void toggle_blue_led(){
  if(BLUE_LED_STATE==1){
    BLUE_LED_STATE = 0;
  } else{
    BLUE_LED_STATE = 1;
  }
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

void display_led_RBG(){
  display_led_RBG_red();
  display_led_RBG_green();
  display_led_RBG_blue();
}

void display_led_RBG_red(){
  if(RED_LED_STATE==1){
    digitalWrite(led1,HIGH);
  }else {
    digitalWrite(led1,LOW);
  }
}
void display_led_RBG_green(){
  if(GREEN_LED_STATE==1){
    digitalWrite(led2,HIGH);
  }else {
    digitalWrite(led2,LOW);
  }
}
void display_led_RBG_blue(){
  if(BLUE_LED_STATE==1){
    digitalWrite(led3,HIGH);
  }else {
    digitalWrite(led3,LOW);
  }
}

void analog()
{
  int val;
  val=analogRead(A0);
  Serial.println(val);
}

void Light()
{
int val;
val=analogRead(A1);
Serial.println(val);
}

void LM35()
{
int val;
val=analogRead(A2);
Serial.println(val);
}


void setColour_red(int red){
  analogWrite(led1, red);
}

void setColour(int red, int green, int blue){
  analogWrite(led1, red);
  analogWrite(led2, green);
  analogWrite(led3, blue);
}

/*
void analog_remote_right(){
  RED_COLOUR_ANALOG_VALUE +=RGB_INCREMENT_VALUE;
}
void analog_remote_left(){
  RED_COLOUR_ANALOG_VALUE -=RGB_INCREMENT_VALUE;
}

// analogRead values go from 0 to 1023, analogWrite values from 0 to 255
void analogColour(){
  if(RED_COLOUR_ANALOG_VALUE >=255){
    RED_COLOUR_ANALOG_VALUE = 255;
  }
  if(RED_COLOUR_ANALOG_VALUE<=0){
    RED_COLOUR_ANALOG_VALUE = 0;
  }
  setColour(RED_COLOUR_ANALOG_VALUE, GREEN_COLOUR_ANALOG, BLUE_COLOUR_ANALOG);
}
*/
