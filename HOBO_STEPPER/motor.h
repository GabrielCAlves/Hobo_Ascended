#ifndef __MOTOR_H
#define __MOTOR_H

const int FRONT = 9762, BACK=3413, LEFT=2413, RIGHT=2132;

void setMotors() {
  Stepper stepperL(stepsPerRev, 22, 26, 24, 28);
  Stepper stepperR(stepsPerRev, 29, 25, 27, 23);
}

void drive(int dir=FRONT, double revA=3, int mSpeed=100) {
  while (revA--)
    moveStep(dir, stepsPerRev);
}

void moveStep(int dir, int stepA) {
  int dL=1, dR=1;
  if ((dir == BACK) || (dir == LEFT)) dL = -1;
  if ((dir == BACK) || (dir == RIGHT)) dR = -1;

  while (stepA--)
    stepperL.step(dL), stepperR.step(dR);
}

void turnAround() {
  Serial.print("TURN AROUND");
  drive(RIGHT, 600);
  drive(FRONT, 100);
}

void turnColor(char dir) {
  Serial.print("TURNING COLOR ");
  Serial.println(dir);

  drive(FRONT, 1);

  int greenTimes = 3;
  if (dir == 'R') drive(RIGHT, greenTimes);
  else if (dir == 'L') drive(LEFT, greenTimes);

  drive(FRONT, 1.5);
}

void turnObstacle() {
  drive(BACK, 1);
  drive(RIGHT, 3);
  drive(FRONT, 3);
  drive(LEFT, 3);
  drive(FRONT, 5);
  drive(LEFT, 3);
  drive(FRONT, 3);
  drive(RIGHT, 3);
  drive(FRONT, 1);
}

#endif
