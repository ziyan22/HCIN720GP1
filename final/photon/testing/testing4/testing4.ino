SYSTEM_MODE(SEMI_AUTOMATIC);
int M1 = D0;
int M2 = D1;
int M3 = D2;
int M4 = D3;
int M5 = D4;
int M6 = D5;
int M7 = D6;
int M8 = D7;
int mPins[8] = [D0, D1, D2, D3, D4, D5, D6, D7]

void setup() {
  Serial.begin(9600);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(M5, OUTPUT);
  pinMode(M6, OUTPUT);
  pinMode(M7, OUTPUT);
  pinMode(M8, OUTPUT);
  // set the magnet pin to the high
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, HIGH);
  digitalWrite(M5, HIGH);
  digitalWrite(M6, HIGH);
  digitalWrite(M7, HIGH);
  digitalWrite(M8, HIGH);
}

void loop() {
}
int numberOfM = 8;
int everyMhole = 2; // 一个磁铁控制几个洞
int allHoles = everyMhole * numberOfM;  //一共有多少个格子来表示这些星期
int weeks = 4; // 最后可以有多少个星期在里面， 最终用day来表示
int maForweek = numberOfM / weeks
int secondsForOneWeek = 60 * 60 * 24 * 7;
int delayForLeftDays = 2000; // !!!!!!!!!!!!!!!!!!!!!!!!!testing

int allInLineInterval = 2000; //!!!!!!!!!!!!!!!!!!!!!!!!!!!testing
int allInDecreaseInterval = 2000; //!!!!!!!!!!!!!!!!!!!!!!!!!!!testing

void removeCurrent(){
  //delay for making sure that every hole is beening bandded
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
  digitalWrite(M5, LOW);
  digitalWrite(M6, LOW);
  digitalWrite(M7, LOW);
  digitalWrite(M8, LOW);
  delay(allInLineInterval);

  //release one by one to make sure all will be attracted by rest of hole
  digitalWrite(M1, HIGH);
  delay(allInDecreaseInterval);
  digitalWrite(M2, HIGH);
  delay(allInDecreaseInterval);
  digitalWrite(M3, HIGH);
  delay(allInDecreaseInterval);
  digitalWrite(M4, HIGH);
  delay(allInDecreaseInterval);
  digitalWrite(M5, HIGH);
  delay(allInDecreaseInterval);
  digitalWrite(M6, HIGH);
  delay(allInDecreaseInterval);
  digitalWrite(M7, HIGH);
  delay(allInDecreaseInterval);
  digitalWrite(M8, HIGH);
  delay(allInDecreaseInterval);
}

int secondToM(int seconds){
  int minutes = seconds / 60;
  int hours = minutes / 60;
  int days = hours / 24;
  int weeks = days / 7;
  int ma = weeks * maForweek;
  return ma;
}

/*void newOneStart(int seconds){
  removeCurrent(); //如果可以知道当前的就不需要这样了
  int sureM = secondToM(seconds);
  int leftDays = (seconds / 60 / 60 / 24) % 7;
  int i = 0;
  for (i = 0; i < sureM; i++){
    digitalWrite(mPins[i], LOW);
  }

  //to process the last few days
  digitalWrite(mPins[sureM],LOW);
  delay(delayForLeftDays);
  for (i = 0; i <= sureM; i++){
    digitalWrite(mPins[i], HIGH);
  }
}*/
