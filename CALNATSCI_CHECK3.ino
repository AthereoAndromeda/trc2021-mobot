void taskTen() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.println("Calibrating Line");
  ssd.println("Sensors...");
  ssd.display();

  calibrateAllSensors();
}


void taskElevenTwelve(bool enableEleven, bool enableTwelve) {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.setTextSize(2);
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
    apdsColor = "RED";
    Serial.println(">> Red-colored pallet detected!");

    if (enableEleven) {
      //      pixels.setPixelColor(0, 255, 0, 0);
      //      pixels.show();
      ssd.println(apdsColor);
      ssd.display();
    }

    if (enableTwelve && !isLifterUp) {
      delay(1000);
      lifterUp();
      isLifterUp = true;
    }
  }
  else if ((greenCalib > redCalib) && (greenCalib > blueCalib) && (greenCalib >= clearCalib)) {
    apdsColor = "GREEN";
    Serial.println(">> Green-colored pallet detected!");
    //    pixels.setPixelColor(0, 0, 255, 0);
    //    pixels.show();
    ssd.println(apdsColor);
    ssd.display();
  }
  else if ((blueCalib > redCalib) && (blueCalib > greenCalib) && (blueCalib >= minRange && blueCalib <= maxRange)) {
    apdsColor = "BLUE";
    Serial.println(">> Blue-colored pallet detected!");

    if (enableEleven) {
      //      pixels.setPixelColor(0, 0, 0, 255);
      //      pixels.show();
      ssd.println(apdsColor);
      ssd.display();
    }

    if (enableTwelve && !isLifterUp) {
      delay(1000);
      lifterUp();
      isLifterUp = true;
    }
  } else {
    apdsColor = "NONE";
    Serial.println(">> Non-existent pallet detected!");

    if (enableEleven) {
      //      pixels.clear();
      //      pixels.show();
      ssd.println(apdsColor);
      ssd.display();
    }

    if (enableTwelve && isLifterUp) {
      delay(1000);
      lifterDown();
      isLifterUp = false;
    }
  }
}

void executeCheckThree() {
  // Task Ten
  taskTen();

  // Tasks Eleven and Twelve are executed in the loop function
}
