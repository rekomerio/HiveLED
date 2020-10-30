#include "MessageHandler.h"

void MessageHandler::ReadSettingsEEPROM()
{
    for (uint8_t clientId = 0; clientId < m_Params.size(); clientId++)
        for (uint8_t param = 0; param < LEDParams::GetNumParams(); param++)
            SetParam(clientId, (Param)param, ReadSettingEEPROM(clientId, (Param)param));
}

uint8_t MessageHandler::ReadSettingEEPROM(uint8_t clientId, Param param)
{
    return EEPROM.read(clientId * LEDParams::GetNumParams() + param);
}

void MessageHandler::WriteSettingEEPROM(uint8_t clientId, uint8_t offset, uint8_t value)
{
    EEPROM.write(clientId * LEDParams::GetNumParams() + offset, value);
}

void MessageHandler::SaveChangesEEPROM(uint8_t clientId)
{
    uint8_t numChanges = 0;

    for (uint8_t i = 0; i < LEDParams::GetNumParams(); i++)
    {
        if (ReadSettingEEPROM(clientId, (Param)i) != GetParam(clientId, (Param)i))
        {
            WriteSettingEEPROM(clientId, i, GetParam(clientId, (Param)i));
            numChanges++;
        }
    }

    if (numChanges > 0)
    {
        EEPROM.commit();
        Serial.print(numChanges);
        Serial.println(" params written to EEPROM");
    }
}