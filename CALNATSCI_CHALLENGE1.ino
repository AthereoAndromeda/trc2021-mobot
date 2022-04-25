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
  Mobot.realign();


  //  colorHandler();
  Mobot.followLine(North);
  Mobot.realign();

  //  colorHandler();
  Mobot.followLine(North);
  Mobot.realign();

  //  colorHandler();
  Mobot.followLine(East);
  Mobot.realign();

  pixels.clear();
  pixels.show();
  delay(100);

  colorHandler();
  moveToLocation();

  pixels.clear();
  pixels.show();
  //  isGreenLedOn = true;
}
