#include <Servo.h>

Servo servo1;

void setup()
{
  servo1.attach(9);
  servo1.write(180);
}
void loop()
{
  servo1.write(-180);
  delay(500);
  servo1.write(180);
  delay(500);
}
