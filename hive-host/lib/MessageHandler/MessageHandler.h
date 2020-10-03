#include <FastLED.h>
#include <array>
#include "../../../common/Message.h"
#include "../LEDEffects/LEDEffects.h"

#ifndef MESSAGEHANDLER
#define MESSAGEHANDLER

class MessageHandler
{
public:
    MessageHandler();
    void Handle(UDPMessage *message);
    void Synchronize(LEDParams &to, LEDParams &with);

    std::array<LEDEffects, 16> effects;
};

#endif