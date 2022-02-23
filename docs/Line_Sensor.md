# Line Sensors

Line Sensors are placed all around the Mobot. There are 4 Line Sensing Module, each at the front, back, left, and right side of the mobot.
Each of those Line Sensing Modules has their 4 sensors. This makes our mobot pretty accurate when sensing lines.

Also make sure to watch the FB Live video to have more info

## Initialization
**TODO**

## Calibration
To use the line sensors, we first need to calibrate it for use. We need to know the
minimum and maximum values it has detected in order to be more accurate. This means the mobot has to move over an intersection while calibrating

**This still hasn't been implemented**

The reason min and max values are required, is so that the mobot can discern lines more accurately. 
The playing field isn't always 100% white, and the lines may not be 100% black. So we calibrate our sensors and the `min` represent the playing field
while the `max` values represent the line.

Usually the `min` values are somewhere between 100-300, while the `max` values are 800-1000.

Here is the implementation in code:
```cpp
void calibrateSensor(QTRSensors &lineSensor, String sensorName) {
  Serial.println("Calibrating . . .");
  Serial.println("Slowly move the sensor across the electrical tape");

  // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
  // = ~25 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++) {
    lineSensor.calibrate();
  }

  ssd.println(sensorName);
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(lineSensor.calibrationOn.minimum[i]);
    Serial.print(" ");
    Serial.print(lineSensor.calibrationOn.maximum[i]);
    Serial.println();
  }
}
```

## Detecting Lines
**TODO**

## Intersection Detection
Now how do we detect intersections? We can do this with the 4 modules actually.

If all our sensors are detecting black, it means it is sitting at an intersection.

Whereas if only `FRONT` and `BACK` sensors are detecting, then it means it is on a normal line.

When it suddenly detects that `LEFT` and `RIGHT` are now black, then it means the mobot has reached the intersection.
