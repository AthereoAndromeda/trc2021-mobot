//void taskOne() {
//  motorMove(Forward, MOTOR_DELAY);
//  motorMove(Stop, 0);
//}
//
//void taskTwo() {
//  motorMove(Backward, MOTOR_DELAY);
//}
//
//void taskThree() {
//  motorMove(CW_Center_Center, MOTOR_DELAY);
//}
//
//void taskFour() {
//  motorMove(CCW_Center_Center, MOTOR_DELAY);
//}
//
//void taskFive() {
//  motorMove(Left, MOTOR_DELAY);
//  motorMove(Left, MOTOR_DELAY);
//}
//
//void taskSix() {
//  motorMove(Right, MOTOR_DELAY);
//  motorMove(Right, MOTOR_DELAY);
//}

//void taskNine() {
//  for (ssdCounter = 1; ssdCounter <= 20; ssdCounter++) {
//    if (ssdCounter <= 8) {
//      for (ssdPosition = 70; ssdPrints < ssdTimes; ssdPosition-ssdPosition*10) {
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
//    for (ssdPosition = 70; ssdPosition >= 0; ssdPosition - ssdPosition*10) {
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
