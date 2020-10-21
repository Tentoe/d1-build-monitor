#include <Arduino.h>
#include <string>

void setup()
{
  Serial.begin(9600);
}

int count = 0;

void loop()
{
  Serial.println(String(count));
  count++;
  delay(1000);
}