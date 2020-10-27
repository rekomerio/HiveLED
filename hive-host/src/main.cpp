#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "UDPHost.h"
#include "HiveServer.h"
#include "MessageHandler.h"
#include "../../common/shared.h"

UDPHost host;
HiveServer *server;

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);

	WiFi.mode(WIFI_AP_STA);
	WiFi.begin(wifiSsid, wifiPass);

	uint8_t statusLedState = 0;
	while (WiFi.status() != WL_CONNECTED)
	{
		digitalWrite(LED_BUILTIN, statusLedState);
		Serial.print('.');
		delay(250);

		statusLedState = !statusLedState;
	}

	digitalWrite(LED_BUILTIN, 1);

	WiFi.softAP(apSsid, apPass, 1, 0, MAX_CLIENTS);

	Serial.println(WiFi.softAPIP());
	Serial.println(WiFi.localIP());

	host.Init();
	messageHandler.Init();
	server = HiveServer::GetInstance();
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