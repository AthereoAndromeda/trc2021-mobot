#define TIMES_COUNTED_TO_PASS 5

void taskTen() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.println("Calibrating Line");
  ssd.println("Sensors...");
  ssd.display();

  calibrateAllSensors();
}

void resetValues(uint8_t* a, uint8_t* b, uint8_t* c) {
  *a = 0;
  *b = 0;
  *c = 0;
}

void detectColor(
  String colorName,
  uint8_t* colorCounted,
  uint8_t* color1,
  uint8_t* color2,
  uint8_t* color3,
  bool* lifterBool,
  bool enableEleven,
  bool enableTwelve
) {
  *colorCounted = *colorCounted + 1;

  if (enableEleven) {
    ssd.println(colorName);
    ssd.display();
  }

  if (enableTwelve && *colorCounted > TIMES_COUNTED_TO_PASS && !(*lifterBool)) {
    resetValues(color1, color2, color3);
    delay(1000);
    lifterUp();
    *lifterBool = true;
  }
}

void taskElevenTwelve(bool enableEleven, bool enableTwelve) {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.setTextSize(2);

  // COLOR SENSOR READINGS
  apds.getColorData(&redVal, &greenVal, &blueVal, &clearVal);

  // Put values between 0-255
  redCalib = constrain(map(redVal, redMin, redMax, 0, 255), 0, 255);
  greenCalib = constrain(map(greenVal, greenMin, greenMax, 0, 255), 0, 255);
  blueCalib = constrain(map(blueVal, blueMin, blueMax, 0, 255), 0, 255);
  clearCalib = constrain(map(clearVal, clearMin, clearMax, 0, 255), 0, 255);

  // Allow unsigned ints to overflow, it is fine
  const uint8_t timesCountedToPass = TIMES_COUNTED_TO_PASS;
  static uint8_t redCounted = 0;
  static uint8_t greenCounted = 0;
  static uint8_t blueCounted = 0;
  static uint8_t noneCounted = 0;

  const uint8_t clearCalibThreshold = 20;
  uint8_t maxRange = clearCalib + clearCalibThreshold;
  int8_t minRange = clearCalib - clearCalibThreshold; // Keep this signed

  if ((redCalib > greenCalib) && (redCalib > blueCalib) && (redCalib >= clearCalib)) {
    Serial.println(">> Red-colored pallet detected!");
    detectColor("RED", &redCounted, &greenCounted, &blueCounted, &noneCounted, &isLifterUp, enableEleven, enableTwelve);

  }
  else if ((greenCalib > redCalib) && (greenCalib > blueCalib) && (greenCalib >= clearCalib)) {
    Serial.println(">> Green-colored pallet detected!");

    if (enableEleven) {
      ssd.println("GREEN");
      ssd.display();
    }
  }
  else if ((blueCalib > redCalib) && (blueCalib > greenCalib) && (blueCalib >= minRange && blueCalib <= maxRange)) {
    Serial.println(">> Blue-colored pallet detected!");
    detectColor("BLUE", &blueCounted, &greenCounted, &redCounted, &noneCounted, &isLifterUp, enableEleven, enableTwelve);

  } else {
    apdsColor = "NONE";
    noneCounted++;
    Serial.println(">> Non-existent pallet detected!");

    if (noneCounted > timesCountedToPass) {
      resetValues(&redCounted, &blueCounted, &greenCounted);
      noneCounted = 0;
    }

    if (enableEleven) {
      ssd.println("NONE");
      ssd.display();
    }

    if (enableTwelve && isLifterUp) {
      delay(1000);
      lifterDown();
      isLifterUp = false;
    }
  }

  if (isLifterUp) {
    lifterDown();
  }
  Serial.println(redCounted);
  Serial.println(greenCounted);
  Serial.println(blueCounted);
  Serial.println(noneCounted);

  //  delay(50);
}

void executeCheckThree() {
  // Task Ten
  taskTen();

  // Tasks Eleven and Twelve are executed in the loop function
}
