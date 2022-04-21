void colorHandler() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  detectColor(&Mobot.colorData);
  String *colorName = &Mobot.colorData.name;

  ssd.print(Mobot.x);
  ssd.print(",");
  ssd.print(Mobot.y);
  ssd.print(" : ");

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
}

void executeCheckOne() {
  pixels.clear();
  pixels.show();

  Mobot.setPosition(1, 0, North);
  colorHandler();
  delay(2000);

  test_realign();

  Mobot.followLine(North);
  pixels.clear();
  pixels.show();
  delay(2000);

  //  colorHandler();
  test_realign();
  delay(2000);

  lifterUp();
  delay(2000);

  Mobot.followLine(West);
  test_realign();
  lifterDown();
  delay(2000);

  Mobot.followLine(South);
  test_realign();
  delay(2000);

  // Task 5
  Mobot.followLine(East);
  test_realign();

  //  colorHandler();
  delay(2000);

  // Task 6
  Mobot.followLine(East);
  test_realign();

  Mobot.followLine(North);
  test_realign();
  Mobot.followLine(North);
  test_realign();
  delay(2000);

  // Task 7
  pixels.clear();
  pixels.show();
  delay(100);
  colorHandler();
  delay(2000);

  // Task 8
  lifterUp();
  delay(2000);

  // Task 9
  Mobot.followLine(North);
  test_realign();
  Mobot.followLine(East);
  test_realign();
  lifterDown();
  delay(2000);

  // Task 10
  Mobot.followLine(South);
  test_realign();
  pixels.clear();
  pixels.show();
  delay(100);

  //  colorHandler();
  Mobot.followLine(South);
  Mobot.followLine(South);
  test_realign();
  Mobot.followLine(West);
  Mobot.followLine(West);
  test_realign();

  delay(2000);
  pixels.clear();
  pixels.show();
}
