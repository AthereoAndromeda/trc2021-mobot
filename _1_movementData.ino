void test_realign() {
  uint16_t retryV = 0;
  uint16_t retryH = 0;

  uint16_t timeStarted = millis();

  do {
    retryV = realignVertically();
    retryH = realignHorizontally();

    // Stop after trying for 1.5 seconds
    if (millis() - timeStarted > 2000) break;
  } while (retryV > 1 && retryH > 1);
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
  const uint16_t tolerance = 300;
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
  const uint16_t runDuration = 5000;
  uint16_t last_change = millis();
  const uint8_t _pwm = 30;

  uint16_t sensorA_pos = 0;
  uint16_t sensorB_pos = 0;

  SensorStatus cur_statusA = (SensorStatus)0;
  SensorStatus cur_statusB = (SensorStatus)0;
  SensorStatus prev_statusA = (SensorStatus)0;
  SensorStatus prev_statusB = (SensorStatus)0;
  setMotorPwm(_pwm);

  bool isInitiated = false;
  uint16_t initTime = 0;

  do {
    sensorA_pos = sensorA->readLineBlack(sensorValues);
    sensorB_pos = sensorB->readLineBlack(sensorValues);

    if (!isInitiated) {
      initTime = millis();
      isInitiated = true;
    }

    cur_statusA = getSensorStatus(sensorA_pos);
    cur_statusB = getSensorStatus(sensorB_pos);

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
        delay(retry * 2);
      }

      last_change = millis();
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
