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

  lifterDown();
}

void handleThirdPallet() {
  Mobot.realign();

  if (*colorName == "RED") {
    Mobot.followLine(North);
    Mobot.realign();
    Mobot.followLine(North);
    Mobot.followLine(North);
    Mobot.realign();
    Mobot.followLine(East);
  } else {
    Mobot.followLine(North);
    Mobot.realign();
    Mobot.followLine(West);
  }

  Mobot.realign();
  lifterUp();

  if (*colorName == "RED") {
    if (Mobot.x == 1) {
      Mobot.followLine(West);
    } else {
      Mobot.followLine(West);
      Mobot.followLine(West);
    }

  } else {
    if (Mobot.x == 1) {
      Mobot.followLine(North);
      Mobot.realign();
      Mobot.followLine(East);
      Mobot.followLine(East);
    } else {
      Mobot.followLine(East);
    }

  }

  lifterDown();
}


void executeChallengeOne() {
  pixels.clear();
  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();

  Mobot.setPosition(1, 0, North);
  delay(2000);
  Mobot.realign();

  handleFirstPallet();
  handleSecondPallet();
  handleThirdPallet();
}
