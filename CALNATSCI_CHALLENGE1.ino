String *colorName = &Mobot.colorData.name;
Color *color = &Mobot.colorData.color;

void colorHandler() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  detectColor(&Mobot.colorData);

  ssd.print(Mobot.x);
  ssd.print(",");
  ssd.print(Mobot.y);
  ssd.print(" : ");

  if (Mobot.colorData.color != None) {
    ssd.print("1,");
    ssd.println(*colorName);

    if (*color == Blue) {
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

void handleFirstPallet() {
  // From (1,0) to (1,1)
  Mobot.followLine(North);
  Mobot.realign();

  lifterUp();
  colorHandler();

  if (*color == Red) {
    // From (1,1) to (0,1)
    Mobot.followLine(West);
  } else {
    Mobot.followLine(South);
    Mobot.realign();
    Mobot.followLine(East);
    //    Mobot.realign();
    Mobot.followLine(East);
  }

  Mobot.realign();
  lifterDown();
}

void handleSecondPallet() {
  // Go to (2,1)
  Mobot.realign();

  if (*colorName == "RED") {
    Mobot.followLine(East);
    //    Mobot.realign();
    Mobot.followLine(East);

  } else {
    Mobot.followLine(North);
    Mobot.realign();
    Mobot.followLine(West);
  }

  Mobot.realign();

  // deliver
  lifterUp();
  if (*colorName == "RED") {
    Mobot.followLine(South);
    Mobot.realign();
    Mobot.followLine(West);
    //    Mobot.realign();
    Mobot.followLine(West);
  } else {
    Mobot.followLine(East);
  }

  Mobot.realign();
  lifterDown();
}

void handleThirdPallet() {
  if (*color == Red) {
    // From (0,0) to (1,3)
    Mobot.followLine(North);
    Mobot.realign();
    Mobot.followLine(North);
    Mobot.followLine(North);
    Mobot.realign();
    Mobot.followLine(East);
  } else {
    // From (3,1) to (2,2)
    Mobot.followLine(North);
    Mobot.realign();
    Mobot.followLine(West);
  }

  Mobot.realign();
  lifterUp();

  if (Mobot.x == 1) {
    if (*color == Red) {
      // From (1,3) to (0,3)
      Mobot.followLine(West);
    } else {
      // From (1,3) to (3,3)
      Mobot.followLine(East);
      Mobot.realign();
      Mobot.followLine(East);
    }
  } else {
    if (*color == Red) {
      // From (2,2) to (0,1)
      Mobot.followLine(West);
      //      Mobot.realign();
      Mobot.followLine(West);
    } else {
      // From (2,2) to (3,2)
      Mobot.followLine(East);
    }
  }

  Mobot.realign();
  lifterDown();
}

void handleFourthPallet() {
  // Last pallet is blue
  if (Mobot.x == 3) {
    // Position
    if (Mobot.y == 2) {
      // From (3,2) to (1,3)
      Mobot.followLine(North);
      Mobot.realign();
      Mobot.followLine(West);
      Mobot.followLine(West);
    } else {
      // From (3,3) to (2,2)
      Mobot.followLine(West);
      Mobot.realign();
      Mobot.followLine(South);
    }
  } else {
    if (Mobot.y == 2) {
      // From (0,2) to (1,3)
      Mobot.followLine(North);
      Mobot.realign();
      Mobot.followLine(East);
    } else {
      // From (0,3) to (2,2)
      Mobot.followLine(South);
      Mobot.realign();
      Mobot.followLine(East);
      Mobot.followLine(East);
    }
  }

  Mobot.realign();
  lifterUp();

  if (Mobot.x == 1) {
    if (*color == Red) {
      // From (1,3) to (0,3)
      Mobot.followLine(West);
    } else {
      // From (1,3) to (3,3)
      Mobot.followLine(East);
      Mobot.followLine(East);
    }
  } else {
    if (*color == Red) {
      // From (2,2) to (0,2)
      Mobot.followLine(West);
      Mobot.followLine(West);
    } else {
      // From (2,2) to (3,2)
      Mobot.followLine(East);
    }
  }

  Mobot.realign();
  lifterDown();
}

void returnToStart() {
  uint8_t timesMoved = 0;

  while (Mobot.y != 0) {
    Mobot.followLine(South);
    timesMoved++;

    //    if (timesMoved >= 2) {
    //      Mobot.realign();
    //      timesMoved = 0;
    //    }
  }

  Mobot.realign();

  if (Mobot.x == 0) {
    Mobot.followLine(East);
  } else {
    while (Mobot.x != 1) {
      Mobot.followLine(West);
      //            Mobot.realign();
    }
  }
}

void executeChallengeOne() {
  pixels.clear();
  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();

  Mobot.setPosition(1, 0, North);
  delay(500);
  //  Mobot.realign();

  handleFirstPallet();
  handleSecondPallet();
  handleThirdPallet();
  handleFourthPallet();
  returnToStart();

  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();
  isGreenLedOn = true;
}
