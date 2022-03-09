void taskTwoColorHandler() {
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

  delay(1000);
  pixels.clear();
  pixels.show();
}

void executeCheckTwo() {
  // Set Init position
  Mobot.orientation = South;
  Mobot.x = 1;
  Mobot.y = 0;

  //  correctMobotOrientation();
  //  correctMobotOrientation();

  delay(2000);
  taskTwoColorHandler();
  delay(2000);

  Mobot._followLine(South);
  taskTwoColorHandler();
  delay(2000);

  Mobot._followLine(South);
  taskTwoColorHandler();
  delay(2000);

  Mobot._followLine(South);
  taskTwoColorHandler();
  delay(2000);
}
