//Fill in the values below with the pins that you chose to use
const int POT_PIN = A0;
const int BUTTON_PIN = 3;

const int HOT_PIN = 11;
const int COLD_PIN = 10;
const int DRY_PIN = 12;
const int LOCK_PIN = 13;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(POT_PIN,INPUT_PULLUP);
  pinMode(HOT_PIN, OUTPUT);
  pinMode(COLD_PIN, OUTPUT);
  pinMode(DRY_PIN, OUTPUT); 
  pinMode(LOCK_PIN,OUTPUT);
}

void loop() {
  if(digitalRead(BUTTON_PIN)==0) {
    int analog = analogRead(POT_PIN);
    if((analog>450) && (analog<620)){
      deluxe();
    }else if(analog<450) {
      economy();
    }else {
      super_deluxe();
    }
  }
  delay(100);
}
void economy() {
  digitalWrite(LOCK_PIN, HIGH);
  digitalWrite(COLD_PIN, HIGH);
  delay(5000);
  digitalWrite(COLD_PIN, LOW);
  if(analogRead(POT_PIN)>450) {
    digitalWrite(DRY_PIN, HIGH);
    delay(7000);
    digitalWrite(DRY_PIN, LOW);
  }else {
    digitalWrite(DRY_PIN, HIGH);
    delay(2000);
    digitalWrite(DRY_PIN, LOW);    
  }
  digitalWrite(LOCK_PIN, LOW);
}

void deluxe() {
  digitalWrite(LOCK_PIN, HIGH);
  digitalWrite(HOT_PIN, HIGH);
  delay(7000);
  digitalWrite(HOT_PIN, LOW);
  if(analogRead(POT_PIN)<450) {
    digitalWrite(DRY_PIN, HIGH);
    delay(2000);
    digitalWrite(DRY_PIN, LOW);
  }else {
    digitalWrite(DRY_PIN, HIGH);
    delay(7000);
    digitalWrite(DRY_PIN, LOW);
  }
  digitalWrite(LOCK_PIN, LOW);
}

void super_deluxe() {
  digitalWrite(LOCK_PIN, HIGH);
  digitalWrite(HOT_PIN, HIGH);
  delay(7000);
  digitalWrite(COLD_PIN, HIGH);
  delay(7000);
  digitalWrite(COLD_PIN, LOW);
  digitalWrite(HOT_PIN, LOW);
  if(analogRead(POT_PIN)<450) {
    digitalWrite(DRY_PIN, HIGH);
    delay(2000);
    digitalWrite(DRY_PIN, LOW);
  }else {
    digitalWrite(DRY_PIN, HIGH);
    delay(7000);
    digitalWrite(DRY_PIN, LOW);
  }
  digitalWrite(LOCK_PIN, LOW);
}
