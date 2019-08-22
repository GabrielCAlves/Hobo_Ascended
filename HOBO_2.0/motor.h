#ifndef __MOTOR_H
#define __MOTOR_H

int portsR[] = {29, 27, 25, 23};
int portsL[] = {22, 24, 26, 28};

// definir direcoes - valores aleatorios
#define FRONT 9762
#define BACK 8612
#define RIGHT 4433
#define LEFT 8164

#define DEFAULT_REP 5
#define TURN_TIMES 50
#define MOTOR_SPEED 3000

void setMotors() {
  for (int i = 0; i < 4; i++) {
    pinMode(portsR[i], OUTPUT);
    pinMode(portsL[i], OUTPUT);
  }
}

void drive(int dir=FRONT, int rep=DEFAULT_REP, int inter=MOTOR_SPEED) {
  while(rep--) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        int onL = ( ((dir==FRONT) || (dir==LEFT)) ? i : 3-i);
        int onR = ( ((dir==FRONT) || (dir==RIGHT)) ? i : 3-i);
        digitalWrite(portsL[j], (j == onL ? HIGH : LOW));
        digitalWrite(portsR[j], (j == onR ? HIGH : LOW));
      }
      delayMicroseconds(inter);
    }
  }
}

void turnAround() {
  Serial.print("TURN AROUND");
  drive(RIGHT, 600);
  drive(FRONT, 100);
}

void turnColor(char dir) {
  Serial.print("TURNING COLOR ");
  Serial.println(dir);

  drive(FRONT, 100);

  int greenTimes = 300;
  if (dir == 'R') drive(RIGHT, greenTimes);
  else if (dir == 'L') drive(LEFT, greenTimes);

  drive(FRONT, 150);
}

void turnObstacle() {
  drive(BACK, 100);
  drive(RIGHT, 300);
  drive(FRONT, 300);
  drive(LEFT, 300);
  drive(FRONT, 500);
  drive(LEFT, 300);
  drive(FRONT, 300);
  drive(RIGHT, 300);
  drive(FRONT, 100);
}

#endif
