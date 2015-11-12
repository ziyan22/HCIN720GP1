SYSTEM_MODE(SEMI_AUTOMATIC);
int i = 0;
int thisStep;
int motor_pin_1 = D0;
int motor_pin_2 = D1;
int motor_pin_3 = D2;
int motor_pin_4 = D3;

void setup() {
    Serial.begin(9600);
    pinMode(motor_pin_1, OUTPUT);
    pinMode(motor_pin_2, OUTPUT);
    pinMode(motor_pin_3, OUTPUT);
    pinMode(motor_pin_4, OUTPUT);
}
void loop() {
  i = i + 1;
  thisStep = i % 4;
  switch (thisStep) {
    case 0:    // 1010
    digitalWrite(motor_pin_1, HIGH);
    digitalWrite(motor_pin_2, LOW);
    digitalWrite(motor_pin_3, LOW);
    digitalWrite(motor_pin_4, LOW);
    break;
    case 1:    // 0110
    digitalWrite(motor_pin_1, LOW);
    digitalWrite(motor_pin_2, HIGH);
    digitalWrite(motor_pin_3, LOW);
    digitalWrite(motor_pin_4, LOW);
    break;
    case 2:    //0101
    digitalWrite(motor_pin_1, LOW);
    digitalWrite(motor_pin_2, LOW);
    digitalWrite(motor_pin_3, HIGH);
    digitalWrite(motor_pin_4, LOW);
    break;
    case 3:    //1001
    digitalWrite(motor_pin_1, LOW);
    digitalWrite(motor_pin_2, LOW);
    digitalWrite(motor_pin_3, LOW);
    digitalWrite(motor_pin_4, HIGH);
    break;
  }
    delay(20);
}
