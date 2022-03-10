void initRotary() {
  pinMode(ROTARY_CLK, INPUT);
  pinMode(ROTARY_DTP, INPUT);
  pinMode(ROTARY_SWP, INPUT_PULLUP);

  lrotState = digitalRead(ROTARY_CLK);
  Serial.println(lrotState);

  Serial.println(">> Rotary encoder configuration successful!");
}

inline void taskHandler(uint8_t task) {
  taskData[task].execute();
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

  if (taskCounter > TASK_COUNT - 1) {
    taskCounter = 0;
  } else if (taskCounter < 0) {
    taskCounter = TASK_COUNT - 1;
  }

  String *displayTextPtr = &taskData[taskCounter].displayText;
  ssd.println(*displayTextPtr);

  int buttonState = digitalRead(ROTARY_SWP);
  if (buttonState == LOW) {
    if (millis() - lbutPress > 50) {
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
  delay(100);
}
