SYSTEM_MODE(SEMI_AUTOMATIC);
int i = 0;
int thisStep;
void setup() {
    Serial.begin(9600);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
}
void loop() {
  digitalWrite(D0, LOW);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  delay(1000);
  digitalWrite(D0, HIGH);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  delay(1000);
}
