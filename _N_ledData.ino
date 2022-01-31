void initLed() {
  pixels.begin();
}

void runLed() {
  pixels.clear();
  pixels.setPixelColor(0, 255, 0, 0);
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(0, 0, 0, 255);
  pixels.show();
  delay(DELAYVAL);
  pixels.setPixelColor(0, 255, 255, 255);
  pixels.show();
  delay(DELAYVAL);
}
