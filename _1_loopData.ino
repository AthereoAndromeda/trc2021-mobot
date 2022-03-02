// Sensors are arranged clockwise
uint16_t lineValues[SENSOR_COUNT][SENSOR_COUNT];

int8_t taskCounter;
#define MAX_TASKS 3

void taskHandler(uint8_t task) {
  switch (task) {
    case 0:
      calibrateAllSensors();
      break;

    case 1:
      cycleLed();
      break;
  }
}

void button() {
  ssd.setTextSize(2);

  // ENCODER KNOB READINGS
  crotState = digitalRead(ROTARY_CLK);

//  Serial.print("crot: ");
//  Serial.println(crotState);
//  Serial.print("lrot: ");
//  Serial.println(lrotState);
//  Serial.print("DTP: ");
//  Serial.println(digitalRead(ROTARY_DTP));

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

//  Serial.print("TC: ");
//  Serial.println(taskCounter);
//  Serial.print("rotVal: ");
//  Serial.println(rotaryVal);
//
//  Serial.println(rotaryDir);

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
      ssd.println("Task 2");
      break;

    case 3:
      ssd.println("Task 3");
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

void loop() {
  button();

  QTR_Front.readCalibrated(lineValues[0]);
  QTR_Right.readCalibrated(lineValues[1]);
  QTR_Back.readCalibrated(lineValues[2]);
  QTR_Left.readCalibrated(lineValues[3]);

  for (int i = 0; i < SENSOR_COUNT; i++) {
    Serial.println(lineValues[2][i]);
  }

  delay(100);
}
