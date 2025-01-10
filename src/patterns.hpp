#include "globals.hpp"

CRGB colors[] = {CRGB(255, 0, 0), CRGB(0, 255, 0), CRGB(0, 0, 255)};

void colors_in_out()
{
    static int colorIndex = 0;

    static int t = 0;
    static int d = 1;
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds[i] = CRGB(0, 0, 0);
    }

    for (int j = 0; j < t; j++)
    {
        leds[j] = colors[colorIndex % 3];
    }

    if (t >= LED_COUNT)
    {
        d = -1;
    }
    else if (t <= 0)
    {
        d = 1;
        colorIndex++;
    }

    t += d;
}

void rainbow()
{
    static int c = 0;
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds[i] = CHSV((c / 3) % 255, 255, 150);
    }
    c++;
}

void rainbowoffsync(float speed = 1, float segment_size = 3)
{
    static int c = 0;
    for (int i = 0; i < LED_COUNT; i++)
    {
        leds[i] = CHSV(int(((c + i) / segment_size) / (1 / speed)) % 255, 255, 120);
    }
    c++;
}