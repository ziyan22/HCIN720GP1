SYSTEM_MODE(SEMI_AUTOMATIC);
int i;
int thisStep;
void setup() {
    Serial.begin(9600);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
}
void loop() {
  i = i + 1;
  thisStep = ( i % 8 ) + 1;
  if( i < 9924 ){
    switch (thisStep) {    //---up
      case 8:
      //case 100:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      //Serial.print(500);
      break;
      case 7:
      //case 100*2:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      //Serial.print(1000);
      break;
      case 6:
      //case 100*3:
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      //Serial.print(1500);
      break;
      case 5:
      //case 100*4:
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //Serial.print(2000);
      break;
      case 4:
      //case 100*5:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      //Serial.print(2500);
      break;
      case 3:
      //case 100*6:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      //Serial.print(3000);
      break;
      case 2:
      //case 100*7:
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      //Serial.print(3500);
      break;
      case 1:
      //case 100*8:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      //Serial.print(4000);
      break;
    }
  }

  if(i >= 9924 && i < 19848){    //----down

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
  }

  if(i >= 19848){
    i = 0;
  }

  delay(2);
  Serial.print(i);
  Serial.print(",");
}

/*void move(){}*/
