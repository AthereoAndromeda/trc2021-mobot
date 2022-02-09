void initRotary() {
  pinMode(ROTARY_CLK, INPUT);
  pinMode(ROTARY_DTP, INPUT);
  pinMode(ROTARY_SWP, INPUT_PULLUP);

  lrotState = digitalRead(ROTARY_CLK);
  Serial.println(lrotState);

  Serial.println(">> Rotary encoder configuration successful!");
}
