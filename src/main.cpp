#include <Arduino.h>
#include <string>
#include "Music.cpp"

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial.begin");
  Music::playCoin();
  delay(1000);
  Music::playFuneral();
  delay(1000);
  Music::play1UP();
  delay(1000);
  Music::playHall();
  delay(1000);
  Music::playFanfare();
}

int count = 0;

void loop()
{
  Serial.println(String(count));
  count++;
  delay(1000);
}
