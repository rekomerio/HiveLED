#include <FastLED.h>
#include <array>
#include "../../../common/Message.h"
#include "../LEDEffect/LEDEffect.h"

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

class MessageHandler
{
public:
    MessageHandler();
    void Handle(UDPMessage *message);
    void Synchronize(LEDParams &sync, LEDParams &with);
    LEDParams *GetParams();

    std::array<LEDEffect, 16> effects;
};

#endif