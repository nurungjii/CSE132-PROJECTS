void setup() {
  
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(~5);
  //Test:
  Serial.println();
  Serial.print("shiftRight(5,1) should return 2:          ");
  Serial.println(shiftRight(5,1));
  Serial.print("shiftRight(7,4) should return 0:          ");
  Serial.println(shiftRight(7,4));

  Serial.println();
  Serial.print("shiftLeft(5,2) should return 20:          ");
  Serial.println(shiftLeft(5,2));
  Serial.print("shiftLeft(-1,1) should return -2:        ");
  Serial.println(shiftLeft(-1,1));

  Serial.println();
  Serial.print("hasAOne(4) should return 1:               ");
  Serial.println(hasAOne(4));
  Serial.print("hasAOne(0) should return 0:               ");
  Serial.println(hasAOne(0));

  Serial.println();
  Serial.print("hasAZero(5) should return 1:              ");
  Serial.println(hasAZero(5));
  Serial.print("hasAZero(-1) should return 0:             ");
  Serial.println(hasAZero(-1));
    
  Serial.println();
  Serial.print("leastSigByteHasAOne(254) should return 1:     ");
  Serial.println(leastSigByteHasAOne(254));
  Serial.print("leastSigByteHasAOne(256) should return 0:     ");
  Serial.println(leastSigByteHasAOne(256));

  Serial.println();
  Serial.print("isNegativeInt(-500) should return 1:      ");
  Serial.println(isNegativeInt(-500));
  Serial.print("isNegativeInt(500) should return 0:       ");
  Serial.println(isNegativeInt(500));

  Serial.println();
  Serial.print("isNegativeLong(-40000) should return 1:   ");
  Serial.println(isNegativeLong(-40000));
  Serial.print("isNegativeLong(40000) should return 0:    ");
  Serial.println(isNegativeLong(40000));

  Serial.println();
  Serial.print("isNegativeChar(-5) should return 1:       ");
  Serial.println(isNegativeChar(-5));
  Serial.print("isNegativeChar(1) should return 0:        ");
  Serial.println(isNegativeChar(1));

  Serial.println();
  Serial.print("negate(-500) should return 500:           ");
  Serial.println(negate(-500));
  Serial.print("negate(500) should return -500:          ");
  Serial.println(negate(500));


}

//
unsigned shiftRight(unsigned num, int n){
  return num>>n;
}

int shiftLeft(int num, int n){
  return num<<n;
}

// Fix the following functions, using only the bitwise and Boolean operators
int hasAOne(int num) {
  return num&&num;
}

int hasAZero(int num) {
  return ~num&&~num;
}

//Note this is refering to the least significant BYTE, not single BIT.
int leastSigByteHasAOne(int num) {
  return hasAOne((num<<8)>>8);
}

int isNegativeInt(int num) {
  return hasAOne(num>>15);
}

int isNegativeLong(long num) {
  return hasAOne(num>>31);
}

int isNegativeChar(char num) {
  return hasAOne(num>>7);
}

int negate(int num) {
  return ~(num-1);
}
