int8_t taskCounter;

void detectColor(ColorData *data) {
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
  unsigned long int timeStarted = millis();
  uint8_t timesMoved;

  motorMove(Stop, 0);
  do {
    QTR_Front.readCalibrated(frontValues);
    QTR_Back.readCalibrated(backValues);
    QTR_Right.readCalibrated(rightValues);
    QTR_Left.readCalibrated(leftValues);

    Serial.println("AAAA");
    Serial.println(frontValues[1]);
    Serial.println(backValues[2]);
    Serial.println(leftValues[2]);
    Serial.println(rightValues[2]);

    int val = 0;
    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
      val += frontValues[i];
      val += backValues[i];
    }

    avg = val / 8;
    Serial.println(avg);

    unsigned long int timeNow = millis();
    //    if (timeNow - timeStarted >= 1000) {
    //      timesMoved++;
    //
    //      if (timesMoved == 0) {
    //        setMotorDir(Backward_Left);
    //        delay(10);
    //        setMotorDir(Stop);
    //      } else if (timesMoved == 1) {
    //        setMotorDir(Forward_Left);
    //        delay(10);
    //        setMotorDir(Stop);
    //      } else if (timesMoved == 2) {
    //        setMotorDir(Backward_Right);
    //        delay(10);
    //        setMotorDir(Stop);
    //      } else {
    //        timesMoved = 0;
    //      }
    //    }

    if (frontValues[0] < 200 && backValues[3] < 200) {
      setMotorDir(CW_Center_Center);
      delay(100);
      setMotorDir(Stop);
    } else {
      setMotorDir(CCW_Center_Center);
      delay(100);
      setMotorDir(Stop);
    }
  } while (
    (frontValues[1] < 300 && frontValues[2] < 300)
    || (backValues[1] < 300 && backValues[2] < 300)
    || (leftValues[1] < 400 && leftValues[2] < 300)
    || (rightValues[1] < 400 && rightValues[2] < 300)
  );

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
    }

    avg = val / SENSOR_COUNT;

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

  switch (direction) {
    case North:
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
      break;

    case East:
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
      break;

    case West:
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
      break;

    case South:
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
      break;
  }

  stopMotors();
  delay(50);
}

void taskHandler(uint8_t task) {
  taskData[task].execute();
}

void loop() {
  rotaryHandler();
}
