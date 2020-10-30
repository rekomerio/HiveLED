#ifndef LEDEFFECT_H
#define LEDEFFECT_H

#include <FastLED.h>
#include <array>
#include "../../../common/defines.h"

enum Param : uint8_t
{
    HUE,
    SATURATION,
    VALUE,
    SPAWN_RATE,
    BRIGHTNESS,
    ACTIVE_EFFECT,
    NEXT_FRAME_MS,
    PALETTE_OFFSET,
    SYNC_WITH_ID,
    NUM_LEDS,
    HUE_ROTATION_RATE,
    FIRE_COOLING,
    FIRE_SPARKING,

    NUM_PARAMS,
};

struct LEDParams
{
    uint8_t hue = 100;
    uint8_t saturation = 255;
    uint8_t value = 255;
    uint8_t spawnRate = 100;
    uint8_t brightness = 100;
    uint8_t activeEffect = 0;
    uint8_t nextFrameMs = 16;
    uint8_t paletteOffset = 0;
    uint8_t syncWithId = 255;
    uint8_t numLeds = 72;
    uint8_t hueRotationRate = 0;
    uint8_t fireCooling = 55;
    uint8_t fireSparking = 120;

    static constexpr uint8_t GetNumParams() { return Param::NUM_PARAMS; };
};

struct LEDHelpers
{
    uint8_t previousEffect = 0;
    uint16_t palettePosition = 0;
    uint32_t lastUpdate = 0;
    uint32_t lastHueRotation = 0;

    uint8_t heat[MAX_LEDS];
};

class LEDEffect
{
public:
    LEDEffect();
    virtual void Enter(CRGB *leds, LEDParams &params, LEDHelpers &helpers) = 0;
    virtual void Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers) = 0;
    virtual const char *GetName() = 0;
    virtual const uint8_t GetIndex() { return m_Index; };

protected:
    uint8_t m_Index;
};

/**
 * @param CLASSNAME Name of the new class to declare
 * @param NAME Display name
 * @brief Add definition of effect into LEDEffect.cpp and push the effect to a vector in MessageHandler.cpp
 */
#define DEFINE_EFFECT(CLASSNAME, NAME)                                            \
    class CLASSNAME : public LEDEffect                                            \
    {                                                                             \
        using LEDEffect::LEDEffect;                                               \
                                                                                  \
    public:                                                                       \
        void Enter(CRGB *leds, LEDParams &params, LEDHelpers &helpers) override;  \
        void Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers) override; \
        const char *GetName() override { return NAME; }                           \
    }

DEFINE_EFFECT(Confetti, "Confetti");
DEFINE_EFFECT(Rainbow, "Rainbow");
DEFINE_EFFECT(Sinelon, "Sinelon");
DEFINE_EFFECT(Bpm, "Bpm");
DEFINE_EFFECT(Juggle, "Juggle");
DEFINE_EFFECT(ColorPalette, "Color palette");
DEFINE_EFFECT(SolidColor, "Solid color");
DEFINE_EFFECT(Fire, "Fire");

#endif