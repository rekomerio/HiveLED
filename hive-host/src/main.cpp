#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "Host.h"
#include "HiveServer.h"
#include "LEDHandler.h"
#include "../../common/shared.h"

void confetti(CRGB *leds, uint8_t clientId);
void sinelon(CRGB *leds);

Host host;
HiveServer *server;
LEDHandler handler;

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
	handler.Init();
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
			handler.clients[0].spawnRate = value;
			break;
		case 'f':
			handler.clients[0].spawnRate = max(value, (uint16_t)16);
			break;
		case 'h':
			handler.clients[0].hue = value;
			break;
		case 'b':
			handler.clients[0].brightness = value;
			break;
		case 'e':
			handler.clients[0].activeEffect++;
			break;
		}
	}

	UDPMessage *message = host.ReadMessage();
	if (message)
	{
		handler.Handle(message);
		host.RespondToClient(message);
	}

	server->Update();
}