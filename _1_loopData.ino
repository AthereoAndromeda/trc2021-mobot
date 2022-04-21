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

void test_realign() {
  uint16_t retryV = 0;
  uint16_t retryH = 0;
  do {
    retryV = realignVertically();
    retryH = realignHorizontally();
  } while (retryV > 1 && retryH > 1);

  // waitForBtnPush();
}

uint16_t realignVertically() {
  const MotorDirection dir_matrix[3][3] = {
    {Left, CCW_Center_Center, CCW_Center_Center},
    {CW_Center_Center, Stop, CCW_Center_Center},
    {CW_Center_Center, CW_Center_Center, Right}
  };
  return realign(&QTR_Front, &QTR_Back, dir_matrix);
}

uint16_t realignHorizontally() {
  const MotorDirection dir_matrix[3][3] = {
    {Forward, CCW_Center_Center, CCW_Center_Center},
    {CW_Center_Center, Stop, CCW_Center_Center},
    {CW_Center_Center, CW_Center_Center, Backward}
  };
  return realign(&QTR_Right, &QTR_Left, dir_matrix);
}

SensorStatus getSensorStatus(uint16_t sensor_pos) {
  const uint16_t center = 1500;
  const uint16_t tolerance = 700;
  const uint16_t upperLimit = center + tolerance;
  const uint16_t lowerLimit = center - tolerance;

  if (sensor_pos > upperLimit)
    return Over;
  else if (sensor_pos < upperLimit && sensor_pos > lowerLimit)
    return Center;
  else if (sensor_pos < lowerLimit)
    return Under;
}

uint16_t sensorValues[4];
uint16_t realign(QTRSensors *sensorA, QTRSensors *sensorB, const MotorDirection adjDirs[][3]) {

  uint16_t retry = 1;
  const uint8_t motorPwm = 20;
  const uint16_t runDuration = 100;
  uint16_t last_change = millis();
  uint16_t _pwm = 70;

  uint16_t sensorA_pos = 0;
  uint16_t sensorB_pos = 0;

  SensorStatus cur_statusA = (SensorStatus)0;
  SensorStatus cur_statusB = (SensorStatus)0;
  SensorStatus prev_statusA = (SensorStatus)0;
  SensorStatus prev_statusB = (SensorStatus)0;

  String delim = ":";
  setMotorPwm(_pwm);

  do {
    sensorA_pos = sensorA->readLineBlack(sensorValues);
    sensorB_pos = sensorB->readLineBlack(sensorValues);

    Serial.println(sensorA_pos + delim + sensorB_pos);

    cur_statusA = getSensorStatus(sensorA_pos);
    cur_statusB = getSensorStatus(sensorB_pos);

    Serial.println(cur_statusA + delim + cur_statusB);


    if (adjDirs[cur_statusA + 1][cur_statusB + 1] == Stop)
      break;
    else {
      if (prev_statusA != cur_statusA || prev_statusB != cur_statusB) {
        // Serial.print("Running at ");
        // Serial.println(p);
        stopMotors();
        // delay(100);


        motorMove(adjDirs[cur_statusA + 1][cur_statusB + 1], 0);


        prev_statusA = cur_statusA;
        prev_statusB = cur_statusB;
      }
      else {
        delay(retry * 5);
      }
      if (millis() - last_change > 100) {
        last_change = millis();
        if (_pwm <= 50) {
          _pwm = _pwm + 10;
          // setMotorPWM(_pwm);
        }
      }
    }
    // run(adjDirs[statusA][statusB],runDuration);
    // runToPwm(adjDirs[statusA][statusB],30);
    // Serial.println(retry);

    retry++;
  } while (retry < 50);

  stopMotors();
  setMotorPwm(MOTOR_PWM);

  return retry;
}

void loop() {
  rotaryHandler();
}
