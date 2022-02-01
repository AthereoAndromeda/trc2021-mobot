void initLed() {
  pixels.begin();
}

void cycleLed(int delayValue) {
  // Red
  pixels.setPixelColor(0, 255, 0, 0);
  pixels.show();
  delay(delayValue);

  // Green
  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();
  delay(delayValue);

  // Blue
  pixels.setPixelColor(0, 0, 0, 255);
  pixels.show();
  delay(delayValue);

  // White
  pixels.setPixelColor(0, 255, 255, 255);
  pixels.show();
  delay(delayValue);

  pixels.clear();
}
