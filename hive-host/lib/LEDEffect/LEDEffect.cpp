#include "LEDEffect.h"

LEDEffect::LEDEffect()
{
    static uint8_t instanceCounter = 0;

    m_Index = instanceCounter++;
}

void Sinelon::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    fadeToBlackBy(leds, params.numLeds, 20);
    int pos = beatsin16(13, 0, params.numLeds - 1) + params.paletteOffset;
    leds[pos % params.numLeds] += CHSV(params.hue, params.saturation, params.value);
}

void Rainbow::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    fill_rainbow(leds, params.numLeds, helpers.palettePosition + params.paletteOffset, 7);
    helpers.palettePosition++;
}

void Bpm::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
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

void Juggle::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
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

void ColorPalette::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    CRGBPalette16 palette = hiveColorPalettes[params.activePalette];
    for (uint16_t i = 0; i < params.numLeds; i++)
    {
        leds[i] = ColorFromPalette(palette, helpers.palettePosition + params.paletteOffset + i);
    }

    helpers.palettePosition++;
}

void Confetti::Enter(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    fill_solid(leds, params.numLeds, CRGB::Black);
}

void Confetti::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    if (millis() - helpers.lastUpdate > params.spawnRate)
    {
        leds[random16(params.numLeds)] += CHSV(params.hue + random8(64), params.saturation, params.value);
        helpers.lastUpdate = millis();
    }

    fadeToBlackBy(leds, params.numLeds, 5);
}

void SolidColor::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    fill_solid(leds, params.numLeds, CHSV(params.hue, params.saturation, params.value));
}

void SolidColor::Exit(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    params.brightnessBreatheRate = 0;
    params.brightnessBreatheScale = 0;
}

void Fire::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    for (uint8_t i = 0; i < params.numLeds; i++)
    {
        helpers.heat[i] = qsub8(helpers.heat[i], random8(0, ((params.fireCooling * 10) / params.numLeds) + 2));
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (uint8_t k = params.numLeds - 1; k >= 2; k--)
    {
        helpers.heat[k] = (helpers.heat[k - 1] + helpers.heat[k - 2] + helpers.heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (random8() < params.fireSparking)
    {
        uint8_t y = random8(7);
        helpers.heat[y] = qadd8(helpers.heat[y], random8(160, 255));
    }

    // Step 4.  Map from heat cells to LED colors
    for (uint8_t j = 0; j < params.numLeds; j++)
    {
        // Scale the heat value from 0-255 down to 0-240
        // for best results with color palettes.
        uint8_t colorIndex = scale8(helpers.heat[j], 240);
        CRGB color = ColorFromPalette(
            CRGBPalette16(
                CRGB::Black,
                CHSV(params.hue, params.saturation, params.value),
                CHSV(params.hue + 60, params.saturation, params.value),
                CHSV(params.hue + 60, qsub8(params.saturation, 120), params.value)),
            colorIndex);

        uint8_t pixelNumber;

        if (false) // Reverse direction
            pixelNumber = (NUM_LEDS - 1) - j;
        else
            pixelNumber = j;

        leds[pixelNumber] = color;
    }
}