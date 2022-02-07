void setup() {
  Serial.begin(SERIAL_BAUD);
  pinMode(LED_BUILTIN, OUTPUT);

  while (!Serial) {
    delay(100);
  } Serial.println(">> Serial monitor initialization successful!");
  if (!apds.begin()) {
    Serial.println(">> Color sensor initialization failed!"); while (1);
  }
  if (!ssd.begin(SSD1306_SWITCHCAPVCC, SSD_ADDR)) {
    Serial.println(">> Lcd screen initialization failed!"); while (1);
  } else {
    Serial.println(">> LCD screen init successful!");
  }

  //  initRotary();
  //  initLed();
  //  setupMecanum();

  //  initLifter();
  //  delay(1000);

  //  motorMove(Forward, 2000);
  //  lifterDown();

  //  initApds();
  //  Serial.println(">> Color sensor calibration successful!");
  setupLineSensors();

  initSsd();

  //  taskThree();
  //  taskFour();

  delay(1000);

  //  calibrate_sensor(qtr_front, "Front Sensors");
  calibrateAllSensors();

  //  taskSeven();

  //  taskNine();

  delay(5000);
}
