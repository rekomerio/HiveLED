#include "LEDEffect.h"

LEDEffect::LEDEffect()
{
    static uint8_t instanceCounter = 0;

    m_Index = instanceCounter++;
}

void Sinelon::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    fadeToBlackBy(leds, params.numLeds, 20);
    int pos = beatsin16(13, 0, params.numLeds - 1) + params.offset;
    leds[pos % params.numLeds] += CHSV(params.hue, params.saturation, params.value);
}

void Rainbow::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    fill_rainbow(leds, params.numLeds, helpers.palettePosition + params.offset, 7);
    helpers.palettePosition++;
}

void Bpm::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    const uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < params.numLeds; i++)
    {
        leds[i] = ColorFromPalette(palette, params.hue + (i * 2), beat - params.offset + (i * 10));
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
        leds[i] = ColorFromPalette(palette, helpers.palettePosition + params.offset + i);
    }

    helpers.palettePosition++;
}

void NoisePalette::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    CRGBPalette16 palette = hiveColorPalettes[params.activePalette];
    for (uint16_t i = 0; i < params.numLeds; i++)
    {
        leds[i] = ColorFromPalette(
            palette,
            helpers.palettePosition + params.offset + i,
            max(map(inoise8(i * params.numLeds, helpers.noiseOffset), 0, 255, -100, 255), 0L));
    }

    if (params.speed != 0 && (uint32_t)(millis() - helpers.lastUpdate) > max(255U - params.speed, 5U) * 5U)
    {
        helpers.palettePosition++;
        helpers.lastUpdate = millis();
    }
    helpers.noiseOffset += 2;
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
    uint8_t value = params.value;

    if (params.brightnessBreatheRate && params.brightnessBreatheScale && params.powerState)
    {
        value = beatsin8(
            params.brightnessBreatheRate,
            value - (uint8_t)(params.brightnessBreatheScale * ((float)value / 255.0f)),
            value);
    }

    fill_solid(leds, params.numLeds, CHSV(params.hue, params.saturation, value));
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

void Droplets::Enter(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    fill_solid(leds, params.numLeds, CRGB::Black);
    
    for (uint8_t i = 0; i < helpers.particles.size(); i++)
    {
        helpers.particles[i].isAlive = false;
    }
}

void Droplets::Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers)
{
    fadeToBlackBy(leds, params.numLeds, 160);

    // 65000 >> 32000 >> 16000 >> 8000
    bool spawnDroplet = (random16() >> 3) < params.spawnRate;

    for (uint8_t i = 0; i < helpers.particles.size(); i++)
    {
        Particle& particle = helpers.particles[i];

        if (!particle.isAlive && spawnDroplet)
        {
            spawnDroplet = false;
            particle.isAlive = true;
            particle.position = 0.0f;
            particle.velocity = 0.005f + (float)((random8() >> 2)) * 0.01f;
            // Add slight offset of hue to get more colorful droplets. Offset having value between 0 - 16
            particle.hue = random8() & 0xf;
        }

        if (particle.isAlive)
        {
            // Magic number
            particle.velocity += params.acceleration * 0.00005f; // TODO: Could account for framerate
            particle.position += particle.velocity;
            
            if (particle.position > params.numLeds)
            {
                particle.isAlive = false;
            } 
            else
            {
                leds[params.numLeds - 1 - static_cast<uint8_t>(particle.position)] = CHSV(params.hue + particle.hue, params.saturation, params.value);
            }
        }
    }
}