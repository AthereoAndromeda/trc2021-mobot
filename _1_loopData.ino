int8_t taskCounter;
#define MAX_TASKS 5

void detectCol(ColorData *data) {
  Serial.println(data->name);

  // COLOR SENSOR READINGS
  apds.getColorData(&redVal, &greenVal, &blueVal, &clearVal);

  // Put values between 0-255
  redCalib = constrain(map(redVal, redMin, redMax, 0, 255), 0, 255);
  greenCalib = constrain(map(greenVal, greenMin, greenMax, 0, 255), 0, 255);
  blueCalib = constrain(map(blueVal, blueMin, blueMax, 0, 255), 0, 255);
  clearCalib = constrain(map(clearVal, clearMin, clearMax, 0, 255), 0, 255);

  const uint8_t clearCalibThreshold = 20;
  uint8_t maxRange = clearCalib + clearCalibThreshold;
  int8_t minRange = clearCalib - clearCalibThreshold; // Keep this signed

  if ((redCalib > greenCalib) && (redCalib > blueCalib) && (redCalib >= clearCalib)) {
    Serial.println(">> Red-colored pallet detected!");
    data->name = "RED";
  }
  else if ((greenCalib > redCalib) && (greenCalib > blueCalib) && (greenCalib >= clearCalib)) {
    Serial.println(">> Green-colored pallet detected!");
    data->name = "GREEN";
  }
  else if ((blueCalib > redCalib) && (blueCalib > greenCalib) && (blueCalib >= minRange && blueCalib <= maxRange)) {
    Serial.println(">> Blue-colored pallet detected!");
    data->name = "BLUE";
  } else {
    Serial.println(">> Non-existent pallet detected!");
    data->name = "NONE";
  }
}

void correctMobotOrientation() {
  uint16_t *frontValues = lineValues[0];
  uint16_t *rightValues = lineValues[1];
  uint16_t *backValues = lineValues[2];
  uint16_t *leftValues = lineValues[3];
  uint16_t avg;

  motorMove(Stop, 0);
  do {
    QTR_Front.readCalibrated(frontValues);
    QTR_Back.readCalibrated(backValues);
    QTR_Right.readCalibrated(rightValues);
    QTR_Left.readCalibrated(leftValues);

    int val = 0;
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
      val += frontValues[i];
      val += backValues[i];
    }

    avg = val / 8;
    Serial.println(avg);
    if (frontValues[0] < 200 && backValues[3] < 200) {
      setMotorDir(CW_Center_Center);
    } else {
      setMotorDir(CCW_Center_Center);
    }
  } while (avg < 250);

  stopMotors();
}

void runLineFollower(
  uint16_t intersectionValues_One[SENSOR_COUNT],
  uint16_t intersectionValues_Two[SENSOR_COUNT],
  uint16_t arr[SENSOR_COUNT],
  void (*cb)(uint16_t[4])
) {
  uint16_t *frontValues = lineValues[0];
  uint16_t *rightValues = lineValues[1];
  uint16_t *backValues = lineValues[2];
  uint16_t *leftValues = lineValues[3];
  long int timeElapsed = millis();
  uint16_t avg;

  // Just uses average to detect a line
  do {
    QTR_Front.readCalibrated(frontValues);
    QTR_Back.readCalibrated(backValues);
    QTR_Right.readCalibrated(rightValues);
    QTR_Left.readCalibrated(leftValues);

    int val = 0;
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
      val += arr[i];
      //      Serial.println(frontValues[i]);
    }

    avg = val / SENSOR_COUNT;
    Serial.print("new avg: ");
    Serial.println(avg);

    // Intersection detecting
    if (intersectionValues_One[1] > 200 & intersectionValues_Two[1] > 200) {
      long int timeDetected = millis();

      // So it doesn't detect while on initial intersection
      if (timeDetected - timeElapsed > 1000) {
        break;
      }
    }

    // Very Basic Line Correcting
    cb(arr);
  } while (avg > 100);
}

// Just moves forward when line is detected
void followLine(LineDirection direction) {
  Serial.println("followLine called");
  uint16_t *frontValues = lineValues[0];
  uint16_t *rightValues = lineValues[1];
  uint16_t *backValues = lineValues[2];
  uint16_t *leftValues = lineValues[3];
  uint16_t val;
  uint16_t avg;
  uint16_t eastVal;
  uint16_t eastAvg;

  if (direction == North) {
    motorMove(Forward, 0);
    runLineFollower(rightValues, leftValues, frontValues, [](uint16_t arr[4]) {
      if (arr[0] < 200 && arr[3] > 200) {
        setMotorDir(Forward_Right);
      } else if (arr[3] < 200 && arr[0] > 200) {
        setMotorDir(Forward_Left);
      } else {
        setMotorDir(Forward);
      }
    });
  } else if (direction == East) {
    motorMove(Right, 0);
    runLineFollower(frontValues, backValues, rightValues, [](uint16_t arr[4]) {
      if (arr[0] < 200 && arr[3] > 200) {
        setMotorDir(Backward_Left);
      } else if (arr[3] < 200 && arr[0] > 200) {
        setMotorDir(Forward_Right);
      } else {
        setMotorDir(Right);
      }
    });
  } else if (direction == West) {
    motorMove(Left, 0);
    runLineFollower(frontValues, backValues, leftValues, [](uint16_t arr[4]) {
      if (arr[0] < 200 && arr[3] > 200) {
        setMotorDir(Backward_Left);
      } else if (arr[3] < 200 && arr[0] > 200) {
        setMotorDir(Forward_Left);
      } else {
        setMotorDir(Left);
      }
    });
  } else {
    motorMove(Backward, 0);
    runLineFollower(leftValues, rightValues, backValues, [](uint16_t arr[4]) {
      if (arr[0] < 200 && arr[3] > 200) {
        setMotorDir(Backward_Right);
      } else if (arr[3] < 200 && arr[0] > 200) {
        setMotorDir(Backward_Left);
      } else {
        setMotorDir(Backward);
      }
    });
  }

  stopMotors();
  delay(10);
}

void taskHandler(uint8_t task) {
  switch (task) {
    case 0:
      delay(1000);
      calibrateAllSensors();
      calibrateApds();
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
      followLine(South);
      break;

    case 5:
      taskOne_2();
      break;
  }
}

void loop() {
  rotaryHandler();

  detectCol(&colorData);
  //  taskElevenTwelve(true, true);
  //  QTR_Front.readCalibrated(lineValues[0]);
  //  QTR_Right.readCalibrated(lineValues[1]);
  //  QTR_Back.readCalibrated(lineValues[2]);
  //  QTR_Left.readCalibrated(lineValues[3]);
  //
  //  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
  //    Serial.println(lineValues[2][i]);
  //  }

  delay(100);
}
