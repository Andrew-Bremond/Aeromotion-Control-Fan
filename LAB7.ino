#include "Timer.h"

enum STATE {off, v_slow, slow, med, fast, v_fast} gState = off;
enum otherSTATE {ones, tens} cState = ones;
int x_joystick;
int y_joystick;
int count = 0;
char gSegPins[] = {2, 3, 4, 5, 6, 7, 8};
int x_tick = 20;
int y_tick = 20;


void displayNumTo7Seg(unsigned int targetNum, int digitPin) {
    unsigned char encodeInt[10] = {
        // 0     1     2     3     4     5     6     7     8     9
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67,
    };
    digitalWrite(digitPin, HIGH);
    for (int k = 0; k < 7; ++k) {
        digitalWrite(gSegPins[k], encodeInt[targetNum] & (1 << k));
    }
    digitalWrite(digitPin, LOW);
}

void display(void) {
  int one_digit = 0, ten_digit = 0;

  //transitions
  switch (cState) {
    case ones:
      cState = tens;
    break;
    case tens:
      cState = ones;
    break;
  }

  //actions
  switch (cState) {
    case ones:
      one_digit = count % 10;
      ten_digit = count / 10;
      digitalWrite(A1, HIGH);
      displayNumTo7Seg(one_digit, A0);
    break;
    case tens:
      one_digit = count % 10;
      ten_digit = count / 10;
      digitalWrite(A0, HIGH);
      displayNumTo7Seg(ten_digit, A1);
    break;
  }
}

void tick(void) {
  //transitions
  switch (gState) {
    case off:
      if (y_joystick < 100 && y_tick >= 40) { // up
        y_tick = 20;
        gState = v_fast;
      }
      else if (y_joystick > 900 && y_tick <= 1) { // down
        y_tick = 20;
        gState = off;
      }
      else if (x_joystick < 100 && x_tick <= 1) { // left    
        x_tick = 20;
        gState = off; //prev state
      }
      else if (x_joystick > 900 && x_tick >= 40) { // right
        x_tick = 20;
        gState = v_slow; // next state
      }
      else if (y_joystick < 100) {
        y_tick++;
      }
      else if (y_joystick > 900) {
        y_tick--;
      }
      else if (x_joystick < 100) {
        x_tick--;
      }
      else if (x_joystick > 900) {
        x_tick++;
      }
    break;
    case v_slow:
      if (y_joystick < 100 && y_tick >= 40) {
        y_tick = 20;
        gState = v_fast;
      }
      else if (y_joystick > 900 && y_tick <= 1) {
        y_tick = 20;
        gState = off;
      }
      else if (x_joystick < 100 && x_tick <= 1) {
        x_tick = 20;
        gState = off; //prev state
      }
      else if (x_joystick > 900 && x_tick >= 40) {
        x_tick = 20;
        gState = slow; // next state
      }
      else if (y_joystick < 100) {
        y_tick++;
      }
      else if (y_joystick > 900) {
        y_tick--;
      }
      else if (x_joystick < 100) {
        x_tick--;
      }
      else if (x_joystick > 900) {
        x_tick++;
      }
    break;
    case slow:
      if (y_joystick < 100 && y_tick >= 40) {
        y_tick = 20;
        gState = v_fast;
      }
      else if (y_joystick > 900 && y_tick <= 1) {
        y_tick = 20;
        gState = off;
      }
      else if (x_joystick < 100 && x_tick <= 1) {
        x_tick = 20;
        gState = v_slow; //prev state
      }
      else if (x_joystick > 900 && x_tick >= 40) {
        x_tick = 20;
        gState = med; // next state
      }
      else if (y_joystick < 100) {
        y_tick++;
      }
      else if (y_joystick > 900) {
        y_tick--;
      }
      else if (x_joystick < 100) {
        x_tick--;
      }
      else if (x_joystick > 900) {
        x_tick++;
      }
    break;
    case med:
      if (y_joystick < 100 && y_tick >= 40) {
        y_tick = 20;
        gState = v_fast;
      }
      else if (y_joystick > 900 && y_tick <= 1) {
        y_tick = 20;
        gState = off;
      }
      else if (x_joystick < 100 && x_tick <= 1) {
        x_tick = 20;
        gState = slow; //prev state
      }
      else if (x_joystick > 900 && x_tick >= 40) {
        x_tick = 20;
        gState = fast; // next state
      }
      else if (y_joystick < 100) {
        y_tick++;
      }
      else if (y_joystick > 900) {
        y_tick--;
      }
      else if (x_joystick < 100) {
        x_tick--;
      }
      else if (x_joystick > 900) {
        x_tick++;
      }
    break;
    case fast:
      if (y_joystick < 100 && y_tick >= 40) {
        y_tick = 20;
        gState = v_fast;
      }
      else if (y_joystick > 900 && y_tick <= 1) {
        y_tick = 20;
        gState = off;
      }
      else if (x_joystick < 100 && x_tick <= 1) {
        x_tick = 20;
        gState = med; //prev state
      }
      else if (x_joystick > 900 && x_tick >= 40) {
        x_tick = 20;
        gState = v_fast; // next state
      }
      else if (y_joystick < 100) {
        y_tick++;
      }
      else if (y_joystick > 900) {
        y_tick--;
      }
      else if (x_joystick < 100) {
        x_tick--;
      }
      else if (x_joystick > 900) {
        x_tick++;
      }
    break;
    case v_fast:
      if (y_joystick < 100 && y_tick >= 40) {
        y_tick = 20;
        gState = v_fast;
      }
      else if (y_joystick > 900 && y_tick <= 1) {
        y_tick = 20;
        gState = off;
      }
      else if (x_joystick < 100 && x_tick <= 1) {
        x_tick = 20;
        gState = fast; //prev state
      }
      else if (x_joystick > 900 && x_tick >= 40) {
        x_tick = 20;
        gState = v_fast; // next state
      }
      else if (y_joystick < 100) {
        y_tick++;
      }
      else if (y_joystick > 900) {
        y_tick--;
      }
      else if (x_joystick < 100) {
        x_tick--;
      }
      else if (x_joystick > 900) {
        x_tick++;
      }
    break;
  }

  //actions
  switch (gState) {
    case off:
      count = 0;
      analogWrite(11,0); //analogWrite affects speed (~60 is the threshold)
      //digitalWrite(ENABLE,0); // digitalWrite turns it on or off
    break;
    case v_slow:
      count = 1;
      analogWrite(11,62);
      // digitalWrite(ENABLE,1);
    break;
    case slow:
      count = 2;
      analogWrite(11,111);
      // digitalWrite(ENABLE,1);
    break;
    case med:
      count = 3;
      analogWrite(11,172);
      // digitalWrite(ENABLE,1);
    break;
    case fast:
      count = 4;
      analogWrite(11,222);
      // digitalWrite(ENABLE,1);
    break;
    case v_fast:
      count = 5;
      analogWrite(11,255);
      // digitalWrite(ENABLE,1);
    break;
  }
}
 
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A4, INPUT); //x_joystick input  
  pinMode(A5, INPUT); //y_joystick input
  TimerSet(10);
  TimerOn();
  Serial.begin(9600);
}

void loop() {
  //map(speed, 0, 225, 0, 5);
  x_joystick = analogRead(A4);
  y_joystick = analogRead(A5);
  display();
  tick();
  while(!TimerFlag){}
  TimerFlag = 0;
  //analogWrite(ENABLE,225); //enable on
  //digitalWrite(DIR_FORWARDS,HIGH);
}
   
