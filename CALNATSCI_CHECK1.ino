void colorHandler(ColorData *data) {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  detectCol(&Mobot.colorData);
  String *colorName = &Mobot.colorData.name;

  if (Mobot.colorData.name != "NONE") {
    ssd.println("PALLET: TRUE");
    ssd.print("COLOR: ");
    ssd.println(*colorName);

    if (*colorName == "BLUE" || *colorName == "RED") {
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


void taskOne_2() {
  correctMobotOrientation();
  // 2,0
  followLine(East);
  delay(2000);

  // 3,0
  followLine(East);

  // 3,1
  followLine(North);
  delay(2000);

  // 3, 2
  followLine(North);
  colorHandler(&Mobot.colorData);
  delay(2000);

  // 3.3
  followLine(North);
  colorHandler(&Mobot.colorData);
  delay(2000);

  // 2,3
  followLine(West);
  colorHandler(&Mobot.colorData);
  delay(2000);

  followLine(South);
  followLine(South);
  followLine(South);
  followLine(West);

  pixels.clear();
  pixels.show();
}
