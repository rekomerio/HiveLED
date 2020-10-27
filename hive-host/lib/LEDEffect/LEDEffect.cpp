#include "LEDEffect.h"

LEDEffect::LEDEffect()
{
    static uint8_t instanceCounter = 0;

    m_Index = instanceCounter++;
}

void Sinelon::Enter(CRGB *leds, LEDParams &params)
{
}

void Sinelon::Update(CRGB *leds, LEDParams &params)
{
    fadeToBlackBy(leds, params.numLeds, 20);
    int pos = beatsin16(13, 0, params.numLeds - 1) + params.paletteOffset;
    leds[pos % params.numLeds] += CHSV(params.hue, params.saturation, params.value);
}

void Rainbow::Enter(CRGB *leds, LEDParams &params)
{
}

void Rainbow::Update(CRGB *leds, LEDParams &params)
{
    fill_rainbow(leds, params.numLeds, params._palettePosition + params.paletteOffset, 7);
    params._palettePosition++;
}

void Bpm::Enter(CRGB *leds, LEDParams &params)
{
}

void Bpm::Update(CRGB *leds, LEDParams &params)
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

void Juggle::Enter(CRGB *leds, LEDParams &params)
{
}

void Juggle::Update(CRGB *leds, LEDParams &params)
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

void ColorPalette::Enter(CRGB *leds, LEDParams &params)
{
}

void ColorPalette::Update(CRGB *leds, LEDParams &params)
{
    for (uint16_t i = 0; i < params.numLeds; i++)
    {
        leds[i] = ColorFromPalette(OceanColors_p, params._palettePosition + params.paletteOffset + i);
    }

    params._palettePosition++;
}

void Confetti::Enter(CRGB *leds, LEDParams &params)
{
    fill_solid(leds, params.numLeds, CRGB::Black);
}

void Confetti::Update(CRGB *leds, LEDParams &params)
{
    if (millis() - params._lastUpdate > params.spawnRate)
    {
        leds[random16(params.numLeds)] += CHSV(params.hue + random8(64), params.saturation, params.value);
        params._lastUpdate = millis();
    }

    fadeToBlackBy(leds, params.numLeds, 5);
}