#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "UDPHost.h"
#include "WebSocketServer.h"
#include "HttpServer.h"
#include "MessageHandler.h"
#include "../../common/shared.h"

#define CONNECT_TO_WIFI 0

UDPHost host;
WebSocketServer *wsServer;
HttpServer *httpServer;

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);

#if CONNECT_TO_WIFI
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
#else
	WiFi.mode(WIFI_AP);
#endif

	digitalWrite(LED_BUILTIN, 1);

	WiFi.softAP(apSsid, apPass, 1, 0, MAX_CLIENTS);

	Serial.println(WiFi.softAPIP());

#if CONNECT_TO_WIFI
	Serial.println(WiFi.localIP());
#endif

	messageHandler.clients = host.clients.data();

	host.Init();
	messageHandler.Init();
	wsServer = WebSocketServer::GetInstance();
	wsServer->Init();

	httpServer = HttpServer::GetInstance();
	httpServer->Init();

	// When adding new parameters, comment this line and boot the device once and change some params so they get set correctly in memory
	messageHandler.ReadSettingsEEPROM();
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

	wsServer->Update();
	httpServer->Update();
}