#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "Host.h"
#include "HiveServer.h"
#include "MessageHandler.h"
#include "../../common/shared.h"

void confetti(CRGB *leds, uint8_t clientId);
void sinelon(CRGB *leds);

Host host;
HiveServer *server;
MessageHandler messageHandler;

void setup()
{
	Serial.begin(115200);
	WiFi.mode(WIFI_AP);
	WiFi.softAP(ssid, pass);

	IPAddress myIP = WiFi.softAPIP();
	Serial.println(myIP);

	host.Init();
	server = HiveServer::GetInstance();
	server->Init();
}

void loop()
{
	if (Serial.available())
	{
		String command = Serial.readString();
		uint8_t index = command[0] - '0';
		uint16_t value = strtoul((const char *)&command[2], NULL, 10);

		switch (command[1])
		{
		case 's':
			messageHandler.effects[index].params.syncWithId = value;
			break;
		case 'o':
			messageHandler.effects[index].params.paletteOffset = value;
			break;
		case 'f':
			messageHandler.effects[index].params.nextFrameMs = max(value, (uint16_t)16);
			break;
		case 'h':
			messageHandler.effects[index].params.hue = value;
			break;
		case 'b':
			messageHandler.effects[index].params.brightness = value;
			break;
		case 'e':
			messageHandler.effects[index].params.activeEffect++;
			break;
		}
	}

	UDPMessage *message = host.ReadMessage();
	if (message)
	{
		messageHandler.Handle(message);
		host.RespondToClient(message);
	}

	server->Update();
}