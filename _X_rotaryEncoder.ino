// This code is for the Arduino Bluno, not on mobot.

/*
#include <Adafruit_NeoPixel.h>

#define PIN_RED_LED 8
#define PIN_GREEN_LED 9
#define PIN_BLUE_LED 10

#define CLK 2
#define DT 3
#define SW 4

int counter = 0;
int ledCounter = 0;
int currentStateCLK;              // gets the current state of the CLK pin
int lastStateCLK;                 // stores the previous state of the CLK pin
String currentDir = "";
unsigned long lastButtonPress = 0;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(115200);
  lastStateCLK = digitalRead(CLK); // Read the initial state of CLK
}

void loop() {
  Serial.println(ledCounter);
  if (ledCounter > 3) {
    ledCounter = 0;
  } else if (ledCounter < 0) {
    ledCounter = 3;
  }

  if (currentDir == "CW") {
    if (ledCounter == 0) {
      rgb_color(255, 0, 0);
    } else if (ledCounter == 1) {
      rgb_color(0, 255, 0);
    } else if (ledCounter == 2) {
      rgb_color(0, 0, 255);
    } else if (ledCounter == 3) {
      rgb_color(255, 255, 255);
    }
  } else {
    if (ledCounter == 3) {
      rgb_color(255, 0, 0);
    } else if (ledCounter == 2) {
      rgb_color(255, 255, 255);
    } else if (ledCounter == 1) {
      rgb_color(0, 0, 255);
    } else if (ledCounter == 0) {
      rgb_color(0, 255, 0);
    }
  }



  currentStateCLK = digitalRead(CLK);   // Read the current state of CLK

  if (currentStateCLK != lastStateCLK  && currentStateCLK == 0) {
    // currentStateCLK != lastStateCLK | if last and current state of CLK are different, then pulse occurred
    // currentStateCLK == 1 | React to only 1 state change to avoid double count

    if (digitalRead(DT) != currentStateCLK) { // If the DT state is different than the CLK state then
      counter ++;                             // Encoder is rotating CW so increment
      ledCounter++;
      currentDir = "CW";
    }
    else {                                  // Encoder is rotating CCW so decrement
      counter --;
      ledCounter--;
      currentDir = "CCW";
    }

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }

  lastStateCLK = currentStateCLK;             // Remember last CLK state

  int btnState = digitalRead(SW);             // Read the button state

  if (btnState == LOW) {                      //If we detect LOW signal, button is pressed

    if (millis() - lastButtonPress > 50) {    //if 50ms have passed since last LOW pulse, it means that the
      //button has been pressed, released and pressed again
      Serial.println("Button pressed!");
    }
    lastButtonPress = millis();               // Remember last button press event
  }
  delay(1);                                   // Put in a slight delay to help debounce the reading
}

void rgb_color(int red_value, int green_value, int blue_value) {
  analogWrite(PIN_RED_LED, red_value);
  analogWrite(PIN_GREEN_LED, green_value);
  analogWrite(PIN_BLUE_LED, blue_value);
}
*/
