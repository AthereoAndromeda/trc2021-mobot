void taskOne() {
  motorMove(Forward, MOTOR_DELAY * 2);
}

void taskTwo() {
  motorMove(Backward, MOTOR_DELAY * 2);
}

void taskThree() {
  motorMove(CCW_Center_Center, ROTATE_MOTOR_DELAY * 2);
}

void taskFour() {
  motorMove(CW_Center_Center, ROTATE_MOTOR_DELAY * 2 - 100);
}

void taskFive() {
  motorMove(Left, SIDEWAYS_MOTOR_DELAY * 2);
}

void taskSix() {
  motorMove(Right, SIDEWAYS_MOTOR_DELAY * 2);
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
