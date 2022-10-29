#include"MorseCodes.h"

//var assignment
const int led = 7;
char readin;
char nextChar;

int sPos = 0;
String total = "";

enum State {
  dotOn,
  dotOff,
  dashOn,
  dashOff,
  spaceOff,
  pause,
  wait
}state = wait;

//make character uppercase
char toUpper(char c) {
  char up = 223;
  if ((c>=65 && c<=90) || (c>=97 && c<=122)) {
    c = c & up;
  }
  return c;
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}


void convertIncomingCharsToMorseCode() {
  if(Serial.available() > 0) {
    
    //read string from input
    readin = Serial.read();

    //convert all char in arr to upper
    readin = toUpper(readin);

    //convert char to morseCode
    String morse;
    if(readin == 32) {
      morse += morseEncode(32);
      morse += morseEncode(32);
    }else {
      morse = morse + morseEncode(readin) + ' ';
    }
    total += morse;

    //convert string to array of chars
    int morse_length = morse.length() + 1;
    char morse_array[morse_length];
    morse.toCharArray(morse_array, morse_length);
    for(int i = 0; i<morse_length - 1; i++) {
      Serial.print(morse_array[i]);
    }
    Serial.println();
  }
}


void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
  convertIncomingCharsToMorseCode();
  state = nextState(state);

}

char getNextChar() {
  if(sPos < total.length()) {
    if(total.charAt(sPos) == ' ') {
      if(sPos + 2 < total.length()) {
        if((total.charAt(sPos + 1) == ' ') && (total.charAt(sPos + 2) == ' ')) {
//          sPos += 3;
          return 'e';
        }
//        sPos += 1;
        return ' ';
      }
    }else if(total.charAt(sPos) == '.') {
//      sPos += 1;
      return '.';   
    }else {
//      sPos += 1;
      return '-';
    }
  }
}

boolean nextIsNothing() {
  if(total.length() == 0) {
    return true;
  }else if(sPos > total.length()) {
    return true;
  }
  return false;
}

unsigned long dotOffPeriod = 0;
unsigned long dashOffPeriod = 0;
unsigned long pausePeriod = 0;
unsigned long dashOnPeriod = 0;
unsigned long dotOnPeriod = 0;
unsigned long spaceOffPeriod = 0;

State nextState(State state) {
  unsigned long now = millis();
  boolean what = nextIsNothing();
  //Serial.println(what);
  if(what) {
    return state ;
  }else {
    nextChar = getNextChar();
    //Serial.print(total);
    //state = dotOff;
  }

  switch(state) {
    case dotOn:
      if(now >= dotOffPeriod) {
        digitalWrite(led, LOW);
        if(nextChar == ' ') {
          pausePeriod = now + 500;
          sPos += 1;
          state = pause;
        }else if(nextChar =='-') {
          dashOnPeriod = now + 500;
          sPos += 1;
          state = dashOff;
        }else if(nextChar == '.') {
          dotOnPeriod = now + 500;
          sPos += 1;
          state = dotOff;
        }else if(nextChar == 'e'){
          spaceOffPeriod = now + 500;
          sPos += 3;
          state = spaceOff;
        }
      }
      break;
    case dotOff:
      if(now >= dotOnPeriod) {
        digitalWrite(led, HIGH);
        dotOffPeriod = now + 500;
        state = dotOn;
        //Serial.println("dot");
      }
      break;
    case dashOn:
      if(now >= dashOffPeriod) {
        digitalWrite(led, LOW);
        if(nextChar == ' ') {
          sPos += 1;
          pausePeriod = now;
          state = pause;
        }else if(nextChar =='-') {
          dashOnPeriod = now + 500;
          sPos += 1;
          state = dashOff;
        }else if(nextChar == '.') {
          dotOnPeriod = now + 500;
          sPos += 1;
          state = dotOff;
        }else if(nextChar == 'e'){
          spaceOffPeriod = now + 500;
          sPos += 3;
          state = spaceOff;
        }
      }
      break;
    case dashOff:
      if(now >= dashOnPeriod) {
        digitalWrite(led, HIGH);
        dashOffPeriod = now + 1500;
        state = dashOn;
        //Serial.println("dash");
      }
      break;
    case pause:
      if(now >= pausePeriod) {
        digitalWrite(led, LOW);
        //Serial.println("pause");
        if(nextChar =='-') {
          dashOnPeriod = now + 1000;
          sPos += 1;
          state = dashOff;
        }else if(nextChar == '.') {
          dotOnPeriod = now + 1000;
          sPos += 1;
          state = dotOff;
        }else if(nextChar == 'e'){
          spaceOffPeriod = now + 1000;
          sPos += 3;
          state = spaceOff;
        }
      }
      break;
      
     case spaceOff:
      if(now >= spaceOffPeriod) {
        digitalWrite(led, LOW);
        if(nextChar == ' ') {
          sPos += 1;
          pausePeriod = now + 3000;
          state = pause;
        }else if(nextChar =='-') {
          dashOnPeriod = now + 3000;
          sPos += 1;
          state = dashOff;
        }else if(nextChar == '.') {
          dotOnPeriod = now + 3000;
          sPos += 1;
          state = dotOff;
        }else if(nextChar == 'e'){
          spaceOffPeriod = now + 3000;
          sPos += 3;
          state = spaceOff;
        }
      }
     break;
    case wait:
      if(nextChar == ' ') {
          sPos += 1;
          state = pause;
        }else if(nextChar =='-') {
          sPos += 1;
          state = dashOff;
        }else if(nextChar == '.') {
          sPos += 1;
          state = dotOff;
        }else if(nextChar == 'e'){
          sPos += 3;
          state = spaceOff;
        }
      break;
  }
  if(what) {
    return wait;
  }else {
    nextChar = getNextChar();
    //Serial.print(nextChar);
    //state = dotOff;
  }
  return state;
}
