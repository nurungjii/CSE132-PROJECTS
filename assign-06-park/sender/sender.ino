/* 
 *  
 *  CSE 132 - Assignment 6
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name:
 *  WUSTL Key:
 *  
 *  and if two are partnered together
 *  
 *  Name: David Park
 *  WUSTL Key: 509876
 */

const int trigPin = 8;           
const int echoPin = 7;
const int potPin = A1;

const int sos = 343;
float distance = 0;

const unsigned long delta = 1000;
unsigned long previousCycle = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  if(now>=previousCycle) {
    String s = "Test";
    int lengthOfS = s.length();
    Serial.write(0x21);
    Serial.write(0x30);
    Serial.write(lengthOfS >> 8);
    Serial.write((lengthOfS<<8)>>8);
    char charBuff[lengthOfS + 1];
    s.toCharArray(charBuff, lengthOfS + 1);
    for(int i = 0; i<lengthOfS; i++) {
      Serial.write(charBuff[i]);
    }
    
    Serial.write(0x21);
    Serial.write(0x32);
    Serial.write(now>>24);
    Serial.write((now<<8)>>24);
    Serial.write((now<<16)>>24);
    Serial.write((now<<24)>>24);


    Serial.write(0x21);
    Serial.write(0x33);
    unsigned int sensorReading = analogRead(potPin);
    Serial.write(sensorReading>>8);
    Serial.write((sensorReading<<8)>>8);
    
    unsigned long echoTime;
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    echoTime = pulseIn(echoPin, HIGH);
    Serial.write(0x21);
    Serial.write(0x34);
    Serial.write(echoTime>>24);
    Serial.write((echoTime<<8)>>24);
    Serial.write((echoTime<<16)>>24);
    Serial.write((echoTime<<24)>>24);

    String error = "High Alarm";
    if(sensorReading > 512) {
      int lengthOfString = error.length();
      Serial.write(0x21);
      Serial.write(0x31);
      Serial.write(lengthOfString >> 8);
      Serial.write((lengthOfString<<8)>>8);
      char charBuf[lengthOfString + 1];
      error.toCharArray(charBuf, lengthOfString + 1);
      for(int i = 0; i<lengthOfString; i++) {
        Serial.write(charBuf[i]);
      }
    }
    
    previousCycle = now + delta;
  }
}
