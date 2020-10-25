#include <FastLED.h>

#ifndef LEDEFFECT_H
#define LEDEFFECT_H

enum Param : uint8_t
{
    HUE,
    SATURATION,
    VALUE,
    SPAWN_RATE,
    BRIGHTNESS,
    ACTIVE_EFFECT,
    NEXT_FRAME_MS,
    PALETTE_POSITION,
    PALETTE_OFFSET,
    SYNC_WITH_ID,
    NUM_LEDS,
    LAST_UPDATE,
    NUM_PARAMS
};

struct LEDParams
{
    uint16_t hue = 100;
    uint16_t saturation = 255;
    uint16_t value = 255;
    uint16_t spawnRate = 100;
    uint16_t brightness = 255;
    uint16_t activeEffect = 0;
    uint16_t nextFrameMs = 16;
    uint16_t palettePosition = 0;
    uint16_t paletteOffset = 0;
    uint16_t syncWithId = 255;
    uint16_t numLeds = 72;
    uint32_t lastUpdate = 0;

    static constexpr uint8_t GetNumParams() { return Param::NUM_PARAMS; };
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