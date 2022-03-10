void challengeOneColorHandler() {
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

  cleartt = true;

  //
  //  delay(100);
  //  pixels.clear();
  //  pixels.show();
}
void executeChallengeOne() {
  Mobot.orientation = North;
  Mobot.x = 1;
  Mobot.y = 0;

  //  correctMobotOrientation();
  //  correctMobotOrientation();

  Mobot._followLine(North);
  challengeOneColorHandler();
  delay(100);

  Mobot._followLine(North);
  challengeOneColorHandler();
  delay(100);

  Mobot._followLine(East);
  challengeOneColorHandler();
  delay(100);

  Mobot._followLine(South);
  challengeOneColorHandler();
  delay(100);

  pixels.clear();
  pixels.show();
}