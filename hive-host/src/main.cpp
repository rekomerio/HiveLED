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

void setup()
{
	Serial.begin(115200);
	WiFi.mode(WIFI_AP_STA);
	WiFi.begin(wifiSsid, wifiPass);

	Serial.println(WiFi.softAPIP());

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(250);
		Serial.print('.');
	}

	WiFi.softAP(apSsid, apPass, 1, 0, MAX_CLIENTS);

	Serial.println(WiFi.softAPIP());
	Serial.println(WiFi.localIP());

	host.Init();
	messageHandler.Init();
	server = HiveServer::GetInstance();
	server->handler = &messageHandler;
	server->Init();
}

void loop()
{
	host.ReadMessage();
	UDPMessage *message = host.PeekMessage();

	if (message)
	{
		messageHandler.Handle(message);
		host.SendMessage(message, host.clients[message->clientId]);
	}

	server->Update();
}