#include"MorseCodes.h"

//var assignment
const int led = 13;
char readin;

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
  
}
