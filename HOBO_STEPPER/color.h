#ifndef __COLOR_H
#define __COLOR_H

#define MAX_COLOR 200
#define MIN_COLOR 0
#define MIN_DIFF 30

bool greenCheck(int r, int g, int b) {
  if ((r < MAX_COLOR) && (b < MAX_COLOR)
      && (r > MIN_COLOR) && (g > MIN_COLOR) && (b > MIN_COLOR)
      && ((g - b) > MIN_DIFF) && ((g - r) > MIN_DIFF)) {
    return true;
  }

  else return false;

}

struct Sensor {
  int s[4];
  int out;
  int thresh[6];
  int leitura[3];

  Sensor(int _s[4], int _out, int _thresh[6]) {
    out = _out;
    pinMode(out, INPUT);

    for (int i = 0; i < 4; i++) {
      s[i] = _s[i];
      pinMode(s[i], OUTPUT);
    }

    for (int i = 0; i < 6; i++) {
      thresh[i] = _thresh[i];
    }

    digitalWrite(s[0], HIGH);
    digitalWrite(s[1], LOW);
  }

  void setSensors(int a, int b) {
    digitalWrite(s[2], a);
    digitalWrite(s[3], b);
  }

  void makeMap() {
    for (int i = 0; i < 3; i++) {
      leitura[i] = map(leitura[i], thresh[2 * i], thresh[2 * i + 1], 255, 0);
    }
  }

  void displayValues() {
    for (int i = 0; i < 3; i++) {
      Serial.print(leitura[i]);
      Serial.print(" ");
    }
  }

  void getReadings() {
    setSensors(LOW, LOW);
    leitura[0] = pulseIn(out, LOW);
    delay(3);

    setSensors(HIGH, HIGH);
    leitura[1] = pulseIn(out, LOW);
    delay(3);

    setSensors(LOW, HIGH);
    leitura[2] = pulseIn(out, LOW);
    delay(3);

    makeMap();
  }

  bool isGreen() {
    getReadings();
    return greenCheck(leitura[0], leitura[1], leitura[2]);
  }

};

#endif
