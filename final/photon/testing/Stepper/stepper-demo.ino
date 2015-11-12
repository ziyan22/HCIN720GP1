//Includes
SYSTEM_MODE(SEMI_AUTOMATIC);
#include "Stepper.h"
#include "math.h"

//Defines
//#define STEPS 200
//#define ADCwidth 12
//#define ADCsteps pow(2, ADCwidth)
//#define maxSpeed 256 //RPM (for test, using max LED value 255)

//Stepper stepper1(STEPS, D0, D1, D2, D3);
Stepper stepper1(200, D1, D2, D3, D4);

//int potPin = A0;
//int ledPin = D5;
//int potVal = 0;
uint8_t speed = 0;

void setup() {
    Serial.begin(9600);
    //pinMode(potPin, INPUT);
    //pinMode(ledPin, OUTPUT); //LED brightness correlates to motor speed
    stepper1.setSpeed(10);
}

void loop() {
    //potVal = analogRead(potPin);
    //speed = floor(potVal/(ADCsteps/maxSpeed));
    //analogWrite(ledPin, speed);
    //stepper1.setSpeed(100);
    stepper1.step(1);
    /*display();*/
}

void display() {
    /*Serial.print("Pot Val: ");
    Serial.print(potVal);
    Serial.print(" | ");
    Serial.print("Speed: ");*/
    //Serial.println(speed);
}
