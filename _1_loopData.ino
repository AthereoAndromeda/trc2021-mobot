void loop() {
  uint16_t lineValues[SENSOR_COUNT];
  int pos = QTR_Front.readLineBlack(lineValues);

//  for (int i = 0; i < SENSOR_COUNT; i++) {
//    Serial.println(lineValues[i]);
//  }

  Serial.println(pos);
  delay(100);
}
