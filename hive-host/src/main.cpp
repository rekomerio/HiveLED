#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "../../common/shared.h"
#include "../../hive-host/lib/Host/Host.h"

void confetti(CRGB *leds, uint8_t clientId);
void sinelon(CRGB *leds);

Host host;

uint8_t spawnRate = 50;
uint8_t nextFrameRate = 16;
uint8_t brightness = 255;
uint8_t hue = 100;
uint8_t activeEffect = 0;

uint32_t lastModifieds[MAX_CLIENTS];

void setup()
{
	Serial.begin(115200);
	WiFi.mode(WIFI_AP);
	WiFi.softAP(ssid, pass);

	IPAddress myIP = WiFi.softAPIP();
	Serial.println(myIP);

	memset(lastModifieds, 0, MAX_CLIENTS);

	host.Init();
}

void loop()
{
	if (Serial.available())
	{
		String command = Serial.readString();
		uint16_t value = strtoul((const char *)&command[1], NULL, 10);

		switch (command[0])
		{
		case 's':
			spawnRate = value;
			break;
		case 'f':
			nextFrameRate = max(value, (uint16_t)16);
			break;
		case 'h':
			hue = value;
			break;
		case 'b':
			brightness = value;
			break;
		case 'e':
			++activeEffect %= 2;
			break;
		}
	}

	UDPMessage *message = host.ReadMessage();
	if (message)
	{
		if (activeEffect == 0)
			confetti((*message).leds, message->clientId);
		if (activeEffect == 1)
			sinelon((*message).leds);

		(*message).requestNextFrameMs = nextFrameRate;
		(*message).brightness = brightness;
		host.RespondToClient(message);
	}
}

void confetti(CRGB *leds, uint8_t clientId)
{
	if (clientId > MAX_CLIENTS)
		return;

	if (millis() - lastModifieds[clientId] > spawnRate)
	{
		uint8_t pos = random16(70);
		leds[pos] += CHSV(hue + random8(64), 200, 255);
		lastModifieds[clientId] = millis();
	}

	fadeToBlackBy(leds, LEDS_ARRAY_SIZE, 5);
}

void sinelon(CRGB *leds)
{
	fadeToBlackBy(leds, LEDS_ARRAY_SIZE, 5);
	leds[beatsin16(30, 0, 72)] += CHSV(hue, 255, 192);
}