#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "UDPHost.h"
#include "WebSocketServer.h"
#include "HttpServer.h"
#include "MessageHandler.h"
#include "../../common/shared.h"

#define CONNECT_TO_WIFI 1

UDPHost host;
WebSocketServer *wsServer;
HttpServer *httpServer;


struct {
	char ssid[64];
	char password[64];
} wifiOpts;

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	
	// Init first to initialize EEPROM 
	messageHandler.Init();

	// EEPROM.get(EEPROM_SIZE_BYTES - 1 - sizeof(wifiOpts), wifiOpts);

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
	wsServer = WebSocketServer::GetInstance();
	wsServer->Init();

	httpServer = HttpServer::GetInstance();
	httpServer->Init();
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