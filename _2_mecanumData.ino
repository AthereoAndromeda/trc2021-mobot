void initMecanumWheels() {
  // Set Outputs/Input pins
  DDRC |= 0b11;   // Standby Pins
  DDRA |= 0xFF;   // Direction Pins
  DDRL |= 0x0F;   // PWM Pins

  PORTA = 0x00;   // Set to STOP
  PORTL &= ~0x0F; // Sets PWM to low

  initMotorPwm();
  motorPWM = MOTOR_PWM;
  Serial.println(">> Mecanum Wheels setup successful!");
}

/**
   Handles interrupt every 10% duty cycle
   Also handles PWM
*/
void motorPwmHandler() {
  if (motorCounter > motorPWM) {
    PORTL &= ~0x0F; // Sets digital low of PWM
  }

  motorCounter++;

  if (motorCounter >= 100) {
    motorCounter = 0; // Resets on overflow
    PORTL |= 0x0F; // Sets digital high of PWM
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

  delay(100);     // Keep this delay, otherwise motor doesn't have enough time to stop, and direction bleeds into other `motorMove` calls
  PORTC &= ~0b11; // Set STANDBY Pins to LOW
}

void runMotors() {
  motorCounter = 0;
  PORTC |= 0b11;  // Set STANDBY Pins to HIGH

  Timer1.start();
}

void motorMove(Direction direction, uint16_t duration) {
  setMotorDir(direction);
  runMotors();

  delay(duration);
  stopMotors();
}

void motorMove(uint16_t direction, uint16_t duration) {
  PORTA = direction;
  runMotors();

  delay(duration);
  stopMotors();
}

inline void setMotorDir(Direction direction) {
  PORTA = direction;
}
