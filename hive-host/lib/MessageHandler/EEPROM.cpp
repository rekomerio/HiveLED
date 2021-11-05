#include "MessageHandler.h"

#define MAX_PARAM_COUNT 80

void MessageHandler::ReadSettingsEEPROM()
{
    for (uint8_t clientId = 0; clientId < m_Params.size(); clientId++)
        for (uint8_t paramIndex = 0; paramIndex < LEDParams::GetNumParams(); paramIndex++)
            SetParam(clientId, (Param)paramIndex, ReadSettingEEPROM(clientId, (Param)paramIndex));
}

uint8_t MessageHandler::ReadSettingEEPROM(uint8_t clientId, Param param)
{
    uint8_t data;
    EEPROM.get(clientId * MAX_PARAM_COUNT + param, data);

    return data;
}

void MessageHandler::WriteSettingEEPROM(uint8_t clientId, uint8_t offset, uint8_t value)
{
    EEPROM.put(clientId * MAX_PARAM_COUNT + offset, value);
}

void MessageHandler::SaveChangesEEPROM(uint8_t clientId)
{
    for (uint8_t i = 0; i < LEDParams::GetNumParams(); i++)
    {
        WriteSettingEEPROM(clientId, i, GetParam(clientId, (Param)i));
    }

    // Commit the changes to flash, for now everything is stored in ram. Library will check for any changes and only commit them 
    // if the data has really changed
    EEPROM.commit(); 
}