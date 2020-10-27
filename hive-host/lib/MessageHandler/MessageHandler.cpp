#include "MessageHandler.h"

MessageHandler messageHandler;

MessageHandler::MessageHandler()
{
}

void MessageHandler::Init()
{
    effects.push_back(new Confetti());
    effects.push_back(new Rainbow());
    effects.push_back(new Sinelon());
    effects.push_back(new Bpm());
    effects.push_back(new Juggle());
    effects.push_back(new ColorPalette());
}

void MessageHandler::Handle(UDPMessage *message)
{
    if (message->clientId > m_Params.size())
        return;

    LEDParams &param = m_Params[message->clientId];

    if (param.syncWithId == message->clientId)
        param.syncWithId = 255; // Cant sync with itself

    if (param.syncWithId != 0xFF && param.syncWithId < MAX_CLIENTS)
        Synchronize(param, m_Params[param.syncWithId]);

    message->brightness = param.brightness;
    message->requestNextFrameMs = param.nextFrameMs;

    if (param.hueRotationRate && (uint32_t)(millis() - param._lastHueRotation) > 255U - param.hueRotationRate)
    {
        param.hue++;
        param._lastHueRotation = millis();
    }

    param.activeEffect %= effects.size();

    if (param.activeEffect != param._previousEffect)
    {
        effects[param.activeEffect]->Enter(message->leds, param);
        param._previousEffect = param.activeEffect;
    }

    effects[param.activeEffect]->Update(message->leds, param);
}

void MessageHandler::Synchronize(LEDParams &sync, LEDParams &with)
{
    sync._palettePosition = with._palettePosition;
    sync.activeEffect = with.activeEffect;
    sync.brightness = with.brightness;
}

LEDParams *MessageHandler::GetParams(uint8_t clientId)
{
    if (clientId >= m_Params.size())
        return nullptr;

    return &m_Params[clientId];
}

uint16_t &MessageHandler::GetParam(uint8_t clientId, Param param)
{
    static uint16_t fallback = 0;

    LEDParams *params = GetParams(clientId);

    if (!param)
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
        return params->paletteOffset;
    case Param::SYNC_WITH_ID:
        return params->syncWithId;
    case Param::NUM_LEDS:
        return params->numLeds;
    case Param::HUE_ROTATION_RATE:
        return params->hueRotationRate;
    }

    return fallback;
}

void MessageHandler::SetParam(uint8_t clientId, Param param, uint16_t value)
{
    GetParam(clientId, param) = value;
}