#include <Servo.h>

#define echoPin 7
#define trigPin 8

int on = -180;
int off = 180;

int lights_on = false;


long duration;
long distance;

Servo servo1;

void setup() 
{
  Serial.begin(9600);
  pinMode (echoPin, INPUT);
  pinMode (trigPin, OUTPUT);
  servo1.attach(9);
  servo1.write(off);
}


void loop() 
{
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin,LOW);

 duration = pulseIn (echoPin, HIGH);

 //This gives us distance in cm
 distance = duration/58.2;

 // print out the distance
 Serial.println (distance);



 if (distance < 10) {
  if (lights_on == false) {
    lights_on = true;
    delay(500);
  }
 }


 
 if (distance < 10) {
  if (lights_on == true) { 
   lights_on = false;
   delay(500);
  }
 }

 if (lights_on == true) {
  servo1.write(on);
 }
 if (lights_on == false) {
  servo1.write(off);
 }

 //Millisecond
 delay(50);
}
