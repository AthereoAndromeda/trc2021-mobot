void taskSeven() {
  cycleLed();
}

int8_t ledCounter = 0;
RotaryDirection lastDir;

void taskEight() {
  // ENCODER KNOB READINGS
  crotState = digitalRead(ROTARY_CLK);
  Serial.println(ledCounter);

  if (crotState != lrotState && crotState == 0) {
    if (digitalRead(ROTARY_DTP) != crotState) {
      rotaryVal++;
      rotaryDir = CW;
    } else {
      rotaryVal--;
      rotaryDir = CCW;
    }

    ledCounter++;
  }

  // If direction chages, reset ledCounter so cycle
  // always restarts with first color (red)
  if (lastDir != rotaryDir) {
    ledCounter = 0;
  }

  lrotState = crotState;
  lastDir = rotaryDir;

  if (ledCounter > 3) {
    ledCounter = 0;
  } else if (ledCounter < 0) {
    ledCounter = 3;
  }

  if (rotaryDir == CW) {
    if (ledCounter == 0) {
      pixels.setPixelColor(0, 255, 0, 0);
    } else if (ledCounter == 1) {
      pixels.setPixelColor(0, 0, 255, 0);
    } else if (ledCounter == 2) {
      pixels.setPixelColor(0, 0, 0, 255);
    } else if (ledCounter == 3) {
      pixels.setPixelColor(0, 255, 255, 255);
    }
  } else {
    if (ledCounter == 0) {
      pixels.setPixelColor(0, 255, 0, 0);
    } else if (ledCounter == 1) {
      pixels.setPixelColor(0, 255, 255, 255);
    } else if (ledCounter == 2) {
      pixels.setPixelColor(0, 0, 0, 255);
    } else if (ledCounter == 3) {
      pixels.setPixelColor(0, 0, 255, 0);
    }
  }

  pixels.show();
}

void taskNine() {
  for (uint8_t i = 1; i <= 21; i++) {
    ssd.clearDisplay();
    ssd.setCursor(0, 0);
    int8_t trailingInt = i - 8;

    for (int8_t j = trailingInt; j < i; j++) {
      if (j <= 0) {
        ssd.println(" ");
      } else {
        ssd.println(j);
      }
    }

    ssd.display();
    delay(100);
  }
}


void executeCheckTwo() {
  // Cycle LED
  taskSeven();

  delay(5000);

  // Rotary Encoder
  // is in loopData

  // Scroll 1-20 LCD
  taskNine();
}
