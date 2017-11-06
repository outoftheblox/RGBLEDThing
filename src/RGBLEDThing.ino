#include <Thing.h>
#include <BlinkPattern.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

#define PIN D2
#define BUFFER_SIZE 1024

using namespace g3rb3n;

Thing thing;
BlinkPattern led(BUILTIN_LED);

BlinkPattern::Pattern<2> start{{1,9},25};
BlinkPattern::Pattern<2> normal{{1,39},25};
BlinkPattern::Pattern<0> disable{{},1000};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

bool state = false;

void setup()
{
  Serial.begin(230400);
  Serial.println();
  Serial.println("Client:" + thing.clientId());

  led.setPattern(start);

  pixels.begin();

  pixels.setPixelColor(0, pixels.Color(10, 0, 0));
  pixels.show();

  thing.onStateChange([](const String& msg){
    Serial.println(msg);
  });

  thing.begin();

  thing.addActuator(thing.clientId() + "/rgbled/color", [](Value& value){
    state = (bool)value;
    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
    String msg = value;
    JsonObject& root = jsonBuffer.parseObject(msg);

    if (!root.success()) {
      Serial.println("parseObject() failed");
      return false;
    }

    int r = root["r"];
    int g = root["g"];
    int b = root["b"];
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show();
    Serial.println("Got:" + String(value));
    //thing.publish(thing.clientId() + "/rbgled/color", value);
  });

  led.setPattern(normal);
}

void loop()
{
  thing.handle();
  led.handle();
}
