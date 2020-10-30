#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <FastLED.h>
#include <array>
#include <vector>
#include <EEPROM.h>
#include "LEDEffect.h"
#include "UDPHost.h"
#include "../../../common/Message.h"

class MessageHandler
{
public:
    MessageHandler();
    void Init();
    void Handle(UDPMessage *message);
    void Synchronize(LEDParams &pSync, LEDHelpers &hSync, LEDParams &pWith, LEDHelpers hWith);

    LEDParams *GetParams(uint8_t clientId);
    uint8_t &GetParam(uint8_t clientId, Param param);
    void SetParam(uint8_t clientId, Param param, uint8_t value);

    char *GetEffectsJSON();
    char *GetClientsJSON();
    char *GetParamsJSON(uint8_t clientId);

    uint8_t ReadSettingEEPROM(uint8_t clientId, Param param);
    void SaveChangesEEPROM(uint8_t clientId);
    void WriteSettingEEPROM(uint8_t clientId, uint8_t offset, uint8_t value);
    void ReadSettingsEEPROM();

    std::vector<LEDEffect *> effects;
    UDPClient *clients;

private:
    uint16_t AddJSONQuotes(char *buffer, uint16_t bufferIndex, const char *str);
    uint16_t AddJSONKeyValue(char *buffer, uint16_t bufferIndex, const char *key, const char *value);
    uint16_t BeginJSONString(char *buffer, const char *key);

    std::array<LEDParams, MAX_CLIENTS> m_Params;
    std::array<LEDHelpers, MAX_CLIENTS> m_Helpers;
    // When was SetParam() last called for a client
    std::array<uint32_t, MAX_CLIENTS> m_LastChangeAt;
    char m_Buffer[1024];
};

extern MessageHandler messageHandler;

#endif