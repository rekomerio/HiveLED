#include <FastLED.h>
#include <array>
#include "../../../common/Message.h"

struct LEDClient
{
    uint8_t id;
    uint8_t hue = 100;
    uint8_t spawnRate = 100;
    uint8_t brightness = 255;
    uint8_t activeEffect = 0;
    uint8_t nextFrameMs = 16;
    uint32_t lastUpdate = 0;
};

class LEDHandler
{
public:
    LEDHandler();
    void Init();
    void Handle(UDPMessage *message);

    std::array<LEDClient, 16> clients;

private:
    void Confetti(CRGB *leds, uint8_t clientId);
};