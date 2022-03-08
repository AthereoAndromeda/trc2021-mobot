void initRotary() {
  pinMode(ROTARY_CLK, INPUT);
  pinMode(ROTARY_DTP, INPUT);
  pinMode(ROTARY_SWP, INPUT_PULLUP);

  lrotState = digitalRead(ROTARY_CLK);
  Serial.println(lrotState);

  Serial.println(">> Rotary encoder configuration successful!");
}


void rotaryHandler() {
  ssd.setTextSize(2);

  // ENCODER KNOB READINGS
  crotState = digitalRead(ROTARY_CLK);

  if (crotState != lrotState && crotState == 0) {
    if (digitalRead(ROTARY_DTP) != crotState) {
      rotaryVal++;
      taskCounter++;
      rotaryDir = CW;
    } else {
      rotaryVal--;
      taskCounter--;
      rotaryDir = CCW;
    }
  }
  lrotState = crotState;

  if (taskCounter > MAX_TASKS) {
    taskCounter = 0;
  } else if (taskCounter < 0) {
    taskCounter = MAX_TASKS;
  }

  switch (taskCounter) {
    case 0:
      ssd.println("Calibrate Sensors");
      break;

    case 1:
      ssd.println("Cycle LED");
      break;

    case 2:
      ssd.println("Raise Lifter");
      break;

    case 3:
      ssd.println("Lower Lifter");
      break;

    case 4:
      ssd.println("Follow Line");
      break;

    case 5:
      ssd.println("Task 1");
      break;
  }

  int buttonState = digitalRead(ROTARY_SWP);

  if (buttonState == LOW) {
    if (millis() - lbutPress > 50) {
      Serial.println("Pressed!");
      ssd.println("Executing!");
      ssd.display();

      ssd.setTextSize(1);
      taskHandler(taskCounter);
      ssd.setTextSize(2);
    }
    lbutPress = millis();
  }

  ssd.display();
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.setTextSize(1);
}
