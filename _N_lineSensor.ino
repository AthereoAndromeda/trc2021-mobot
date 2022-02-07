//const uint8_t SensorCount = 4;
//uint16_t sensorValues[SensorCount];

void setupLineSensors()
{
  const uint16_t def_timeout = 1000;
  Serial.println("initializinf line sensors . . .");

  //front line sensor
  qtr_front.setTimeout(def_timeout);
  qtr_front.setTypeRC();
  qtr_front.setSensorPins((const uint8_t[]) {
    A0, A1, A2, A3
  }, SensorCount);
  qtr_front.setEmitterPin(33);
  /*
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
    qtr_right.setEmitterPin(31);*/
}

void calibrate_sensor(QTRSensors &lineSensor)
{
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
  //
  //  Serial.print("Minimum Values: ");
  //  // print the calibration minimum values measured when emitters were on
  //  for (uint8_t i = 0; i < SensorCount; i++) {
  //    Serial.print(lineSensor.calibrationOn.minimum[i]);
  //    Serial.print(' ');
  //
  //    ssd.print(lineSensor.calibrationOn.minimum[i]);
  //    ssd.print(' ');
  //  }
  //  ssd.println();
  //  Serial.println();
  //
  //  Serial.print("Maximum Values: ");
  //  // print the calibration maximum values measured when emitters were on
  //  for (uint8_t i = 0; i < SensorCount; i++) {
  //    Serial.print(lineSensor.calibrationOn.maximum[i]);
  //    Serial.print(' ');
  //
  //    ssd.print(lineSensor.calibrationOn.maximum[i]);
  //    ssd.print(' ');
  //  }
  //  ssd.println();
  //  Serial.println();



  for (uint8_t i = 0; i < SensorCount; i++) {
    ssd.print("Sensor ");
    ssd.print(i);
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

//void loop()
//{
//  // read raw sensor values
//  qtr_front.read(sensorValues);
//
//  // print the sensor values as numbers from 0 to 2500, where 0 means maximum
//  // reflectance and 2500 means minimum reflectance
//  for (uint8_t i = 0; i < SensorCount; i++)
//  {
//    Serial.print(sensorValues[i]);
//    Serial.print('\t');
//  }
//  Serial.println();
//
//  delay(250);
//}
