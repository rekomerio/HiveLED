#include <FastLED.h>
#include <array>
#include <vector>
#include "../../../common/Message.h"
#include "../LEDEffect/LEDEffect.h"

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

class MessageHandler
{
public:
    MessageHandler();
    void Init();
    void Handle(UDPMessage *message);
    void Synchronize(LEDParams &sync, LEDParams &with);
    LEDParams *GetParams(uint8_t clientId);
    uint16_t &GetParam(uint8_t clientId, Param param);
    void SetParam(uint8_t clientId, Param param, uint16_t value);
    char *GetEffectsJSON();
    char *GetClientsJSON();
    char *GetParamsJSON(uint8_t clientId);

    std::vector<LEDEffect *> effects;
    std::array<LEDParams, MAX_CLIENTS> params;

private:
    uint16_t AddJSONQuotes(char *buffer, uint16_t bufferIndex, const char *str);
    uint16_t AddJSONKeyValue(char *buffer, uint16_t bufferIndex, const char *key, const char *value);
    uint16_t BeginJSONString(char *buffer, const char *key);
    char m_Buffer[1024];
};

#endif