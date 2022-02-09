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
  motorMove(CW_Center_Center, ROTATE_MOTOR_DELAY * 2 - 100);
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

void taskEight() {
  // ENCODER KNOB READINGS
  crotState = digitalRead(ROTARY_CLK);

  if (crotState != lrotState && crotState == 0) {
    if (digitalRead(ROTARY_DTP) != crotState) {
      rotaryVal++;
      rotaryDir = "CW";
    }
    else {
      rotaryVal--;
      rotaryDir = "CCW";
    }
  }
  lrotState = crotState;

  // ENCODER BUTTON READINGS
  buttonState = digitalRead(ROTARY_SWP);
  cbutPress = millis();

  Serial.println(buttonState);
  Serial.println(cbutPress);

  if (buttonState == LOW) {
    Serial.println("Button Pressed!");
    delay(1000);
    if (cbutPress - lbutPress > 50) {
      if (rotaryVal >= 0 && rotaryVal <= 42) {
        //        taskOne();
      }
      else if (rotaryVal >= 43 && rotaryVal <= 84) {
        //        taskTwo();
      }
      else if (rotaryVal >= 85 && rotaryVal <= 127) {
        //        taskThree();
      }
      else if (rotaryVal >= 128 && rotaryVal <= 170) {
        //        taskFour();
      }
      else if (rotaryVal >= 171 && rotaryVal <= 213) {
        //        taskFive();
      }
      else if (rotaryVal >= 214 && rotaryVal <= 255) {
        //        taskSix();
      }
      Serial.println("Executing commands for selected task!");
      delay(2000);
    }
    lbutPress = cbutPress;
  }

  delay(1);
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

void taskEleven() {
  // COLOR SENSOR READINGS
  apds.getColorData(&redVal, &greenVal, &blueVal, &clearVal);

  redCalib = constrain(map(redVal, redMin, redMax, 0, 255), 0, 255);
  greenCalib = constrain(map(greenVal, greenMin, greenMax, 0, 255), 0, 255);
  blueCalib = constrain(map(blueVal, blueMin, blueMax, 0, 255), 0, 255);
  clearCalib = constrain(map(clearVal, clearMin, clearMax, 0, 255), 0, 255);

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
  } else {
    apdsColor = "none";
    Serial.println(">> Non-existent pallet detected!");
    pixels.setPixelColor(0, 0, 0, 0);
    pixels.clear();
    pixels.show();
    Serial.println(isLifterUp);

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

void executeCheckThree() {
  // Task Ten
  calibrateAllSensors();

  // Tasks Eleven and Twelve are executed in the loop function
}
