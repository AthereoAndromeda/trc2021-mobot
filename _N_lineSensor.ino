#define DELAY_TIME 5000

void setupLineSensors() {
  const uint16_t def_timeout = 1000;
  Serial.println("initializing line sensors . . .");

  //front line sensor
  qtr_front.setTimeout(def_timeout);
  qtr_front.setTypeRC();
  qtr_front.setSensorPins((const uint8_t[]) {
    A0, A1, A2, A3
  }, SensorCount);
  qtr_front.setEmitterPin(33);

  //back line sensor
  qtr_back.setTimeout(def_timeout);
  qtr_back.setTypeRC();
  qtr_back.setSensorPins((const uint8_t[]) {
    A15, A14, A13, A12
  }, SensorCount);
  qtr_back.setEmitterPin(32);

  //left line sensor
  qtr_left.setTimeout(def_timeout);
  qtr_left.setTypeRC();
  qtr_left.setSensorPins((const uint8_t[]) {
    A7, A6, A5, A4
  }, SensorCount);
  qtr_left.setEmitterPin(30);

  //right line sensor
  qtr_right.setTimeout(def_timeout);
  qtr_right.setTypeRC();
  qtr_right.setSensorPins((const uint8_t[]) {
    A8, A9, A10, A11
  }, SensorCount);
  qtr_right.setEmitterPin(31);
}

void calibrate_sensor(QTRSensors &lineSensor, String sensorName) {
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
  for (uint8_t i = 0; i < SensorCount; i++) {
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
  for (uint8_t i = 0; i < SensorCount; i++) {
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
    qtr_front.calibrate();
    qtr_back.calibrate();
    qtr_left.calibrate();
    qtr_right.calibrate();
  }

  Serial.println();

  _printSensorValues(qtr_front, "Front Sensors");
  delay(DELAY_TIME);
  _printSensorValues(qtr_back, "Back Sensors");
  delay(DELAY_TIME);
  _printSensorValues(qtr_left, "Left Sensors");
  delay(DELAY_TIME);
  _printSensorValues(qtr_right, "Right Sensors");
  delay(DELAY_TIME);

  Serial.println("Done calibrating!");
  ssd.display();
}
