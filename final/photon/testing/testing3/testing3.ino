SYSTEM_MODE(SEMI_AUTOMATIC);
int i;
int thisStep;
int eachStep;

void setup() {
    Serial.begin(9600);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
}
void loop() {
}


void move(int steps){
  //是正的时候向上移动， 负的时候向下移动
  eachStep = 0;
  if(steps > 0){
    //向上 up
    eachStep = -1;
  }
  if(steps < 0){
    //向下 down
    eachStep = 1;
  }
  int thisStep;
  int i = 0;
  int steps_left = abs(steps);

  while(i < abs(steps)){
    i = i + 1;
    steps_left = steps_left + eachStep;
    thisStep = ( steps_left % 8 ) + 1;
    switch (thisStep) {
      case 1:
      //case 100:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      //Serial.print(500);
      break;
      case 2:
      //case 100*2:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      //Serial.print(1000);
      break;
      case 3:
      //case 100*3:
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      //Serial.print(1500);
      break;
      case 4:
      //case 100*4:
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //Serial.print(2000);
      break;
      case 5:
      //case 100*5:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //Serial.print(2500);
      break;
      case 6:
      //case 100*6:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      //Serial.print(3000);
      break;
      case 7:
      //case 100*7:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      //Serial.print(3500);
      break;
      case 8:
      //case 100*8:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      //Serial.print(4000);
      break;
    }
    delay(2);
  }
}
