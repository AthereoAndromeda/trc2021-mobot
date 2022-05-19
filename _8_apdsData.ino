void initApds() {
  apds.enableColor(true);
  apds.enableProximity();
  while (!apds.colorDataReady()) delay(100);

  Serial.println(">> Color sensor calibration successful!");
}

void calibrateApds() {
  pixels.clear();
  pixels.show();

  for (uint8_t i = 0; i < APDS_ACCURACY; i++) {
    apds.getColorData(&redVal, &greenVal, &blueVal, &clearVal);

    redArr[i] = redVal;
    greenArr[i] = greenVal;
    blueArr[i] = blueVal;
    clearArr[i] = clearVal;
  }

  redMin, redMax = redArr[0];
  greenMin, greenMax = greenArr[0];
  blueMin, blueMax = blueArr[0];
  clearMin, clearMax = clearArr[0];

  for (uint8_t i = 0; i < APDS_ACCURACY; i++) {
    redMin = min(redArr[i], redMin);
    redMax = max(redArr[i], redMax);

    greenMin = min(greenArr[i], greenMin);
    greenMax = max(greenArr[i], greenMax);

    blueMin = min(blueArr[i], blueMin);
    blueMax = max(blueArr[i], blueMax);

    clearMin = min(clearArr[i], clearMin);
    clearMax = max(clearArr[i], clearMax);
  }
}

void detectColor(ColorData *data) {
  Serial.println(data->name);

  // COLOR SENSOR READINGS
  apds.getColorData(&redVal, &greenVal, &blueVal, &clearVal);
  uint16_t prox = apds.readProximity();

  // Put values between 0-255
  redCalib = constrain(map(redVal, redMin, redMax, 0, 255), 0, 255);
  greenCalib = constrain(map(greenVal, greenMin, greenMax, 0, 255), 0, 255);
  blueCalib = constrain(map(blueVal, blueMin, blueMax, 0, 255), 0, 255);
  clearCalib = constrain(map(clearVal, clearMin, clearMax, 0, 255), 0, 255);

  Serial.print("Prosimity: ");
  Serial.println(prox);
  Serial.println("Colors");
  Serial.print("Red: ");
  Serial.println(redCalib);
  Serial.print("Green: ");
  Serial.println(greenCalib);
  Serial.print("Blue: ");
  Serial.println(blueCalib);
  Serial.print("Clear: ");
  Serial.println(clearCalib);

  const uint8_t threshold = 15;
  const uint8_t detectThreshold = 100;
  uint8_t maxRange = clearCalib + threshold;
  int8_t minRange = clearCalib - threshold; // Keep this signed
  uint8_t maxVal = 250;

  if ((prox <= 8) /*&& (redCalib >= maxVal) && (blueCalib >= maxVal) && (greenCalib >= maxVal)*/ && (clearCalib >= 200)) {
    Serial.println(">> Non-existent pallet detected!");
    data->name = "NONE";
    data->color = None;
  }

  else if ((redCalib >= detectThreshold) && (redCalib >= greenCalib) && (redCalib >= blueCalib) && (redCalib >= minRange)) {
    Serial.println(">> Red-colored pallet detected!");
    data->name = "RED";
    data->color = Red;
  }
  else if ((greenCalib >= detectThreshold) && (greenCalib >= redCalib) && (greenCalib >= blueCalib) && (greenCalib >= minRange)) {
    Serial.println(">> Green-colored pallet detected!");
    data->name = "GREEN";
    data->color = Green;
  }
  else if (/*(blueCalib >= detectThreshold) &&*/ (blueCalib >= redCalib - 10) && (blueCalib >= greenCalib) && (blueCalib >= minRange)) {
    Serial.println(">> Blue-colored pallet detected!");
    data->name = "BLUE";
    data->color = Blue;
  }

  else {
    Serial.println(">> Non-existent pallet detected!");
    data->name = "NONE";
    data->color = None;
  }
}
