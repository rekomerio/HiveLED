#include "HttpClient.h"

void GetTime()
{
    WiFiClient client;
    HTTPClient httpClient;
    if (httpClient.begin(client, "http://worldclockapi.com/api/json/est/now"))
    {
        int httpCode = httpClient.GET();
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
            String payload = httpClient.getString();
            Serial.println(payload);
            httpClient.end();
        }
        else
        {
            ESP.restart();
        }
    }
}