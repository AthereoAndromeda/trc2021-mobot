void taskOne() {
  motorMove(Forward, MOTOR_DELAY);
}

void taskTwo() {
  motorMove(Backward, MOTOR_DELAY);
}

void taskThree() {
  motorMove(CW_Center_Center, MOTOR_DELAY);
}

void taskFour() {
  motorMove(CCW_Center_Center, MOTOR_DELAY);
}

void taskFive() {
  motorMove(Left, MOTOR_DELAY);
  motorMove(Left, MOTOR_DELAY);
}

void taskSix() {
  motorMove(Right, MOTOR_DELAY);
  motorMove(Right, MOTOR_DELAY);
}

void taskNine() {
  for (int i = 1; i <= 21; i++) {
    ssd.clearDisplay();
    ssd.setCursor(0, 0);
    int trailingInt = i - 8;

    for (int j = trailingInt; j < i; j++) {
      if (j <= 0) {
        ssd.println("");
      } else {
        ssd.println(j);
      }
    }

    ssd.display();
    delay(100);
  }
}
