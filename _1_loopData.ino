int8_t taskCounter;

//void correctMobotOrientation() {
//  uint16_t *frontValues = lineValues[0];
//  uint16_t *rightValues = lineValues[1];
//  uint16_t *backValues = lineValues[2];
//  uint16_t *leftValues = lineValues[3];
//  uint16_t avg;
//  unsigned long int timeStarted = millis();
//  uint8_t timesMoved;
//
//  motorMove(Stop, 0);
//  do {
//    QTR_Front.readCalibrated(frontValues);
//    QTR_Back.readCalibrated(backValues);
//    QTR_Right.readCalibrated(rightValues);
//    QTR_Left.readCalibrated(leftValues);
//
//    Serial.println("AAAA");
//    Serial.println(frontValues[1]);
//    Serial.println(backValues[2]);
//    Serial.println(leftValues[2]);
//    Serial.println(rightValues[2]);
//
//    int val = 0;
//    for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
//      val += frontValues[i];
//      val += backValues[i];
//    }
//
//    avg = val / 8;
//    Serial.println(avg);
//
//    unsigned long int timeNow = millis();
//    if (frontValues[0] < 200 && backValues[3] < 200) {
//      setMotorDir(CW_Center_Center);
//      delay(100);
//      setMotorDir(Stop);
//    } else {
//      setMotorDir(CCW_Center_Center);
//      delay(100);
//      setMotorDir(Stop);
//    }
//  } while (
//    (frontValues[1] < 300 && frontValues[2] < 300)
//    || (backValues[1] < 300 && backValues[2] < 300)
//    || (leftValues[1] < 400 && leftValues[2] < 300)
//    || (rightValues[1] < 400 && rightValues[2] < 300)
//  );
//
//  stopMotors();
//}

void loop() {
  rotaryHandler();
}
