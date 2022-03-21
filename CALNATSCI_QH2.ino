#define ROTARY_SWP 6
#define ROTARY_DTP 18
#define ROTARY_CLK 19
#define LIFTER_PIN 7

#define LED_PIN 10
#define LED_COUNT 1

#define SERIAL_BAUD 115200
#define APDS_ACCURACY 5

#define SSD_WIDTH 128
#define SSD_HEIGHT 64
#define SSD_ADDR 0x3C

#define LIFTER_ANGLE 100
#define LIFTER_SPEED 1
#define LIFTER_MIN 500
#define LIFTER_MAX 2500

#define SENSOR_COUNT 4

// MOTOR_DELAY represents 1 block
#define MOTOR_DELAY 3000
#define MOTOR_DELAY_SIDEWAYS 3230
// MOTOR_PWM sets % of duty cycle
#define MOTOR_PWM 100 // 80

// PORTC
#define MOTOR_STANDBY_1 36
#define MOTOR_STANDBY_2 37

#include <Wire.h>
#include <Servo.h>
#include <TimerOne.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_APDS9960.h>
#include <Adafruit_SSD1306.h>

#include <QTRSensors.h>
QTRSensors QTR_Front;
QTRSensors QTR_Back;
QTRSensors QTR_Left;
QTRSensors QTR_Right;

Servo lifter;
Adafruit_APDS9960 apds;
Adafruit_SSD1306 ssd(SSD_WIDTH, SSD_HEIGHT, &Wire, -1);
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Format:
// Top_Right Top_Left Bottom_Left Bottom_Right
//
// 10 -> Move Rotor Forward (or Clockwise)
// 01 -> Move Rotor Backward (or Counterclockwise)
// 00 -> Do nothing
// 11 -> ? (I think same as 00)
enum MotorDirection {
  Forward = 0xAA,       // 10 10 10 10
  Backward = 0x55,      // 01 01 01 01
  Left = 0x99,
  Right = 0x66,
  Forward_Left = 0x88,
  Forward_Right = 0x22,
  Backward_Right = 0x44,
  Backward_Left = 0x11,
  CW_Center_Center = 0x69,
  CCW_Center_Center = 0x96,
  CW_Back_Center = 0x5F,
  CCW_Back_Center = 0xAF,
  CW_Front_Center = 0xF5,
  CCW_Front_Center = 0xFA,
  CW_Center_Left = 0x7D,
  CCW_Center_Left = 0xBE,
  CW_Center_Right = 0xEB,
  CCW_Center_Right = 0xD7,
  Stop = 0xFF
};

enum RotaryDirection { CW, CCW };
RotaryDirection rotaryDir, lastDir;
int rotaryVal = 0;
int crotState, lrotState, buttonState;
unsigned long lbutPress, cbutPress = 0;

static uint8_t motorCounter = 0;

enum LifterState { Up, Down };
int liftPwm, liftPosition;

//uint16_t sensorValues[SENSOR_COUNT];
// Sensors are arranged clockwise
uint16_t lineValues[SENSOR_COUNT][SENSOR_COUNT];
enum LineDirection {
  North,
  South,
  East,
  West
};

struct ColorData {
  String name;
} colorData;

struct TaskData {
  String displayText;
  void (*execute)(void);
};

#define TASK_COUNT 4

TaskData taskData[TASK_COUNT] = {
  {
    "Calibrate Sensors",
    calibrateAllSensors
  },
  {
    "Check One",
    executeCheckOne
  },
  {
    "Check Two",
    executeCheckTwo
  },
  {
    "Challenge One",
    executeChallengeOne
  }
};

String apdsColor;
uint16_t redVal, greenVal, blueVal, clearVal;
uint16_t redArr[APDS_ACCURACY], greenArr[APDS_ACCURACY], blueArr[APDS_ACCURACY], clearArr[APDS_ACCURACY];
uint16_t redMin, greenMin, blueMin, clearMin;
uint16_t redMax, greenMax, blueMax, clearMax;
uint8_t redCalib, greenCalib, blueCalib, clearCalib;
static bool isGreenLedOn = false;
static bool isLifterUp = false;

void lifterMove(LifterState liftState, uint16_t liftAngle, unsigned int liftSpeed);
void setMotorDir(MotorDirection direction);
void motorMove(MotorDirection direction, uint16_t duration);
void calibrateSensor(QTRSensors &lineSensor, String sensorName);
void runFollowLine(LineDirection direction);
void detectColor(ColorData *data);
void colorHandler(ColorData *data);

class MobotClass {
  public:
    uint8_t x, y;
    LineDirection orientation;
    ColorData colorData;

    MobotClass(uint8_t initX, uint8_t initY, LineDirection initOrient) {
      Serial.println(">> MobotClass instance constructed!");
      x = initX;
      y = initY;
      orientation = initOrient;
    }

    ~MobotClass() {}

    // \brief Initializes components
    void init() {
      initRotary();
      initLifter();
      initLed();
      initSsd();
      initApds();
      initLineSensors();
      initMecanumWheels();
    }

    void followLine(LineDirection dir) {
      determineXY(dir);

      runFollowLine(dir);
    }

    void move(MotorDirection dir, uint16_t duration) {
      motorMove(dir, duration);
    }

    void setPosition(uint8_t _x, uint8_t _y, LineDirection _orientation) {
      x = _x;
      y = _y;
      orientation = _orientation;
    };

  private:
    void determineXY(LineDirection dir) {
      if (orientation == North) {
        switch (dir) {
          case North:
            y++;
            break;

          case South:
            y--;
            break;

          case East:
            x++;
            break;

          case West:
            x--;
            break;
        }
      } else if (orientation == South) {
        switch (dir) {
          case North:
            y--;
            break;

          case South:
            y++;
            break;

          case East:
            x--;
            break;

          case West:
            x++;
            break;
        }
      } else if (orientation == East) {
        switch (dir) {
          case North:
            x++;
            break;

          case South:
            x--;
            break;

          case East:
            y--;
            break;

          case West:
            y++;
            break;
        }
      } else {
        switch (dir) {
          case North:
            x--;
            break;

          case South:
            x++;
            break;

          case East:
            y++;
            break;

          case West:
            y--;
            break;
        }
      }
    }
};

MobotClass Mobot(1, 0, North);
