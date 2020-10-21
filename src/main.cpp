#include <Arduino.h>
#include <string>
#include "pitches.h"

const int BUZZER_PIN = D5;

std::vector<std::vector<int>> axel = {
    {329, 500},
    {391, 375},
    {329, 250},
    {329, 125},
    {440, 250},
    {329, 250},
    {293, 250},
    {329, 500},
    {493, 375},
    {329, 250},
    {329, 125},
    {523, 250},
    {493, 250},
    {391, 250},
    {329, 250},
    {493, 250},
    {659, 250},
    {329, 125},
    {293, 250},
    {293, 125},
    {246, 250},
    {369, 250},
    {329, 250}};

void playSong(std::vector<std::vector<int>>  song)
{
  for (unsigned int note = 0; note < song.size(); note++)
  {
    int noteDuration = song[note][1];
    tone(BUZZER_PIN, song[note][0], noteDuration);
    delay(noteDuration);
    noTone(BUZZER_PIN);
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial.begin");
}

int count = 0;

void loop()
{
  Serial.println(String(count));
  count++;
  delay(1000);
  playSong(axel);
}
