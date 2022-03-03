// Sensors are arranged clockwise
uint16_t lineValues[SENSOR_COUNT][SENSOR_COUNT];

int8_t taskCounter;
#define MAX_TASKS 5

// Just moves forward when line is detected
void followLine() {
  delay(3000);
  Serial.println("followLine called");
  uint16_t *frontValues = lineValues[0];
  uint16_t *backValues = lineValues[2];
  uint16_t val;
  uint16_t avg;

  motorMove(Forward, 0);

  // Just uses average to detect a line
  do {
    QTR_Front.readCalibrated(frontValues);
    QTR_Back.readCalibrated(backValues);

    val = 0;
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
      val += frontValues[i];
      Serial.println(frontValues[i]);
    }

    avg = val / 4;
    Serial.print("new avg: ");
    Serial.println(avg);

    // Very Basic Line Correcting
    if (frontValues[0] < 200) {
      setMotorDir(Forward_Right);
    } else if (frontValues[3] < 200) {
      setMotorDir(Forward_Left);
    } else {
      setMotorDir(Forward);
    }

    delay(10);
  } while (avg > 100);

  stopMotors();
}

void taskHandler(uint8_t task) {
  switch (task) {
    case 0:
      calibrateAllSensors();
      break;

    case 1:
      cycleLed();
      break;

    case 2:
      lifterUp();
      break;

    case 3:
      lifterDown();
      break;

    case 4:
      followLine();
      break;
  }
}

void button() {
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

  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    Serial.println(lineValues[2][i]);
  }

  delay(100);
}
