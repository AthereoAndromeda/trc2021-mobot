void setupMecanum() {
  pinMode(STNDBY1, OUTPUT);
  pinMode(STNDBY2, OUTPUT);

  DDRA = DDRA | 0b11111111;
  DDRL = DDRL | 0x0F;

  PORTA = 0b00000000;
  PORTL &= ~0x0F;
  initMotorPwm();

  setMotorPWM(SET_PWM);
  Serial.println(">> Mecanum Wheels setup successful!");
}

void initMotorPwm(void) {
  Timer1.initialize(100);
  Timer1.attachInterrupt(MotorPwmHandler);
  Timer1.stop();
}

void prepMotors(void) {
  stopmotor = false;

  PORTL |= 0x0F;

  pwmcounter = 0;
  stopmotor = false;

  initMotorPwm();

  digitalWrite(STNDBY1, HIGH);
  digitalWrite(STNDBY2, HIGH);
}

void stopMotors(void) {
  Timer1.stop();
  setMotorDir(Stop);
  delay(200);
  digitalWrite(STNDBY1, LOW);
  digitalWrite(STNDBY2, LOW);
}

void runMotors(void) {
  pwmcounter = 0;
  digitalWrite(STNDBY1, HIGH);
  digitalWrite(STNDBY2, HIGH);
  Timer1.start();
}

void MotorPwmHandler(void) {

  if (pwmcounter > _pwmvalue) {
    PORTL &= ~0x0F;
  }
  pwmcounter++;

  if (pwmcounter >= 100) {
    pwmcounter = 0;
    PORTL |= 0x0F;
  }
}

void setMotorPWM(int pwm) {
  _pwmvalue = pwm;
}

void motorMove(Direction direction, int duration) {
  setMotorDir(direction);

  runMotors();

  if (duration > 0) {
    delay(duration);
    stopMotors();
  }
}
