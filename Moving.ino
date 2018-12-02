float WHEEL_DIAMETR = 67.0;
float FULL_DIAMETR = 280.0;
float CIRCLE_LENGTH = PI * FULL_DIAMETR; //mm?
float DELIM = 128;
float TICK_LENGTH = PI * WHEEL_DIAMETR / DELIM; //mm

int speed = 400;

void forward(int mm) {
  int ticks = mm * (5 / 3) * 10 * TICK_LENGTH;
  Serial.println(TICK_LENGTH);

  digitalWrite(dirPins[0], HIGH); //forward L
  digitalWrite(dirPins[1], LOW); //forward R
  for (int i = 0; i < ticks; i++) {
    digitalWrite(stepPins[0], HIGH);
    digitalWrite(stepPins[1], HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPins[0], LOW);
    digitalWrite(stepPins[1], LOW);
    delayMicroseconds(speed);
  }
}

void backward(int mm) {
  int ticks = mm * (5 / 3) * 10 * TICK_LENGTH;
  digitalWrite(dirPins[0], LOW); //backward L
  digitalWrite(dirPins[1], HIGH); //backward R
  for (int i = 0; i < ticks; i++) {
    digitalWrite(stepPins[0], HIGH);
    digitalWrite(stepPins[1], HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPins[0], LOW);
    digitalWrite(stepPins[1], LOW);
    delayMicroseconds(speed);
  }
}

void left(int deg) {
  float delim = 0.125;
  float mm = CIRCLE_LENGTH * delim;
  float ticks = mm * 1.66 * 10 * TICK_LENGTH;
  ticks *= 0.55;
  digitalWrite(dirPins[0], LOW); //backward L
  digitalWrite(dirPins[1], LOW); //forward R
  for (int i = 0; i < ticks; i++) {
    digitalWrite(stepPins[0], HIGH);
    digitalWrite(stepPins[1], HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPins[0], LOW);
    digitalWrite(stepPins[1], LOW);
    delayMicroseconds(speed);
  }
}

void right(int deg) {
  float delim = 0.125;
  float mm = CIRCLE_LENGTH * delim;
  float ticks = mm * 1.66 * 10 * TICK_LENGTH;
  ticks *= 0.55;
  digitalWrite(dirPins[0], HIGH); //backward L
  digitalWrite(dirPins[1], HIGH); //forward R
  for (int i = 0; i < ticks; i++) {
    digitalWrite(stepPins[0], HIGH);
    digitalWrite(stepPins[1], HIGH);
    delayMicroseconds(speed);
    digitalWrite(stepPins[0], LOW);
    digitalWrite(stepPins[1], LOW);
    delayMicroseconds(speed);
  }
}

void rotateByValue(int state) {
  if (state == 1) {
    right(45);
  } else {
    left(45);
  }
}

void followPoint(int angle, int dist) {
  int r1 = 1;
  int r2 = 2;
  if (angle < 0) {
    r1 = 2;
    r2 = 1;
  }
  angle = abs(angle);

  int a = dist / tan(radians(90 - angle));
  int d1 = a / cos(radians(45));
  int d2 = a * tan(radians(45));

  int d = dist - d2;

  rotateByValue(r1);
  forward(d1 * 1.45);
  rotateByValue(r2);
  forward(d);
}

