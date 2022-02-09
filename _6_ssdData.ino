void initSsd() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.setTextSize(2);
  ssd.setTextColor(SSD1306_WHITE);
  ssd.cp437(true);

  displayIdentifier();
  Serial.println(">> Lcd screen configuration successful!");
}

/**
 * Displays the secret or identifying code
 */
void displayIdentifier() {
  ssd.setTextSize(2);
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  const String identifier = "CalNatSci TRC2021";
  ssd.println(identifier);
  ssd.display();

  ssd.setTextSize(1);
}
