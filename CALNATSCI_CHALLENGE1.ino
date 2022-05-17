String *colorName = &Mobot.colorData.name;

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

void handleFirstPallet() {
  Mobot.followLine(North);
  Mobot.realign();

  lifterUp();
  colorHandler();

  if (*colorName == "RED") {
    Mobot.followLine(West);
  } else {
    Mobot.followLine(South);
    Mobot.realign();
    Mobot.followLine(East);
    Mobot.realign();
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
    Mobot.realign();
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
    Mobot.realign();
    Mobot.followLine(West);
  } else {
    Mobot.followLine(East);
  }

  Mobot.realign();
  lifterDown();
}

void handleThirdPallet() {
  if (*colorName == "RED") {
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
    if (*colorName == "RED") {
      // From (1,3) to (0,3)
      Mobot.followLine(West);
    } else {
      // From (1,3) to (3,3)
      Mobot.followLine(East);
      Mobot.realign();
      Mobot.followLine(East);
    }
  } else {
    if (*colorName == "RED") {
      // From (2,2) to (0,1)
      Mobot.followLine(West);
      Mobot.realign();
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
    if (*colorName == "RED") {
      // From (1,3) to (0,3)
      Mobot.followLine(West);
    } else {
      // From (1,3) to (3,3)
      Mobot.followLine(East);
      Mobot.followLine(East);
    }
  } else {
    if (*colorName == "RED") {
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
  while (Mobot.y != 0) {
    Mobot.followLine(South);
    Mobot.realign();
  }

  if (Mobot.x == 0) {
    Mobot.followLine(East);
  } else {
    while (Mobot.x != 1) {
      Mobot.followLine(West);
      Mobot.realign();
    }
  }
}

void executeChallengeOne() {
  pixels.clear();
  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();

  Mobot.setPosition(1, 0, North);
  delay(500);
  Mobot.realign();

  handleFirstPallet();
  handleSecondPallet();
  handleThirdPallet();
  handleFourthPallet();
  returnToStart();

  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();
}
