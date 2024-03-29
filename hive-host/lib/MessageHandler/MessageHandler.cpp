#include "MessageHandler.h"

MessageHandler messageHandler;

MessageHandler::MessageHandler()
{
    clients = nullptr;
}

void MessageHandler::Init()
{
    effects.push_back(new SolidColor());
    effects.push_back(new ColorPalette());
    effects.push_back(new NoisePalette());
    effects.push_back(new Rainbow());
    effects.push_back(new Confetti());
    effects.push_back(new Sinelon());
    effects.push_back(new Bpm());
    effects.push_back(new Juggle());
    effects.push_back(new Fire());
    effects.push_back(new Droplets());

    memset(m_LastChangeAt.data(), 0, sizeof(uint32_t) * m_LastChangeAt.size());

    EEPROM.begin(EEPROM_SIZE_BYTES);
}

void MessageHandler::Handle(UDPMessage *message)
{
    uint8_t clientId = message->clientId;

    if (clientId >= m_Params.size())
        return;

    LEDParams &param = m_Params[clientId];
    LEDHelpers &helper = m_Helpers[clientId];

    if (param.syncWithId == clientId)
        param.syncWithId = 255; // Cant sync with itself

    if (param.syncWithId != 255 && param.syncWithId < MAX_CLIENTS)
        Synchronize(param, helper, m_Params[param.syncWithId], m_Helpers[param.syncWithId]);

    message->brightness = param.powerState ? param.brightness : 0;
    message->requestNextFrameMs = param.nextFrameMs;

    if (param.hueRotationRate && (uint32_t)(millis() - helper.lastHueRotation) > 255U - param.hueRotationRate)
    {
        param.hue++;
        helper.lastHueRotation = millis();
    }

    param.activePalette %= hiveColorPaletteCount;
    param.activeEffect %= effects.size();

    // Exit old method and enter the new one if they have changed
    if (param.activeEffect != helper.previousEffect)
    {
        effects[helper.previousEffect]->Exit(message->leds, param, helper);
        effects[param.activeEffect]->Enter(message->leds, param, helper);
        helper.previousEffect = param.activeEffect;
    }

    // Save changes if there are some and last change has been done 30 seconds ago or more
    if (m_LastChangeAt[clientId] && (uint32_t)(millis() - m_LastChangeAt[clientId]) > 30000)
    {
        SaveChangesEEPROM(clientId);
        m_LastChangeAt[clientId] = 0;
    }

    effects[param.activeEffect]->Update(message->leds, param, helper);
}

void MessageHandler::Synchronize(LEDParams &pSync, LEDHelpers &hSync, LEDParams &pWith, LEDHelpers hWith)
{
    pSync.speed = pWith.speed;
    pSync.brightness = pWith.brightness;
    pSync.activeEffect = pWith.activeEffect;
    pSync.activePalette = pWith.activePalette;
    hSync.palettePosition = hWith.palettePosition;
    pSync.hueRotationRate = pWith.hueRotationRate;
    pSync.brightnessBreatheRate = pWith.brightnessBreatheRate;
    pSync.brightnessBreatheScale = pWith.brightnessBreatheScale;
}

LEDParams *MessageHandler::GetParams(uint8_t clientId)
{
    if (clientId >= m_Params.size())
        return nullptr;

    return &m_Params[clientId];
}

uint8_t &MessageHandler::GetParam(uint8_t clientId, Param param)
{
    static uint8_t fallback = 0;

    LEDParams *params = GetParams(clientId);

    if (params == nullptr)
        return fallback;

    switch (param)
    {
    case Param::HUE:
        return params->hue;
    case Param::SATURATION:
        return params->saturation;
    case Param::VALUE:
        return params->value;
    case Param::SPAWN_RATE:
        return params->spawnRate;
    case Param::BRIGHTNESS:
        return params->brightness;
    case Param::ACTIVE_EFFECT:
        return params->activeEffect;
    case Param::NEXT_FRAME_MS:
        return params->nextFrameMs;
    case Param::PALETTE_OFFSET:
        return params->offset;
    case Param::SYNC_WITH_ID:
        return params->syncWithId;
    case Param::NUM_LEDS:
        return params->numLeds;
    case Param::HUE_ROTATION_RATE:
        return params->hueRotationRate;
    case Param::FIRE_COOLING:
        return params->fireCooling;
    case Param::FIRE_SPARKING:
        return params->fireSparking;
    case Param::ACTIVE_PALETTE:
        return params->activePalette;
    case Param::POWER_STATE:
        return params->powerState;
    case Param::BRIGHTNESS_BREATHE_RATE:
        return params->brightnessBreatheRate;
    case Param::BRIGHTNESS_BREATHE_SCALE:
        return params->brightnessBreatheScale;
    case Param::SPEED:
        return params->speed;
    case Param::ACCELERATION:
        return params->acceleration;
    }

    return fallback;
}

void MessageHandler::SetParam(uint8_t clientId, Param param, uint8_t value)
{
    GetParam(clientId, param) = value;
    m_LastChangeAt[clientId] = millis();
}