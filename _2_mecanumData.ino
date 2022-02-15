void initMecanumWheels() {
  pinMode(STNDBY1, OUTPUT);
  pinMode(STNDBY2, OUTPUT);

  DDRA = DDRA | 0b11111111;
  DDRL = DDRL | 0x0F;

  PORTA = 0b00000000;
  PORTL &= ~0x0F;
  
  initMotorPwm();
  motorPWM = MOTOR_PWM;
  Serial.println(">> Mecanum Wheels setup successful!");
}

/**
   Handles interrupt every 10% duty cycle
*/
void motorPwmHandler() {
  if (motorCounter > motorPWM) {
    PORTL &= ~0x0F;
  }

  motorCounter++;

  if (motorCounter >= 100) {
    motorCounter = 0;
    PORTL |= 0x0F;
  }
}

/**
  Attaches Interrupt every 1000us for each % of duty cycle
*/
void initMotorPwm() {
  Timer1.initialize(100);
  Timer1.attachInterrupt(motorPwmHandler);
  Timer1.stop();
}

void stopMotors() {
  Timer1.stop();
  setMotorDir(Stop);
  delay(200);
  digitalWrite(STNDBY1, LOW);
  digitalWrite(STNDBY2, LOW);
}

void runMotors() {
  motorCounter = 0;
  digitalWrite(STNDBY1, HIGH);
  digitalWrite(STNDBY2, HIGH);
  Timer1.start();
}

void motorMove(Direction direction, uint16_t duration) {
  setMotorDir(direction);
  runMotors();

  delay(duration);
  stopMotors();
}

void motorMoveCustom(uint8_t direction, uint16_t duration) {
  PORTA = direction;
  runMotors();

  delay(duration);
  stopMotors();
}

void setMotorDir(Direction direction) {
  switch (direction) {
    // Format:
    // Top_Right Top_Left Bottom_Left Bottom_Right
    //
    // 10 -> Move Rotor Forward (or Clockwise)
    // 01 -> Move Rotor Backward (or Counterclockwise)
    // 00 -> Do nothing
    // 11 -> ?

    case Forward:
      PORTA = 0xAA; // 10 10 10 10
      break;
    case Backward:
      PORTA = 0x55; // 01 01 01 01
      break;
    case Left:
      PORTA = 0x99; // 10 01 10 01
      break;
    case Right:
      PORTA = 0x66; // 01 10 01 10
      break;
    case Forward_Left:
      PORTA = 0x88;
      break;
    case Forward_Right:
      PORTA = 0x22; // 00 10 00 10
      break;
    case Backward_Left:
      PORTA = 0x44;
      break;
    case Backward_Right:
      PORTA = 0x11;
      break;
    case CW_Center_Center:
      PORTA = 0x69; // 01 10 10 01
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
      PORTA = 0xFF; // 11 11 11 11
      break;

    default:
      Serial.println("Unknown Direction!");
      while (true);
      break;
  }
}
