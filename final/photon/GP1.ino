#include <stdio.h>
#include <stdlib.h>
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
int j;
int thisStep;
int eachStep;
int MOTOR1 = A0;
int MOTOR2 = A1;
int MOTOR3 = A2;
int MOTOR4 = A3;
int SWITCH1 = A4;
char inByte = 'D';
int state = 100;

int forChecking = 3;


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
  pinMode(SWITCH1, INPUT);

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

  Spark.function("newDue1",increaseM1);
  Spark.function("newDue2",increaseM2);
  Spark.function("newDue3",increaseM3);
}

void loop()
{
  //测试是否收到信号
    if (Serial.available())
    {
       inByte = Serial.read();
       state = int(inByte);
       Serial.println(state);
       if(state == 81){
         move(896);    //全长12560
       }else if( state == 87){
         move(-896);
       }else if (state == 97){
         turnOnMag(0);
       }else if (state == 115){
         turnOnMag(1);
       }else if (state == 100){
         turnOnMag(2);
       }else if (state == 102){
         turnOnMag(3);
       }else if (state == 103){
         turnOnMag(4);
       }else if (state == 104){
         turnOnMag(5);
       }else if (state == 106){
         turnOnMag(6);
       }else if (state == 107){
         turnOnMag(7);
       }else if (state == 65){
         turnOffMag(0);
       }else if (state == 83){
         turnOffMag(1);
       }else if (state == 68){
         turnOffMag(2);
       }else if (state == 70){
         turnOffMag(3);
       }else if (state == 71){
         turnOffMag(4);
       }
       else if (state == 72){
         turnOffMag(5);
       }
       else if (state == 74){
         turnOffMag(6);
       }else if (state == 75){
         turnOffMag(7);
       }else if(state == 79){
           pattern1(7);
       }else if(state == 73){
           patternForRemoving1(7);
       }
    }
}


void pattern1(int hights){
    i = 0;
    j = hights;
    //digitalWrite(mPins[0], LOW);
    for ( j = hights; j > 1; j = j - 2 ){
        for( i = 0; i < j - 1; i = i + 1 ){
            // could change the pattern
            // change the number
            digitalWrite(mPins[0+i], LOW);
            digitalWrite(mPins[1+i], LOW);
            digitalWrite(mPins[2+i], LOW);
            //改变时间
            //-- 固定时间， 每次都改变时间，越来越长
            delay(1000);
            digitalWrite(mPins[0+i], HIGH);
            delay(1000);
            digitalWrite(mPins[1+i], HIGH);
            delay(1000);
            digitalWrite(mPins[2+i], HIGH);
            delay(1000);
        }
    }
}

void patternForRemoving1(int hights){
    //digitalWrite(mPins[0], LOW);
    int realhights = 7;
    // if(hights){
    //     realhights = hights;
    // }
    int i = 0;
    int j = 0;
    for ( j = realhights; j > 1; j = j - 2 ){
        for( i = j; i > 0; i = i - 1 ){
            // could change the pattern
            // change the number

            digitalWrite(mPins[i], LOW);
            digitalWrite(mPins[i-1], LOW);
            // digitalWrite(mPins[i-2], LOW);
            //改变时间
            //-- 固定时间， 每次都改变时间，越来越长
            delay(500);
            digitalWrite(mPins[i], HIGH);
            delay(5000);
            if(i == 1){
                digitalWrite(mPins[i-1], HIGH);
                delay(5000);
                Serial.println("here");
                continue;
            }
            digitalWrite(mPins[i-1], HIGH);
            delay(500);
            // digitalWrite(mPins[i-2], HIGH);
            // delay(500);
        }
    }

}

void turnOnMag(int numberOfM){
    digitalWrite(mPins[numberOfM], LOW);
}


void turnOffMag(int numberOfM){
    digitalWrite(mPins[numberOfM], HIGH);
}


void moveBack(){
    //not sure if could digital read
    while(digitalRead(SWITCH1) == 0){
        move(8);
    }
    // move to 1 place
    move(-896*2);
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

//when this function is in the waiting mode, the forMn will change to 1;
int forM1 = 0;
int forM2 = 0;
int forM3 = 0;
char x[256];
int days;
int leftDays1 = 0;
int leftDays2 = 0;
int leftDays3 = 0;


int increaseM1(String command) {
     //when the forChecking == 3, will run the increaseM1, otherwise this function won't run.
     //when the forChecking != 3, means other increase function still running
    if(forChecking != 3){
        Serial.print("not running 1");
        Serial.print("\n");
    }else{
        forChecking = 0;
        Serial.print("running 1");
        Serial.print("\n");
        //update left date
        strcpy(x, command.c_str());
        days = atoi(x);
        Serial.print("1 original day is ");
        Serial.print(leftDays1);
        Serial.print("\n");
        Serial.print("1 need day is ");
        Serial.print(days);
        Serial.print("\n");
        if(leftDays1 != days){

            leftDays1 = days;
            //run motor
            moveBack();
            move(-80);
            //run magnet
            pattern1(leftDays1 / 2);
            Serial.print("1 lefting days are different");
            Serial.print("\n");
            delay(5000);
        }

        forChecking = 1;
        Serial.print("finishing 1");
        Serial.print("\n");
    }
}

int increaseM2(String command) {

    if(forChecking != 1){
        Serial.print("not running 2");
        Serial.print("\n");
    }else{
        forChecking = 0;
        Serial.print("running 2");
        Serial.print("\n");

        strcpy(x, command.c_str());
        days = atoi(x);
        Serial.print("2 original day is ");
        Serial.print(leftDays2);
        Serial.print("\n");
        Serial.print("2 need day is ");
        Serial.print(days);
        Serial.print("\n");

        if(leftDays2 != days){
            leftDays2 = days;
            //run motor
            moveBack();
            move(-896*5);

            //run magnet
            pattern1(leftDays2 / 2);
            Serial.print("2 lefting days are different");
            Serial.print("\n");
            delay(5000);
        }

        forChecking = 2;
        Serial.print("finishing 2");
        Serial.print("\n");
    }
}

int increaseM3(String command) {

    if(forChecking != 2){
        Serial.print("not running 3");
        Serial.print("\n");
    }else{
        forChecking = 0;
        Serial.print("running 3");
        Serial.print("\n");


        strcpy(x, command.c_str());
        days = atoi(x);
        Serial.print("3 original day is ");
        Serial.print(leftDays3);
        Serial.print("\n");
        Serial.print("3 need day is ");
        Serial.print(days);
        Serial.print("\n");
        if(leftDays3 != days){
            leftDays3 = days;
            //run motor
            moveBack();
            move(-896*10-640);
            //run magnet
            pattern1(leftDays3 / 2);
            Serial.print("3 lefting days are different");
            Serial.print("\n");
            delay(5000);
        }

        forChecking = 3;
        Serial.print("finishing 3");
        Serial.print("\n");
    }
}
