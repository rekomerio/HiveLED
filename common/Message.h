#include "../../../hive-host/.pio/libdeps/d1_mini_lite/FastLED/FastLED.h"
#include "defines.h"

#ifndef UDPMESSAGE
#define UDPMESSAGE

struct UDPMessage
{
    uint8_t clientId;
    uint8_t brightness;
    uint8_t requestNextFrameMs;
    uint16_t checksum;
    CRGB leds[LEDS_ARRAY_SIZE];

    uint16_t CalculateChecksum()
    {
        return crc16((uint8_t *)leds, LEDS_ARRAY_SIZE);
    }

    bool ChecksumMatches()
    {
        return CalculateChecksum() == checksum;
    }

    void ComputeChecksum()
    {
        checksum = CalculateChecksum();
    }

    unsigned short crc16(const unsigned char *data_p, unsigned char length)
    {
        unsigned char x;
        unsigned short crc = 0xFFFF;

        while (length--)
        {
            x = crc >> 8 ^ *data_p++;
            x ^= x >> 4;
            crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x << 5)) ^ ((unsigned short)x);
        }
        return crc;
    }
};

#endif