void initApds() {
  apds.enableColor(true);
  while (!apds.colorDataReady()) delay(100);

  for (uint8_t i = 0; i <= APDS_ACCURACY; i++) {
    apds.getColorData(&redVal, &greenVal, &blueVal, &clearVal);

    redArr[i] = redVal;
    greenArr[i] = greenVal;
    blueArr[i] = blueVal;
    clearArr[i] = clearVal;
  }

  redMin, redMax = redArr[0];
  greenMin, greenMax = greenArr[0];
  blueMin, blueMax = blueArr[0];
  clearMin, clearMax = clearArr[0];

  for (uint8_t i = 0; i <= APDS_ACCURACY; i++) {
    redMin = min(redArr[i], redMin);
    redMax = max(redArr[i], redMax);

    greenMin = min(greenArr[i], greenMin);
    greenMax = max(greenArr[i], greenMax);

    blueMin = min(blueArr[i], blueMin);
    blueMax = max(blueArr[i], blueMax);

    clearMin = min(clearArr[i], clearMin);
    clearMax = max(clearArr[i], clearMax);
  }
}
