#include <FastLED.h>

#ifndef LEDEFFECTS
#define LEDEFFECTS

struct LEDParams
{
    uint8_t hue = 100;
    uint8_t spawnRate = 100;
    uint8_t brightness = 255;
    uint8_t activeEffect = 0;
    uint8_t nextFrameMs = 16;
    uint8_t palettePosition = 0;
    uint8_t paletteOffset = 0;
    uint8_t syncWithId = 255;
    uint16_t numLeds = 72;
    uint32_t lastUpdate = 0;
};

class LEDEffects
{
public:
    LEDEffects();
    void Update(CRGB *leds);
    LEDParams params;

private:
    void Confetti();
    void Rainbow();
    void Sinelon();
    void Bpm();
    void Juggle();
    void ColorPalette();

    CRGB *leds;
};

#endif