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

    lifterDown();

    // Return to init
    Mobot.followLine(West);
    Mobot.followLine(West);
  } else {
    Mobot.followLine(North);
    Mobot.followLine(West);
    Mobot.followLine(West);

    lifterDown();

    // return
    Mobot.followLine(South);
    Mobot.followLine(South);
    Mobot.followLine(South);
    Mobot.followLine(East);
  }
}

void executeChallengeOne() {
  pixels.clear();
  pixels.show();

  Mobot.setPosition(1, 0, North);
  delay(2000);

  //  colorHandler();
  Mobot.followLine(North);

  //  colorHandler();
  Mobot.followLine(North);

  //  colorHandler();
  Mobot.followLine(East);
  pixels.clear();
  pixels.show();
  delay(100);

  //  colorHandler();
  moveToLocation();



  pixels.clear();
  pixels.show();
  //  isGreenLedOn = true;
}
