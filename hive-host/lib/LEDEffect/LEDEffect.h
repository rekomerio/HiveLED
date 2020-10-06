#include <FastLED.h>

#ifndef LEDEFFECT_H
#define LEDEFFECT_H

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

enum Effect
{
    CONFETTI,
    RAINBOW,
    SINELON,
    BPM,
    JUGGLE,
    COLORPALETTE
};

class LEDEffect
{
public:
    LEDEffect(uint8_t index);
    virtual void Update(CRGB *leds, LEDParams &params) = 0;
    virtual const char *GetName() { return ""; };
    virtual const uint8_t GetIndex() { return m_Index; };
    virtual const char *GetParams() = 0;

protected:
    uint8_t m_Index;
};

#define DEFINE_EFFECT(CLASSNAME, NAME)                       \
    class CLASSNAME : public LEDEffect                       \
    {                                                        \
        using LEDEffect::LEDEffect;                          \
                                                             \
    public:                                                  \
        void Update(CRGB *leds, LEDParams &params) override; \
        const char *GetName() override { return NAME; }      \
        const char *GetParams() override;                    \
    }

DEFINE_EFFECT(Confetti, "Confetti");
DEFINE_EFFECT(Rainbow, "Rainbow");
DEFINE_EFFECT(Sinelon, "Sinelon");
DEFINE_EFFECT(Bpm, "Bpm");
DEFINE_EFFECT(Juggle, "Juggle");
DEFINE_EFFECT(ColorPalette, "Color palette");

#endif