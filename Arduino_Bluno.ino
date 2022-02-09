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
#define LIFTER_SPEED 2
#define LIFTER_DELAY 3000
#define LIFTER_MIN 500
#define LIFTER_MAX 2500

#define SENSOR_COUNT 4

// MOTOR_DELAY represents 1 block
#define MOTOR_DELAY 3000 // 3970
#define ROTATE_MOTOR_DELAY 3000
#define SIDEWAYS_MOTOR_DELAY 3230 // 4200
#define SET_PWM 80 // 60

#define STNDBY1 36
#define STNDBY2 37

#include <Preset.h>
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

enum Direction {
  Forward,
  Backward,
  Left,
  Right,
  Forward_Left,
  Forward_Right,
  Backward_Left,
  Backward_Right,
  CW_Center_Center,
  CCW_Center_Center,
  CW_Back_Center,
  CCW_Back_Center,
  CW_Front_Center,
  CCW_Front_Center,
  CW_Center_Left,
  CCW_Center_Left,
  CW_Center_Right,
  CCW_Center_Right,
  Stop
};

int rotaryVal = 0;
String rotaryDir;
int crotState, lrotState, buttonState;
unsigned long lbutPress, cbutPress = 0;
unsigned int _pwmvalue = 0;
static bool stopmotor = true;
static int pwmcounter = 0;

enum LifterState { Up, Down };
int liftPwm, liftPosition;

String apdsColor;
uint16_t redVal, greenVal, blueVal, clearVal;
uint16_t redArr[5], greenArr[5], blueArr[5], clearArr[5];
uint16_t redMin, greenMin, blueMin, clearMin;
uint16_t redMax, greenMax, blueMax, clearMax;
uint8_t redCalib, greenCalib, blueCalib, clearCalib;
uint16_t sensorValues[SENSOR_COUNT];
boolean isLifterUp = false;

void lifterMove(LifterState liftState, uint16_t liftAngle, int liftSpeed);
void setMotorDir(Direction direction);
void motorMove(Direction direction, int duration);
void calibrateSensor(QTRSensors &lineSensor, String sensorName);
void _printSensorValues(QTRSensors &lineSensor, String sensorName);
