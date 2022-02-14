#define LED_CYCLE_DELAY 500

void initLed() {
  pixels.begin();
  delay(300);
}

void cycleLed() {
  // Red
  pixels.setPixelColor(0, 255, 0, 0);
  pixels.show();
  delay(LED_CYCLE_DELAY);

  // Green
  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();
  delay(LED_CYCLE_DELAY);

  // Blue
  pixels.setPixelColor(0, 0, 0, 255);
  pixels.show();
  delay(LED_CYCLE_DELAY);

  // White
  pixels.setPixelColor(0, 255, 255, 255);
  pixels.show();
  delay(LED_CYCLE_DELAY);

  pixels.clear();
  pixels.show();
}
