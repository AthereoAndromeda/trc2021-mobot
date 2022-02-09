void loop() {
  //  taskEleven();
  delay(100);

  // ENCODER KNOB READINGS
  //  crotState = digitalRead(ROTARY_CLK);
  //  Serial.print("crotState: ");
  //  Serial.println(crotState);
  //  Serial.print("lrotState:");
  //  Serial.println(lrotState);
  //
  //  if (crotState != lrotState && crotState == 0) {
  //    if (digitalRead(ROTARY_DTP) != crotState) {
  //      rotaryVal++;
  //      rotaryDir = "CW";
  //    }
  //    else {
  //      rotaryVal--;
  //      rotaryDir = "CCW";
  //    }
  //  }
  //  lrotState = crotState;
  //
  //
  //  Serial.print("rotaryVal: ");
  //  Serial.println(rotaryVal);
  //  Serial.print("RotaryDir: ");
  //  Serial.println(rotaryDir);

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
  //  buttonState = digitalRead(ROTARY_SWP);
  //  cbutPress = millis();
  //
  //  Serial.println(buttonState);
  //  Serial.println(cbutPress);
  //
  //  if (buttonState == LOW) {
  //    Serial.println("Button Pressed!");
  //    delay(1000);
  //    if (cbutPress - lbutPress > 50) {
  //      if (rotaryVal >= 0 && rotaryVal <= 42) {
  //        //        taskOne();
  //      }
  //      else if (rotaryVal >= 43 && rotaryVal <= 84) {
  //        //        taskTwo();
  //      }
  //      else if (rotaryVal >= 85 && rotaryVal <= 127) {
  //        //        taskThree();
  //      }
  //      else if (rotaryVal >= 128 && rotaryVal <= 170) {
  //        //        taskFour();
  //      }
  //      else if (rotaryVal >= 171 && rotaryVal <= 213) {
  //        //        taskFive();
  //      }
  //      else if (rotaryVal >= 214 && rotaryVal <= 255) {
  //        //        taskSix();
  //      }
  //      Serial.println("Executing commands for selected task!");
  //      delay(2000);
  //    }
  //    lbutPress = cbutPress;
  //  }
  //
  //  delay(1);
}
