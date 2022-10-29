/* cricket
 *  
 *  CSE 132 - Assignment 3
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: David Park
 *  WUSTL Key: d.park@wustl.edu
 *  
 *  and if two are partnered together
 *  
 *  Name:
 *  WUSTL Key:
 */
const int tempSensor = A1;
const int LED = 7;

const unsigned long cyclePeriod = 250;
unsigned long nextCycle = 0;
const unsigned long blinkDuration = 200; //off
unsigned long nextBlinkCycle = 0; // off
unsigned long blinkPeriod = 0;
unsigned long nextBlinkPeriod = 0;

float temp;
float rAvg;

const int FILTER_COUNTS = 8;
float tempSet[FILTER_COUNTS];
unsigned int count = 0;
unsigned int count2 = 1;
float fluctSum = 0;
float holder = 0;

enum State {
  Blink,
  stopBlink
}state = stopBlink;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tempSensor, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  analogReference(INTERNAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  if(now >= nextCycle) {
    readTemp();
    rollingAvg();
    Serial.print("temp: ");
    Serial.print(temp);
    Serial.print("          avg: ");
    Serial.println(rAvg);
    //Serial.println(blinkPeriod);
    nextCycle = now + cyclePeriod;
  }
  blinkPeriod = 1/((((rAvg-10)*7)+40)/60000); 
  state = nextState(state);
}

State nextState(State state) {
  unsigned long now = millis();
  switch(state) {
    case Blink:
      if(now >= nextBlinkPeriod) {
        //Serial.println("off");
        digitalWrite(LED, LOW);
        nextBlinkCycle = now + blinkDuration;
        state = stopBlink;
        
      }
      break;
    case stopBlink:
      if(now >= nextBlinkCycle) {
        //Serial.println("on");
        digitalWrite(LED, HIGH);
        nextBlinkPeriod = now + blinkPeriod;
        
        state = Blink;
      }
      break;
  }
  return state;
}

void readTemp() {
    int rawCount = analogRead(tempSensor);
    //Serial.print("Raw Count: ");
    //Serial.println(rawCount);
    float volt = rawCount*0.001;
    //Serial.print("Voltage: ");
    //Serial.println(volt);
    temp = 25+((volt-0.750)*100);
    tempSet[count % FILTER_COUNTS] = temp;
    count += 1;
    
}

void rollingAvg() {
  if(count2<=8) {
    fluctSum += temp;
    holder = tempSet[0];
  }else {
    fluctSum -= holder;
    fluctSum += temp;
    holder = tempSet[count2%FILTER_COUNTS];
  }
  
  count2 += 1;
  if(count2 <= 8) {
    rAvg = fluctSum/(count2-1);
  }else {
    rAvg = fluctSum/FILTER_COUNTS;
  }
}
