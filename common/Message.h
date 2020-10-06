#include "../../../hive-host/.pio/libdeps/d1_mini_lite/FastLED/FastLED.h"
#include "defines.h"

#ifndef UDPMESSAGE
#define UDPMESSAGE

struct UDPMessage
{
    uint8_t clientId;
    uint8_t brightness;
    uint8_t requestNextFrameMs;
    CRGB leds[MAX_LEDS];
};

#endif