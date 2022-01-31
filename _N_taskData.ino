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

//void taskNine() {
//  for (ssdCounter = 1; ssdCounter <= 20; ssdCounter++) {
//    if (ssdCounter <= 8) {
//      for (ssdPosition = 70; ssdPrints < ssdTimes; ssdPosition - ssdPosition * 10) {
//        ssd.setCursor(0, ssdPosition);
//        ssd.println(ssdCounter - ssdRow);
//        ssd.display();
//        ssd.clearDisplay();
//        delay(100);
//
//        ssdPrints++;
//        ssdRow++;
//      }
//      ssdTimes++;
//      ssdPrints, ssdRow = 0;
//      continue;
//    }
//
//    ssdRow = 0;
//
//    for (ssdPosition = 70; ssdPosition >= 0; ssdPosition - ssdPosition * 10) {
//      ssd.setCursor(0, ssdPosition);
//      ssd.println(ssdCounter - ssdRow);
//      ssd.display();
//      ssd.clearDisplay();
//      delay(100);
//
//      if (ssdRow == 7) ssdRow = 0;
//      else ssdRow++;
//    }
//    ssd.clearDisplay();
//  }
//}

// To conceptualize/visualize possible method
void manualLed() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  ssd.println(1);
  ssd.display();
  ssd.clearDisplay();
  delay(500);

  ssd.setCursor(0, 0);
  ssd.println(1);
  ssd.println(2);
  ssd.display();
  ssd.clearDisplay();
  delay(500);

  ssd.setCursor(0, 0);
  for (int i = 1; i < 8; i++) {
    ssd.println(i);
  }
  ssd.display();
  ssd.clearDisplay();
  delay(500);

  ssd.setCursor(0, 0);
  for (int i = 2; i < 9; i++) {
    ssd.println(i);
  }
  ssd.display();
  ssd.clearDisplay();
  delay(500);

  ssd.setCursor(0, 0);
  for (int i = 3; i < 10; i++) {
    ssd.println(i);
  }
  ssd.display();
  ssd.clearDisplay();
  delay(500);
}

void taskNine_B() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);

  for (int i = 1; i <= 21; i++) {
    ssd.setCursor(0, 0);
    int storedInt = i - 8;

    // Prevents printing of negative and zero numbers
    if (storedInt <= 0) continue;

    for (int j = storedInt; j < i; j++) {
      ssd.println(j);
      ssd.display();
    }

    ssd.clearDisplay();
    delay(100);
  }

}

void taskNine_A() {
  ssd.clearDisplay();
  ssd.setCursor(0, 0);
  ssd.println("aa");
  ssd.display();

  delay(3000);
  ssd.clearDisplay();

  int arr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  //  int arr[8];
  int counter = 0;
  enum CountState { Descending, Ascending };
  CountState countState = Ascending;

  for (int i = 1; i <= 20; i++) {
    ssd.setCursor(0, 0);
    arr[counter] = i;
    counter++;

    Serial.print("Counter: ");
    Serial.println(counter);
    Serial.println(i);


    for (int j = 0; j < 8; j++) {
      int number = arr[j];
      Serial.print("J is: ");
      Serial.println(number);
      ssd.println(number);
      ssd.display();
    }

    if (counter >= 8) {
      counter = 0;
    }

    //    ssd.display();
    delay(500);

    ssd.clearDisplay();
  }
}
