#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "../../common/shared.h"
#include "../../hive-client/lib/HiveClient/HiveClient.h"

#define NETWORK_ID 1
#define DATA_PIN 12 // D6 for Wemos D1 mini
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

HiveClient client = HiveClient(NETWORK_ID);
uint8_t statusLedState = 0;

void onConnectionChanged(bool isConnected)
{
	Serial.println(isConnected ? "connected" : "disconnected");
	digitalWrite(LED_BUILTIN, !isConnected);
}

void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);

	FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(client.GetLeds(), LEDS_ARRAY_SIZE).setCorrection(TypicalLEDStrip);

	WiFi.begin(ssid, pass);
	WiFi.mode(WIFI_STA);

	while (WiFi.status() != WL_CONNECTED)
	{
		digitalWrite(LED_BUILTIN, statusLedState);
		Serial.println("Connecting to host...");
		delay(250);

		statusLedState = !statusLedState;
	}

	digitalWrite(LED_BUILTIN, 1);
	Serial.print("Connected, IP address: ");
	Serial.println(WiFi.localIP());

	client.onConnectionChanged = onConnectionChanged;
	client.Init();
}

void loop()
{
	client.TestConnection();
	client.KeepAlive();
	UDPMessage *message = client.ReadMessage();

	if (message)
	{
		FastLED.setBrightness(message->brightness);
		FastLED.show();
	}
}