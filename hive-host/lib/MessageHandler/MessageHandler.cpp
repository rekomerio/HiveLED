#include "MessageHandler.h"

MessageHandler::MessageHandler()
{
}

void MessageHandler::Init()
{
    uint8_t i = 0;
    effects.push_back(new Confetti(i++));
    effects.push_back(new Rainbow(i++));
    effects.push_back(new Sinelon(i++));
    effects.push_back(new Bpm(i++));
    effects.push_back(new Juggle(i++));
    effects.push_back(new ColorPalette(i++));
}

void MessageHandler::Handle(UDPMessage *message)
{
    if (message->clientId > params.size())
        return;

    LEDParams &param = params[message->clientId];

    if (param.syncWithId == message->clientId)
        param.syncWithId = 255; // Cant sync with itself

    if (param.syncWithId != 0xFF && param.syncWithId < MAX_CLIENTS)
        Synchronize(param, params[param.syncWithId]);

    message->brightness = param.brightness;
    message->requestNextFrameMs = param.nextFrameMs;

    param.activeEffect %= effects.size();

    effects[param.activeEffect]->Update(message->leds, param);
}

void MessageHandler::Synchronize(LEDParams &sync, LEDParams &with)
{
    sync.palettePosition = with.palettePosition;
    sync.activeEffect = with.activeEffect;
    sync.brightness = with.brightness;
}

LEDParams *MessageHandler::GetParams(uint8_t clientId)
{
    return &params[clientId];
}

uint16_t &MessageHandler::GetParam(uint8_t clientId, Param param)
{
    static uint16_t fallback = 0;

    switch (param)
    {
    case Param::HUE:
        return GetParams(clientId)->hue;
    case Param::SPAWN_RATE:
        return GetParams(clientId)->spawnRate;
    case Param::BRIGHTNESS:
        return GetParams(clientId)->brightness;
    case Param::ACTIVE_EFFECT:
        return GetParams(clientId)->activeEffect;
    case Param::NEXT_FRAME_MS:
        return GetParams(clientId)->nextFrameMs;
    case Param::PALETTE_POSITION:
        return GetParams(clientId)->palettePosition;
    case Param::PALETTE_OFFSET:
        return GetParams(clientId)->paletteOffset;
    case Param::SYNC_WITH_ID:
        return GetParams(clientId)->syncWithId;
    case Param::NUM_LEDS:
        return GetParams(clientId)->numLeds;
    }

    return fallback;
}

void MessageHandler::SetParam(uint8_t clientId, Param param, uint16_t value)
{
    GetParam(clientId, param) = value;
}

char *MessageHandler::GetEffectsJSON()
{
    memset(m_Buffer, 0, 1024);

    uint16_t bufferIndex = 0;
    m_Buffer[bufferIndex++] = '[';

    auto addProperty = [&bufferIndex, this](const char *string) {
        m_Buffer[bufferIndex++] = '"';
        strcpy(&m_Buffer[bufferIndex], string);
        bufferIndex += strlen(string);
        m_Buffer[bufferIndex++] = '"';
    };

    for (size_t i = 0; i < effects.size(); i++)
    {
        m_Buffer[bufferIndex++] = '{';
        addProperty(String(effects[i]->GetIndex()).c_str());
        m_Buffer[bufferIndex++] = ':';
        addProperty(effects[i]->GetName());
        m_Buffer[bufferIndex++] = '}';

        if (i < effects.size() - 1)
            m_Buffer[bufferIndex++] = ',';
    }

    m_Buffer[bufferIndex++] = ']';
    m_Buffer[bufferIndex++] = '\0';

    return m_Buffer;
}