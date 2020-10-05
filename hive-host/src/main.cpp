#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "Host.h"
#include "HiveServer.h"
#include "MessageHandler.h"
#include "../../common/shared.h"

Host host;
HiveServer *server;
MessageHandler messageHandler;

const char *sssid = "Redmi";
const char *passw = "1b18a7431459";

void setup()
{
	Serial.begin(115200);
	WiFi.mode(WIFI_AP_STA);
	WiFi.begin(sssid, passw);

	Serial.println(WiFi.softAPIP());

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(250);
		Serial.print('.');
	}

	WiFi.softAP(ssid, pass, 1, 0, MAX_CLIENTS);

	Serial.println(WiFi.softAPIP());
	Serial.println(WiFi.localIP());

	host.Init();
	server = HiveServer::GetInstance();
	server->Init();
	server->handler = &messageHandler;
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

	host.ReadMessage();
	UDPMessage *message = host.PeekMessage();
	if (message)
	{
		messageHandler.Handle(message);
		//host.RespondToClient(message);
		host.SendMessage(message, host.clients[message->clientId]);
	}

	server->Update();
}