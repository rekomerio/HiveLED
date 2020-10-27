#include "MessageHandler.h"

char *MessageHandler::GetEffectsJSON()
{
    static char *key = "effects";
    memset(m_Buffer, 0, 1024);

    uint16_t bufferIndex = BeginJSONString(m_Buffer, key);
    m_Buffer[bufferIndex++] = '{';

    for (size_t i = 0; i < effects.size(); i++)
    {
        bufferIndex = AddJSONKeyValue(m_Buffer, bufferIndex, String(effects[i]->GetIndex()).c_str(), effects[i]->GetName());

        if (i < effects.size() - 1)
            m_Buffer[bufferIndex++] = ',';
    }

    m_Buffer[bufferIndex++] = '}';
    m_Buffer[bufferIndex++] = '}';
    m_Buffer[bufferIndex++] = '\0';

    return m_Buffer;
}

char *MessageHandler::GetParamsJSON(uint8_t clientId)
{
    static char *key = "params@@";
    key[7] = clientId + '0';

    memset(m_Buffer, 0, 1024);

    uint16_t bufferIndex = BeginJSONString(m_Buffer, key);
    m_Buffer[bufferIndex++] = '{';

    for (uint8_t i = 0; i < m_Params[clientId].GetNumParams(); i++)
    {
        bufferIndex = AddJSONKeyValue(m_Buffer, bufferIndex, String(i).c_str(), String(GetParam(clientId, (Param)i)).c_str());

        if (i < m_Params[clientId].GetNumParams() - 1)
            m_Buffer[bufferIndex++] = ',';
    }

    m_Buffer[bufferIndex++] = '}';
    m_Buffer[bufferIndex++] = '}';
    m_Buffer[bufferIndex++] = '\0';

    return m_Buffer;
}

uint16_t MessageHandler::AddJSONQuotes(char *buffer, uint16_t bufferIndex, const char *str)
{
    buffer[bufferIndex++] = '"';
    strcpy(&buffer[bufferIndex], str);
    bufferIndex += strlen(str);
    buffer[bufferIndex++] = '"';

    return bufferIndex;
}

uint16_t MessageHandler::AddJSONKeyValue(char *buffer, uint16_t bufferIndex, const char *key, const char *value)
{
    bufferIndex = AddJSONQuotes(buffer, bufferIndex, key);
    buffer[bufferIndex++] = ':';
    bufferIndex = AddJSONQuotes(buffer, bufferIndex, value);

    return bufferIndex;
}

uint16_t MessageHandler::BeginJSONString(char *buffer, const char *key)
{
    uint16_t bufferIndex = 0;
    buffer[bufferIndex++] = '{';
    bufferIndex = AddJSONQuotes(buffer, bufferIndex, key);
    buffer[bufferIndex++] = ':';

    return bufferIndex;
}
