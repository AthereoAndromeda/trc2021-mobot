void initLifter() {
  lifter.attach(LIFTER_PIN);
  Serial.println(">> Lifter servo configuration successful!");
}

void lifterMove(lifterState liftState, int liftAngle, int liftSpeed) {
  if (liftAngle < 0) liftAngle = 0;
  else if (liftAngle > 270) liftAngle = 270;

  liftPwm = map(liftAngle, 0, 270, LIFTER_MIN, LIFTER_MAX);

  if (liftState == up) {
    for (liftPosition = LIFTER_MIN; liftPosition <= liftPwm; liftPosition += 1) {
      lifter.writeMicroseconds(liftPosition);
      delay(liftSpeed);
    }
  }
  else if (liftState == down) {
    for (liftPosition = liftPwm; liftPosition >= LIFTER_MIN; liftPosition -= 1) {
      lifter.writeMicroseconds(liftPosition);
      delay(liftSpeed);
    }
  }
}

void lifterUp() {
  Serial.println("Moving up the lifter!");
  lifterMove(up, LIFTER_ANGLE, LIFTER_SPEED);
}

void lifterDown() {
  Serial.println("Moving down the lifter!");
  lifterMove(down, LIFTER_ANGLE, LIFTER_SPEED);
}
