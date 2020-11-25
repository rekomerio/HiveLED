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
 * Effects field is left empty, if the parameter is already implemented in the UI
 */
struct LEDParams
{
    // @Name: Hue
    // @Range: 0-255
    uint8_t hue = 100;
    // @Name: Saturation
    // @Range: 0-255
    uint8_t saturation = 255;
    // @Name: Value
    // @Range: 0-255
    uint8_t value = 255;
    // @Name: Spawn rate
    // @Range: 0-255
    // @Effects: ["Confetti"]
    uint8_t spawnRate = 100;
    // @Name: Brightness
    // @Range: 0-255
    uint8_t brightness = 100;
    // @Name: Active effect
    // @Range: 0-255
    uint8_t activeEffect = 0;
    // @Name: Next frame ms
    // @Range: 16-255
    uint8_t nextFrameMs = 16;
    // @Name: Offset
    // @Range: 0-255
    // @Effects: ["Color palette", "Sinelon", "Rainbow", "Bpm"]
    uint8_t offset = 0;
    // @Name: Sync with id
    // @Range: 0-255
    uint8_t syncWithId = 255;
    // @Name: Num LED's
    // @Range: 0-150
    uint8_t numLeds = 72;
    // @Name: Hue rotation rate
    // @Range: 0-255
    uint8_t hueRotationRate = 0;
    // @Name: Fire cooling
    // @Range: 20-100
    // @Effects: ["Fire"]
    uint8_t fireCooling = 55;
    // @Name: Fire sparking
    // @Range: 50-200
    // @Effects: ["Fire"]
    uint8_t fireSparking = 120;
    // @Name: Active palette
    // @Range: 0-255
    uint8_t activePalette = 0;
    // @Name: Power state
    // @Range: 0-1
    uint8_t powerState = 1;
    // @Name: Brightness breathe rate
    // @Range: 0-250
    // @Effects: ["Solid color"]
    uint8_t brightnessBreatheRate = 0;
    // @Name: Brightness breathe scale
    // @Range: 0-255
    // @Effects: ["Solid color"]
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