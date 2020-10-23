#include <Arduino.h>

class Music
{
public:
    static const int BUZZER_PIN = D5;
    static void playCoin()
    {
        playSong({{987, 75}, {1318, 225}});
    }
    static void play1UP()
    {
        playSong({{659, 125}, {783, 125}, {1318, 125}, {1046, 125}, {1174, 125}, {1567, 125}});
    }
    static void playHall()
    {
        playSong({{246, 250}, {277, 250}, {293, 250}, {329, 250}, {369, 250}, {293, 250}, {369, 500}, {349, 250}, {277, 250}, {349, 500}, {329, 250}, {261, 250}, {329, 500}, {246, 250}, {277, 250}, {293, 250}, {329, 250}, {369, 250}, {293, 250}, {369, 250}, {493, 250}, {440, 250}, {369, 250}, {293, 250}, {369, 250}, {440, 1000}});
    }
    static void playFanfare()
    {
        playSong({{0, 75}, {0, 37}, {261, 131}, {329, 93}, {391, 150}, {523, 150}, {659, 150}, {783, 300}, {659, 300}, {0, 75}, {0, 37}, {261, 131}, {329, 93}, {391, 150}, {523, 150}, {659, 150}, {830, 300}, {659, 300}, {0, 75}, {0, 37}, {293, 131}, {349, 93}, {493, 150}, {587, 150}, {698, 150}, {987, 300}, {987, 150}, {987, 150}, {987, 150}, {1046, 600}});
    }
    static void playFuneral()
    {
        playSong({{493, 500}, {493, 375}, {493, 125}, {493, 500}, {587, 375}, {523, 125}, {523, 375}, {493, 125}, {493, 375}, {493, 125}, {493, 1000}});
    }

private:
    static void playSong(std::vector<std::vector<int>> song)
    {
        for (unsigned int note = 0; note < song.size(); note++)
        {
            int noteDuration = song[note][1];
            tone(BUZZER_PIN, song[note][0], noteDuration);
            delay(noteDuration);
            noTone(BUZZER_PIN);
        }
    }
};
