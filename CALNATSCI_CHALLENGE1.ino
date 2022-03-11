void challengeOneColorHandler() {
  pixels.clear();
  pixels.show();
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  detectColor(&Mobot.colorData);
  String *colorName = &Mobot.colorData.name;

  ssd.print("<");
  ssd.print(Mobot.x);
  ssd.print(",");
  ssd.print(Mobot.y);
  ssd.print(">: ");

  if (Mobot.colorData.name != "NONE") {
    ssd.print("1, ");
    ssd.println(*colorName);

    if (*colorName == "BLUE") {
      pixels.setPixelColor(0, 0, 0, 255);
    } else {
      pixels.setPixelColor(0, 255, 0, 0);
    }
  } else {
    ssd.print("0, 0");
    pixels.setPixelColor(0, 255, 255, 255);
  }

  ssd.display();
  pixels.show();

  if (Mobot.colorData.name == "BLUE") {
    lifterUp();
    delay(100);
    lifterDown();
  }

  delay(100);
  pixels.clear();
  pixels.show();
}

void executeChallengeOne() {
  Mobot.setPosition(1, 0, North);

  Mobot.followLine(North);
  challengeOneColorHandler();
  delay(100);

  Mobot.followLine(North);
  challengeOneColorHandler();
  delay(100);

  Mobot.followLine(East);
  challengeOneColorHandler();
  delay(100);

  Mobot.followLine(South);
  challengeOneColorHandler();
  delay(100);

  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();
  //  delay(2000);
  //  pixels.clear();
  //  pixels.show();
}
