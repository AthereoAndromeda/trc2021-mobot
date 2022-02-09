#define DELAY_TIME 5000
#define DEF_TIMEOUT 1000

void initLineSensors() {
  Serial.println("initializing line sensors . . .");

  //front line sensor
  QTR_Front.setTimeout(DEF_TIMEOUT);
  QTR_Front.setTypeRC();
  QTR_Front.setSensorPins((const uint8_t[]) {
    A0, A1, A2, A3
  }, SENSOR_COUNT);
  QTR_Front.setEmitterPin(33);

  //back line sensor
  QTR_Back.setTimeout(DEF_TIMEOUT);
  QTR_Back.setTypeRC();
  QTR_Back.setSensorPins((const uint8_t[]) {
    A15, A14, A13, A12
  }, SENSOR_COUNT);
  QTR_Back.setEmitterPin(32);

  //left line sensor
  QTR_Left.setTimeout(DEF_TIMEOUT);
  QTR_Left.setTypeRC();
  QTR_Left.setSensorPins((const uint8_t[]) {
    A7, A6, A5, A4
  }, SENSOR_COUNT);
  QTR_Left.setEmitterPin(30);

  //right line sensor
  QTR_Right.setTimeout(DEF_TIMEOUT);
  QTR_Right.setTypeRC();
  QTR_Right.setSensorPins((const uint8_t[]) {
    A8, A9, A10, A11
  }, SENSOR_COUNT);
  QTR_Right.setEmitterPin(31);
}

void calibrateSensor(QTRSensors &lineSensor, String sensorName) {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  Serial.println("Calibrating . . .");
  Serial.println("Slowly move the sensor across the electrical tape");
  // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
  // = ~25 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++) {
    lineSensor.calibrate();
  }
  Serial.println();

  ssd.println(sensorName);
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    ssd.print("Sensor ");
    ssd.print(i + 1);
    ssd.print(": ");
    ssd.print(lineSensor.calibrationOn.minimum[i]);
    ssd.print(" ");
    ssd.print(lineSensor.calibrationOn.maximum[i]);
    ssd.println();
  }

  ssd.display();
  Serial.println("Done calibrating!");
  ssd.display();

  delay(1000);
  Serial.println();
}

void _printSensorValues(QTRSensors &lineSensor, String sensorName) {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  ssd.println(sensorName);
  ssd.println();
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    ssd.print("Sensor ");
    ssd.print(i + 1);
    ssd.print(": ");
    ssd.print(lineSensor.calibrationOn.minimum[i]);
    ssd.print(" ");
    ssd.print(lineSensor.calibrationOn.maximum[i]);
    ssd.println();
  }

  ssd.display();
}

void calibrateAllSensors() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  Serial.println("Calibrating . . .");
  Serial.println("Slowly move the sensor across the electrical tape");

  // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
  // = ~25 ms per calibrate() call.
  // Call calibrate() 100 times to make calibration take about 10 seconds.
  for (uint8_t i = 0; i < 100; i++) {
    QTR_Front.calibrate();
    QTR_Back.calibrate();
    QTR_Left.calibrate();
    QTR_Right.calibrate();
  }

  Serial.println();

  _printSensorValues(QTR_Front, "Front Sensors");
  delay(DELAY_TIME);
  _printSensorValues(QTR_Back, "Back Sensors");
  delay(DELAY_TIME);
  _printSensorValues(QTR_Left, "Left Sensors");
  delay(DELAY_TIME);
  _printSensorValues(QTR_Right, "Right Sensors");
  delay(DELAY_TIME);

  Serial.println("Done calibrating!");
  ssd.display();
}