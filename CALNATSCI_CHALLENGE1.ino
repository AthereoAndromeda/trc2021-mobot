//void challengeOneColorHandler() {
//  detectColor(&Mobot.colorData);
//  String *colorName = &Mobot.colorData.name;
//
//  ssd.print("<");
//  ssd.print(Mobot.x);
//  ssd.print(",");
//  ssd.print(Mobot.y);
//  ssd.print(">: ");
//
//  if (Mobot.colorData.name != "NONE") {
//    ssd.print("1, ");
//    ssd.println(*colorName);
//
//    if (*colorName == "BLUE") {
//      pixels.setPixelColor(0, 0, 0, 255);
//    } else {
//      pixels.setPixelColor(0, 255, 0, 0);
//    }
//  } else {
//    ssd.print("0, 0");
//    pixels.setPixelColor(0, 255, 255, 255);
//  }
//
//  ssd.display();
//  pixels.show();
//
//  if (Mobot.colorData.name == "BLUE") {
//    lifterUp();
//    delay(100);
//    lifterDown();
//  }
//
//  delay(100);
//  pixels.clear();
//  pixels.show();
//}

void moveToLocation() {
  lifterUp();
  String *color = &Mobot.colorData.name;

  if (*color == "BLUE") {
    Mobot.followLine(East);
    Mobot.followLine(South);
    Mobot.followLine(South);
    test_realign();

    lifterDown();

    // Return to init
    Mobot.followLine(West);
    Mobot.followLine(West);
  } else {
    Mobot.followLine(West);
    Mobot.followLine(West);
    test_realign();

    Mobot.followLine(North);

    lifterDown();

    // return
    Mobot.followLine(South);
    test_realign();
    Mobot.followLine(South);
    Mobot.followLine(South);
    test_realign();
    Mobot.followLine(East);
  }
}

void executeChallengeOne() {
  pixels.clear();
  pixels.show();

  Mobot.setPosition(1, 0, North);
  colorHandler();
  delay(2000);
  test_realign();


  //  colorHandler();
  Mobot.followLine(North);
  test_realign();

  //  colorHandler();
  Mobot.followLine(North);
  test_realign();

  //  colorHandler();
  Mobot.followLine(East);
  test_realign();

  pixels.clear();
  pixels.show();
  delay(100);

  colorHandler();
  moveToLocation();

  pixels.clear();
  pixels.show();
  //  isGreenLedOn = true;
}
