uint16_t sensorValues[SensorCount];
boolean isLifterUp = false;

void loop() {
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
  else if ((blueCalib > redCalib) && (blueCalib > greenCalib) && (blueCalib >= clearCalib)) {
    apdsColor = "blue";
    pixels.setPixelColor(0, 0, 0, 255);
    pixels.show();
    Serial.println(">> Blue-colored pallet detected!");
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



  delay(500);

  return;


  // read raw sensor values
  qtr_front.read(sensorValues);

  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
  // reflectance and 2500 means minimum reflectance
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

  delay(250);
  return;

  // ENCODER KNOB READINGS
  crotState = digitalRead(ROTARY_CLK);
  Serial.print("crotState: ");
  Serial.println(crotState);
  Serial.print("lrotState:");
  Serial.println(lrotState);

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


  Serial.print("rotaryVal: ");
  Serial.println(rotaryVal);
  Serial.print("RotaryDir: ");
  Serial.println(rotaryDir);

  // LCD SCREEN DISPLAYS
  //  if (rotaryVal >= 0 && rotaryVal <= 42) {
  //    ssd.println("Movement #01: Forward");
  //  }
  //  else if (rotaryVal >= 43 && rotaryVal <= 84) {
  //    ssd.println("Movement #02: Backward");
  //  }
  //  else if (rotaryVal >= 85 && rotaryVal <= 127) {
  //    ssd.println("Movement #03: Rotate Left");
  //  }
  //  else if (rotaryVal >= 128 && rotaryVal <= 170) {
  //    ssd.println("Movement #04: Rotate Right");
  //  }
  //  else if (rotaryVal >= 171 && rotaryVal <= 213) {
  //    ssd.println("Movement #05: Shift Left");
  //  }
  //  else if (rotaryVal >= 214 && rotaryVal <= 255) {
  //    ssd.println("Movement #06: Shift Right");
  //  }

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
