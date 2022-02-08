void initSsd() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.setTextSize(2);
  ssd.setTextColor(SSD1306_WHITE);
  ssd.cp437(true);

  displayIdentifier();
  ssd.display();

  Serial.println(">> Lcd screen configuration successful!");
}

void testchar() {
  ssd.clearDisplay();
  ssd.setTextSize(1);
  ssd.setTextColor(SSD1306_WHITE);
  ssd.setCursor(0, 0);
  ssd.cp437(true);

  for (int16_t i = 0; i < 256; i++) {
    if (i == '\n') ssd.write(' ');
    else ssd.write(i);
  }

  ssd.display();
  delay(2000);
}

void testInt() {
  for (uint8_t i = 1; i <= 20; i++) {
    ssd.println(i);
    ssd.display();
  }
}

// The secret code or identifying text
void displayIdentifier() {
  ssd.setTextSize(2);
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  ssd.println("CalNatSci TRC2021");
  ssd.display();

  ssd.setTextSize(1);
}
