void colorHandler() {
  //  ssd.clearDisplay();
  //  ssd.setCursor(0, 0);

  detectColor(&Mobot.colorData);
  String *colorName = &Mobot.colorData.name;

  //  ssd.print(Mobot.x);
  //  ssd.print(",");
  //  ssd.print(Mobot.y);
  //  ssd.print(" : ");

  if (Mobot.colorData.name != "NONE") {
    ssd.print("1,");
    ssd.println(*colorName);

    if (*colorName == "BLUE") {
      pixels.setPixelColor(0, 0, 0, 255);
    } else {
      pixels.setPixelColor(0, 255, 0, 0);
    }
  } else {
    ssd.println("0,0");
    pixels.setPixelColor(0, 255, 255, 255);
  }

  ssd.display();
  pixels.show();

  //    delay(1000);
  //    pixels.clear();
  //    pixels.show();
}

void executeCheckOne() {
  pixels.clear();
  pixels.show();
  delay(2000);

  Mobot.setPosition(1, 0, North);
  //  colorHandler();

  Mobot.followLine(North);
  pixels.clear();
  pixels.show();
  delay(2000);

  //  colorHandler();
  delay(2000);

  lifterUp();
  delay(2000);

  Mobot.followLine(West);
  lifterDown();
  delay(2000);

  Mobot.followLine(South);
  pixels.clear();
  pixels.show();
  delay(100);

  //  colorHandler();
  delay(2000);

  // Task 5
  Mobot.followLine(East);
  delay(500);

  //  colorHandler();
  delay(2000);

  // Task 6
  Mobot.followLine(East);
  Mobot.followLine(North);
  Mobot.followLine(North);
  pixels.clear();
  pixels.show();
  delay(2000);

  // Task 7
  //  colorHandler();
  delay(2000);

  // Task 8
  lifterUp();
  delay(2000);

  // Task 9
  Mobot.followLine(North);
  Mobot.followLine(East);
  lifterDown();
  delay(2000);

  // Task 10
  Mobot.followLine(South);
  pixels.clear();
  pixels.show();
  delay(100);

  //  colorHandler();
  Mobot.followLine(South);
  Mobot.followLine(South);
  Mobot.followLine(West);
  Mobot.followLine(West);

  delay(2000);
  pixels.clear();
  pixels.show();
}
