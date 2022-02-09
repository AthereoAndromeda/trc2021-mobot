void taskOne() {
  motorMove(Forward, MOTOR_DELAY * 2);
}

void taskTwo() {
  motorMove(Backward, MOTOR_DELAY * 2);
}

void taskThree() {
  motorMove(CCW_Center_Center, ROTATE_MOTOR_DELAY * 2);
}

void taskFour() {
  motorMove(CW_Center_Center, ROTATE_MOTOR_DELAY * 2);
}

void taskFive() {
  motorMove(Left, SIDEWAYS_MOTOR_DELAY * 2);
}

void taskSix() {
  motorMove(Right, SIDEWAYS_MOTOR_DELAY * 2);
}

void taskSeven() {
  cycleLed(500);
}

void taskNine() {
  for (uint8_t i = 1; i <= 21; i++) {
    ssd.clearDisplay();
    ssd.setCursor(0, 0);
    int trailingInt = i - 8;

    for (uint8_t j = trailingInt; j < i; j++) {
      if (j <= 0) {
        ssd.println("");
      } else {
        ssd.println(j);
      }
    }

    ssd.display();
    delay(100);
  }
}

void taskTen() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.println("Calibrating Line");
  ssd.println("Sensors...");
  ssd.display();

  calibrateAllSensors();
}

uint16_t sensorValues[SensorCount];
boolean isLifterUp = false;

void taskEleven() {
  // COLOR SENSOR READINGS
  apds.getColorData(&redVal, &greenVal, &blueVal, &clearVal);

  redCalib = constrain(map(redVal, redMin, redMax, 0, 255), 0, 255);
  greenCalib = constrain(map(greenVal, greenMin, greenMax, 0, 255), 0, 255);
  blueCalib = constrain(map(blueVal, blueMin, blueMax, 0, 255), 0, 255);
  clearCalib = constrain(map(clearVal, clearMin, clearMax, 0, 255), 0, 255);

  Serial.print("redVal: ");
  Serial.print(redVal);
  Serial.print(" ");
  Serial.print(redMin);
  Serial.print(" ");
  Serial.print(redMax);
  Serial.print(" ");
  Serial.println();

  Serial.print("blueVal: ");
  Serial.print(" ");
  Serial.print(blueVal);
  Serial.print(" ");
  Serial.print(blueMin);
  Serial.print(" ");
  Serial.print(blueMax);
  Serial.println();

  Serial.print("greenVal: ");
  Serial.print(" ");
  Serial.print(greenVal);
  Serial.print(" ");
  Serial.print(greenMin);
  Serial.print(" ");
  Serial.print(greenMax);
  Serial.println();

  Serial.print("clearVal: ");
  Serial.print(" ");
  Serial.print(clearVal);
  Serial.print(" ");
  Serial.print(clearMin);
  Serial.print(" ");
  Serial.print(clearMax);
  Serial.println();

  Serial.println(redCalib);
  Serial.println(greenCalib);
  Serial.println(blueCalib);
  Serial.println(clearCalib);

  const uint8_t clearCalibThreshold = 10;
  uint8_t maxRange = clearCalib + clearCalibThreshold;
  int8_t minRange = clearCalib - clearCalibThreshold; // Keep this signed

  if ((redCalib > greenCalib) && (redCalib > blueCalib) && (redCalib >= clearCalib)) {
    apdsColor = "red";
    Serial.println(">> Red-colored pallet detected!");
    pixels.setPixelColor(0, 255, 0, 0);
    pixels.show();

    if (!isLifterUp) {
      delay(1000);
      lifterUp();
      isLifterUp = true;
    }
  }
  else if ((greenCalib > redCalib) && (greenCalib > blueCalib) && (greenCalib >= clearCalib)) {
    apdsColor = "green";
    pixels.setPixelColor(0, 0, 255, 0);
    pixels.show();
    Serial.println(">> Green-colored pallet detected!");
  }
  //  else if ((blueCalib > redCalib) && (blueCalib > greenCalib) && (blueCalib >= clearCalib)) {
  else if ((blueCalib > redCalib) && (blueCalib > greenCalib) && (blueCalib >= minRange && blueCalib <= maxRange)) {
    apdsColor = "blue";
    pixels.setPixelColor(0, 0, 0, 255);
    pixels.show();
    Serial.println(">> Blue-colored pallet detected!");

    if (!isLifterUp) {
      delay(1000);
      lifterUp();
      isLifterUp = true;
    }
  }
  else {
    apdsColor = "none";
    Serial.println(">> Non-existent pallet detected!");
    pixels.setPixelColor(0, 0, 0, 0);
    pixels.clear();
    pixels.show();

    if (isLifterUp) {
      delay(1000);
      lifterDown();
      isLifterUp = false;
    }
  }
}

// ====

void executeCheckOne() {
  // Forward/Backwards
  taskOne();
  taskTwo();

  // Rotate Left/Right
  taskThree();
  taskFour();

  // Shift Left/Right
  taskFive();
  taskSix();
}

void executeCheckTwo() {
  // Cycle LED
  taskSeven();

  // Rotary Encoder
  // Is skipped

  // Scroll 1-20 LCD
  taskNine();
}
