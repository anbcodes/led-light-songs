// clang-format off
#include <FastLED.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoOTA.h>
#include <Arduino.h>
// clang-format on

#include "src/globals.hpp"
#include "src/effects.hpp"
#include "songs/if.hpp"
#include "src/patterns.hpp"
#include "src/secrets.hpp"

CRGB color = CRGB(0, 0, 255);

void connect() {
    Serial.begin(9600);
    // delay(3000);
    leds[0] = CRGB(255, 255, 255);
    FastLED.setBrightness(255);
    FastLED.show();

    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        leds[0] = CRGB(255, 0, 0);
        FastLED.show();
        while (1)
            ;
    }

    arduino::String fv = WiFi.firmwareVersion();

    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.println("Please upgrade the firmware");
        Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
        leds[0] = CRGB(255, 0, 0);
        FastLED.show();
    }

    int attempts = 0;

    int status = 0;

    while (status != WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.print("Attempting to connect to SSID: ");

        Serial.println(WIFI_SSID);

        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        if (status == WL_CONNECTED) {
            break;
        }

        Serial.println(status);

        delay(4000);
        attempts++;
        if (attempts > 10) {
            NVIC_SystemReset();
        }
    }

    leds[0] = CRGB(255, 0, 255);
    FastLED.show();
}

WiFiServer server(11234);

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, LED_COUNT);
    pinMode(LED_BUILTIN, OUTPUT);
    connect();
    ArduinoOTA.begin(WiFi.localIP(), "LED", "LEDS1234", InternalStorage);
    server.begin();
}




void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        NVIC_SystemReset();
    }

    ArduinoOTA.poll();


    // colors_in_out(); // fills with a color then unfills then fills with a different color
    // rainbow(); // solid rainbow
    rainbowoffsync(); // Rainbow going across
    // song_if();
    // broken();
    // test();
    // rainbowoffsync(5, 4); // ^ fast


    FastLED.show();
}
