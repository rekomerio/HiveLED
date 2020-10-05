#include "MessageHandler.h"

MessageHandler::MessageHandler()
{
}

void MessageHandler::Handle(UDPMessage *message)
{
    if (message->clientId > effects.size())
        return;

    LEDEffect &effect = effects[message->clientId];

    if (effect.params.syncWithId == message->clientId)
        effect.params.syncWithId = 255; // Cant sync with itself

    if (effect.params.syncWithId != 0xFF && effect.params.syncWithId < MAX_CLIENTS)
        Synchronize(effect.params, effects[effect.params.syncWithId].params);

    message->brightness = effect.params.brightness;
    message->requestNextFrameMs = effect.params.nextFrameMs;

    effect.Update(message->leds);
}

void MessageHandler::Synchronize(LEDParams &sync, LEDParams &with)
{
    sync.palettePosition = with.palettePosition;
    sync.activeEffect = with.activeEffect;
    sync.brightness = with.brightness;
}