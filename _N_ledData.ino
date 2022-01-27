#include <Adafruit_NeoPixel.h>
#define LED_PIN 10
#define LED_COUNT 1
#define DELAYVAL 5000

Adafruit_NeoPixel pixels (LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void initLed() {
  pixels.begin();
}

//void loop() {
//  pixels.clear();
//  pixels.setPixelColor(0, 255, 0, 0);
//  pixels.show();
//  delay(DELAYVAL);
//  pixels.setPixelColor(0, 0, 255, 0);
//  pixels.show();
//  delay(DELAYVAL);
//  pixels.setPixelColor(0, 0, 0, 255);
//  pixels.show();
//  delay(DELAYVAL);
//  pixels.setPixelColor(0, 255, 255, 255);
//  pixels.show();
//  delay(DELAYVAL);
//}
