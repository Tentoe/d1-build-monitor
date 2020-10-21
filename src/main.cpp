#include <Arduino.h>
#include <string>
#include "pitches.h"

// notes in the melody:
int melody[] = {659, 622, 659, 622, 659, 494, 587, 523, 440, 262, 330, 440, 494, 330, 415, 494, 523, 330, 659, 622, 659, 622, 659, 494, 587, 523, 440, 262, 330, 440, 494, 330, 523, 494, 440 };

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

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

  for (int thisNote = 0;thisNote < (sizeof(melody) / sizeof(melody[0])); thisNote++)
  {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = noteDurations[thisNote];

    tone(D5, melody[thisNote], 120);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(120);

    // stop the tone playing:

    noTone(8);
  }
}