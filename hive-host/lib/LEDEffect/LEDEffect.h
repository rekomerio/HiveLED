#ifndef LEDEFFECT_H
#define LEDEFFECT_H

#include <FastLED.h>
#include <array>
#include "ColorPalettes.h"
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
    ACTIVE_PALETTE,
    POWER_STATE,
    BRIGHTNESS_BREATHE_RATE,
    BRIGHTNESS_BREATHE_SCALE,

    NUM_PARAMS,
};

/**
 * Name, min-max, names of effects that use the parameter
 * Leave the last field empty, if the parameter is already implement in the UI
 */
struct LEDParams
{
    // Hue, 0-255
    uint8_t hue = 100;
    // Saturation, 0-255
    uint8_t saturation = 255;
    // Value, 0-255
    uint8_t value = 255;
    // Spawn rate, 0-255, ["Confetti"]
    uint8_t spawnRate = 100;
    // Brightness, 0-255
    uint8_t brightness = 100;
    // Active effect, 0-255
    uint8_t activeEffect = 0;
    // Next frame ms, 16-255
    uint8_t nextFrameMs = 16;
    // Palette offset, 0-255
    uint8_t paletteOffset = 0;
    // Sync with id, 0-255
    uint8_t syncWithId = 255;
    // Num LED's, 0-150
    uint8_t numLeds = 72;
    // Hue rotation rate, 0-255
    uint8_t hueRotationRate = 0;
    // Fire cooling, 20-100, ["Fire"]
    uint8_t fireCooling = 55;
    // Fire sparking, 50-200, ["Fire"]
    uint8_t fireSparking = 120;
    // Active palette, 0-255
    uint8_t activePalette = 0;
    // Power state, 0-1
    uint8_t powerState = 1;
    // Brightness breathe rate, 0-250, ["Solid color"]
    uint8_t brightnessBreatheRate = 0;
    // Brightness breathe scale, 0-255, ["Solid color"]
    uint8_t brightnessBreatheScale = 0;

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
    virtual void Enter(CRGB *leds, LEDParams &params, LEDHelpers &helpers){};
    virtual void Exit(CRGB *leds, LEDParams &params, LEDHelpers &helpers){};
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
        void Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers) override; \
        const char *GetName() override { return NAME; }                           \
    }

class Confetti : public LEDEffect
{
    using LEDEffect::LEDEffect;

public:
    void Enter(CRGB *leds, LEDParams &params, LEDHelpers &helpers) override;
    void Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers) override;
    const char *GetName() override { return "Confetti"; }
};

class SolidColor : public LEDEffect
{
    using LEDEffect::LEDEffect;

public:
    void Exit(CRGB *leds, LEDParams &params, LEDHelpers &helpers) override;
    void Update(CRGB *leds, LEDParams &params, LEDHelpers &helpers) override;
    const char *GetName() override { return "Solid color"; }
};

DEFINE_EFFECT(Rainbow, "Rainbow");
DEFINE_EFFECT(Sinelon, "Sinelon");
DEFINE_EFFECT(Bpm, "Bpm");
DEFINE_EFFECT(Juggle, "Juggle");
DEFINE_EFFECT(ColorPalette, "Color palette");
DEFINE_EFFECT(Fire, "Fire");

extern const TProgmemRGBGradientPalettePtr hiveColorPalettes[];
extern const uint8_t hiveColorPaletteCount;

#endif