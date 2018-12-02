int stepPins[2] = {32, 28};
int dirPins[2] = {31, 27};

void setup() {
  Serial.begin(9600);
  for (int i : stepPins) {
    pinMode(i, OUTPUT);
  }
  for (int i : dirPins) {
    pinMode(i, OUTPUT);
  }

}

void loop() {
  while (Serial.available() > 0) {
    String in = String(Serial.readString());
    if (in != "") {
      String cmd = split(in, '(', 0);
      String params = split(split(in, '(', 1), ')', 0);
      Serial.println(in);
      if (cmd == "gt") {
        int a = 0, d = 0;
        int n = sscanf(in.c_str() , "gt(%d, %d)", &a, &d);
        followPoint(a, d);
      }
    }
  }
}
