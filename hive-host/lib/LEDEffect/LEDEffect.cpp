#include "LEDEffect.h"

LEDEffect::LEDEffect(uint8_t index)
{
    m_Index = index;
}

void Sinelon::Update(CRGB *leds, LEDParams &params)
{
    fadeToBlackBy(leds, params.numLeds, 20);
    int pos = beatsin16(13, 0, params.numLeds - 1) + params.paletteOffset;
    leds[pos % params.numLeds] += CHSV(params.hue, params.saturation, params.value);
}

const char *Sinelon::GetParams()
{
    return "none";
}

void Rainbow::Update(CRGB *leds, LEDParams &params)
{
    fill_rainbow(leds, params.numLeds, params.palettePosition + params.paletteOffset, 7);
    params.palettePosition++;
}

const char *Rainbow::GetParams()
{
    return "none";
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

const char *Bpm::GetParams()
{
    return "none";
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

const char *Juggle::GetParams()
{
    return "none";
}

void ColorPalette::Update(CRGB *leds, LEDParams &params)
{
    for (uint16_t i = 0; i < params.numLeds; i++)
    {
        leds[i] = ColorFromPalette(OceanColors_p, params.palettePosition + params.paletteOffset + i);
    }

    params.palettePosition++;
}

const char *ColorPalette::GetParams()
{
    return "none";
}

void Confetti::Update(CRGB *leds, LEDParams &params)
{
    if (millis() - params.lastUpdate > params.spawnRate)
    {
        leds[random16(params.numLeds)] += CHSV(params.hue + random8(64), params.saturation, params.value);
        params.lastUpdate = millis();
    }

    fadeToBlackBy(leds, params.numLeds, 5);
}

const char *Confetti::GetParams()
{
    return "none";
}
