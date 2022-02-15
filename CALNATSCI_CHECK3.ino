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

void displayColor(bool isEnabled, String color) {
  if (isEnabled) {
    ssd.println(color);
    ssd.display();
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
  const uint8_t timesCountedToPass = 5;
  static uint8_t redCounted = 0;
  static uint8_t greenCounted = 0;
  static uint8_t blueCounted = 0;
  static uint8_t noneCounted = 0;

  const uint8_t clearCalibThreshold = 20;
  uint8_t maxRange = clearCalib + clearCalibThreshold;
  int8_t minRange = clearCalib - clearCalibThreshold; // Keep this signed

  if ((redCalib > greenCalib) && (redCalib > blueCalib) && (redCalib >= clearCalib)) {
    apdsColor = "RED";
    redCounted++;
    Serial.println(">> Red-colored pallet detected!");

    displayColor(enableEleven, apdsColor);

    if (enableTwelve && redCounted > timesCountedToPass && !isLifterUp) {
      resetValues(&noneCounted, &blueCounted, &greenCounted);
      delay(1000);
      lifterUp();
      isLifterUp = true;
    }
  }
  else if ((greenCalib > redCalib) && (greenCalib > blueCalib) && (greenCalib >= clearCalib)) {
    apdsColor = "GREEN";
    greenCounted++;
    Serial.println(">> Green-colored pallet detected!");

    displayColor(enableEleven, apdsColor);

    if (greenCounted > timesCountedToPass) {
      resetValues(&redCounted, &blueCounted, &noneCounted);
    }
  }
  else if ((blueCalib > redCalib) && (blueCalib > greenCalib) && (blueCalib >= minRange && blueCalib <= maxRange)) {
    apdsColor = "BLUE";
    blueCounted++;
    Serial.println(">> Blue-colored pallet detected!");

    displayColor(enableEleven, apdsColor);

    if (enableTwelve && blueCounted > timesCountedToPass && !isLifterUp) {
      resetValues(&redCounted, &greenCounted, &noneCounted);
      delay(1000);
      lifterUp();
      isLifterUp = true;
    }
  } else {
    apdsColor = "NONE";
    noneCounted++;
    Serial.println(">> Non-existent pallet detected!");

    if (noneCounted > timesCountedToPass) {
      resetValues(&redCounted, &blueCounted, &greenCounted);
      noneCounted = 0;
    }

    displayColor(enableEleven, apdsColor);

    if (enableTwelve && isLifterUp) {
      delay(1000);
      lifterDown();
      isLifterUp = false;
    }
  }

  Serial.println(redCounted);
  Serial.println(greenCounted);
  Serial.println(blueCounted);
  Serial.println(noneCounted);

  delay(50);
}

void executeCheckThree() {
  // Task Ten
  taskTen();

  // Tasks Eleven and Twelve are executed in the loop function
}
