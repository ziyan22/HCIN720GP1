int M1 = D0;
int M2 = D1;
int M3 = D2;
int M4 = D3;
int M5 = D4;
int M6 = D5;
int M7 = D6;
int M8 = D7;
int mPins[8] = {D0, D1, D2, D3, D4, D5, D6, D7};
int i;
int thisStep;
int eachStep;
int MOTOR1 = A0;
int MOTOR2 = A1;
int MOTOR3 = A2;
int MOTOR4 = A3;
int SWITCH1 = A4;


void setup()
{
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D7, OUTPUT);

  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(MOTOR3, OUTPUT);
  pinMode(MOTOR4, OUTPUT);
  // set the magnet pin to the high
  digitalWrite(D0, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);
  digitalWrite(D7, HIGH);
}

void loop()
{
  //测试是否收到信号
    if (Serial.available())
    {
       inByte = Serial.read();
       state = int(inByte);
       Serial.println(state);
       if(state == 0){
         //move(8);
       }else if( state == 1){
         //move(-8);
       }else if (state == 49){
         //turnOnMag(0);
       }else if (state == 50){
         //turnOnMag(1);
       }else if (state == 51){
         //turnOnMag(2);
       }else if (state == 52){
         turnOnMag(3);
       }else if (state == 53){
         //turnOnMag(4);
       }else if (state == 54){
         //turnOnMag(5);
       }else if (state == 55){
         //turnOnMag(6);
       }else if (state == 56){
         //turnOnMag(7);
       }else if (state == 57){
         //turnOffMag(0);
       }else if (state == 58){
         //turnOffMag(1);
       }else if (state == 59){
         //turnOffMag(2);
       }else if (state == 60){
         //turnOffMag(3);
       }else if (state == 61){
         //turnOffMag(4);
       }
       else if (state == 62){
         //turnOffMag(5);
       }
       else if (state == 63){
         //turnOffMag(6);
       }else if (state == 64){
         //turnOffMag(7);
       }
    }

    /*if (accel.available())
    {
        accel.read();
        unsigned lightSensor = analogRead(A0);
        int x = accel.x;
        float cx = accel.cx;
        int y = accel.y;
        float cy = accel.cy;
        int z = accel.z;
        float cz = accel.cz;
        int click = 0;
        //int tap= accel.readTap();
        allLight(x);
        if(digitalRead(button) == HIGH)
        {
          click = 1;
        }

        sprintf(publishString1,"{\"sensor\":%u, \"cx\":%f, \"x\":%d, \"cy\":%f, \"y\":%d, \"cz\":%f, \"z\":%d, \"click\":%d, \"state\":%d}",lightSensor,cx,x,cy,y,cz,z,click,state);
        Serial.println(publishString1);
        if(selection == 1){
          Spark.publish("everything",publishString1);
        }else{
          Spark.publish("erase",publishString1);
        }
    }*/


}

void turnOnMag(int numberOfM){
    digitalWrite(mPins[numberOfM], LOW);
}

void turnOffMag(int numberOfM){
    digitalWrite(mPins[numberOfM], HIGH);
}

int move(int steps){
  //是正的时候向上移动， 负的时候向下移动
  //负的时候向没有开关的一边移动
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
      digitalWrite(MOTOR1, HIGH);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, LOW);
      //Serial.print(500);
      break;
      case 2:
      //case 100*2:
      digitalWrite(MOTOR1, HIGH);
      digitalWrite(MOTOR2, HIGH);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, LOW);
      //Serial.print(1000);
      break;
      case 3:
      //case 100*3:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, HIGH);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, LOW);
      //Serial.print(1500);
      break;
      case 4:
      //case 100*4:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, HIGH);
      digitalWrite(MOTOR3, HIGH);
      digitalWrite(MOTOR4, LOW);
      //Serial.print(2000);
      break;
      case 5:
      //case 100*5:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, HIGH);
      digitalWrite(MOTOR4, LOW);
      //Serial.print(2500);
      break;
      case 6:
      //case 100*6:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, HIGH);
      digitalWrite(MOTOR4, HIGH);
      //Serial.print(3000);
      break;
      case 7:
      //case 100*7:
      digitalWrite(MOTOR1, LOW);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, HIGH);
      //Serial.print(3500);
      break;
      case 8:
      //case 100*8:
      digitalWrite(MOTOR1, HIGH);
      digitalWrite(MOTOR2, LOW);
      digitalWrite(MOTOR3, LOW);
      digitalWrite(MOTOR4, HIGH);
      //Serial.print(4000);
      break;
    }
    delay(2);
  }
  return 1;
}
