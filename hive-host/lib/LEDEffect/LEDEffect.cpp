#include "LEDEffect.h"

LEDEffect::LEDEffect()
{
}

void LEDEffect::Update(CRGB *leds)
{
    this->leds = leds;

    switch (params.activeEffect)
    {
    case 0:
        ColorPalette();
        break;
    case 1:
        Confetti();
        break;
    case 2:
        Sinelon();
        break;
    case 3:
        Rainbow();
        break;
    case 4:
        Bpm();
        break;
    case 5:
        Juggle();
        break;
    default:
        params.activeEffect = 0;
        break;
    }
}

void LEDEffect::Confetti()
{

    if (millis() - params.lastUpdate > params.spawnRate)
    {
        leds[random16(params.numLeds)] += CHSV(params.hue + random8(64), 200, 255);
        params.lastUpdate = millis();
    }

    fadeToBlackBy(leds, params.numLeds, 5);
}

void LEDEffect::Sinelon()
{
    fadeToBlackBy(leds, params.numLeds, 20);
    int pos = beatsin16(13, 0, params.numLeds - 1) + params.paletteOffset;
    leds[pos % params.numLeds] += CHSV(params.hue, 255, 192);
}

void LEDEffect::Rainbow()
{
    fill_rainbow(leds, params.numLeds, params.hue, 7);
}

void LEDEffect::Bpm()
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < params.numLeds; i++)
    {
        leds[i] = ColorFromPalette(palette, params.hue + (i * 2), beat - params.paletteOffset + (i * 10));
    }
}

void LEDEffect::Juggle()
{
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(leds, params.numLeds, 20);
    byte dothue = 0;
    for (int i = 0; i < 8; i++)
    {
        leds[beatsin16(i + 7, 0, params.numLeds - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}

void LEDEffect::ColorPalette()
{
    for (uint16_t i = 0; i < params.numLeds; i++)
    {
        leds[i] = ColorFromPalette(OceanColors_p, params.palettePosition + params.paletteOffset + i);
    }

    params.palettePosition++;
}