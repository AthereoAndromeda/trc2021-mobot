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

  // Initialize Components
  initRotary();
  initLifter();
  initLed();
  initSsd();
  initApds();
  initLineSensors();
  initMecanumWheels();

  Serial.println("Executing Tasks");
  delay(1000);
  //  calibrateAllSensors();
}
