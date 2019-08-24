#ifndef __MOTOR_H
#define __MOTOR_H

int portsL[] = {29, 27, 25, 23};
int portsR[] = {28, 26, 24, 22};

const int FRONT = 9762, BACK=3413, LEFT=2413, RIGHT=2132;

int otherSide(int side=FRONT) {
  if (side == FRONT) return BACK;
  if (side == BACK) return FRONT;
  if (side == LEFT) return RIGHT;
  if (side == RIGHT) return LEFT;
}

#define DEFAULT_REP 5
#define MOTOR_SPEED 3000
#define NINETY_REP 350

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

void turn90(int dir=RIGHT) {
  Serial.println("TURNING NINETY");
  drive(dir, NINETY_REP, MOTOR_SPEED);
}

void turnAround() {
  Serial.print("TURN AROUND");
  turn90(RIGHT);
  turn90(RIGHT);

  drive(FRONT, 10);
}

void turnColor(char dir) {
  Serial.print("TURNING COLOR ");
  Serial.println(dir);

  drive(FRONT, 100);

  if (dir == 'R') turn90(RIGHT);
  else if (dir == 'L') turn90(LEFT);

  drive(FRONT, 150);
}

void turnObstacle() {
  Serial.println("SAW OBSTACLE");
  drive(BACK, 300);
  turn90(RIGHT);
  drive(FRONT, 450);
  turn90(LEFT);
  drive(FRONT, 1000);
  turn90(LEFT);
  drive(FRONT, 450);
  turn90(RIGHT);
  drive(FRONT, 100);
}

#endif
