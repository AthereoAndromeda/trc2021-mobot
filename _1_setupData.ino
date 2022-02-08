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
  setupMecanum();

  //  initLifter();

  //  lifterDown();
  //  delay(1000);

  //  motorMove(Forward, 2000);
  //  taskOne();
  //  lifterUp();

  //  taskTwo();
  //  lifterDown();
  //  delay(1000);

  // light for color sensor
  //  pixels.setPixelColor(0, 255, 255, 255);
  //  pixels.show();

  delay(1000);

  initApds();
  Serial.println(">> Color sensor calibration successful!");
  //  setupLineSensors();

  initSsd();

  taskOne();
  taskTwo();

  delay(1000);

  //  calibrate_sensor(qtr_front, "Front Sensors");
  //  calibrateAllSensors();

  //  taskSeven();

  //  taskNine();

  delay(5000);
}
