void colorHandler(ColorData *data) {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  detectColor(&Mobot.colorData);
  String *colorName = &Mobot.colorData.name;

  if (Mobot.colorData.name != "NONE") {
    ssd.println("PALLET: TRUE");

    if (*colorName == "BLUE") {
      ssd.print("COLOR: ");
      ssd.println(*colorName);
      pixels.setPixelColor(0, 0, 0, 255);
    } else {
      pixels.setPixelColor(0, 0, 255, 0);
    }
  } else {
    ssd.println("PALLET: FALSE");
    pixels.setPixelColor(0, 255, 255, 255);
  }

  ssd.display();
  pixels.show();

  delay(1000);
  pixels.clear();
  pixels.show();
}

void executeCheckOne() {
  Mobot.setPosition(1, 0, North);

  // 2,0
  Mobot.followLine(East);
  delay(2000);

  // 3,0
  Mobot.followLine(East);

  // 3,1
  Mobot.followLine(North);
  delay(2000);

  // 3, 2
  Mobot.followLine(North);
  colorHandler(&Mobot.colorData);
  delay(2000);

  // 3.3
  Mobot.followLine(North);
  colorHandler(&Mobot.colorData);
  delay(2000);

  // 2,3
  Mobot.followLine(West);
  colorHandler(&Mobot.colorData);
  delay(2000);

  Mobot.followLine(South);
  Mobot.followLine(South);
  Mobot.followLine(South);
  Mobot.followLine(West);

  pixels.clear();
  pixels.show();
}
