

#include "HID-Project.h"
// input pins for encoder channel A and channel B
int pinA = 2;
int pinB = 3;

// input pin for pushbutton
int pinButton = 4;

volatile bool previousButtonValue = false;

volatile int previous = 0;
volatile int counter = 0;

const int count[] = {1,0,6,7,8,9};

void keydown();

void setup() {
  pinMode(pinA, INPUT_PULLUP); 
  pinMode(pinB, INPUT_PULLUP);
  pinMode(pinButton, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), changed, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), changed, CHANGE);

  for (int i = 0; i < 3; i++) {
     pinMode(count[i], INPUT_PULLUP);//打开芯片内部上拉电阻
  }
  for (int j = 3; j < 6; j++) {
     pinMode(count[j], OUTPUT);
     digitalWrite(count[j], LOW);//按键按下,读到的逻辑电平为低
  }
  Serial.begin(9600);
  Keyboard.begin();//测试时直接按下0-F
  
  SurfaceDial.begin();
}

void changed() {
  int A = digitalRead(pinA); 
  int B = digitalRead(pinB);

  int current = (A << 1) | B;
  int combined  = (previous << 2) | current;
   
  if(combined == 0b0010 || 
     combined == 0b1011 ||
     combined == 0b1101 || 
     combined == 0b0100) {
    counter++;
  }
   
  if(combined == 0b0001 ||
     combined == 0b0111 ||
     combined == 0b1110 ||
     combined == 0b1000) {
    counter--;
  }

  previous = current;
}

void loop(){ 
  bool buttonValue = digitalRead(pinButton);
  if(buttonValue != previousButtonValue){
    if(buttonValue) {
      SurfaceDial.press();
    } else {
      SurfaceDial.release();
    }    
    previousButtonValue = buttonValue;
  }

  if(counter >= 4) {
    SurfaceDial.rotate(50);
    counter -= 4;
  } else if(counter <= -4) {
    SurfaceDial.rotate(-50);
    counter += 4;
  } 
  
  for (int j = 3; j < 6; j++) {
    digitalWrite(count[j], LOW);
  }
  if((digitalRead(1)*digitalRead(0)*digitalRead(6))==0)
  {
     for (int j = 3; j < 6; j++) {
          digitalWrite(count[j], HIGH);
     }
    keydown();
  }  
}

void keydown(){
  //开始检测第一列
    digitalWrite(9, LOW);
    if(digitalRead(1)==0){//正面看按键3按下
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      Keyboard.releaseAll();
      delay(500);
      }
    if(digitalRead(0)==0){//正面看按键6按下
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('3');
      Keyboard.releaseAll();
      delay(500);
      }
    if(digitalRead(6)==0){//正面看按键9按下
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_DELETE);
      Keyboard.press('y');
      Keyboard.releaseAll();
      delay(500);
      }

//开始检测第二列
   digitalWrite(9, HIGH);//此列已经检测过了
   digitalWrite(8, LOW);
    if(digitalRead(1)==0){//正面看按键2按下
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press('c');
       Keyboard.releaseAll();
       delay(500);
      }  
    if(digitalRead(0)==0){//正面看按键5按下
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press(KEY_LEFT_ALT);
       Keyboard.press('2');
       Keyboard.releaseAll();
       delay(500);
      }
    if(digitalRead(6)==0){//正面看按键8按下
       Keyboard.press(KEY_LEFT_GUI);
       Keyboard.press('d');
       Keyboard.releaseAll();
       delay(500);
      }

 //开始检测第三列  
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    if(digitalRead(1)==0){//正面看按键1按下
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press('s');
       Keyboard.releaseAll();
       delay(500);
      }  
    if(digitalRead(0)==0){//正面看按键4按下
       Keyboard.press(KEY_LEFT_CTRL);
       Keyboard.press(KEY_LEFT_ALT);
       Keyboard.press('1');
       Keyboard.releaseAll();
       delay(500);
      }
    if(digitalRead(6)==0){//正面看按键7按下
       Keyboard.press(KEY_LEFT_GUI);
       Keyboard.press('r');
       Keyboard.releaseAll();
       delay(500);
      }
    
    Keyboard.releaseAll(); 
}