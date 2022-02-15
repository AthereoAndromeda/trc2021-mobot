void taskOne() {
  motorMove(Forward, MOTOR_DELAY * 2);
}

void taskTwo() {
  motorMove(Backward, MOTOR_DELAY * 2);
}

void taskThree() {
  motorMove(CCW_Center_Center, MOTOR_DELAY * 2);
}

void taskFour() {
  motorMove(CW_Center_Center, MOTOR_DELAY * 2);
}

void taskFive() {
  motorMove(Left, MOTOR_DELAY_SIDEWAYS * 2);
}

void taskSix() {
  motorMove(Right, MOTOR_DELAY_SIDEWAYS * 2);
}


void executeCheckOne() {
  // Forward/Backwards
  taskOne();
  taskTwo();

  // Rotate Left/Right
  taskThree();
  taskFour();

  // Shift Left/Right
  taskFive();
  taskSix();
}
