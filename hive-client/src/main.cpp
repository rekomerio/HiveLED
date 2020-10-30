#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "HiveClient.h"
#include "../../common/shared.h"

#define NETWORK_ID 1
#define DATA_PIN 12 // D6 for Wemos D1 mini
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define HOST_AP 1

uint32_t disconnectedAt = 0;

#if HOST_AP
HiveClient client = HiveClient(NETWORK_ID, IPAddress(192, 168, 4, 1));
#else
HiveClient client = HiveClient(NETWORK_ID, IPAddress(192, 168, 1, 200));
#endif

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);

	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(client.GetLeds(), MAX_LEDS).setCorrection(TypicalLEDStrip);
	fill_solid(client.GetLeds(), MAX_LEDS, CRGB::Black);
	FastLED.show();

	WiFi.mode(WIFI_STA);

#if HOST_AP
	WiFi.begin(apSsid, apPass);
#else
	WiFi.begin(wifiSsid, wifiPass);
#endif

	Serial.println("Connecting to WiFi...");

	uint8_t statusLedState = 0;
	while (WiFi.status() != WL_CONNECTED)
	{
		digitalWrite(LED_BUILTIN, statusLedState);
		Serial.print(".");
		delay(250);

		statusLedState = !statusLedState;
	}

	digitalWrite(LED_BUILTIN, 0);
	Serial.print("Connected, IP address: ");
	Serial.println(WiFi.localIP());

	if (!client.Init())
		ESP.restart();
}

void loop()
{
	bool isConnected = WiFi.status() == WL_CONNECTED;

	if (disconnectedAt == 0 && !isConnected)
	{
		disconnectedAt = millis();
		digitalWrite(LED_BUILTIN, 1);
	}

	if (disconnectedAt != 0 && isConnected)
	{
		disconnectedAt = 0;
		digitalWrite(LED_BUILTIN, 0);
	}

	if (disconnectedAt && (uint32_t)(millis() - disconnectedAt) > 2500)
		ESP.restart();

	client.Loop();
}