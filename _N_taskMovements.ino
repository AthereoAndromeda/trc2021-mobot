void movement1() {
//  if (test_directions)
//  {
//    digitalWrite(LED_BUILTIN, HIGH);
    run(Forward, RUN_DELAY);
    run(Stop, 0);

//    stopMotors();

//    test_directions = false;
//  }
//  digitalWrite(LED_BUILTIN, LOW);
}

void movement2() {
  if (test_directions)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    run(Backward, RUN_DELAY);
    run(Stop, 0);

    stopMotors();

    test_directions = false;
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void movement3() {
  if (test_directions)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    run(CW_Center_Center, RUN_DELAY);
    run(Stop, 0);

    stopMotors();

    test_directions = false;
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void movement4() {
//    digitalWrite(LED_BUILTIN, HIGH);
    run(CCW_Center_Center, RUN_DELAY);
//    run(Stop, 0);
//    stopMotors();

//  digitalWrite(LED_BUILTIN, LOW);
}

void movement5() {
  if (test_directions)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    run(Left, RUN_DELAY);
    run(Stop, 0);

    stopMotors();

    test_directions = false;
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void movement6() {
  if (test_directions)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    run(Right, RUN_DELAY);
    run(Stop, 0);

    stopMotors();

    test_directions = false;
  }
  digitalWrite(LED_BUILTIN, LOW);
}
