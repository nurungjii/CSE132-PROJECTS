/*
   FSM assignment
*/

#include <Arduino.h>
#include <Wire.h>

enum State {
  up0,
  up1,
  up2,
  up3,
  up4,
  up5,
  up6,
  up7,
  down0,
  down1,
  down2,
  down3,
  down4,
  down5,
  down6,
  down7
} state = up0;


void setup() {
  Serial.begin(9600);
}

void loop() {
  state = nextState(state);
  delay(1000);
}


State nextState(State state){
  switch(state) {
      case up0:
        Serial.println("0 : 000");
        if (checkReverse()) {
          state = down7;
          break;
        }
        else {
          state = up1;
          break;
        }
      case up1:
        Serial.println("1 : 001");
        if (checkReverse()) {
          state = down0;
          break;

        }
        else {
          state = up2;
          break;
        }
      case up2:
        Serial.println("2 : 010");
        if(checkReverse()) {
          state = down1;
          break;
        }
        else {
          state = up3;
          break;
        }
      case up3:
        Serial.println("3 : 011");
        if(checkReverse()) {
          state = down2;
          break;
        }
        else {
          state = up4;
          break;
        }
      case up4:
        Serial.println("4 : 100");
        if(checkReverse()) {
          state = down3;
          break;
        }
        else {
          state = up5;
          break;
        }
      case up5:
        Serial.println("5 : 101");
        if(checkReverse()) {
          state = down4;
          break;
        }
        else {
          state = up6;
          break;
        }
      case up6:
        Serial.println("6 : 110");
        if(checkReverse()) {
          state = down5;
          break;
        }
        else {
          state = up7;
          break;
        }
      case up7:
        Serial.println("7 : 111");
        if(checkReverse()) {
          state = down6;
          break;
        }
        else {
          state = up0;
          break;
        }
      case down0:
        Serial.println("0 : 000");
        if (checkReverse()) {
          state = up1;
          break;
        }
        else {
          state = down7;
          break;
        }
      case down1:
        Serial.println("1 : 001");
        if (checkReverse()) {
          state = up2;
          break;
        }
        else {
          state = down0;
          break;
        }
      case down2:
        Serial.println("2 : 010");
        if(checkReverse()) {
          state = up3;
          break;
        }
        else {
          state = down1;
          break;
        }
      case down3:
        Serial.println("3 : 011");
        if(checkReverse()) {
          state = up4;
          break;
        }
        else {
          state = down2;
          break;
        }
      case down4:
        Serial.println("4 : 100");
        if(checkReverse()) {
          state = up5;
          break;
        }
        else {
          state = down3;
          break;
        }
      case down5:
        Serial.println("5 : 101");
        if(checkReverse()) {
          state = up6;
          break;
        }
        else {
          state = down4;
          break;
        }
      case down6:
        Serial.println("6 : 110");
        if(checkReverse()) {
          state = up7;
          break;
        }
        else {
          state = down5;
          break;
        }
      case down7:
        Serial.println("7 : 111");
        if(checkReverse()) {
          state = up0;
          break;
        }
        else {
          state = down6;
          break;
        }
  }
  return state;
}

bool checkReverse(){

  int readThing = Serial.read();
  if(readThing != -1) {
    Serial.println("--Reverse--");
    return true;
  }
  else {
    return false;
  }
}
