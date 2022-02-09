void initMecanumWheels() {
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

void initMotorPwm() {
  Timer1.initialize(100);
  Timer1.attachInterrupt(motorPwmHandler);
  Timer1.stop();
}

void prepMotors() {
  stopmotor = false;

  PORTL |= 0x0F;

  pwmcounter = 0;
  stopmotor = false;

  initMotorPwm();

  digitalWrite(STNDBY1, HIGH);
  digitalWrite(STNDBY2, HIGH);
}

void stopMotors() {
  Timer1.stop();
  setMotorDir(Stop);
  delay(200);
  digitalWrite(STNDBY1, LOW);
  digitalWrite(STNDBY2, LOW);
}

void runMotors() {
  pwmcounter = 0;
  digitalWrite(STNDBY1, HIGH);
  digitalWrite(STNDBY2, HIGH);
  Timer1.start();
}

void motorPwmHandler() {
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

void setMotorDir(Direction direction) {
  switch (direction) {
    case Forward:
      PORTA = 0xAA;
      break;
    case Backward:
      PORTA = 0x55;
      break;
    case Left:
      PORTA = 0x99;
      break;
    case Right:
      PORTA = 0x66;
      break;
    case Forward_Left:
      PORTA = 0x88;
      break;
    case Forward_Right:
      PORTA = 0x22;
      break;
    case Backward_Left:
      PORTA = 0x44;
      break;
    case Backward_Right:
      PORTA = 0x11;
      break;
    case CW_Center_Center:
      PORTA = 0x69;
      break;
    case CCW_Center_Center:
      PORTA = 0x96;
      break;
    case CW_Back_Center:
      PORTA = 0x5F;
      break;
    case CCW_Back_Center:
      PORTA = 0xAF;
      break;
    case CW_Front_Center:
      PORTA = 0xF5;
      break;
    case CCW_Front_Center:
      PORTA = 0xFA;
      break;
    case CW_Center_Left:
      PORTA = 0x7D;
      break;
    case CCW_Center_Left:
      PORTA = 0xBE;
      break;
    case CW_Center_Right:
      PORTA = 0xEB;
      break;
    case CCW_Center_Right:
      PORTA = 0xD7;
      break;

    case Stop:
      PORTA = 0xFF;
      break;

    default:
      Serial.println("Unknown Direction!");
      while (true);
      break;
  }
}
